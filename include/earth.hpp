#pragma once
#include "cmn.hpp"

namespace common
{

    class Earth
    {
    public:
        static constexpr double GRAVITY_fps2 = 32.174;
        static constexpr double WGS84_r_ft = 20925646.33;
        static constexpr double WGS84_e = 0.08181919078;
        static constexpr double WGS84_e2 = WGS84_e * WGS84_e;
        static constexpr double WGS84_f = 0.00335281066;
        static constexpr double AIR_RATIO_OF_SPECIFIC_HEATS = 1.4;
        static constexpr double AIR_SPECIFIC_GAS_CONSTANT_J_PER_KG_K = 287.05;
        double accelerationDueToGravity(CMN::matrix ecef);
        double primeVerticalRadiusOfCurvature(double latG_d);
        CMN::matrix lla2ecef(CMN::matrix lla);
        CMN::matrix ecef2lla(CMN::matrix ecef);
    };

} // namespace common