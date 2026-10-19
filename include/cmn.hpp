#ifndef CMN_HPP
#define CMN_HPP

#include <Arduino.h>

class CMN
{
public:
    CMN();

    double _PI = 3.141592653589793;
    double GRAVITY_fps2 = 32.174;    // ft/s²
    double WGS84_r_ft = 20925646.33; // ft
    double WGS84_e = 0.08181919078;
    double WGS84_e2 = 0.08181919078 * 0.08181919078;
    double WGS84_f = 0.00335281066;
    double DEG2RAD = 0.01745329251994;
    double RAD2DEG = 57.2957795130823;
    double FT2M = 0.3048;
    double M2FT = 3.2808;
    double MIN2SEC = 60.0;

    // bus definitions
    struct busEcef
    {
        double x_ft;
        double y_ft;
        double z_ft;
    };

    struct busvEcef
    {
        double x_fps;
        double y_fps;
        double z_fps;
    };

    struct busLLA
    {
        double latG_d;
        double lon_d;
        double hae_ft;
    };

    struct matrix
    {
        int rows;
        int cols;
        double m[15][15]; // max size, but you only use rows×cols
    };

    // common methods
    double norm(double x, double y, double z);
    double abs(double x);
    int sign(double x);
    double protectedDivide(double numerator, double denominator, double threshold = 1e-6);
    double interpolate(matrix xArray, matrix yArray, double x, int rowIndex);
    double primeVerticalRadiusOfCurvature(double latG_d);

    matrix getNed2body(matrix ned2body, double roll_d, double pitch_d, double yaw_d);
    matrix getBody2ned(matrix body2ned, double roll_d, double pitch_d, double yaw_d);
    matrix getNed2ecef(matrix ned2ecef, double latG_d, double lon_d);
    matrix getEcef2ned(matrix ecef2ned, double latG_d, double lon_d);
    matrix getBody2ecef(matrix body2ecef, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d);
    matrix getEcef2body(matrix ecef2body, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d);
    matrix euler2quat(matrix quat, matrix euler);
    matrix quat2euler(matrix euler, matrix quat);
    matrix matrixMultiply(matrix A, matrix B);
    matrix matrixAdd(matrix A, matrix B, bool negate_b = false);
    matrix matrixTranspose(matrix A);
    matrix matrixInverse(matrix A);
    matrix crossProductMatrix(matrix A, matrix B);
    busEcef lla2ecef(busLLA lla_ddft);
    busLLA ecef2lla(busEcef ecef_ft);

private:
    double x, y, z;
    double x_prev, alpha, dt_s;
    double n_ft;
    int _nIterLat = 5;
    int _nIter;
    busLLA m_LLA = {0.0, 0.0, 0.0};
    busEcef m_ECEF = {0.0, 0.0, 0.0};
};
#endif // CMN_HPP
