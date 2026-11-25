#pragma once
namespace common
{

    class Atmosphere
    {
    public:
        // Altitude is in meters MSL. Results use Celsius, kPa, kg/m^3, and m/s.
        double getTemperature(double altitudeM);
        double getPressure(double altitudeM);
        double getDensity(double altitudeM);
        double getSpeedOfSound(double altitudeM);
    };

} // namespace common