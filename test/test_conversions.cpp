#include "../include/conversions.hpp"
#include "minitest.hpp"

using namespace common;
using namespace minitest;

int main()
{

    assert_near(Conversions::deg2rad(180.0), 3.141592653589793, 1e-12,
                "deg2rad(180)");

    assert_near(Conversions::rad2deg(3.141592653589793), 180.0, 1e-12,
                "rad2deg(pi)");

    assert_near(Conversions::meters2feet(1.0), 3.280839895013123, 1e-12,
                "meters2feet(1)");

    assert_near(Conversions::feet2meters(3.280839895013123), 1.0, 1e-12,
                "feet2meters(3.280839...)");

    summary();
    return tests_failed;
}
