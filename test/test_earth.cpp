#include "../include/earth.hpp"
#include "minitest.hpp"

using namespace common;
using namespace minitest;

namespace
{
    CMN::matrix vector3(double first, double second, double third)
    {
        CMN::matrix value{};
        value.rows = 3;
        value.cols = 1;
        value.m[0][0] = first;
        value.m[1][0] = second;
        value.m[2][0] = third;
        return value;
    }
}

int main()
{
    Earth earth;
    CMN cmn;

    assert_near(earth.primeVerticalRadiusOfCurvature(0.0), Earth::WGS84_r_ft,
                1e-9, "prime vertical radius at equator");
    assert_near(earth.primeVerticalRadiusOfCurvature(90.0),
                Earth::WGS84_r_ft / cmn.sqrt(1.0 - Earth::WGS84_e2),
                1e-7, "prime vertical radius at pole");

    const CMN::matrix equator = earth.lla2ecef(vector3(0.0, 0.0, 0.0));
    assert_near(equator.m[0][0], Earth::WGS84_r_ft, 1e-9,
                "equator ECEF x");
    assert_near(equator.m[1][0], 0.0, 1e-9, "equator ECEF y");
    assert_near(equator.m[2][0], 0.0, 1e-9, "equator ECEF z");

    const CMN::matrix eastEquator = earth.lla2ecef(vector3(0.0, 90.0, 0.0));
    assert_near(eastEquator.m[0][0], 0.0, 1e-8, "90-degree longitude ECEF x");
    assert_near(eastEquator.m[1][0], Earth::WGS84_r_ft, 1e-8,
                "90-degree longitude ECEF y");

    const CMN::matrix northPole = earth.lla2ecef(vector3(90.0, 0.0, 0.0));
    assert_near(northPole.m[0][0], 0.0, 1e-8, "north pole ECEF x");
    assert_near(northPole.m[1][0], 0.0, 1e-8, "north pole ECEF y");
    assert_near(northPole.m[2][0],
                Earth::WGS84_r_ft * cmn.sqrt(1.0 - Earth::WGS84_e2), 1e-8,
                "north pole ECEF z");

    const CMN::matrix original = vector3(47.6205, -122.3493, 350.0);
    const CMN::matrix roundTrip = earth.ecef2lla(earth.lla2ecef(original));
    assert_near(roundTrip.m[0][0], original.m[0][0], 1e-10,
                "round-trip latitude");
    assert_near(roundTrip.m[1][0], original.m[1][0], 1e-10,
                "round-trip longitude");
    assert_near(roundTrip.m[2][0], original.m[2][0], 1e-6,
                "round-trip altitude");

    summary();
    return tests_failed;
}
