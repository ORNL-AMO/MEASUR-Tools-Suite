/**
 * @file
 * @brief Calculate estimated power(kW) consumption and air flow(acfm) for a compressor based on control type.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include <algorithm>
#include "compressedAir/Compressors.h"

double CompressorsBase::roundDouble(double value) const { return round(value * 10000.0) / 10000.0; }

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromPerkW_BlowOff(double PerkW, double blowPer)
{
    double CPer = 0;

    if (roundDouble(PerkW) <= roundDouble(kWPer_blow))
        CPer = CPer_blow - blowPer;
    else
        CPer = ((1 - CPer_blow) / (1 - kWPer_blow)) * (PerkW - 1 + ((1 - kWPer_blow) / (1 - CPer_blow)));

    const double C_blowPer = CPer_blow - CPer;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromPerC_BlowOff(double CPer)
{
    double PerkW = 0;
    double C_blowPer = 0;

    if (CPer < CPer_blow)
    {
        PerkW = kWPer_blow;
        C_blowPer = CPer_blow - CPer;
    }
    else
        PerkW = ((1 - kWPer_blow) / (1 - CPer_blow)) * (CPer) + 1 - ((1 - kWPer_blow) / (1 - CPer_blow)) * 1;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromkWMeasured_BlowOff(double kW, double blowPer)
{
    return Compressors_Centrifugal_BlowOff::calculateFromPerkW_BlowOff(kW / kW_fl, blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromCMeasured_BlowOff(double C)
{
    return Compressors_Centrifugal_BlowOff::calculateFromPerC_BlowOff(C / C_fl);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromVIPFMeasured_BlowOff(double V, double I, double PF, double blowPer)
{
    return Compressors_Centrifugal_BlowOff::calculateFromkWMeasured_BlowOff(V * I * PF * 1.732 / 1000, blowPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromPerkW(double PerkW)
{
    const double CPer = ((PerkW - kWPer_nl) * ((CPer_fl - CPer_nl) / (1 - kWPer_nl)));

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromPerC(double CPer)
{
    const double PerkW = (((1 - kWPer_nl) / (CPer_fl - CPer_nl)) * (CPer) + kWPer_nl);

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromCMeasured(double C)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromPerkW(double PerkW)
{
    double CPer = 1;
    if (PerkW <= kWPer_nl)
        CPer = CPer_nl;
    else if (PerkW < kWPer_ul)
        CPer = (PerkW - kWPer_nl) * ((CPer_ul - CPer_nl) / (kWPer_ul - kWPer_nl));
    else if (PerkW >= kWPer_ul)
        CPer = ((1 - CPer_ulB) / (kWPer_max - kWPer_ul)) * PerkW + (1 - (1 - CPer_ulB) / (kWPer_max - kWPer_ul));

    return Output(PerkW * kW_fl, (CPer < CPer_ulB ? C_fl : C_max) * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromPerC(double CPer)
{
    double PerkW = 1;
    if (CPer < kWPer_ul)
        PerkW = ((kWPer_ul - kWPer_nl) / (CPer_ul - CPer_nl)) * (CPer) + kWPer_nl;
    else if (CPer < CPer_max)
        PerkW = ((kWPer_max - kWPer_ul) / (CPer_max - CPer_ul)) * (CPer) + kWPer_max - ((kWPer_max - kWPer_ul) / (CPer_max - CPer_ul)) * CPer_max;

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromCMeasured(double C)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromPerkW(double PerkW)
{
    double C_Calc = 1;
    if (PerkW < lf_nl)
        return Output(0, 0, 0, 0);
    else if (PerkW >= 1)
        C_Calc = C_fl;
    else
    {
        if (woUnload)
        {
            C_Calc = pow(((PerkW * kW_fl - kW_nl) / (kW_fl - kW_nl)), 1 / mod_exp) * C_fl;
        }
        else
        {
            if (kW_nl == kW_fl)
            {
                C_Calc = C_fl;
            }
            else
            {
                // for with unload: kw_nl = kW_avg in algorithm
                double kW_max_mod = (kW_max * noLoadPowerFM);
                double numerator = (kW_nl - kW_max_mod);
                double denominator = (kW_max - kW_max_mod);
                C_Calc = pow((numerator / denominator), (1 / mod_exp)) * C_fl;
            }
        }
    }

    return Output(PerkW * kW_fl, C_Calc, (PerkW), (C_Calc / C_fl));
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromPerC(double CPer)
{

    if (CPer > 1){
        return Output(kW_fl, C_fl * CPer, 1, CPer);
    }

    double kW_Calc;
    if (woUnload)
    {
        kW_Calc = (kW_fl - kW_nl) * pow(CPer, mod_exp) + kW_nl;
    }
    else
    {
        // for with unload: kw_nl = kw_max in algorithm
        double kW_max_mod = (kW_nl * noLoadPowerFM);
        kW_Calc = (kW_nl - kW_max_mod) * pow(CPer, mod_exp) + kW_max_mod;
    }

    return Output(kW_Calc, C_fl * CPer, kW_Calc / kW_fl, CPer);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_ModulationWOUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromCMeasured(double C)
{
    return Compressors_ModulationWOUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_ModulationWOUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_StartStop::calculateFromPerkW(double PerkW)
{
    // StartStop no load power = 0;
    if (PerkW == 0)
    {
        return Output(0, 0, 0, 0);
    }

    double C_Calc = C_fl * PerkW / ((kWPer_fl + kW_max / kW_fl) / 2);
    return Output(PerkW * kW_fl, C_Calc, (PerkW), (C_Calc / C_fl));
}

CompressorsBase::Output Compressors_StartStop::calculateFromPerC(double CPer)
{
    if (CPer > 1){
        return Output(kW_fl, C_fl * CPer, 1, CPer);
    }

    const double kW_Calc = (((kWPer_fl + kW_max / kW_fl) / 2) * CPer * kW_fl);
    return Output(kW_Calc, C_fl * CPer, kW_Calc / kW_fl, CPer);
}

CompressorsBase::Output Compressors_StartStop::calculateFromkWMeasured(double kW)
{
    return Compressors_StartStop::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_StartStop::calculateFromCMeasured(double C)
{
    return Compressors_StartStop::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_StartStop::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_StartStop::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

double Compressors_LoadUnload::CurveFit(double value, bool capacityVPower) const
{

    const double kW_maxmod = lf_fl * kW_max;
    const double t_bdc = t_blowdown / log(1 / a_tol);
    const double t_spc = t_sdt / log(1 / a_tol);

    std::vector<double> PerCapacity;
    std::vector<double> PerPower;
    const double decrementC = C_fl / 76;
    double C_curve = C_fl;
    do
    {
        double t_rmod = 0;
        // calculateThermalResistance kW_avg_mod
        double kW_avg_mod = 0;
        if (C_ul != C_fl)
        {
            if (C_curve < C_ul)
            {
                t_rmod = ((P_mod * C_storage) / (P_atm * C_fl)) * log((C_fl - C_curve) / (C_ul - C_curve)) * 60;
                if (t_rmod == 0)
                {
                    t_rmod = 1;
                }

                const double p_avg_mod_1 = P_max + P_mod - C_curve * P_mod / C_fl;
                const double p_avg_mod_2 = (((C_curve * P_mod) / C_fl) - P_mod);
                const double p_avg_mod_3 = (P_mod * C_storage / P_atm / C_fl);
                const double p_avg_mod_4 = (1 - exp(-P_atm * C_fl / P_mod / C_storage * t_rmod / 60)) / t_rmod * 60;
                const double P_avg_mod = p_avg_mod_1 + p_avg_mod_2 * p_avg_mod_3 * p_avg_mod_4;
                kW_avg_mod = (kW_max - kW_maxmod) * pow((P_max + P_mod - P_avg_mod) / P_mod, mod_exp) + kW_maxmod;
            }
            else
            {
                kW_avg_mod = (kW_max - kW_maxmod) * pow(C_curve / C_fl, mod_exp) + kW_maxmod;
            }
        }

        // calculateThermalResistance kW_curve
        double kW_curve;
        if (C_curve < C_ul)
        {
            // kw_bd
            const double t_dd = C_storage * 60 * (P_ul - P_fl) / (C_curve * P_atm);
            const double t_bd = std::min(t_blowdown, t_dd);

            const double kW_avg_bd = kW_nl + (((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod) - kW_nl) * ((1 - exp(-t_bd / t_bdc)) * (t_bdc / t_bd));
            double kW_bd = t_bd * kW_avg_bd;

            // kw_ol
            const double t_ol = t_dd - t_bd;
            const double kW_avg_ol = kW_fl * lf_nl;
            double kW_ol = t_ol * kW_avg_ol;
            // kW_rl
            const double P_sump_bla = P_sump_ul + (P_ul - P_sump_ul) * exp(-t_bd / t_bdc);
            const double t_rl = t_reload * ((P_ul - P_sump_bla) / ((P_ul - (P_ul - P_sump_ul) * a_tol)));
            double kW_min_bd = 0;
            if (t_bd == t_blowdown)
            {
                kW_min_bd = kW_nl;
            }
            else
            {
                kW_min_bd = kW_nl + ((((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod) - kW_nl) * exp(-t_bd / t_bdc));
            }
            const double kW_avg_rl = (kW_min_bd + kW_fl) / 2;

            double kW_rl = t_rl * kW_avg_rl;

            // kW_rpu
            const double t_rpu = 60 * C_storage * ((P_max - P_fl + (t_rl / 60) * P_atm * (C_curve / C_storage)) / (P_atm * (C_fl - C_curve)));
            const double kW_avg_rpu = ((1 - (P_atm * C_curve * t_rl) / (C_storage * 60 * 200)) * kW_fl + kW_max) / 2;
            double kW_rpu = t_rpu * kW_avg_rpu;

            // kW_r_mod
            double kW_r_mod;
            if (C_ul != C_fl)
            {
                kW_r_mod = t_rmod * kW_avg_mod;
            }
            else
            {
                kW_r_mod = 0;
            }

            // kW_curve
            double t_cycle = t_bd + t_ol + t_rl + t_rpu + t_rmod;
            kW_curve = (kW_bd + kW_ol + kW_rl + kW_rpu + kW_r_mod) / t_cycle;
        }
        else
        {
            kW_curve = kW_avg_mod;
        }

        PerCapacity.push_back(C_curve / C_fl);

        // if C_curve == C_fl then Percent Capacity = 100 and Percent Power = 100
        if (C_curve != C_fl)
        {
            PerPower.push_back(kW_curve / kW_fl);
        }
        else
        {
            PerPower.push_back(1);
        }

        if (C_curve == 0.0001)
        {
            break;
        }
        C_curve -= decrementC;
        if (C_curve <= 0)
        {
            C_curve = 0.0001;
        }
    } while (C_curve >= 0);

    if (capacityVPower)
    {
        CurveFitVal curveFitValCap(PerCapacity, PerPower, 6);
        return curveFitValCap.calculate(value);
    }
    CurveFitVal curveFitValCap(PerPower, PerCapacity, 6);
    return curveFitValCap.calculate(value);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromPerkW(double PerkW)
{
    if (PerkW == 1)
        return Output(kW_fl, C_fl, 1, 1);

    if (PerkW < lf_nl)
    {
        return Output(0, 0, 0, 0);
    }

    if (CntrlType == ControlType::ModulationUnload || CntrlType == ControlType::VariableDisplacementUnload)
    {
        const double kW_avg = PerkW * kW_fl;
        if (kW_avg >= kW_ul)
        {
            // pass kW_avg as kW_nl in ModulationWOUnload
            return Compressors_ModulationWOUnload(kW_fl, C_fl, kW_avg, CntrlType == ControlType::VariableDisplacementUnload ? 2 : 1, false, CompType, noLoadPowerFM, kW_max).calculateFromPerkW(PerkW);
        }
    }
    const double CPer = CurveFit(PerkW, false);
    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromPerC(double CPer)
{
    if (CPer == 1 || CPer > 1){
        return Output(kW_fl, C_fl * CPer, 1, CPer);
    }

    // if modulation or variable displacement
    if (CntrlType == ControlType::ModulationUnload || CntrlType == ControlType::VariableDisplacementUnload)
    {
        // check if in modulation mode
        double C_ul = C_fl * PerC_ul / 100;
        if (C_fl * CPer >= C_ul)
        {
            // For compressors with modulation... kW_nl = kW_max as a compressor without modulation
            return Compressors_ModulationWOUnload(kW_fl, C_fl, kW_max, CntrlType == ControlType::VariableDisplacementUnload ? 2 : 1, false, CompType, noLoadPowerFM).calculateFromPerC(CPer);
        }
    }

    double C_curve = C_fl * CPer;
    if (C_curve == 0)
    {
        // C_curve of 0 breaks algorithm
        C_curve = .00000000001;
    }

    const double kW_maxmod = lf_fl * kW_max;
    const double t_bdc = t_blowdown / log(1 / a_tol);

    const double t_spc = t_sdt / log(1 / a_tol);

    double t_rmod = 0;
    // calculateThermalResistance kW_avg_mod
    double kW_avg_mod = 0;
    if (C_ul != C_fl)
    {
        if (C_curve < C_ul)
        {
            t_rmod = ((P_mod * C_storage) / (P_atm * C_fl)) * log((C_fl - C_curve) / (C_ul - C_curve)) * 60;
            if (t_rmod == 0)
            {
                t_rmod = 1;
            }

            const double p_avg_mod_1 = P_max + P_mod - C_curve * P_mod / C_fl;
            const double p_avg_mod_2 = (((C_curve * P_mod) / C_fl) - P_mod);
            const double p_avg_mod_3 = (P_mod * C_storage / P_atm / C_fl);
            const double p_avg_mod_4 = (1 - exp(-P_atm * C_fl / P_mod / C_storage * t_rmod / 60)) / t_rmod * 60;
            const double P_avg_mod = p_avg_mod_1 + p_avg_mod_2 * p_avg_mod_3 * p_avg_mod_4;
            kW_avg_mod = (kW_max - kW_maxmod) * pow((P_max + P_mod - P_avg_mod) / P_mod, mod_exp) + kW_maxmod;
        }
        else
        {
            kW_avg_mod = (kW_max - kW_maxmod) * pow(C_curve / C_fl, mod_exp) + kW_maxmod;
        }
    }

    // calculateThermalResistance kW_curve
    double kW_curve;
    if (C_curve < C_ul)
    {
        // kw_bd
        const double t_dd = C_storage * 60 * (P_ul - P_fl) / (C_curve * P_atm);
        const double t_bd = std::min(t_blowdown, t_dd);

        const double kW_avg_bd = kW_nl + (((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod) - kW_nl) * ((1 - exp(-t_bd / t_bdc)) * t_bdc / t_bd);

        double kW_bd = t_bd * kW_avg_bd;

        // kw_ol
        const double t_ol = t_dd - t_bd;
        const double kW_avg_ol = kW_fl * lf_nl;
        double kW_ol = t_ol * kW_avg_ol;
        // kW_rl
        const double P_sump_bla = P_sump_ul + (P_ul - P_sump_ul) * exp(-t_bd / t_bdc);
        const double t_rl = t_reload * ((P_ul - P_sump_bla) / ((P_ul - (P_ul - P_sump_ul) * a_tol)));
        double kW_min_bd = 0;
        if (t_bd == t_blowdown)
        {
            kW_min_bd = kW_nl;
        }
        else
        {
            kW_min_bd = kW_nl + ((((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod) - kW_nl) * exp(-t_bd / t_bdc));
        }

        const double kW_avg_rl = (kW_min_bd + kW_fl) / 2;
        double kW_rl = t_rl * kW_avg_rl;

        // kW_rpu
        const double t_rpu = 60 * C_storage * ((P_max - P_fl + (t_rl / 60) * P_atm * (C_curve / C_storage)) / (P_atm * (C_fl - C_curve)));
        const double kW_avg_rpu = ((1 - (P_atm * C_curve * t_rl) / (C_storage * 60 * 200)) * kW_fl + kW_max) / 2;
        double kW_rpu = t_rpu * kW_avg_rpu;

        // kW_r_mod
        double kW_r_mod;
        if (C_ul != C_fl)
        {
            kW_r_mod = t_rmod * kW_avg_mod;
        }
        else
        {
            kW_r_mod = 0;
        }

        // kW_curve
        double t_cycle = t_bd + t_ol + t_rl + t_rpu + t_rmod;
        kW_curve = (kW_bd + kW_ol + kW_rl + kW_rpu + kW_r_mod) / t_cycle;
    }
    else
    {
        kW_curve = kW_avg_mod;
    }

    double PerkW = kW_curve / kW_fl;
    // double PerkW = CurveFit(CPer, true);
    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_LoadUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromCMeasured(double C)
{
    return Compressors_LoadUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_LoadUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

// VFD
CompressorsBase::Output Compressor_VFD::calculateFromPerC(double CPer)
{
    double PerkW;
    if (CPer > 1)
    {
        PerkW = 1;
    }
    else if (CPer < turndownPercentCapacity)
    {
        // if CPer < % turndown capacity
        // line from no load to turndown
        // slope = (turndown % power - no load % power) / (turndown % capacity - no load % capacity)
        double slope = (turndownPercentPower - noLoadPercentPower) / (turndownPercentCapacity - 0);
        // b = no load % power - (slope) * (no load % capacity)
        double b = noLoadPercentPower - (slope * 0);
        // PerkW = (slope)CPer + b
        PerkW = (slope * CPer) + b;
    }
    else
    {
        // if CPer > % turndown
        // curve fit turndown, midturndown and full load
        std::vector<double> PerCapacity;
        PerCapacity.push_back(turndownPercentCapacity);
        PerCapacity.push_back(midTurndownPercentCapacity);
        PerCapacity.push_back(1);
        std::vector<double> PerPower;
        PerPower.push_back(turndownPercentPower);
        PerPower.push_back(midTurndownPercentPower);
        PerPower.push_back(1);
        CurveFitVal curveFitValCap(PerCapacity, PerPower, 2);
        PerkW = curveFitValCap.calculate(CPer);
    }

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressor_VFD::calculateFromPerkW(double PerkW)
{

    if (PerkW == 1)
        return Output(kW_fl, C_fl, 1, 1);

    double power = PerkW * kW_fl;

    if (power < noLoadPower)
    {
        return Output(0, 0, 0, 0);
    }

    double CPer;
    if (PerkW < turndownPercentPower)
    {
        // if PerkW < % turndown power
        // line from no load to turndown
        // slope = (turndown % capacity - no load % capacity) / (turndown % power - no load % power)
        double slope = (turndownPercentCapacity - 0) / (turndownPercentPower - noLoadPercentPower);
        // b = no load % capacity - (slope) * (no load % power)
        double b = 0 - (slope * noLoadPercentPower);
        // CPer  = (slope)PerkW + b
        CPer = (slope * PerkW) + b;
    }
    else
    {
        // if PerKw > % turndown
        // curve fit turndown, midturndown and full load
        std::vector<double> PerPower;
        PerPower.push_back(turndownPercentPower);
        PerPower.push_back(midTurndownPercentPower);
        PerPower.push_back(1);
        std::vector<double> PerCapacity;
        PerCapacity.push_back(turndownPercentCapacity);
        PerCapacity.push_back(midTurndownPercentCapacity);
        PerCapacity.push_back(1);

        // get coefficients for x:per capacity, y: per KW
        CurveFitVal curveFitValCap(PerCapacity, PerPower, 2);

        // use quadratic formula for find CPer
        double a = curveFitValCap.coeff.at(2);
        double b = curveFitValCap.coeff.at(1);
        double c = curveFitValCap.coeff.at(0);

        CPer = (-b + sqrt(pow(b, 2) - (4 * a * (c - PerkW)))) / (2 * a);
    }

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressor_VFD::calculateFromkWMeasured(double kW)
{
    return Compressor_VFD::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressor_VFD::calculateFromCMeasured(double C)
{
    return Compressor_VFD::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressor_VFD::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressor_VFD::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}