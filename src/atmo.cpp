#include "atmo.hpp"
#include "cmn.hpp"
#include "earth.hpp"

namespace common
{
    namespace
    {
        struct AtmosphereState
        {
            double temperatureC;
            double pressureKPa;
        };

        AtmosphereState stateAt(double altitudeM)
        {
            constexpr double maxDouble = 1.7976931348623157e308;

            CMN cmn;
            if (altitudeM > 25000.0)
            {
                const double temperatureC = -131.21 + 0.00299 * altitudeM;
                const double temperatureRatio = (temperatureC + 273.1) / 216.6;
                return {temperatureC, 2.488 * cmn.pwr(temperatureRatio, -11.388)};
            }

            if (altitudeM > 11000.0)
            {
                return {-56.46, 22.65 * cmn.exp(1.73 - 0.000157 * altitudeM)};
            }

            const double temperatureC = 15.04 - 0.00649 * altitudeM;
            const double temperatureRatio = (temperatureC + 273.1) / 288.08;

            return {temperatureC, 101.29 * cmn.pwr(temperatureRatio, 5.256)};
        }
    }

    double Atmosphere::getTemperature(double altitudeM)
    {
        return stateAt(altitudeM).temperatureC;
    }

    double Atmosphere::getPressure(double altitudeM)
    {
        return stateAt(altitudeM).pressureKPa;
    }

    double Atmosphere::getDensity(double altitudeM)
    {
        const AtmosphereState state = stateAt(altitudeM);
        return state.pressureKPa / (0.2869 * (state.temperatureC + 273.1));
    }

    double Atmosphere::getSpeedOfSound(double altitudeM)
    {
        const AtmosphereState state = stateAt(altitudeM);
        const double temperatureK = state.temperatureC + Earth::CELSIUS_TO_KELVIN;
        CMN cmn;
        return cmn.sqrt(Earth::AIR_RATIO_OF_SPECIFIC_HEATS *
                        Earth::AIR_SPECIFIC_GAS_CONSTANT_J_PER_KG_K * temperatureK);
    }

} // namespace common
