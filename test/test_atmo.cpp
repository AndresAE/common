#include "../include/atmo.hpp"
#include "../include/cmn.hpp"
#include "../include/earth.hpp"
#include "../include/conversions.hpp"
#include "minitest.hpp"

using namespace common;
using namespace minitest;

int main()
{
    Atmosphere atmosphere;
    CMN cmn;
    Conversions C;

    const double seaLevelTemperatureC = 15.04;
    const double seaLevelPressure =
        C.pa2psf(1000.0 * 101.29 *
                  cmn.pwr((seaLevelTemperatureC + 273.1) / 288.08, 5.256));
    assert_near(atmosphere.getTemperature(0.0),
                C.celsius2fahrenheit(seaLevelTemperatureC), 1e-12,
                "sea-level temperature");
    assert_near(atmosphere.getPressure(0.0), seaLevelPressure, 1e-12,
                "sea-level pressure");
    assert_near(atmosphere.getDensity(0.0),
                C.kgm3_2_slugft3(
                    C.psf2pa(seaLevelPressure) /
                    (0.2869 * (seaLevelTemperatureC + C.CELSIUS_TO_KELVIN))),
                1e-12,
                "sea-level density");
    assert_near(atmosphere.getSpeedOfSound(0.0),
                cmn.sqrt(Earth::AIR_RATIO_OF_SPECIFIC_HEATS *
                         Earth::AIR_SPECIFIC_GAS_CONSTANT_J_PER_KG_K *
                         (seaLevelTemperatureC + C.CELSIUS_TO_KELVIN)),
                1e-12,
                "sea-level speed of sound");

    const double troposphereAltitudeM = 5000.0;
    const double troposphereAltitudeFt = C.m2ft(troposphereAltitudeM);
    const double troposphereTemperatureC =
        15.04 - 0.00649 * troposphereAltitudeM;
    const double tropospherePressure =
        C.pa2psf(1000.0 * 101.29 *
                 cmn.pwr((troposphereTemperatureC + 273.1) / 288.08, 5.256));
    assert_near(atmosphere.getTemperature(troposphereAltitudeFt),
                C.celsius2fahrenheit(troposphereTemperatureC), 1e-12,
                "troposphere temperature");
    assert_near(atmosphere.getPressure(troposphereAltitudeFt),
                tropospherePressure, 1e-12,
                "troposphere pressure");

    const double tropopauseM = 11000.0;
    const double tropopauseFt = C.m2ft(tropopauseM);
    assert_near(atmosphere.getTemperature(tropopauseFt),
                C.celsius2fahrenheit(15.04 - 0.00649 * tropopauseM), 1e-12,
                "temperature at tropopause");
    assert_near(atmosphere.getTemperature(C.m2ft(11001.0)),
                C.celsius2fahrenheit(-56.46), 1e-12,
                "lower stratosphere temperature");
    assert_near(atmosphere.getPressure(C.m2ft(18000.0)),
                C.pa2psf(1000.0 * 22.65 *
                         cmn.exp(1.73 - 0.000157 * 18000.0)),
                1e-12,
                "lower stratosphere pressure");

    assert_near(atmosphere.getTemperature(C.m2ft(25000.0)),
                C.celsius2fahrenheit(-56.46), 1e-12,
                "temperature at stratopause");
    const double upperTemperatureC = -131.21 + 0.00299 * 30000.0;
    assert_near(atmosphere.getTemperature(C.m2ft(30000.0)),
                C.celsius2fahrenheit(upperTemperatureC), 1e-12,
                "upper stratosphere temperature");
    assert_near(atmosphere.getPressure(C.m2ft(30000.0)),
                C.pa2psf(1000.0 * 2.488 *
                         cmn.pwr((upperTemperatureC + 273.1) / 216.6, -11.388)),
                1e-12, "upper stratosphere pressure");

    summary();
    return tests_failed;
}