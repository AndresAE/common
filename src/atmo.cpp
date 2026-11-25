#include "atmo.hpp"

namespace common
{
    Atmosphere::atmoState Atmosphere::update(double altMsl_ft)
    {
        altMsl_m = C.ft2m(altMsl_ft);

        if (altMsl_m > 25000.0)
        {
            const double temperatureC = -131.21 + 0.00299 * altMsl_m;
            const double temperatureRatio = (temperatureC + 273.1) / 216.6;
            return {
                C.celsius2fahrenheit(temperatureC),
                C.pa2psf(1000.0 * 2.488 * cmn.pwr(temperatureRatio, -11.388))};
        }

        if (altMsl_m > 11000.0)
        {
            return {
                C.celsius2fahrenheit(-56.46),
                C.pa2psf(1000.0 * 22.65 * cmn.exp(1.73 - 0.000157 * altMsl_m))};
        }

        const double temperatureC = 15.04 - 0.00649 * altMsl_m;
        const double temperatureRatio = (temperatureC + 273.1) / 288.08;

        return {
            C.celsius2fahrenheit(temperatureC),
            C.pa2psf(1000.0 * 101.29 * cmn.pwr(temperatureRatio, 5.256))};
    }

    double Atmosphere::getTemperature(double altMsl_ft)
    {
        return update(altMsl_ft).temp_F;
    }

    double Atmosphere::getPressure(double altMsl_ft)
    {
        return update(altMsl_ft).pres_PSF;
    }

    double Atmosphere::getDensity(double altMsl_ft)
    {
        const atmoState state = update(altMsl_ft);
        return C.kgm3_2_slugft3(C.psf2pa(state.pres_PSF) / (0.2869 * (C.fahrenheit2celsius(state.temp_F) + C.CELSIUS_TO_KELVIN)));
    }

    double Atmosphere::getSpeedOfSound(double altMsl_ft)
    {
        const atmoState state = update(altMsl_ft);
        const double temperatureK = C.fahrenheit2celsius(state.temp_F) + C.CELSIUS_TO_KELVIN;
        CMN cmn;
        return cmn.sqrt(Earth::AIR_RATIO_OF_SPECIFIC_HEATS *
                        Earth::AIR_SPECIFIC_GAS_CONSTANT_J_PER_KG_K * temperatureK);
    }

} // namespace common
