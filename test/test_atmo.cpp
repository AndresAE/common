#include "../include/atmo.hpp"
#include "../include/cmn.hpp"
#include "../include/earth.hpp"
#include "minitest.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

using namespace common;
using namespace minitest;

int main()
{
    Atmosphere atmosphere;
    CMN cmn;

    const double seaLevelTemperature = 15.04;
    const double seaLevelPressure =
        101.29 * std::pow((seaLevelTemperature + 273.1) / 288.08, 5.256);
    assert_near(atmosphere.getTemperature(0.0), 15.04, 1e-12,
                "sea-level temperature");
    assert_near(atmosphere.getPressure(0.0), seaLevelPressure, 1e-12,
                "sea-level pressure");
    assert_near(atmosphere.getDensity(0.0),
                seaLevelPressure / (0.2869 * (seaLevelTemperature + 273.1)), 1e-12,
                "sea-level density");
    assert_near(atmosphere.getSpeedOfSound(0.0),
                cmn.sqrt(Earth::AIR_RATIO_OF_SPECIFIC_HEATS *
                         Earth::AIR_SPECIFIC_GAS_CONSTANT_J_PER_KG_K *
                         (15.04 + Earth::CELSIUS_TO_KELVIN)),
                1e-12,
                "sea-level speed of sound");

    const double troposphereTemperature = 15.04 - 0.00649 * 5000.0;
    const double tropospherePressure =
        101.29 * std::pow((troposphereTemperature + 273.1) / 288.08, 5.256);
    assert_near(atmosphere.getTemperature(5000.0), troposphereTemperature, 1e-12,
                "troposphere temperature");
    assert_near(atmosphere.getPressure(5000.0), tropospherePressure, 1e-12,
                "troposphere pressure");

    assert_near(atmosphere.getTemperature(11000.0),
                15.04 - 0.00649 * 11000.0, 1e-12,
                "temperature at tropopause");
    assert_near(atmosphere.getTemperature(11001.0), -56.46, 1e-12,
                "lower stratosphere temperature");
    assert_near(atmosphere.getPressure(18000.0),
                22.65 * std::exp(1.73 - 0.000157 * 18000.0), 1e-12,
                "lower stratosphere pressure");

    assert_near(atmosphere.getTemperature(25000.0), -56.46, 1e-12,
                "temperature at stratopause");
    const double upperTemperature = -131.21 + 0.00299 * 30000.0;
    assert_near(atmosphere.getTemperature(30000.0), upperTemperature, 1e-12,
                "upper stratosphere temperature");
    assert_near(atmosphere.getPressure(30000.0),
                2.488 * std::pow((upperTemperature + 273.1) / 216.6, -11.388),
                1e-12, "upper stratosphere pressure");

    summary();
    return tests_failed;
}