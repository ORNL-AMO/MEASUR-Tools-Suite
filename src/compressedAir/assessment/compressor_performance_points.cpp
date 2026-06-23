#include "compressedAir/assessment/compressor_performance_points.h"

#include <cmath>

namespace compressed_air::assessment {

namespace {

double roundTo(double value, int digits) {
    const double scale = std::pow(10.0, digits);
    return std::round(value * scale) / scale;
}

double roundPressure(double pressure) { return roundTo(pressure, 1); }

double roundAirflow(double airflow) { return roundTo(airflow, 0); }

double roundPower(double power) { return roundTo(power, 1); }

double pressurePowerFactor(double atmospheric_pressure) {
    return -0.0000577 * std::pow(atmospheric_pressure, 3) +
           0.000251 * std::pow(atmospheric_pressure, 2) + 0.0466 * atmospheric_pressure + 0.4442;
}

double pressureFlowFactor(double atmospheric_pressure) {
    return 0.000258 * std::pow(atmospheric_pressure, 3) -
           0.0116 * std::pow(atmospheric_pressure, 2) + 0.176 * atmospheric_pressure + 0.09992;
}

double quadraticInterpolate(double x, double x1, double y1, double x2, double y2, double x3, double y3) {
    const double d1 = (x1 - x2) * (x1 - x3);
    const double d2 = (x2 - x1) * (x2 - x3);
    const double d3 = (x3 - x1) * (x3 - x2);
    if (d1 == 0.0 || d2 == 0.0 || d3 == 0.0) {
        return y2;
    }

    return y1 * ((x - x2) * (x - x3) / d1) +
           y2 * ((x - x1) * (x - x3) / d2) +
           y3 * ((x - x1) * (x - x2) / d3);
}

bool isCentrifugal(const CompressorNameplateData& nameplate) {
    return nameplate.compressorType == CompressorType::Centrifugal;
}

bool isNoLoadPressureZero(const CompressorNameplateData& nameplate, const CompressorControlsData& controls) {
    return nameplate.compressorType == CompressorType::Centrifugal ||
           controls.control == CompressorControl::StartStop ||
           nameplate.compressorType == CompressorType::Reciprocating ||
           nameplate.lubricant == CompressorLubricant::Free;
}

double vfdPointPower(double airflow, double full_load_airflow, double full_load_power) {
    const double load_fraction = full_load_airflow == 0.0 ? 0.0 : airflow / full_load_airflow;
    constexpr double lffm      = 15.0;
    return ((lffm / 100.0) * (1.0 - load_fraction) + load_fraction) * full_load_power;
}

double vfdPointPressure(double airflow, double full_load_airflow, double full_load_pressure) {
    const double load_fraction = full_load_airflow == 0.0 ? 0.0 : airflow / full_load_airflow;
    constexpr double modulating_pressure_range = 6.0;
    return full_load_pressure + modulating_pressure_range * (1.0 - load_fraction);
}

} // namespace

double calculatePressureAdjustedAirflow(double capacity_acfm, double point_pressure_psig,
                                        double rated_pressure_psig, double atmospheric_pressure_psia) {
    return pressureFlowFactor(atmospheric_pressure_psia) * capacity_acfm *
           (1.0 - 0.00075 * (point_pressure_psig - rated_pressure_psig));
}

double calculatePressureAdjustedPower(CompressorType compressor_type, double inlet_pressure_psia,
                                      double point_pressure_psig, double rated_full_load_pressure_psig,
                                      double package_power_kw, double atmospheric_pressure_psia) {
    constexpr double polytropic_exponent = (1.4 - 1.0) / 1.4;
    double           pressure_factor     = atmospheric_pressure_psia / inlet_pressure_psia;
    double           operating_ratio     = (point_pressure_psig + atmospheric_pressure_psia) / atmospheric_pressure_psia;

    if (compressor_type == CompressorType::Screw) {
        pressure_factor = pressurePowerFactor(atmospheric_pressure_psia);
        operating_ratio = (point_pressure_psig + inlet_pressure_psia) / inlet_pressure_psia;
    }

    const double rated_ratio_term =
        std::pow((rated_full_load_pressure_psig + inlet_pressure_psia) / inlet_pressure_psia,
                 polytropic_exponent) -
        1.0;
    if (rated_ratio_term == 0.0) {
        return 0.0;
    }

    return pressure_factor * (std::pow(operating_ratio, polytropic_exponent) - 1.0) /
           rated_ratio_term * package_power_kw;
}

double calculateNoLoadPower(double no_load_power_ul_percent, double package_power_kw,
                            double design_efficiency_percent) {
    if (no_load_power_ul_percent < 25.0) {
        const double denominator =
            no_load_power_ul_percent /
            (no_load_power_ul_percent - 25.0 + 2521.834 / design_efficiency_percent) /
            design_efficiency_percent;
        if (denominator == 0.0) {
            return 0.0;
        }
        return no_load_power_ul_percent * package_power_kw / denominator / 10000.0;
    }
    return no_load_power_ul_percent * package_power_kw / 100.0;
}

double calculateNoLoadPowerWithoutUnloading(double no_load_power_fm_percent, double full_load_power_kw) {
    return no_load_power_fm_percent / 100.0 * full_load_power_kw;
}

double calculateUnloadPointPower(double no_load_power_fm_percent, double unload_point_capacity_percent,
                                 double exponent, double max_full_flow_power_kw) {
    const double capacity_fraction = unload_point_capacity_percent / 100.0;
    const double power =
        ((no_load_power_fm_percent / 100.0) * (1.0 - std::pow(capacity_fraction, exponent)) +
         std::pow(capacity_fraction, exponent)) *
        max_full_flow_power_kw;
    return roundPower(power);
}

double calculateUnloadPointAirflow(double full_load_airflow_acfm, double unload_point_capacity_percent) {
    return full_load_airflow_acfm * (unload_point_capacity_percent / 100.0);
}

double calculateUnloadPointDischargePressure(double max_full_flow_pressure_psig,
                                             double modulating_pressure_range_psig,
                                             double full_load_airflow_acfm,
                                             double unload_point_airflow_acfm) {
    if (full_load_airflow_acfm == 0.0) {
        return max_full_flow_pressure_psig;
    }
    return max_full_flow_pressure_psig +
           modulating_pressure_range_psig * (1.0 - unload_point_airflow_acfm / full_load_airflow_acfm);
}

double calculateCentrifugalUnloadPointAirflow(const CentrifugalSpecifics& centrifugal,
                                              double discharge_pressure_psig) {
    const double denominator =
        (centrifugal.maxFullLoadPressurePsig - centrifugal.minFullLoadPressurePsig) /
        (centrifugal.maxFullLoadCapacityAcfm - centrifugal.surgeAirflowAcfm);
    if (denominator == 0.0) {
        return centrifugal.surgeAirflowAcfm;
    }

    return (discharge_pressure_psig -
            (centrifugal.minFullLoadPressurePsig - denominator * centrifugal.surgeAirflowAcfm)) /
           denominator;
}

double calculateRatedSpecificPower(double total_package_input_power_kw, double full_load_rated_capacity_acfm) {
    if (full_load_rated_capacity_acfm == 0.0) {
        return 0.0;
    }
    return (total_package_input_power_kw / full_load_rated_capacity_acfm) * 100.0;
}

double calculateRatedIsentropicEfficiency(double rated_specific_power,
                                          double full_load_operating_pressure_psig) {
    if (rated_specific_power == 0.0) {
        return 0.0;
    }

    const double pressure_term = std::pow((full_load_operating_pressure_psig + 14.5) / 14.5, 0.2857);
    return roundTo(((16.52 * (pressure_term - 1.0)) / rated_specific_power) * 100.0, 4);
}

CompressorPerformancePoints generatePerformancePoints(CompressorPerformancePointInput input) {
    CompressorPerformancePoints points = input.points;

    if (points.fullLoad.isDefaultPressure) {
        points.fullLoad.dischargePressurePsig = input.nameplate.fullLoadOperatingPressurePsig;
    }
    if (points.fullLoad.isDefaultAirflow) {
        double airflow = 0.0;
        if (isCentrifugal(input.nameplate)) {
            airflow = quadraticInterpolate(points.fullLoad.dischargePressurePsig,
                                           input.centrifugal.maxFullLoadPressurePsig,
                                           input.centrifugal.maxFullLoadCapacityAcfm,
                                           input.nameplate.fullLoadOperatingPressurePsig,
                                           input.nameplate.fullLoadRatedCapacityAcfm,
                                           input.centrifugal.minFullLoadPressurePsig,
                                           input.centrifugal.minFullLoadCapacityAcfm);
        }
        else {
            airflow = calculatePressureAdjustedAirflow(input.nameplate.fullLoadRatedCapacityAcfm,
                                                       points.fullLoad.dischargePressurePsig,
                                                       input.nameplate.fullLoadOperatingPressurePsig,
                                                       input.atmosphericPressurePsia);
        }
        points.fullLoad.airflowAcfm = roundAirflow(airflow);
    }
    if (points.fullLoad.isDefaultPower) {
        double power = input.nameplate.totalPackageInputPowerKw;
        if (!isCentrifugal(input.nameplate)) {
            power = calculatePressureAdjustedPower(input.nameplate.compressorType, input.design.inputPressurePsia,
                                                   points.fullLoad.dischargePressurePsig,
                                                   input.nameplate.fullLoadOperatingPressurePsig,
                                                   input.nameplate.totalPackageInputPowerKw,
                                                   input.atmosphericPressurePsia);
        }
        points.fullLoad.powerKw = roundPower(power);
    }

    const bool needs_max_full_flow =
        input.controls.control == CompressorControl::ModulationUnload ||
        input.controls.control == CompressorControl::VariableDisplacementUnload ||
        input.controls.control == CompressorControl::LoadUnload ||
        input.controls.control == CompressorControl::StartStop ||
        input.controls.control == CompressorControl::MultiStepUnloading;

    if (needs_max_full_flow) {
        if (points.maxFullFlow.isDefaultPressure) {
            points.maxFullFlow.dischargePressurePsig = roundPressure(input.design.maxFullFlowPressurePsig);
        }
        if (points.maxFullFlow.isDefaultAirflow) {
            double airflow = 0.0;
            if (isCentrifugal(input.nameplate)) {
                airflow = quadraticInterpolate(points.maxFullFlow.dischargePressurePsig,
                                               input.centrifugal.maxFullLoadPressurePsig,
                                               input.centrifugal.maxFullLoadCapacityAcfm,
                                               input.nameplate.fullLoadOperatingPressurePsig,
                                               input.nameplate.fullLoadRatedCapacityAcfm,
                                               input.centrifugal.minFullLoadPressurePsig,
                                               input.centrifugal.minFullLoadCapacityAcfm);
            }
            else {
                airflow = calculatePressureAdjustedAirflow(points.fullLoad.airflowAcfm,
                                                           points.maxFullFlow.dischargePressurePsig,
                                                           points.fullLoad.dischargePressurePsig,
                                                           input.atmosphericPressurePsia);
            }
            points.maxFullFlow.airflowAcfm = roundAirflow(airflow);
        }
        if (points.maxFullFlow.isDefaultPower) {
            double power = points.fullLoad.powerKw;
            if (!isCentrifugal(input.nameplate)) {
                power = calculatePressureAdjustedPower(input.nameplate.compressorType, input.design.inputPressurePsia,
                                                       points.maxFullFlow.dischargePressurePsig,
                                                       points.fullLoad.dischargePressurePsig,
                                                       points.fullLoad.powerKw,
                                                       input.atmosphericPressurePsia);
            }
            points.maxFullFlow.powerKw = roundPower(power);
        }
    }

    if (input.controls.control == CompressorControl::ModulationUnload ||
        input.controls.control == CompressorControl::VariableDisplacementUnload) {
        if (isCentrifugal(input.nameplate)) {
            if (points.unloadPoint.isDefaultPressure) {
                points.unloadPoint.dischargePressurePsig = roundPressure(points.maxFullFlow.dischargePressurePsig);
            }
            if (points.unloadPoint.isDefaultAirflow) {
                points.unloadPoint.airflowAcfm =
                    roundAirflow(calculateCentrifugalUnloadPointAirflow(input.centrifugal,
                                                                        points.unloadPoint.dischargePressurePsig));
            }
        }
        else {
            if (points.unloadPoint.isDefaultAirflow) {
                points.unloadPoint.airflowAcfm =
                    roundAirflow(calculateUnloadPointAirflow(points.fullLoad.airflowAcfm,
                                                             input.controls.unloadPointCapacityPct));
            }
            if (points.unloadPoint.isDefaultPressure) {
                points.unloadPoint.dischargePressurePsig =
                    roundPressure(calculateUnloadPointDischargePressure(points.maxFullFlow.dischargePressurePsig,
                                                                        input.design.modulatingPressurePsig,
                                                                        points.fullLoad.airflowAcfm,
                                                                        points.unloadPoint.airflowAcfm));
            }
        }
        if (points.unloadPoint.isDefaultPower) {
            double unload_capacity = input.controls.unloadPointCapacityPct;
            double exponent        = input.controls.control == CompressorControl::VariableDisplacementUnload ? 2.0 : 1.0;
            if (isCentrifugal(input.nameplate)) {
                unload_capacity = points.maxFullFlow.airflowAcfm == 0.0
                                      ? 0.0
                                      : (points.unloadPoint.airflowAcfm / points.maxFullFlow.airflowAcfm) * 100.0;
                exponent = 1.0;
            }
            else if (input.controls.control == CompressorControl::ModulationUnload) {
                unload_capacity = points.fullLoad.airflowAcfm == 0.0
                                      ? 0.0
                                      : (points.unloadPoint.airflowAcfm / points.fullLoad.airflowAcfm) * 100.0;
            }
            points.unloadPoint.powerKw =
                calculateUnloadPointPower(input.design.noLoadPowerFMPercent, unload_capacity, exponent,
                                          points.maxFullFlow.powerKw);
        }
    }

    if (input.controls.control == CompressorControl::BlowOff && isCentrifugal(input.nameplate)) {
        if (points.blowoff.isDefaultPressure) {
            points.blowoff.dischargePressurePsig = roundPressure(points.fullLoad.dischargePressurePsig);
        }
        if (points.blowoff.isDefaultAirflow) {
            points.blowoff.airflowAcfm =
                roundAirflow(calculateCentrifugalUnloadPointAirflow(input.centrifugal,
                                                                    points.blowoff.dischargePressurePsig));
        }
        if (points.blowoff.isDefaultPower) {
            const double unload_capacity = points.fullLoad.airflowAcfm == 0.0
                                               ? 0.0
                                               : (points.blowoff.airflowAcfm / points.fullLoad.airflowAcfm) * 100.0;
            points.blowoff.powerKw = calculateUnloadPointPower(input.design.noLoadPowerFMPercent, unload_capacity,
                                                               1.0, points.fullLoad.powerKw);
        }
    }

    if (input.controls.control == CompressorControl::Vfd) {
        if (points.midTurndown.isDefaultAirflow) {
            const double capacity_fraction = input.controls.unloadPointCapacityPct / 100.0;
            points.midTurndown.airflowAcfm =
                roundAirflow(((1.0 - capacity_fraction) / 2.0 + capacity_fraction) *
                             points.fullLoad.airflowAcfm);
        }
        if (points.midTurndown.isDefaultPressure) {
            points.midTurndown.dischargePressurePsig =
                roundPressure(vfdPointPressure(points.midTurndown.airflowAcfm, points.fullLoad.airflowAcfm,
                                               points.fullLoad.dischargePressurePsig));
        }
        if (points.midTurndown.isDefaultPower) {
            points.midTurndown.powerKw =
                roundPower(vfdPointPower(points.midTurndown.airflowAcfm, points.fullLoad.airflowAcfm,
                                         points.fullLoad.powerKw));
        }

        if (points.turndown.isDefaultAirflow) {
            points.turndown.airflowAcfm =
                roundAirflow((input.controls.unloadPointCapacityPct / 100.0) * points.fullLoad.airflowAcfm);
        }
        if (points.turndown.isDefaultPressure) {
            points.turndown.dischargePressurePsig =
                roundPressure(vfdPointPressure(points.turndown.airflowAcfm, points.fullLoad.airflowAcfm,
                                               points.fullLoad.dischargePressurePsig));
        }
        if (points.turndown.isDefaultPower) {
            points.turndown.powerKw =
                roundPower(vfdPointPower(points.turndown.airflowAcfm, points.fullLoad.airflowAcfm,
                                         points.fullLoad.powerKw));
        }
    }

    if (points.noLoad.isDefaultPressure) {
        double pressure = 0.0;
        if (isNoLoadPressureZero(input.nameplate, input.controls)) {
            pressure = 0.0;
        }
        else if (input.controls.control == CompressorControl::ModulationWithoutUnload) {
            pressure = points.fullLoad.dischargePressurePsig + input.design.modulatingPressurePsig;
        }
        else {
            pressure = input.controls.unloadSumpPressurePsig;
        }
        points.noLoad.dischargePressurePsig = roundPressure(pressure);
    }
    if (points.noLoad.isDefaultAirflow) {
        points.noLoad.airflowAcfm = 0.0;
    }
    if (points.noLoad.isDefaultPower) {
        double power = 0.0;
        if (input.controls.control == CompressorControl::ModulationWithoutUnload) {
            power = calculateNoLoadPowerWithoutUnloading(input.design.noLoadPowerFMPercent, points.fullLoad.powerKw);
        }
        else if (input.controls.control == CompressorControl::StartStop) {
            power = 0.0;
        }
        else {
            power = calculateNoLoadPower(input.design.noLoadPowerULPercent,
                                         input.nameplate.totalPackageInputPowerKw,
                                         input.design.designEfficiencyPct);
        }
        points.noLoad.powerKw = roundPower(power);
    }

    return points;
}

CompressorPerformancePoints adjustPerformancePointsForSequencer(SequencerSetPointInput input) {
    input.compressor.points.fullLoad.dischargePressurePsig = input.targetPressurePsig - input.variancePsig;
    input.compressor.points.fullLoad.isDefaultPressure     = false;
    input.compressor.points.fullLoad.isDefaultAirflow      = true;
    input.compressor.points.fullLoad.isDefaultPower        = true;

    input.compressor.points.maxFullFlow.isDefaultAirflow = true;
    input.compressor.points.maxFullFlow.isDefaultPower   = true;
    input.compressor.points.noLoad.isDefaultAirflow      = true;
    input.compressor.points.noLoad.isDefaultPressure     = true;
    input.compressor.points.noLoad.isDefaultPower        = true;
    input.compressor.points.unloadPoint.isDefaultAirflow = true;
    input.compressor.points.unloadPoint.isDefaultPower   = true;
    input.compressor.points.blowoff.isDefaultAirflow     = true;
    input.compressor.points.blowoff.isDefaultPressure    = true;
    input.compressor.points.blowoff.isDefaultPower       = true;

    const CompressorControl control = input.compressor.controls.control;
    if (control == CompressorControl::ModulationUnload ||
        control == CompressorControl::VariableDisplacementUnload ||
        control == CompressorControl::MultiStepUnloading ||
        control == CompressorControl::LoadUnload) {
        input.compressor.points.unloadPoint.dischargePressurePsig = input.targetPressurePsig + input.variancePsig;
        input.compressor.points.unloadPoint.isDefaultPressure     = false;
        if (input.compressor.points.maxFullFlow.dischargePressurePsig >
            input.compressor.points.fullLoad.dischargePressurePsig) {
            input.compressor.points.maxFullFlow.dischargePressurePsig =
                input.compressor.points.fullLoad.dischargePressurePsig;
            input.compressor.points.maxFullFlow.isDefaultPressure = false;
        }
    }
    else if (control == CompressorControl::ModulationWithoutUnload) {
        input.compressor.points.noLoad.dischargePressurePsig = input.targetPressurePsig + input.variancePsig;
        input.compressor.points.noLoad.isDefaultPressure     = false;
    }
    else if (control == CompressorControl::StartStop) {
        input.compressor.points.maxFullFlow.dischargePressurePsig = input.targetPressurePsig + input.variancePsig;
        input.compressor.points.maxFullFlow.isDefaultPressure     = false;
    }
    else if (control == CompressorControl::BlowOff) {
        input.compressor.points.blowoff.dischargePressurePsig = input.targetPressurePsig + input.variancePsig;
        input.compressor.points.blowoff.isDefaultPressure     = false;
    }

    return generatePerformancePoints(input.compressor);
}

CompressorPerformancePoints reduceSystemPressurePerformancePoints(PressureReductionPointInput input) {
    input.compressor.points.fullLoad.dischargePressurePsig -= input.pressureReductionPsig;
    input.compressor.points.fullLoad.isDefaultPressure = false;
    input.compressor.points.fullLoad.isDefaultAirflow  = true;
    input.compressor.points.fullLoad.isDefaultPower    = true;

    input.compressor.points.maxFullFlow.isDefaultAirflow = true;
    input.compressor.points.maxFullFlow.isDefaultPower   = true;
    if (input.compressor.controls.control != CompressorControl::ModulationWithoutUnload &&
        input.compressor.controls.control != CompressorControl::BlowOff) {
        input.compressor.points.maxFullFlow.dischargePressurePsig -= input.pressureReductionPsig;
        input.compressor.points.maxFullFlow.isDefaultPressure = false;
    }

    input.compressor.points.noLoad.isDefaultAirflow      = true;
    input.compressor.points.noLoad.isDefaultPressure     = true;
    input.compressor.points.noLoad.isDefaultPower        = true;
    input.compressor.points.unloadPoint.isDefaultAirflow = true;
    input.compressor.points.unloadPoint.isDefaultPressure = true;
    input.compressor.points.unloadPoint.isDefaultPower   = true;
    input.compressor.points.blowoff.isDefaultAirflow     = true;
    input.compressor.points.blowoff.isDefaultPressure    = true;
    input.compressor.points.blowoff.isDefaultPower       = true;

    return generatePerformancePoints(input.compressor);
}

CompressorPerformancePoints adjustCascadingSetPointPerformancePoints(CascadingSetPointInput input) {
    input.compressor.points.fullLoad.dischargePressurePsig = input.fullLoadPressurePsig;
    input.compressor.points.fullLoad.isDefaultPressure     = false;
    input.compressor.points.fullLoad.isDefaultAirflow      = false;
    input.compressor.points.fullLoad.isDefaultPower        = true;

    input.compressor.points.maxFullFlow.dischargePressurePsig = input.maxFullFlowPressurePsig;
    input.compressor.points.maxFullFlow.isDefaultPressure     = false;
    input.compressor.points.maxFullFlow.isDefaultAirflow      = true;
    input.compressor.points.maxFullFlow.isDefaultPower        = true;

    input.compressor.points.noLoad.isDefaultAirflow       = true;
    input.compressor.points.noLoad.isDefaultPressure      = true;
    input.compressor.points.noLoad.isDefaultPower         = true;
    input.compressor.points.unloadPoint.isDefaultAirflow  = true;
    input.compressor.points.unloadPoint.isDefaultPressure = true;
    input.compressor.points.unloadPoint.isDefaultPower    = true;
    input.compressor.points.blowoff.isDefaultAirflow      = true;
    input.compressor.points.blowoff.isDefaultPressure     = true;
    input.compressor.points.blowoff.isDefaultPower        = true;

    return generatePerformancePoints(input.compressor);
}

} // namespace compressed_air::assessment
