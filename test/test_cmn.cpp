#include "../include/cmn.hpp"
#include "minitest.hpp"

using namespace minitest;

namespace
{
    using Matrix = CMN::matrix;

    Matrix matrix2x2(double a, double b, double c, double d)
    {
        Matrix value{};
        value.rows = 2;
        value.cols = 2;
        value.m[0][0] = a;
        value.m[0][1] = b;
        value.m[1][0] = c;
        value.m[1][1] = d;
        return value;
    }

    Matrix vector3(double x, double y, double z)
    {
        Matrix value{};
        value.rows = 3;
        value.cols = 1;
        value.m[0][0] = x;
        value.m[1][0] = y;
        value.m[2][0] = z;
        return value;
    }

}

int main()
{
    CMN common;

    assert_near(common.norm(3.0, 4.0, 12.0), 13.0, 1e-12, "3D norm");
    assert_near(common.hypot(3.0, 4.0), 5.0, 1e-12, "hypotenuse");
    assert_near(common.hypot(3e200, 4e200), 5e200, 1e188,
                "hypotenuse avoids intermediate overflow");
    assert_near(common.abs(-4.5), 4.5, 1e-12, "absolute value");
    assert_near(common.clamp(2.0, -1.0, 1.0), 1.0, 1e-12,
                "clamp upper bound");
    assert_near(common.clamp(-2.0, -1.0, 1.0), -1.0, 1e-12,
                "clamp lower bound");
    assert_near(common.clamp(0.5, -1.0, 1.0), 0.5, 1e-12,
                "clamp within bounds");
    assert_near(common.sqrt(0.0), 0.0, 1e-12, "square root of zero");
    assert_near(common.sqrt(2.0), 1.4142135623730951, 1e-12,
                "square root of two");
    assert_near(common.sqrt(-1.0), 0.0, 1e-12,
                "square root of negative value");
    const double pi = 3.14159265358979323846;
    assert_near(common.sin(pi / 6.0), 0.5, 1e-12, "sine");
    assert_near(common.sin(-pi / 6.0), -0.5, 1e-12, "negative sine");
    assert_near(common.cos(pi / 3.0), 0.5, 1e-12, "cosine");
    assert_near(common.cos(pi), -1.0, 1e-12, "cosine at pi");
    assert_near(common.tan(pi / 4.0), 1.0, 1e-12, "tangent");
    assert_near(common.asin(0.5), pi / 6.0, 1e-12, "inverse sine");
    assert_near(common.atan(1.0), pi / 4.0, 1e-12, "inverse tangent");
    assert_near(common.atan2(1.0, -1.0), 3.0 * pi / 4.0, 1e-12,
                "atan2 second quadrant");
    assert_near(common.atan2(-1.0, -1.0), -3.0 * pi / 4.0, 1e-12,
                "atan2 third quadrant");
    assert_near(common.pwr(2.0, 10.0), 1024.0, 1e-12,
                "integer pwr");
    assert_near(common.pwr(9.0, 0.5), 3.0, 1e-12,
                "fractional pwr");
    assert_near(common.pwr(2.0, -3.0), 0.125, 1e-12,
                "negative exponent");
    assert_near(common.pwr(-2.0, 3.0), -8.0, 1e-12,
                "negative base with odd exponent");
    assert_near(common.pwr(-2.0, 4.0), 16.0, 1e-12,
                "negative base with even exponent");
    assert_near(common.pwr(7.0, 0.0), 1.0, 1e-12,
                "zero exponent");
    assert_near(common.pwr(-2.0, 0.5), 0.0, 1e-12,
                "fractional pwr of negative base rejected");
    assert_near(common.pwr(0.0, -2.0), 0.0, 1e-12,
                "zero to negative pwr rejected");
    assert_near(common.pwr(1e200, 2.0), 1.7976931348623157e308, 0.0,
                "integer pwr overflow saturates");
    assert_near(common.exp(0.0), 1.0, 1e-12, "exponential of zero");
    assert_near(common.exp(1.0), 2.718281828459045, 1e-12,
                "exponential of one");
    assert_near(common.exp(-1.0), 0.36787944117144233, 1e-12,
                "exponential of negative one");
    assert_true(common.sign(2.0) == 1, "positive sign");
    assert_true(common.sign(-2.0) == -1, "negative sign");
    assert_true(common.sign(0.0) == 0, "zero sign");

    assert_near(common.protectedDivide(6.0, 2.0), 3.0, 1e-12,
                "protected divide normal denominator");
    assert_near(common.protectedDivide(2.0, 0.0, 0.5), 4.0, 1e-12,
                "protected divide zero denominator");
    assert_near(common.protectedDivide(2.0, -0.1, 0.5), -4.0, 1e-12,
                "protected divide preserves negative denominator");
    assert_near(common.protectedDivide(2.0, 0.0, 0.0), 0.0, 1e-12,
                "invalid protected divide threshold");

    Matrix xValues{};
    xValues.rows = 1;
    xValues.cols = 3;
    xValues.m[0][0] = 0.0;
    xValues.m[0][1] = 10.0;
    xValues.m[0][2] = 20.0;
    Matrix yValues{};
    yValues.rows = 1;
    yValues.cols = 3;
    yValues.m[0][0] = 1.0;
    yValues.m[0][1] = 3.0;
    yValues.m[0][2] = 7.0;
    assert_near(common.interpolate(xValues, yValues, 5.0), 2.0, 1e-12,
                "linear interpolation");
    assert_near(common.interpolate(xValues, yValues, -5.0), 1.0, 1e-12,
                "interpolation clamps below range");
    assert_near(common.interpolate(xValues, yValues, 25.0), 7.0, 1e-12,
                "interpolation clamps above range");

    const Matrix left = matrix2x2(1.0, 2.0, 3.0, 4.0);
    const Matrix right = matrix2x2(5.0, 6.0, 7.0, 8.0);
    const Matrix sum = common.matrixAdd(left, right);
    assert_near(sum.m[0][0], 6.0, 1e-12, "matrix addition");
    assert_near(sum.m[1][1], 12.0, 1e-12, "matrix addition");
    const Matrix difference = common.matrixAdd(right, left, true);
    assert_near(difference.m[0][0], 4.0, 1e-12, "matrix subtraction");
    assert_near(difference.m[1][1], 4.0, 1e-12, "matrix subtraction");

    const Matrix product = common.matrixMultiply(left, right);
    assert_near(product.m[0][0], 19.0, 1e-12, "matrix multiplication");
    assert_near(product.m[0][1], 22.0, 1e-12, "matrix multiplication");
    assert_near(product.m[1][0], 43.0, 1e-12, "matrix multiplication");
    assert_near(product.m[1][1], 50.0, 1e-12, "matrix multiplication");

    const Matrix transposed = common.matrixTranspose(left);
    assert_true(transposed.rows == 2 && transposed.cols == 2,
                "transpose dimensions");
    assert_near(transposed.m[0][1], 3.0, 1e-12, "matrix transpose");
    assert_near(transposed.m[1][0], 2.0, 1e-12, "matrix transpose");

    const Matrix invertible = matrix2x2(4.0, 7.0, 2.0, 6.0);
    const Matrix inverse = common.matrixInverse(invertible);
    assert_near(inverse.m[0][0], 0.6, 1e-12, "matrix inverse");
    assert_near(inverse.m[0][1], -0.7, 1e-12, "matrix inverse");
    assert_near(inverse.m[1][0], -0.2, 1e-12, "matrix inverse");
    assert_near(inverse.m[1][1], 0.4, 1e-12, "matrix inverse");
    const Matrix identity = common.matrixMultiply(invertible, inverse);
    assert_near(identity.m[0][0], 1.0, 1e-12, "inverse product identity");
    assert_near(identity.m[0][1], 0.0, 1e-12, "inverse product identity");
    assert_near(identity.m[1][0], 0.0, 1e-12, "inverse product identity");
    assert_near(identity.m[1][1], 1.0, 1e-12, "inverse product identity");

    const Matrix singular = common.matrixInverse(matrix2x2(1.0, 2.0, 2.0, 4.0));
    assert_true(singular.rows == 0 && singular.cols == 0,
                "singular inverse returns empty matrix");

    const Matrix cross = common.crossProductMatrix(vector3(1.0, 0.0, 0.0),
                                                   vector3(0.0, 1.0, 0.0));
    assert_near(cross.m[0][0], 0.0, 1e-12, "cross product x");
    assert_near(cross.m[1][0], 0.0, 1e-12, "cross product y");
    assert_near(cross.m[2][0], 1.0, 1e-12, "cross product z");

    assert_near(common.interpolate(xValues, yValues, 0.0, 0), 1.0, 1e-12,
                "interpolation first endpoint");

    summary();
    return tests_failed;
}
