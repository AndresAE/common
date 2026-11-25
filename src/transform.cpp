#include "transform.hpp"

namespace common
{
  namespace
  {
    constexpr double pi = 3.14159265358979323846;
    constexpr double degToRad = pi / 180.0;

    CMN::matrix matrix3x3()
    {
      CMN::matrix result{};
      result.rows = 3;
      result.cols = 3;
      return result;
    }

    CMN::matrix transpose3x3(const CMN::matrix &matrix)
    {
      CMN::matrix result = matrix3x3();
      for (int row = 0; row < 3; ++row)
      {
        for (int column = 0; column < 3; ++column)
        {
          result.m[row][column] = matrix.m[column][row];
        }
      }
      return result;
    }

    CMN::matrix multiply3x3(const CMN::matrix &left, const CMN::matrix &right)
    {
      CMN::matrix result = matrix3x3();
      for (int row = 0; row < 3; ++row)
      {
        for (int column = 0; column < 3; ++column)
        {
          for (int inner = 0; inner < 3; ++inner)
          {
            result.m[row][column] += left.m[row][inner] * right.m[inner][column];
          }
        }
      }
      return result;
    }
  }

  CMN::matrix Transform::euler2quat(CMN::matrix quat, CMN::matrix euler)
  {
    CMN cmn;
    const double roll = euler.m[0][0] * 0.5;
    const double pitch = euler.m[1][0] * 0.5;
    const double yaw = euler.m[2][0] * 0.5;
    const double cr = cmn.cos(roll);
    const double sr = cmn.sin(roll);
    const double cp = cmn.cos(pitch);
    const double sp = cmn.sin(pitch);
    const double cy = cmn.cos(yaw);
    const double sy = cmn.sin(yaw);

    quat = {};
    quat.rows = 4;
    quat.cols = 1;
    quat.m[0][0] = cr * cp * cy + sr * sp * sy;
    quat.m[1][0] = sr * cp * cy - cr * sp * sy;
    quat.m[2][0] = cr * sp * cy + sr * cp * sy;
    quat.m[3][0] = cr * cp * sy - sr * sp * cy;
    return quat;
  }

  CMN::matrix Transform::quat2euler(CMN::matrix euler, CMN::matrix quat)
  {
    CMN cmn;
    const double w = quat.m[0][0];
    const double x = quat.m[1][0];
    const double y = quat.m[2][0];
    const double z = quat.m[3][0];
    const double sinPitch = cmn.clamp(2.0 * (w * y - z * x), -1.0, 1.0);

    euler = {};
    euler.rows = 3;
    euler.cols = 1;
    euler.m[0][0] = cmn.atan2(2.0 * (w * x + y * z),
                              1.0 - 2.0 * (x * x + y * y));
    euler.m[1][0] = cmn.asin(sinPitch);
    euler.m[2][0] = cmn.atan2(2.0 * (w * z + x * y),
                              1.0 - 2.0 * (y * y + z * z));
    return euler;
  }

  CMN::matrix Transform::getNed2body(CMN::matrix ned2body, double roll_d, double pitch_d, double yaw_d)
  {
    CMN cmn;
    const double roll = roll_d * degToRad;
    const double pitch = pitch_d * degToRad;
    const double yaw = yaw_d * degToRad;
    const double cr = cmn.cos(roll);
    const double sr = cmn.sin(roll);
    const double cp = cmn.cos(pitch);
    const double sp = cmn.sin(pitch);
    const double cy = cmn.cos(yaw);
    const double sy = cmn.sin(yaw);

    ned2body = matrix3x3();
    ned2body.m[0][0] = cp * cy;
    ned2body.m[0][1] = cp * sy;
    ned2body.m[0][2] = -sp;
    ned2body.m[1][0] = sr * sp * cy - cr * sy;
    ned2body.m[1][1] = sr * sp * sy + cr * cy;
    ned2body.m[1][2] = sr * cp;
    ned2body.m[2][0] = cr * sp * cy + sr * sy;
    ned2body.m[2][1] = cr * sp * sy - sr * cy;
    ned2body.m[2][2] = cr * cp;
    return ned2body;
  }

  CMN::matrix Transform::getBody2ned(CMN::matrix body2ned, double roll_d, double pitch_d, double yaw_d)
  {
    return transpose3x3(getNed2body({}, roll_d, pitch_d, yaw_d));
  }

  CMN::matrix Transform::getNed2ecef(CMN::matrix ned2ecef, double latG_d, double lon_d)
  {
    CMN cmn;
    const double latitude = latG_d * degToRad;
    const double longitude = lon_d * degToRad;
    const double sinLat = cmn.sin(latitude);
    const double cosLat = cmn.cos(latitude);
    const double sinLon = cmn.sin(longitude);
    const double cosLon = cmn.cos(longitude);

    ned2ecef = matrix3x3();
    ned2ecef.m[0][0] = -sinLat * cosLon;
    ned2ecef.m[0][1] = -sinLon;
    ned2ecef.m[0][2] = -cosLat * cosLon;
    ned2ecef.m[1][0] = -sinLat * sinLon;
    ned2ecef.m[1][1] = cosLon;
    ned2ecef.m[1][2] = -cosLat * sinLon;
    ned2ecef.m[2][0] = cosLat;
    ned2ecef.m[2][1] = 0.0;
    ned2ecef.m[2][2] = -sinLat;
    return ned2ecef;
  }

  CMN::matrix Transform::getEcef2ned(CMN::matrix ecef2ned, double latG_d, double lon_d)
  {
    return transpose3x3(getNed2ecef({}, latG_d, lon_d));
  }

  CMN::matrix Transform::getBody2ecef(CMN::matrix body2ecef, double latG_d, double lon_d,
                                      double roll_d, double pitch_d, double yaw_d)
  {
    const CMN::matrix ned2ecef = getNed2ecef({}, latG_d, lon_d);
    const CMN::matrix body2ned = getBody2ned({}, roll_d, pitch_d, yaw_d);
    return multiply3x3(ned2ecef, body2ned);
  }

  CMN::matrix Transform::getEcef2body(CMN::matrix ecef2body, double latG_d, double lon_d,
                                      double roll_d, double pitch_d, double yaw_d)
  {
    return transpose3x3(getBody2ecef({}, latG_d, lon_d, roll_d, pitch_d, yaw_d));
  }

} // namespace common