#include "cmn.hpp"

CMN::CMN()
{
  // Constructor logic if needed
}

double CMN::norm(double x, double y, double z)
{
  return sqrt(x * x + y * y + z * z);
}

double CMN::abs(double x)
{
  return sqrt(x * x);
}

int CMN::sign(double x)
{
  if (x > 0)
    return 1;
  if (x < 0)
    return -1;
  return 0;
}

double CMN::protectedDivide(double numerator, double denominator, double threshold)
{
  if (fabs(denominator) < threshold)
  {
    return numerator >= 0.0 ? (numerator / threshold) : (numerator / -threshold);
  }
  return numerator / denominator;
}

double CMN::interpolate(CMN::matrix xArray, CMN::matrix yArray, double x, int rowIndex = 0)
{
  if (xArray.cols < 2)
    return 0.0; // Not enough data points

  int ii = 0;
  while (ii < xArray.cols - 1 && xArray.m[rowIndex][ii] < x)
    ii++;

  // clamp ii to valid range
  if (ii == 0)
    return yArray.m[rowIndex][0]; // Return first value if x is less than or equal to first x value

  double x0 = xArray.m[rowIndex][ii - 1];
  double y0 = yArray.m[rowIndex][ii - 1];
  double x1 = xArray.m[rowIndex][ii];
  double y1 = yArray.m[rowIndex][ii];

  if (x <= x1)
  {
    if (x1 - x0 == 0.0)
      return y0; // avoid division by zero
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
  }
  else
  {
    return y1; // x > x1, return last value
  }
}

double CMN::primeVerticalRadiusOfCurvature(double latG_d)
{
  double sinLat = sin(DEG2RAD * latG_d);
  return WGS84_r_ft / sqrt(1.0 - WGS84_e2 * (sinLat * sinLat));
}

CMN::busEcef CMN::lla2ecef(busLLA lla_ddft)
{
  n_ft = primeVerticalRadiusOfCurvature(lla_ddft.latG_d);
  double cosLat = cos(DEG2RAD * lla_ddft.latG_d);
  double cosLon = cos(DEG2RAD * lla_ddft.lon_d);
  double sinLat = sin(DEG2RAD * lla_ddft.latG_d);
  m_ECEF.x_ft = (n_ft + lla_ddft.hae_ft) * cosLat * cosLon;
  m_ECEF.y_ft = (n_ft + lla_ddft.hae_ft) * cosLat * sin(DEG2RAD * lla_ddft.lon_d);
  m_ECEF.z_ft = ((1.0 - WGS84_e2) * n_ft + lla_ddft.hae_ft) * sinLat;
  return m_ECEF;
}

CMN::busLLA CMN::ecef2lla(busEcef ecef_ft)
{
  m_LLA.lon_d = RAD2DEG * atan2(ecef_ft.y_ft, ecef_ft.x_ft);
  _nIter = 0;
  m_LLA.hae_ft = 0.0;
  n_ft = WGS84_r_ft;

  while (_nIter < _nIterLat)
  {
    m_LLA.latG_d = RAD2DEG * atan((ecef_ft.z_ft) / (sqrt(ecef_ft.x_ft * ecef_ft.x_ft + ecef_ft.y_ft * ecef_ft.y_ft) * (1 - (WGS84_e2 * n_ft) / (n_ft + m_LLA.hae_ft))));
    n_ft = primeVerticalRadiusOfCurvature(m_LLA.latG_d);
    m_LLA.hae_ft = sqrt(ecef_ft.x_ft * ecef_ft.x_ft + ecef_ft.y_ft * ecef_ft.y_ft) / cos(DEG2RAD * m_LLA.latG_d) - n_ft;
    _nIter++;
  }
  return m_LLA;
}

CMN::matrix CMN::euler2quat(CMN::matrix quat, CMN::matrix euler)
{
  quat.m[0][0] = cos(euler.m[0][0] / 2) * cos(euler.m[1][0] / 2) * cos(euler.m[2][0] / 2) + sin(euler.m[0][0] / 2) * sin(euler.m[1][0] / 2) * sin(euler.m[2][0] / 2);
  quat.m[1][0] = sin(euler.m[0][0] / 2) * cos(euler.m[1][0] / 2) * cos(euler.m[2][0] / 2) - cos(euler.m[0][0] / 2) * sin(euler.m[1][0] / 2) * sin(euler.m[2][0] / 2);
  quat.m[2][0] = cos(euler.m[0][0] / 2) * sin(euler.m[1][0] / 2) * cos(euler.m[2][0] / 2) + sin(euler.m[0][0] / 2) * cos(euler.m[1][0] / 2) * sin(euler.m[2][0] / 2);
  quat.m[3][0] = cos(euler.m[0][0] / 2) * cos(euler.m[1][0] / 2) * sin(euler.m[2][0] / 2) - sin(euler.m[0][0] / 2) * sin(euler.m[1][0] / 2) * cos(euler.m[2][0] / 2);
  return quat;
}

CMN::matrix CMN::quat2euler(CMN::matrix euler, CMN::matrix quat)
{
  euler.m[0][0] = atan2(2 * (quat.m[0][0] * quat.m[1][0] + quat.m[2][0] * quat.m[3][0]), 1 - 2 * (quat.m[1][0] * quat.m[1][0] + quat.m[2][0] * quat.m[2][0]));
  euler.m[1][0] = asin(2 * (quat.m[0][0] * quat.m[2][0] - quat.m[3][0] * quat.m[1][0]));
  euler.m[2][0] = atan2(2 * (quat.m[0][0] * quat.m[3][0] + quat.m[1][0] * quat.m[2][0]), 1 - 2 * (quat.m[2][0] * quat.m[2][0] + quat.m[3][0] * quat.m[3][0]));
  return euler;
}

CMN::matrix CMN::matrixMultiply(CMN::matrix A, CMN::matrix B)
{
  CMN::matrix mat;
  mat.rows = A.rows;
  mat.cols = B.cols;
  for (int i = 0; i < A.rows; i++)
  {
    for (int j = 0; j < B.cols; j++)
    {
      mat.m[i][j] = 0.0f;
      for (int k = 0; k < A.cols; k++)
      {
        mat.m[i][j] += A.m[i][k] * B.m[k][j];
      }
    }
  }
  return mat;
}

CMN::matrix CMN::matrixAdd(CMN::matrix A, CMN::matrix B, bool negate_b)
{
  CMN::matrix R;
  R.rows = A.rows;
  R.cols = A.cols;
  for (int i = 0; i < A.rows; i++)
  {
    for (int j = 0; j < A.cols; j++)
    {
      if (negate_b)
      {
        R.m[i][j] = A.m[i][j] - B.m[i][j];
      }
      else
      {
        R.m[i][j] = A.m[i][j] + B.m[i][j];
      }
    }
  }
  return R;
}

CMN::matrix CMN::matrixTranspose(CMN::matrix A)
{
  CMN::matrix T;
  T.rows = A.cols;
  T.cols = A.rows;
  for (int i = 0; i < A.rows; i++)
  {
    for (int j = 0; j < A.cols; j++)
    {
      T.m[j][i] = A.m[i][j];
    }
  }
  return T;
}

CMN::matrix CMN::matrixInverse(CMN::matrix A)
{
  int n = A.rows;
  CMN::matrix aug;
  aug.rows = n;
  aug.cols = 2 * n;

  // build augmented matrix [A | I]
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      aug.m[i][j] = A.m[i][j];
    }
    for (int j = 0; j < n; j++)
    {
      aug.m[i][n + j] = (i == j) ? 1.0f : 0.0f;
    }
  }

  // Gauss-Jordan elimination
  for (int i = 0; i < n; i++)
  {
    // find pivot
    int pivot = i;
    float maxVal = fabs(aug.m[i][i]);
    for (int r = i + 1; r < n; r++)
    {
      if (fabs(aug.m[r][i]) > maxVal)
      {
        maxVal = fabs(aug.m[r][i]);
        pivot = r;
      }
    }
    if (pivot != i)
    {
      for (int c = 0; c < 2 * n; c++)
      {
        float tmp = aug.m[i][c];
        aug.m[i][c] = aug.m[pivot][c];
        aug.m[pivot][c] = tmp;
      }
    }

    float diag = aug.m[i][i];
    if (fabs(diag) < 1e-9f)
    {
      // singular; return zero-sized matrix
      CMN::matrix zero;
      zero.rows = 0;
      zero.cols = 0;
      return zero;
    }

    // normalize row
    for (int c = 0; c < 2 * n; c++)
      aug.m[i][c] /= diag;

    // eliminate other rows
    for (int r = 0; r < n; r++)
    {
      if (r == i)
        continue;
      float factor = aug.m[r][i];
      for (int c = 0; c < 2 * n; c++)
      {
        aug.m[r][c] -= factor * aug.m[i][c];
      }
    }
  }

  CMN::matrix inv;
  inv.rows = n;
  inv.cols = n;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      inv.m[i][j] = aug.m[i][n + j];
    }
  }
  return inv;
}

CMN::matrix CMN::crossProductMatrix(CMN::matrix A, CMN::matrix B)
{
  CMN::matrix C;
  C.rows = 3;
  C.cols = 1;
  C.m[0][0] = A.m[1][0] * B.m[2][0] - A.m[2][0] * B.m[1][0];
  C.m[1][0] = A.m[2][0] * B.m[0][0] - A.m[0][0] * B.m[2][0];
  C.m[2][0] = A.m[0][0] * B.m[1][0] - A.m[1][0] * B.m[0][0];
  return C;
}

CMN::matrix CMN::getNed2body(CMN::matrix ned2body, double roll_d, double pitch_d, double yaw_d)
{
  double pitch_r = pitch_d * DEG2RAD;
  double yaw_r = yaw_d * DEG2RAD;
  double roll_r = roll_d * DEG2RAD;

  ned2body.m[0][0] = cos(pitch_r) * cos(yaw_r);
  ned2body.m[0][1] = cos(pitch_r) * sin(yaw_r);
  ned2body.m[0][2] = -sin(pitch_r);
  ned2body.m[1][0] = sin(roll_r) * sin(pitch_r) * cos(yaw_r) - cos(roll_r) * sin(yaw_r);
  ned2body.m[1][1] = sin(roll_r) * sin(pitch_r) * sin(yaw_r) + cos(roll_r) * cos(yaw_r);
  ned2body.m[1][2] = sin(roll_r) * cos(pitch_r);
  ned2body.m[2][0] = cos(roll_r) * sin(pitch_r) * cos(yaw_r) + sin(roll_r) * sin(yaw_r);
  ned2body.m[2][1] = cos(roll_r) * sin(pitch_r) * sin(yaw_r) - sin(roll_r) * cos(yaw_r);
  ned2body.m[2][2] = cos(roll_r) * cos(pitch_r);

  return ned2body;
}

CMN::matrix CMN::getBody2ned(CMN::matrix body2ned, double roll_d, double pitch_d, double yaw_d)
{
  CMN::matrix ned2body = {3, 3, {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
  ned2body = getNed2body(ned2body, roll_d, pitch_d, yaw_d);
  body2ned = matrixTranspose(ned2body);
  return body2ned;
}

CMN::matrix CMN::getNed2ecef(CMN::matrix ned2ecef, double latG_d, double lon_d)
{
  double lat = latG_d * DEG2RAD;
  double lon = lon_d * DEG2RAD;

  ned2ecef.m[0][0] = static_cast<float>(-sin(lat) * cos(lon));
  ned2ecef.m[0][1] = static_cast<float>(-sin(lon));
  ned2ecef.m[0][2] = static_cast<float>(-cos(lat) * cos(lon));
  ned2ecef.m[1][0] = static_cast<float>(-sin(lat) * sin(lon));
  ned2ecef.m[1][1] = static_cast<float>(cos(lon));
  ned2ecef.m[1][2] = static_cast<float>(-cos(lat) * sin(lon));
  ned2ecef.m[2][0] = static_cast<float>(cos(lat));
  ned2ecef.m[2][1] = 0.0f;
  ned2ecef.m[2][2] = static_cast<float>(-sin(lat));
  return ned2ecef;
}

CMN::matrix CMN::getEcef2ned(CMN::matrix ecef2ned, double latG_d, double lon_d)
{
  CMN::matrix ned2ecef = getNed2ecef(CMN::matrix(), latG_d, lon_d);
  ecef2ned = matrixTranspose(ned2ecef);
  return ecef2ned;
}

CMN::matrix CMN::getBody2ecef(CMN::matrix body2ecef, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d)
{
  CMN::matrix ned2ecef = getNed2ecef(CMN::matrix(), latG_d, lon_d);
  CMN::matrix ned2body = getNed2body(CMN::matrix(), roll_d, pitch_d, yaw_d);
  body2ecef = matrixMultiply(ned2ecef, matrixTranspose(ned2body));
  return body2ecef;
}

CMN::matrix CMN::getEcef2body(CMN::matrix ecef2body, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d)
{
  CMN::matrix body2ecef = getBody2ecef(CMN::matrix(), latG_d, lon_d, roll_d, pitch_d, yaw_d);
  ecef2body = matrixTranspose(body2ecef);
  return ecef2body;
}
