#ifndef CMN_HPP
#define CMN_HPP

class CMN
{
public:
    CMN() = default;

    struct matrix
    {
        static constexpr int maxDimension = 15;
        int rows = 0;
        int cols = 0;
        double m[maxDimension][maxDimension]{};
    };

    double norm(double x, double y, double z);
    double hypot(double x, double y);
    double abs(double x);
    double clamp(double value, double lowerBound, double upperBound);
    double sqrt(double value);
    double sin(double angle);
    double cos(double angle);
    double tan(double angle);
    double asin(double value);
    double atan(double value);
    double atan2(double y, double x);
    // Invalid domains return 0; overflow saturates at the largest finite double.
    double pwr(double base, double exponent);
    double exp(double exponent);
    int sign(double x);
    double protectedDivide(double numerator, double denominator, double threshold = 1e-6);
    double interpolate(matrix xArray, matrix yArray, double x, int rowIndex = 0);

    matrix matrixMultiply(matrix A, matrix B);
    matrix matrixAdd(matrix A, matrix B, bool negate_b = false);
    matrix matrixTranspose(matrix A);
    matrix matrixInverse(matrix A);
    matrix crossProductMatrix(matrix A, matrix B);
};
#endif // CMN_HPP
