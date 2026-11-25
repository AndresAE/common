#include "cmn.hpp"
#include "earth.hpp"
#include "conversions.hpp"

#pragma once
namespace common
{

    class Atmosphere
    {
    public:
        struct atmoState
        {
            double temp_F;
            double pres_PSF;
        };

        atmoState update(double altMsl_ft);
        double getTemperature(double altMsl_ft);
        double getPressure(double altMsl_ft);
        double getDensity(double altMsl_ft);
        double getSpeedOfSound(double altMsl_ft);

    private:
        CMN cmn;
        Conversions C;
        double altMsl_m;
    };

} // namespace common