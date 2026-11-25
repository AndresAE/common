#include "earth.hpp"

#include <stdexcept>

namespace common
{
    namespace
    {
        constexpr double pi = 3.14159265358979323846;
        constexpr double degToRad = pi / 180.0;
        constexpr double radToDeg = 180.0 / pi;

        void requireVector3(const CMN::matrix &value)
        {
            if (value.rows != 3 || value.cols != 1)
            {
                throw std::invalid_argument("Earth conversions require a 3x1 matrix");
            }
        }
    }

    double Earth::primeVerticalRadiusOfCurvature(double latG_d)
    {
        CMN cmn;
        const double sinLat = cmn.sin(degToRad * latG_d);
        return WGS84_r_ft / cmn.sqrt(1.0 - WGS84_e2 * sinLat * sinLat);
    }

    CMN::matrix Earth::lla2ecef(CMN::matrix lla)
    {
        CMN cmn;
        requireVector3(lla);
        const double latitude = lla.m[0][0] * degToRad;
        const double longitude = lla.m[1][0] * degToRad;
        const double altitude = lla.m[2][0];
        const double sinLat = cmn.sin(latitude);
        const double cosLat = cmn.cos(latitude);
        const double primeVerticalRadius =
            WGS84_r_ft / cmn.sqrt(1.0 - WGS84_e2 * sinLat * sinLat);

        CMN::matrix ecef{};
        ecef.rows = 3;
        ecef.cols = 1;
        ecef.m[0][0] = (primeVerticalRadius + altitude) * cosLat * cmn.cos(longitude);
        ecef.m[1][0] = (primeVerticalRadius + altitude) * cosLat * cmn.sin(longitude);
        ecef.m[2][0] =
            ((1.0 - WGS84_e2) * primeVerticalRadius + altitude) * sinLat;
        return ecef;
    }

    CMN::matrix Earth::ecef2lla(CMN::matrix ecef)
    {
        CMN cmn;
        requireVector3(ecef);
        const double x = ecef.m[0][0];
        const double y = ecef.m[1][0];
        const double z = ecef.m[2][0];
        const double p = cmn.hypot(x, y);
        if (p == 0.0 && z == 0.0)
        {
            throw std::invalid_argument("ECEF origin has no defined geodetic coordinates");
        }

        const double semiMinorAxis = WGS84_r_ft * cmn.sqrt(1.0 - WGS84_e2);
        const double secondEccentricitySquared =
            (WGS84_r_ft * WGS84_r_ft - semiMinorAxis * semiMinorAxis) /
            (semiMinorAxis * semiMinorAxis);
        const double theta = cmn.atan2(z * WGS84_r_ft, p * semiMinorAxis);
        const double sinTheta = cmn.sin(theta);
        const double cosTheta = cmn.cos(theta);
        const double latitude = cmn.atan2(
            z + secondEccentricitySquared * semiMinorAxis * sinTheta * sinTheta * sinTheta,
            p - WGS84_e2 * WGS84_r_ft * cosTheta * cosTheta * cosTheta);
        const double longitude = cmn.atan2(y, x);
        const double sinLat = cmn.sin(latitude);
        const double cosLat = cmn.cos(latitude);
        const double primeVerticalRadius =
            WGS84_r_ft / cmn.sqrt(1.0 - WGS84_e2 * sinLat * sinLat);
        const double altitude = cmn.abs(cosLat) > 1e-12
                                    ? p / cosLat - primeVerticalRadius
                                    : cmn.abs(z) - semiMinorAxis;

        CMN::matrix lla{};
        lla.rows = 3;
        lla.cols = 1;
        lla.m[0][0] = latitude * radToDeg;
        lla.m[1][0] = longitude * radToDeg;
        lla.m[2][0] = altitude;
        return lla;
    }

} // namespace common
