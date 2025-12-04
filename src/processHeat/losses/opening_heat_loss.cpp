#include "processHeat/losses/opening_heat_loss.h"

#include <cmath>
#include <numbers>

#include "physics/constants.h"

namespace opening_heat_loss {

double totalHeatLoss(double area, double emissivity, double insideTemperature, double ambientTemperature,
                     double viewFactor, double percentTimeOpen) {
    using namespace physics::us;
    const double hlRad = emissivity * kStefanBoltzmann *
                         (std::pow(insideTemperature + 460, 4) - std::pow(ambientTemperature + 460, 4)) * area;
    double heatLoss = hlRad * viewFactor * percentTimeOpen / 100;
    return heatLoss;
}

double totalHeatLossQuad(double emissivity, double length, double width, double ambientTemperature,
                         double insideTemperature, double percentTimeOpen, double viewFactor) {
    double area = (length * width) / 144;
    return totalHeatLoss(area, emissivity, insideTemperature, ambientTemperature, viewFactor, percentTimeOpen);
}

double totalHeatLossCircular(double emissivity, double diameter, double ambientTemperature, double insideTemperature,
                             double percentTimeOpen, double viewFactor) {
    const double d    = diameter / 12;
    double       area = std::numbers::pi * (d / 2) * (d / 2);
    return totalHeatLoss(area, emissivity, insideTemperature, ambientTemperature, viewFactor, percentTimeOpen);
}

/**
 * These equations are polynomial approximations for the radiative view factor of a circular opening in a furnace or
 * enclosure wall, as a function of the thickness-to-diameter ratio.
 */
static double viewFactorCase1(double thicknessRatio) {
    return (1.10000000001829 + 92.8571428570049 * thicknessRatio - 57.5892857139671 * std::pow(thicknessRatio, 2) +
            15.6249999998005 * std::pow(thicknessRatio, 3)) /
           100.0;
}
static double viewFactorCase2(double thicknessRatio) {
    return (29.4999999989821 + 26.8416666684161 * thicknessRatio - 4.35416666785322 * std::pow(thicknessRatio, 2) -
            8.33333330461522E-02 * std::pow(thicknessRatio, 3) + 0.104166666655532 * std::pow(thicknessRatio, 4) -
            8.33333333686747E-03 * std::pow(thicknessRatio, 5)) /
           100.0;
}
static double viewFactorCase3(double thicknessRatio) {
    return (3.50000000001719 + 89.5833333332039 * thicknessRatio - 49.9999999997023 * std::pow(thicknessRatio, 2) +
            10.4166666664804 * std::pow(thicknessRatio, 3)) /
           100.0;
}
static double viewFactorCase4(double thicknessRatio) {
    return (23.9999999965639 + 39.3916666718743 * thicknessRatio - 11.6041666697487 * std::pow(thicknessRatio, 2) +
            1.85416666706894 * std::pow(thicknessRatio, 3) - 0.145833333217932 * std::pow(thicknessRatio, 4) +
            4.16666663902102E-03 * std::pow(thicknessRatio, 5)) /
           100.0;
}
static double viewFactorCase5(double thicknessRatio) {
    return (2.70000000002409 + 112.678571428391 * thicknessRatio - 70.9821428567315 * std::pow(thicknessRatio, 2) +
            15.6249999997447 * std::pow(thicknessRatio, 3)) /
           100.0;
}
static double viewFactorCase6(double thicknessRatio) {
    return (35.4999999992976 + 29.4583333347815 * thicknessRatio - 4.52083333446976 * std::pow(thicknessRatio, 2) -
            0.687499999606652 * std::pow(thicknessRatio, 3) + 0.270833333273064 * std::pow(thicknessRatio, 4) -
            2.08333333303721E-02 * std::pow(thicknessRatio, 5)) /
           100.0;
}
static double viewFactorCase7(double thicknessRatio) {
    return (13.0000000000278 + 123.74999999979 * thicknessRatio - 99.9999999995182 * std::pow(thicknessRatio, 2) +
            31.249999999699 * std::pow(thicknessRatio, 3)) /
           100.0;
}
static double viewFactorCase8(double thicknessRatio) {
    return (26.9999999903567 + 64.5666666806646 * thicknessRatio - 29.9166666745008 * std::pow(thicknessRatio, 2) +
            7.14583333396145 * std::pow(thicknessRatio, 3) - 0.833333332874441 * std::pow(thicknessRatio, 4) +
            3.74999999085373E-02 * std::pow(thicknessRatio, 5)) /
           100.0;
}

double calculateViewFactorCircular(const double thickness, const double diameter) {
    if (!diameter)
        return 0;
    const double thicknessRatio = (!thickness) ? 6 : diameter / thickness;
    if (thicknessRatio >= 6)
        return viewFactorCase2(6);
    if (thicknessRatio < 0.1)
        return viewFactorCase1(0.1) * thicknessRatio / 0.1;
    if (thicknessRatio < 1)
        return viewFactorCase1(thicknessRatio);
    return viewFactorCase2(thicknessRatio);
}

double calculateViewFactorQuad(const double thickness, const double length, const double height) {
    double thicknessRatio, lateralDimensionRatio;
    if (!length || !height)
        return 0;
    if (height > length) {
        lateralDimensionRatio = height / length;
        thicknessRatio        = (!thickness) ? 6 : length / thickness;
    }
    else {
        lateralDimensionRatio = length / height;
        thicknessRatio        = (!thickness) ? 6 : height / thickness;
    }

    if (thicknessRatio >= 6) {
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorCase4(6) + (viewFactorCase6(6) - viewFactorCase4(6)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorCase6(6) + (viewFactorCase8(6) - viewFactorCase6(6)) * (lateralDimensionRatio - 2) / 8;
        }
        return viewFactorCase8(6);
    }
    else if (thicknessRatio < 1) {
        auto const tr = (thicknessRatio < 0.1) ? 0.1 : thicknessRatio;
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorCase3(tr) + (viewFactorCase5(tr) - viewFactorCase3(tr)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorCase5(tr) + (viewFactorCase7(tr) - viewFactorCase5(tr)) * (lateralDimensionRatio - 2) / 8;
        }
        return viewFactorCase7(tr) * thicknessRatio / tr;
    }
    else {
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorCase4(thicknessRatio) +
                   (viewFactorCase6(thicknessRatio) - viewFactorCase4(thicknessRatio)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorCase6(thicknessRatio) +
                   (viewFactorCase8(thicknessRatio) - viewFactorCase6(thicknessRatio)) * (lateralDimensionRatio - 2) /
                       8;
        }
        return viewFactorCase8(thicknessRatio);
    }
}

} // namespace opening_heat_loss