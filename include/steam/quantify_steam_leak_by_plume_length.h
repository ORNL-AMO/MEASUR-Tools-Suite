#pragma once

/**
 * @file
 * @brief Implementations of DOE's Quantify and Eliminate Steam Leaks
 *
 * http://files.engineering.com/download.aspx?folder=fe5f4331-c289-403b-9b79-8169f3aa1c2f&file=Department_of_energy_steam_leaks.pdf
 *
 * @author Omer Aziz
 *
 */

#include <stdexcept>
#include <array>
#include <cmath>

class QuantifySteamLeakByPlumeLength {
    public:
    /**
     *
     * @param pressure double, Steam Pressure in psig
     * @param plumeLength double, Plume Length in feet
     * @param ambTemp double Ambient Temperature in F
     *
     * @return double value of amount of Steam Loss in lb/hr
     */
    static double estimate(const double pressure, const double plumeLength, const double ambTemp) {
        if (pressure < 115 || pressure > 415) {
            throw std::runtime_error("Steam Leak with Plume length method, Header pressure / steam pressure has to be "
                "in the range of 115 and 415 psig, provided value is " +
                std::to_string(pressure));
        }

        if (plumeLength < 3 || plumeLength > 12) {
            throw std::runtime_error("Steam Leak with Plume length method, Plume Length has to be in the range of 3 "
                "and 12 ft, provided value is " +
                std::to_string(plumeLength));
        }

        if (ambTemp < 45 || ambTemp > 90) {
            throw std::runtime_error("Steam Leak with Plume length method, ambient temperature has to be in the range "
                "of 45 and 90 F, provided value is " +
                std::to_string(ambTemp));
        }

        constexpr int pressureSize = 2;
        constexpr int lengthsSize = 4;
        constexpr int tempsSize = 3;
        constexpr std::array<int, pressureSize> pressures = { 115, 415 };
        constexpr std::array<int, lengthsSize> lengths = { 3, 6, 9, 12 };
        constexpr std::array<int, tempsSize> temps = { 45, 75, 90 };
        constexpr std::array<std::array<std::array<int, tempsSize>, lengthsSize>, pressureSize> steamLossData = { {
            {{ // 115
                {{10, 30, 50}},    //  3
                {{30, 170, 280}},  //  6
                {{70, 420, 700}},  //  9
                {{110, 650, 1100}} // 12
            }},
            {{ // 415
                {{20, 35, 50}},    //  3
                {{50, 170, 290}},  //  6
                {{130, 500, 800}}, //  9
                {{220, 870, 1400}} // 12
            }}
        } };

        int lengthIndexL = 0, lengthIndexH = 1;
        if (plumeLength <= 6) { lengthIndexL = 0; lengthIndexH = 1; }
        else if (plumeLength <= 9) { lengthIndexL = 1; lengthIndexH = 2; }
        else if (plumeLength <= 12) { lengthIndexL = 2; lengthIndexH = 3; }

        int tempIndexL = 0, tempIndexH = 1;
        if (ambTemp > 75) { tempIndexL = 1; tempIndexH = 2; }

        std::array<std::array<double, 2>, 2> steamLossRange = { {
            {{0, 0}},
            {{0, 0}}
        } };
        int r2 = pressures[1], r1 = pressures[0], r = static_cast<int>(std::round(pressure));
        steamLossRange[0][0] = interpolate(r2, r1, r, steamLossData[0][lengthIndexL][tempIndexL], steamLossData[1][lengthIndexL][tempIndexL]);
        steamLossRange[0][1] = interpolate(r2, r1, r, steamLossData[0][lengthIndexH][tempIndexL], steamLossData[1][lengthIndexH][tempIndexL]);
        steamLossRange[1][0] = interpolate(r2, r1, r, steamLossData[0][lengthIndexL][tempIndexH], steamLossData[1][lengthIndexL][tempIndexH]);
        steamLossRange[1][1] = interpolate(r2, r1, r, steamLossData[0][lengthIndexH][tempIndexH], steamLossData[1][lengthIndexH][tempIndexH]);

        r2 = temps[tempIndexH], r1 = temps[tempIndexL], r = static_cast<int>(std::round(ambTemp));
        const double steamLossL = interpolate(r2, r1, r, steamLossRange[0][0], steamLossRange[1][0]);
        const double steamLossH = interpolate(r2, r1, r, steamLossRange[0][1], steamLossRange[1][1]);

        r2 = lengths[lengthIndexH], r1 = lengths[lengthIndexL], r = static_cast<int>(std::round(plumeLength));
        return interpolate(r2, r1, r, steamLossL, steamLossH);
    }

    private:
        static double interpolate(const int r2, const int r1, const int r, const double l, const double u) { return (u - l) / (r2 - r1) * (r - r1) + l; }
};
