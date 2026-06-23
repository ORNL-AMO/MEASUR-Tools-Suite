#include "compressedAir/assessment/compressor_system_profile.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "compressedAir/assessment/centrifugal_compressor.h"
#include "compressedAir/assessment/load_unload_compressor.h"
#include "compressedAir/assessment/modulation_without_unload_compressor.h"
#include "compressedAir/assessment/start_stop_compressor.h"
#include "compressedAir/assessment/vfd_compressor.h"

namespace compressed_air::assessment {

namespace {

double receiverVolume(const CompressorProfileOptions& options) {
    return options.totalAirStorageFt3 + options.additionalReceiverVolumeFt3;
}

double totalFullLoadAirflow(const CompressorProfileCompressorV& compressors) {
    double total = 0.0;
    for (const auto& compressor : compressors) {
        total += compressor.performancePoints.fullLoad.airflowAcfm;
    }
    return total;
}

double totalFullLoadPower(const CompressorProfileCompressorV& compressors) {
    double total = 0.0;
    for (const auto& compressor : compressors) {
        total += compressor.performancePoints.fullLoad.powerKw;
    }
    return total;
}

const CompressorProfileCompressor* findCompressor(const CompressorProfileCompressorV& compressors,
                                                  const std::string& compressor_id) {
    const auto it = std::find_if(compressors.begin(), compressors.end(),
                                 [&](const auto& compressor) { return compressor.compressorId == compressor_id; });
    return it == compressors.end() ? nullptr : &(*it);
}

const CompressorRuntimeState* findRuntimeState(const CompressorRuntimeStateV& runtime_states,
                                               const std::string& compressor_id,
                                               const std::string& day_type_id,
                                               double time_interval) {
    const auto it = std::find_if(runtime_states.begin(), runtime_states.end(), [&](const auto& state) {
        return state.compressorId == compressor_id && state.dayTypeId == day_type_id &&
               state.timeIntervalHr == time_interval;
    });
    return it == runtime_states.end() ? nullptr : &(*it);
}

std::vector<std::size_t> intervalRowIndices(const CompressorProfileRowV& rows, const std::string& day_type_id,
                                            double time_interval) {
    std::vector<std::size_t> indices;
    for (std::size_t i = 0; i < rows.size(); ++i) {
        if (rows[i].dayTypeId == day_type_id && rows[i].timeIntervalHr == time_interval) {
            indices.push_back(i);
        }
    }
    return indices;
}

CompressorProfileRow zeroRow(CompressorProfileRow row) {
    row.powerKw               = 0.0;
    row.airflowAcfm           = 0.0;
    row.powerFraction         = 0.0;
    row.airflowFraction       = 0.0;
    row.systemPowerFraction   = 0.0;
    row.systemAirflowFraction = 0.0;
    row.operatingOrder        = 0;
    return row;
}

CompressorProfileRow resultRow(CompressorProfileRow row, const CompressorPerformanceResult& result,
                               double system_capacity, double system_power, int order) {
    row.powerKw               = result.powerKw;
    row.airflowAcfm           = result.airflowAcfm;
    row.powerFraction         = result.powerFraction;
    row.airflowFraction       = result.airflowFraction;
    row.systemAirflowFraction = system_capacity == 0.0 ? 0.0 : result.airflowAcfm / system_capacity;
    row.systemPowerFraction   = system_power == 0.0 ? 0.0 : result.powerKw / system_power;
    row.operatingOrder        = order;
    return row;
}

CompressorProfileRow resultRow(CompressorProfileRow row, const CompressorBlowOffResult& result,
                               double system_capacity, double system_power, int order) {
    row.powerKw               = result.powerKw;
    row.airflowAcfm           = result.airflowAcfm;
    row.powerFraction         = result.powerFraction;
    row.airflowFraction       = result.airflowFraction;
    row.systemAirflowFraction = system_capacity == 0.0 ? 0.0 : result.airflowAcfm / system_capacity;
    row.systemPowerFraction   = system_power == 0.0 ? 0.0 : result.powerKw / system_power;
    row.operatingOrder        = order;
    return row;
}

template <typename TResult>
CompressorProfileRow resultRowForCompressor(const CompressorProfileCompressor& compressor, TResult result,
                                             const CompressorProfileOptions& options, int order) {
    CompressorProfileRow row;
    row.compressorId    = compressor.compressorId;
    row.dayTypeId       = options.dayTypeId;
    row.timeIntervalHr  = 0.0;
    row.powerFactor     = 0.0;
    row.amps            = 0.0;
    row.volts           = 0.0;
    return resultRow(row, result, compressor.performancePoints.fullLoad.airflowAcfm,
                     compressor.performancePoints.fullLoad.powerKw, order);
}

CompressorPerformanceResult calculatePositiveDisplacement(const CompressorProfileCompressor& compressor,
                                                          CompressorInputBasis input_basis, double input_value,
                                                          const CompressorProfileOptions& options,
                                                          double power_factor, double amps, double volts) {
    const auto& points = compressor.performancePoints;

    switch (compressor.control) {
    case CompressorControl::ModulationWithoutUnload: {
        ModulationWithoutUnloadCompressor model(points.fullLoad.powerKw, points.fullLoad.airflowAcfm,
                                                points.noLoad.powerKw, 1.0, true, compressor.compressorType);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }
    case CompressorControl::ModulationUnload:
    case CompressorControl::VariableDisplacementUnload: {
        ModulationWithUnloadCompressor model(
            points.fullLoad.powerKw, points.fullLoad.airflowAcfm, receiverVolume(options),
            points.maxFullFlow.powerKw, points.noLoad.powerKw, points.fullLoad.dischargePressurePsig,
            points.maxFullFlow.dischargePressurePsig, compressor.modulatingPressurePsig,
            options.atmosphericPressurePsia,
            points.fullLoad.airflowAcfm == 0.0
                ? 100.0
                : (points.unloadPoint.airflowAcfm / points.fullLoad.airflowAcfm) * 100.0,
            compressor.control, compressor.blowdownTimeSec, compressor.unloadSumpPressurePsig,
            compressor.noLoadPowerFractionForModulation, points.unloadPoint.powerKw,
            points.unloadPoint.dischargePressurePsig, points.unloadPoint.airflowAcfm);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }
    case CompressorControl::StartStop: {
        StartStopCompressor model(points.fullLoad.powerKw, points.fullLoad.airflowAcfm,
                                  points.fullLoad.powerKw == 0.0 ? 1.0
                                                                  : points.maxFullFlow.powerKw /
                                                                        points.fullLoad.powerKw,
                                  1.0);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }
    case CompressorControl::Vfd: {
        VariableFrequencyDriveCompressor model(points.fullLoad.powerKw, points.midTurndown.powerKw,
                                               points.turndown.powerKw, points.noLoad.powerKw,
                                               points.fullLoad.airflowAcfm, points.midTurndown.airflowAcfm,
                                               points.turndown.airflowAcfm);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }
    case CompressorControl::LoadUnload:
    case CompressorControl::MultiStepUnloading:
    default: {
        LoadUnloadCompressor model(
            points.fullLoad.powerKw, points.fullLoad.airflowAcfm, receiverVolume(options),
            points.maxFullFlow.powerKw, points.fullLoad.dischargePressurePsig,
            points.maxFullFlow.dischargePressurePsig, compressor.modulatingPressurePsig,
            points.fullLoad.powerKw == 0.0 ? 0.0 : points.noLoad.powerKw / points.fullLoad.powerKw,
            options.atmosphericPressurePsia, compressor.compressorType, compressor.lubricant,
            compressor.control, points.noLoad.powerKw,
            points.fullLoad.airflowAcfm == 0.0
                ? 100.0
                : (points.unloadPoint.airflowAcfm / points.fullLoad.airflowAcfm) * 100.0,
            compressor.blowdownTimeSec, compressor.unloadSumpPressurePsig,
            compressor.noLoadPowerFractionForModulation, points.unloadPoint.powerKw,
            points.unloadPoint.dischargePressurePsig, points.unloadPoint.airflowAcfm);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }
    }

    return {};
}

CompressorBlowOffResult calculateCentrifugalBlowOff(const CompressorProfileCompressor& compressor,
                                                    CompressorInputBasis input_basis, double input_value,
                                                    double power_factor, double amps, double volts) {
    const auto& points = compressor.performancePoints;
    CentrifugalBlowOffCompressor model(points.fullLoad.powerKw, points.fullLoad.airflowAcfm,
                                       points.blowoff.powerKw, points.blowoff.airflowAcfm);
    switch (input_basis) {
    case CompressorInputBasis::PowerFraction:
        return model.calculateFromPowerFraction(input_value, 1.0);
    case CompressorInputBasis::CapacityFraction:
        return model.calculateFromCapacityFraction(input_value);
    case CompressorInputBasis::MeasuredPower:
        return model.calculateFromMeasuredPower(input_value, 1.0);
    case CompressorInputBasis::MeasuredCapacity:
        return model.calculateFromMeasuredCapacity(input_value);
    case CompressorInputBasis::Electrical:
        return model.calculateFromElectrical(volts, amps, power_factor, 1.0);
    }
    return {};
}

CompressorPerformanceResult calculateCentrifugal(const CompressorProfileCompressor& compressor,
                                                 CompressorInputBasis input_basis, double input_value,
                                                 double power_factor, double amps, double volts) {
    const auto& points = compressor.performancePoints;
    if (compressor.control == CompressorControl::ModulationUnload ||
        compressor.control == CompressorControl::VariableDisplacementUnload) {
        CentrifugalModulationUnloadCompressor model(points.fullLoad.powerKw, points.fullLoad.airflowAcfm,
                                                    points.noLoad.powerKw, points.maxFullFlow.airflowAcfm,
                                                    points.unloadPoint.powerKw, points.unloadPoint.airflowAcfm);
        switch (input_basis) {
        case CompressorInputBasis::PowerFraction:
            return model.calculateFromPowerFraction(input_value);
        case CompressorInputBasis::CapacityFraction:
            return model.calculateFromCapacityFraction(input_value);
        case CompressorInputBasis::MeasuredPower:
            return model.calculateFromMeasuredPower(input_value);
        case CompressorInputBasis::MeasuredCapacity:
            return model.calculateFromMeasuredCapacity(input_value);
        case CompressorInputBasis::Electrical:
            return model.calculateFromElectrical(volts, amps, power_factor);
        }
    }

    CentrifugalLoadUnloadCompressor model(points.fullLoad.powerKw, points.fullLoad.airflowAcfm,
                                          points.noLoad.powerKw);
    switch (input_basis) {
    case CompressorInputBasis::PowerFraction:
        return model.calculateFromPowerFraction(input_value);
    case CompressorInputBasis::CapacityFraction:
        return model.calculateFromCapacityFraction(input_value);
    case CompressorInputBasis::MeasuredPower:
        return model.calculateFromMeasuredPower(input_value);
    case CompressorInputBasis::MeasuredCapacity:
        return model.calculateFromMeasuredCapacity(input_value);
    case CompressorInputBasis::Electrical:
        return model.calculateFromElectrical(volts, amps, power_factor);
    }
    return {};
}

std::vector<std::vector<std::string>> combinations(const std::vector<std::string>& values) {
    std::vector<std::vector<std::string>> result;
    const std::size_t limit = std::size_t{1} << values.size();
    for (std::size_t mask = 1; mask < limit; ++mask) {
        std::vector<std::string> combo;
        for (std::size_t i = 0; i < values.size(); ++i) {
            if ((mask & (std::size_t{1} << i)) != 0U) {
                combo.push_back(values[i]);
            }
        }
        result.push_back(combo);
    }
    std::sort(result.begin(), result.end(),
              [](const auto& lhs, const auto& rhs) { return lhs.size() < rhs.size(); });
    return result;
}

void applyRuntimeState(CompressorProfileRow& row, const CompressorRuntimeState* runtime_state, int& order_count) {
    if (runtime_state == nullptr) {
        return;
    }
    if (!runtime_state->isCompressorOn) {
        row.operatingOrder = 0;
    }
    else if (row.operatingOrder == 0) {
        row.operatingOrder = order_count;
        ++order_count;
    }
    else {
        ++order_count;
    }
}

} // namespace

CompressorProfileRow calculateCompressorProfileRow(const CompressorProfileCompressor& compressor,
                                                   CompressorInputBasis input_basis, double input_value,
                                                   const CompressorProfileOptions& options,
                                                   double power_factor, double amps, double volts) {
    CompressorProfileRow base;
    base.compressorId = compressor.compressorId;
    base.dayTypeId    = options.dayTypeId;
    base.powerFactor  = power_factor;
    base.amps         = amps;
    base.volts        = volts;

    const bool capacity_basis =
        input_basis == CompressorInputBasis::CapacityFraction ||
        input_basis == CompressorInputBasis::MeasuredCapacity;
    if (options.canShutdown && capacity_basis && input_value == 0.0 && compressor.automaticShutdown) {
        return zeroRow(base);
    }

    if (compressor.compressorType == CompressorType::Centrifugal &&
        compressor.control == CompressorControl::BlowOff) {
        return resultRowForCompressor(compressor,
                                      calculateCentrifugalBlowOff(compressor, input_basis, input_value,
                                                                  power_factor, amps, volts),
                                      options, 1);
    }

    const CompressorPerformanceResult result =
        compressor.compressorType == CompressorType::Centrifugal
            ? calculateCentrifugal(compressor, input_basis, input_value, power_factor, amps, volts)
            : calculatePositiveDisplacement(compressor, input_basis, input_value, options,
                                            power_factor, amps, volts);
    return resultRowForCompressor(compressor, result, options, 1);
}

CompressorProfileRowV calculateBaselineProfile(const CompressorProfileCompressorV& compressors,
                                               const CompressorProfileRowV& profile_rows,
                                               const CompressorProfileOptions& options) {
    CompressorProfileRowV result;
    result.reserve(profile_rows.size());

    const double system_capacity = totalFullLoadAirflow(compressors);
    const double system_power    = totalFullLoadPower(compressors);

    for (const auto& row : profile_rows) {
        CompressorProfileRow output = row;
        if (row.dayTypeId != options.dayTypeId || row.operatingOrder == 0) {
            result.push_back(zeroRow(output));
            continue;
        }

        const auto* compressor = findCompressor(compressors, row.compressorId);
        if (compressor == nullptr) {
            result.push_back(zeroRow(output));
            continue;
        }

        double input_value = 0.0;
        switch (options.inputBasis) {
        case CompressorInputBasis::PowerFraction:
            input_value = row.powerFraction;
            break;
        case CompressorInputBasis::CapacityFraction:
            input_value = row.airflowFraction;
            break;
        case CompressorInputBasis::MeasuredPower:
            input_value = row.powerKw;
            break;
        case CompressorInputBasis::MeasuredCapacity:
            input_value = row.airflowAcfm;
            break;
        case CompressorInputBasis::Electrical:
            input_value = row.powerFactor;
            break;
        }

        output = calculateCompressorProfileRow(*compressor, options.inputBasis, input_value, options,
                                               row.powerFactor, row.amps, row.volts);
        output.dayTypeId       = row.dayTypeId;
        output.timeIntervalHr  = row.timeIntervalHr;
        output.operatingOrder  = row.operatingOrder;
        output.powerFactor     = row.powerFactor;
        output.amps            = row.amps;
        output.volts           = row.volts;
        output.systemAirflowFraction = system_capacity == 0.0 ? 0.0 : output.airflowAcfm / system_capacity;
        output.systemPowerFraction   = system_power == 0.0 ? 0.0 : output.powerKw / system_power;
        if (options.canShutdown && output.airflowAcfm == 0.0 && compressor->automaticShutdown) {
            output = zeroRow(output);
        }
        result.push_back(output);
    }

    return result;
}

CompressorProfileTotalV calculateProfileTotals(const CompressorProfileCompressorV& compressors,
                                               const CompressorProfileRowV& profile_rows,
                                               double interval_hours) {
    (void)interval_hours;
    CompressorProfileTotalV totals;
    const double system_capacity = totalFullLoadAirflow(compressors);
    const double system_power    = totalFullLoadPower(compressors);

    for (const auto& row : profile_rows) {
        auto it = std::find_if(totals.begin(), totals.end(), [&](const auto& total) {
            return total.dayTypeId == row.dayTypeId && total.timeIntervalHr == row.timeIntervalHr;
        });
        if (it == totals.end()) {
            CompressorProfileTotal total;
            total.dayTypeId       = row.dayTypeId;
            total.timeIntervalHr  = row.timeIntervalHr;
            totals.push_back(total);
            it = totals.end() - 1;
        }

        if (row.operatingOrder != 0 && !std::isnan(row.airflowAcfm)) {
            it->airflowAcfm += row.airflowAcfm;
        }
        if (row.operatingOrder != 0 && !std::isnan(row.powerKw)) {
            it->powerKw += row.powerKw;
        }
        it->totalPowerKw    = it->powerKw + it->auxiliaryPowerKw;
        it->airflowFraction = system_capacity == 0.0 ? 0.0 : it->airflowAcfm / system_capacity;
        it->powerFraction   = system_power == 0.0 ? 0.0 : it->powerKw / system_power;
    }

    return totals;
}

CompressorProfileRowV reallocateProfileFlow(const CompressorProfileCompressorV& compressors,
                                             const CompressorProfileRowV& previous_profile_rows,
                                             const CompressorProfileTotalV& demand_rows,
                                             const CompressorProfileOptions& options,
                                             const CompressorRuntimeStateV& runtime_states,
                                             const CompressorTrimSelectionV& trim_selections) {
    CompressorProfileRowV output = previous_profile_rows;
    const double system_capacity = totalFullLoadAirflow(compressors);
    const double system_power    = totalFullLoadPower(compressors);

    for (const auto& demand : demand_rows) {
        if (demand.dayTypeId != options.dayTypeId) {
            continue;
        }

        auto indices = intervalRowIndices(output, options.dayTypeId, demand.timeIntervalHr);
        if (indices.empty()) {
            continue;
        }

        if (options.controlMode == CompressorSystemControlMode::BaseTrim) {
            const auto trim_it = std::find_if(trim_selections.begin(), trim_selections.end(),
                                              [&](const auto& trim) { return trim.dayTypeId == options.dayTypeId; });
            if (trim_it != trim_selections.end()) {
                const auto* trim_compressor = findCompressor(compressors, trim_it->compressorId);
                if (trim_compressor != nullptr) {
                    const double additional_airflow =
                        demand.airflowAcfm - trim_compressor->performancePoints.fullLoad.airflowAcfm;
                    if (additional_airflow <= 0.0) {
                        for (const auto index : indices) {
                            output[index].operatingOrder =
                                output[index].compressorId == trim_it->compressorId ? 1 : 0;
                        }
                    }
                    else {
                        std::vector<std::string> base_ids;
                        int runtime_order = 1;
                        for (const auto index : indices) {
                            const auto* runtime =
                                findRuntimeState(runtime_states, output[index].compressorId,
                                                 output[index].dayTypeId, output[index].timeIntervalHr);
                            applyRuntimeState(output[index], runtime, runtime_order);
                            if (output[index].compressorId != trim_it->compressorId &&
                                output[index].operatingOrder != 0) {
                                base_ids.push_back(output[index].compressorId);
                            }
                        }

                        const auto combos = combinations(base_ids);
                        std::size_t selected_size = 0;
                        bool        found_size    = false;
                        for (const auto& combo : combos) {
                            double combo_airflow = 0.0;
                            for (const auto& id : combo) {
                                const auto* compressor = findCompressor(compressors, id);
                                if (compressor != nullptr) {
                                    combo_airflow += compressor->performancePoints.fullLoad.airflowAcfm;
                                }
                            }
                            if (additional_airflow - combo_airflow <= 0.0) {
                                selected_size = combo.size();
                                found_size    = true;
                                break;
                            }
                        }

                        if (found_size) {
                            std::vector<std::string> selected_ids;
                            double selected_power = std::numeric_limits<double>::infinity();
                            for (const auto& combo : combos) {
                                if (combo.size() != selected_size) {
                                    continue;
                                }
                                double combo_airflow = 0.0;
                                double combo_power   = 0.0;
                                for (const auto& id : combo) {
                                    const auto* compressor = findCompressor(compressors, id);
                                    if (compressor != nullptr) {
                                        combo_airflow += compressor->performancePoints.fullLoad.airflowAcfm;
                                        combo_power += compressor->performancePoints.fullLoad.powerKw;
                                    }
                                }
                                if (additional_airflow - combo_airflow <= 0.0 && combo_power < selected_power) {
                                    selected_power = combo_power;
                                    selected_ids   = combo;
                                }
                            }

                            int base_order = 1;
                            for (const auto index : indices) {
                                if (output[index].compressorId == trim_it->compressorId) {
                                    output[index].operatingOrder = static_cast<int>(selected_size) + 1;
                                }
                                else if (std::find(selected_ids.begin(), selected_ids.end(),
                                                   output[index].compressorId) != selected_ids.end()) {
                                    output[index].operatingOrder = base_order++;
                                }
                                else {
                                    output[index].operatingOrder = 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (options.controlMode == CompressorSystemControlMode::LoadSharing) {
            std::vector<std::string> available_ids;
            int runtime_order = 1;
            for (const auto index : indices) {
                const auto* runtime =
                    findRuntimeState(runtime_states, output[index].compressorId, output[index].dayTypeId,
                                     output[index].timeIntervalHr);
                applyRuntimeState(output[index], runtime, runtime_order);
                if (output[index].operatingOrder != 0) {
                    available_ids.push_back(output[index].compressorId);
                }
            }

            std::vector<CompressorProfileRow> selected_rows;
            double min_power = std::numeric_limits<double>::infinity();
            for (const auto& combo : combinations(available_ids)) {
                double combo_capacity = 0.0;
                for (const auto& id : combo) {
                    const auto* compressor = findCompressor(compressors, id);
                    if (compressor != nullptr) {
                        combo_capacity += compressor->performancePoints.fullLoad.airflowAcfm;
                    }
                }
                if (combo_capacity == 0.0) {
                    continue;
                }
                const double load = demand.airflowAcfm / combo_capacity;
                if (load > 1.0) {
                    continue;
                }

                double combo_power = 0.0;
                std::vector<CompressorProfileRow> candidate_rows;
                for (const auto& id : combo) {
                    const auto* compressor = findCompressor(compressors, id);
                    if (compressor == nullptr) {
                        continue;
                    }
                    auto row = calculateCompressorProfileRow(
                        *compressor, CompressorInputBasis::MeasuredCapacity,
                        load * compressor->performancePoints.fullLoad.airflowAcfm, options);
                    row.compressorId      = compressor->compressorId;
                    row.dayTypeId         = options.dayTypeId;
                    row.timeIntervalHr    = demand.timeIntervalHr;
                    combo_power += row.powerKw;
                    candidate_rows.push_back(row);
                }
                if (combo_power < min_power) {
                    min_power     = combo_power;
                    selected_rows = candidate_rows;
                }
            }

            int order = 1;
            for (const auto index : indices) {
                const auto selected =
                    std::find_if(selected_rows.begin(), selected_rows.end(), [&](const auto& row) {
                        return row.compressorId == output[index].compressorId;
                    });
                if (selected == selected_rows.end()) {
                    output[index] = zeroRow(output[index]);
                }
                else {
                    output[index] = resultRow(output[index],
                                              CompressorPerformanceResult{selected->powerKw,
                                                                          selected->airflowAcfm,
                                                                          selected->powerFraction,
                                                                          selected->airflowFraction},
                                              system_capacity, system_power, order++);
                }
            }
            continue;
        }

        std::sort(indices.begin(), indices.end(), [&](std::size_t lhs, std::size_t rhs) {
            return output[lhs].operatingOrder < output[rhs].operatingOrder;
        });

        int order_count = 1;
        double needed_airflow = demand.airflowAcfm;
        for (const auto index : indices) {
            const auto* runtime =
                options.controlMode == CompressorSystemControlMode::BaseTrim
                    ? nullptr
                    : findRuntimeState(runtime_states, output[index].compressorId,
                                       output[index].dayTypeId, output[index].timeIntervalHr);
            applyRuntimeState(output[index], runtime, order_count);

            if (output[index].operatingOrder == 0) {
                output[index] = zeroRow(output[index]);
                continue;
            }

            const auto* compressor = findCompressor(compressors, output[index].compressorId);
            if (compressor == nullptr) {
                output[index] = zeroRow(output[index]);
                continue;
            }

            CompressorProfileCompressor effective = *compressor;
            if (runtime != nullptr) {
                effective.automaticShutdown = runtime->automaticShutdownTimer;
            }

            double full_load_airflow = effective.performancePoints.fullLoad.airflowAcfm;
            if (std::abs(needed_airflow) < 0.01) {
                full_load_airflow = 0.0;
            }

            auto row = calculateCompressorProfileRow(effective, CompressorInputBasis::MeasuredCapacity,
                                                     full_load_airflow, options);
            double temporary_needed_airflow = needed_airflow - row.airflowAcfm;
            if (temporary_needed_airflow < 0.0 && full_load_airflow + temporary_needed_airflow > 0.0) {
                row = calculateCompressorProfileRow(effective, CompressorInputBasis::MeasuredCapacity,
                                                    full_load_airflow + temporary_needed_airflow, options);
                temporary_needed_airflow = needed_airflow - row.airflowAcfm;
            }

            needed_airflow = temporary_needed_airflow;
            output[index] =
                resultRow(output[index], CompressorPerformanceResult{row.powerKw, row.airflowAcfm,
                                                                     row.powerFraction, row.airflowFraction},
                          system_capacity, system_power, output[index].operatingOrder);
        }
    }

    return output;
}

CompressorProfileSavingsResult calculateProfileSavings(const CompressorProfileRowV& baseline_rows,
                                                       const CompressorProfileRowV& adjusted_rows,
                                                       const CompressorProfileSavingsInput& input) {
    auto annual_energy = [&](const CompressorProfileRowV& rows) {
        double energy = 0.0;
        for (const auto& row : rows) {
            if (row.dayTypeId == input.dayTypeId && row.operatingOrder != 0 && !std::isnan(row.powerKw)) {
                energy += row.powerKw * input.intervalHours * input.operatingDays;
            }
        }
        return energy;
    };

    CompressorProfileSavingsResult result;
    result.baselineEnergyKwh = annual_energy(baseline_rows);
    result.baselineCost      = result.baselineEnergyKwh * input.electricityCostPerKwh;
    result.adjustedEnergyKwh = annual_energy(adjusted_rows) + input.auxiliaryEnergyKwh;
    result.adjustedCost      = result.adjustedEnergyKwh * input.electricityCostPerKwh;
    result.energySavingsKwh  = result.baselineEnergyKwh - result.adjustedEnergyKwh;
    result.costSavings       = result.baselineCost - result.adjustedCost;
    result.percentSavings    = result.baselineCost == 0.0 ? 0.0 : (result.costSavings / result.baselineCost) * 100.0;
    result.implementationCost = input.implementationCost;
    result.salvageValue       = input.salvageValue;
    result.paybackMonths =
        result.costSavings <= 0.0 ? 0.0 : ((input.implementationCost - input.salvageValue) / result.costSavings) * 12.0;
    if (result.paybackMonths < 0.0) {
        result.paybackMonths = 0.0;
    }
    return result;
}

double calculatePressureReducedAirflow(double use_airflow_acfm, double adjusted_full_load_pressure_psig,
                                       double altitude_pressure_psia,
                                       double original_full_load_pressure_psig) {
    if (adjusted_full_load_pressure_psig == original_full_load_pressure_psig) {
        return use_airflow_acfm;
    }

    const double pressure_ratio =
        (adjusted_full_load_pressure_psig + altitude_pressure_psia) /
        (original_full_load_pressure_psig + 14.7);
    return use_airflow_acfm - (use_airflow_acfm - use_airflow_acfm * pressure_ratio) * 0.6;
}

} // namespace compressed_air::assessment
