#include "../include/transform.hpp"
#include "minitest.hpp"

using namespace common;
using namespace minitest;

namespace
{
    CMN::matrix vector3(double x, double y, double z)
    {
        CMN::matrix value{};
        value.rows = 3;
        value.cols = 1;
        value.m[0][0] = x;
        value.m[1][0] = y;
        value.m[2][0] = z;
        return value;
    }

    void assert_identity(const CMN::matrix &value, const char *message)
    {
        assert_true(value.rows == 3 && value.cols == 3, message);
        for (int row = 0; row < 3; ++row)
        {
            for (int column = 0; column < 3; ++column)
            {
                assert_near(value.m[row][column], row == column ? 1.0 : 0.0,
                            1e-12, message);
            }
        }
    }
}

int main()
{
    Transform transform;

    const CMN::matrix zeroEuler = vector3(0.0, 0.0, 0.0);
    const CMN::matrix identityQuat = transform.euler2quat({}, zeroEuler);
    assert_near(identityQuat.m[0][0], 1.0, 1e-12, "identity quaternion scalar");
    assert_near(identityQuat.m[1][0], 0.0, 1e-12, "identity quaternion x");
    assert_near(identityQuat.m[2][0], 0.0, 1e-12, "identity quaternion y");
    assert_near(identityQuat.m[3][0], 0.0, 1e-12, "identity quaternion z");

    const CMN::matrix euler = vector3(0.3, -0.2, 0.7);
    const CMN::matrix quaternion = transform.euler2quat({}, euler);
    const CMN::matrix roundTrip = transform.quat2euler({}, quaternion);
    for (int i = 0; i < 3; ++i)
    {
        assert_near(roundTrip.m[i][0], euler.m[i][0], 1e-12,
                    "Euler-quaternion round trip");
    }

    const CMN::matrix ned2body = transform.getNed2body({}, 0.0, 0.0, 90.0);
    assert_near(ned2body.m[0][0], 0.0, 1e-12, "NED-to-body yaw matrix");
    assert_near(ned2body.m[0][1], 1.0, 1e-12, "NED-to-body yaw matrix");
    assert_near(ned2body.m[1][0], -1.0, 1e-12, "NED-to-body yaw matrix");
    assert_identity(transform.getBody2ned({}, 0.0, 0.0, 0.0),
                    "body-to-NED zero attitude");

    const CMN::matrix ned2ecef = transform.getNed2ecef({}, 0.0, 0.0);
    assert_near(ned2ecef.m[0][0], 0.0, 1e-12, "NED-to-ECEF at equator");
    assert_near(ned2ecef.m[0][2], -1.0, 1e-12, "NED-to-ECEF at equator");
    assert_near(ned2ecef.m[2][0], 1.0, 1e-12, "NED-to-ECEF at equator");

    const CMN::matrix ecef2ned = transform.getEcef2ned({}, 0.0, 0.0);
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert_near(ecef2ned.m[row][column], ned2ecef.m[column][row],
                        1e-12, "ECEF-to-NED transpose");
        }
    }

    const CMN::matrix body2ecef =
        transform.getBody2ecef({}, 0.0, 0.0, 0.0, 0.0, 0.0);
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert_near(body2ecef.m[row][column], ned2ecef.m[row][column],
                        1e-12, "body-to-ECEF zero attitude");
        }
    }

    const CMN::matrix ecef2body =
        transform.getEcef2body({}, 0.0, 0.0, 0.0, 0.0, 0.0);
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            assert_near(ecef2body.m[row][column], body2ecef.m[column][row],
                        1e-12, "ECEF-to-body transpose");
        }
    }

    summary();
    return tests_failed;
}