#include "cmn.hpp"

namespace
{
    using Matrix = CMN::matrix;
    constexpr double maxDouble = 1.7976931348623157e308;

    double absolute(double value)
    {
        return value < 0.0 ? -value : value;
    }

    bool isFinite(double value)
    {
        return value == value && value <= maxDouble && value >= -maxDouble;
    }

    bool validDimensions(const Matrix &matrix)
    {
        return matrix.rows >= 0 && matrix.rows <= Matrix::maxDimension &&
               matrix.cols >= 0 && matrix.cols <= Matrix::maxDimension;
    }

    Matrix makeMatrix(int rows, int cols)
    {
        Matrix result{};
        result.rows = rows;
        result.cols = cols;
        return result;
    }

    double reduceAngle(double angle)
    {
        constexpr double twoPi = 6.28318530717958647692;
        if (!isFinite(angle))
        {
            return 0.0;
        }

        double divisor = twoPi;
        while (divisor <= absolute(angle) * 0.5 && divisor < maxDouble * 0.5)
        {
            divisor *= 2.0;
        }
        while (divisor >= twoPi)
        {
            if (angle >= divisor)
            {
                angle -= divisor;
            }
            else if (angle <= -divisor)
            {
                angle += divisor;
            }
            divisor *= 0.5;
        }
        while (angle > 3.14159265358979323846)
        {
            angle -= twoPi;
        }
        while (angle < -3.14159265358979323846)
        {
            angle += twoPi;
        }
        return angle;
    }

    double atanUnit(double value)
    {
        constexpr double piOverFour = 0.78539816339744830962;
        constexpr double tanPiOverEight = 0.41421356237309504880;
        const bool negative = value < 0.0;
        double magnitude = absolute(value);
        double offset = 0.0;
        if (magnitude > tanPiOverEight)
        {
            magnitude = (magnitude - 1.0) / (magnitude + 1.0);
            offset = piOverFour;
        }

        const double squared = magnitude * magnitude;
        double term = magnitude;
        double result = term;
        for (int denominator = 3; denominator <= 101; denominator += 2)
        {
            term *= -squared;
            result += term / denominator;
        }
        result += offset;
        return negative ? -result : result;
    }

    double squareRoot(double value)
    {
        if (value < 0.0)
        {
            return 0.0;
        }
        if (value == 0.0 || value != value || value > maxDouble)
        {
            return value;
        }

        double scaled = value;
        double factor = 1.0;
        while (scaled >= 4.0)
        {
            scaled *= 0.25;
            factor *= 2.0;
        }
        while (scaled < 1.0)
        {
            scaled *= 4.0;
            factor *= 0.5;
        }

        double result = (scaled + 1.0) * 0.5;
        for (int iteration = 0; iteration < 12; ++iteration)
        {
            result = (result + scaled / result) * 0.5;
        }
        return result * factor;
    }

    double naturalLog(double value)
    {
        constexpr double sqrtHalf = 0.70710678118654752440;
        constexpr double sqrtTwo = 1.41421356237309504880;
        constexpr double lnTwo = 0.69314718055994530942;
        int exponent = 0;
        while (value >= sqrtTwo)
        {
            value *= 0.5;
            ++exponent;
        }
        while (value < sqrtHalf)
        {
            value *= 2.0;
            --exponent;
        }

        const double ratio = (value - 1.0) / (value + 1.0);
        const double ratioSquared = ratio * ratio;
        double term = ratio;
        double sum = term;
        for (int denominator = 3; denominator <= 101; denominator += 2)
        {
            term *= ratioSquared;
            sum += term / denominator;
        }
        return 2.0 * sum + exponent * lnTwo;
    }

    double naturalExp(double value)
    {
        constexpr double lnTwo = 0.69314718055994530942;
        constexpr double halfLnTwo = lnTwo * 0.5;
        constexpr double maxLog = 709.78271289338397310;
        constexpr double minLog = -744.44007192138121809;
        if (value > maxLog)
        {
            return maxDouble;
        }
        if (value < minLog)
        {
            return 0.0;
        }

        int exponent = 0;
        while (value > halfLnTwo)
        {
            value -= lnTwo;
            ++exponent;
        }
        while (value < -halfLnTwo)
        {
            value += lnTwo;
            --exponent;
        }

        double sum = 1.0;
        double term = 1.0;
        for (int index = 1; index <= 18; ++index)
        {
            term *= value / index;
            sum += term;
        }
        while (exponent > 0)
        {
            if (sum > maxDouble * 0.5)
            {
                return maxDouble;
            }
            sum *= 2.0;
            --exponent;
        }
        while (exponent < 0)
        {
            sum *= 0.5;
            ++exponent;
        }
        return sum;
    }
}

double CMN::norm(double x, double y, double z)
{
    const double absX = abs(x);
    const double absY = abs(y);
    const double absZ = abs(z);
    const double scale = absX > absY ? (absX > absZ ? absX : absZ)
                                     : (absY > absZ ? absY : absZ);
    if (scale == 0.0 || !isFinite(scale))
    {
        return scale;
    }
    const double sx = x / scale;
    const double sy = y / scale;
    const double sz = z / scale;
    return scale * squareRoot(sx * sx + sy * sy + sz * sz);
}

double CMN::hypot(double x, double y)
{
    return norm(x, y, 0.0);
}

double CMN::abs(double x)
{
    return x < 0.0 ? -x : x;
}

double CMN::clamp(double value, double lowerBound, double upperBound)
{
    if (lowerBound > upperBound)
    {
        return value;
    }
    if (value < lowerBound)
    {
        return lowerBound;
    }
    if (value > upperBound)
    {
        return upperBound;
    }
    return value;
}

double CMN::sqrt(double value)
{
    return squareRoot(value);
}

double CMN::sin(double angle)
{
    const double reduced = reduceAngle(angle);
    constexpr double halfPi = 1.57079632679489661923;
    constexpr double pi = 3.14159265358979323846;
    double value = reduced;
    if (value > halfPi)
    {
        value = pi - value;
    }
    else if (value < -halfPi)
    {
        value = -pi - value;
    }

    const double squared = value * value;
    double term = value;
    double result = term;
    for (int index = 1; index <= 10; ++index)
    {
        term *= -squared / ((2.0 * index) * (2.0 * index + 1.0));
        result += term;
    }
    return result;
}

double CMN::cos(double angle)
{
    const double reduced = reduceAngle(angle);
    constexpr double halfPi = 1.57079632679489661923;
    constexpr double pi = 3.14159265358979323846;
    double value = absolute(reduced);
    double sign = 1.0;
    if (value > halfPi)
    {
        value = pi - value;
        sign = -1.0;
    }

    const double squared = value * value;
    double term = 1.0;
    double result = term;
    for (int index = 1; index <= 10; ++index)
    {
        term *= -squared / ((2.0 * index - 1.0) * (2.0 * index));
        result += term;
    }
    return sign * result;
}

double CMN::tan(double angle)
{
    const double cosine = cos(angle);
    if (absolute(cosine) < 1e-15)
    {
        return sin(angle) < 0.0 ? -maxDouble : maxDouble;
    }
    return sin(angle) / cosine;
}

double CMN::atan(double value)
{
    if (!isFinite(value))
    {
        return value < 0.0 ? -1.57079632679489661923
                           : 1.57079632679489661923;
    }
    if (absolute(value) <= 1.0)
    {
        return atanUnit(value);
    }
    constexpr double halfPi = 1.57079632679489661923;
    const double result = halfPi - atanUnit(1.0 / absolute(value));
    return value < 0.0 ? -result : result;
}

double CMN::atan2(double y, double x)
{
    constexpr double pi = 3.14159265358979323846;
    constexpr double halfPi = 1.57079632679489661923;
    if (x > 0.0)
    {
        return atan(y / x);
    }
    if (x < 0.0)
    {
        return y >= 0.0 ? atan(y / x) + pi : atan(y / x) - pi;
    }
    if (y > 0.0)
    {
        return halfPi;
    }
    if (y < 0.0)
    {
        return -halfPi;
    }
    return 0.0;
}

double CMN::asin(double value)
{
    constexpr double halfPi = 1.57079632679489661923;
    if (!isFinite(value) || value < -1.0 || value > 1.0)
    {
        return 0.0;
    }
    if (value == 1.0)
    {
        return halfPi;
    }
    if (value == -1.0)
    {
        return -halfPi;
    }
    return atan2(value, squareRoot(1.0 - value * value));
}

double CMN::pwr(double base, double exponent)
{
    if (exponent == 0.0 || base == 1.0)
    {
        return 1.0;
    }
    if (!isFinite(base) || !isFinite(exponent))
    {
        return 0.0;
    }
    if (base == 0.0)
    {
        return 0.0;
    }

    const bool exponentInIntegerRange = exponent >= -9007199254740991.0 &&
                                        exponent <= 9007199254740991.0;
    const long long integerExponent = exponentInIntegerRange
                                          ? static_cast<long long>(exponent)
                                          : 0;
    const bool integerPower = exponentInIntegerRange
                                  ? static_cast<double>(integerExponent) == exponent
                                  : true;
    if (base < 0.0 && !integerPower)
    {
        return 0.0;
    }

    if (integerPower && exponentInIntegerRange &&
        integerExponent >= -64 && integerExponent <= 64)
    {
        unsigned long long remaining = integerExponent < 0
                                           ? static_cast<unsigned long long>(-integerExponent)
                                           : static_cast<unsigned long long>(integerExponent);
        double result = 1.0;
        double factor = base;
        while (remaining > 0)
        {
            if ((remaining & 1ULL) != 0ULL)
            {
                result *= factor;
            }
            factor *= factor;
            remaining >>= 1ULL;
        }
        result = integerExponent < 0 ? 1.0 / result : result;
        if (!isFinite(result))
        {
            return result < 0.0 ? -maxDouble : maxDouble;
        }
        return result;
    }

    const double logResult = exponent * naturalLog(abs(base));
    const double result = naturalExp(logResult);
    if (base < 0.0 && integerPower && integerExponent % 2 != 0)
    {
        return -result;
    }
    return result;
}

double CMN::exp(double exponent)
{
    if (!isFinite(exponent))
    {
        return 0.0;
    }
    return naturalExp(exponent);
}

int CMN::sign(double x)
{
    if (x > 0.0)
    {
        return 1;
    }
    if (x < 0.0)
    {
        return -1;
    }
    return 0;
}

double CMN::protectedDivide(double numerator, double denominator, double threshold)
{
    if (!(threshold > 0.0) || !isFinite(threshold))
    {
        return 0.0;
    }

    if (abs(denominator) < threshold)
    {
        const bool negativeZero = denominator == 0.0 && (1.0 / denominator) < 0.0;
        denominator = denominator < 0.0 || negativeZero ? -threshold : threshold;
    }
    return numerator / denominator;
}

double CMN::interpolate(matrix xArray, matrix yArray, double x, int rowIndex)
{
    if (!validDimensions(xArray) || !validDimensions(yArray) ||
        xArray.cols != yArray.cols || rowIndex < 0 ||
        rowIndex >= xArray.rows || rowIndex >= yArray.rows)
    {
        return 0.0;
    }
    if (xArray.cols < 2)
    {
        return 0.0;
    }

    int upper = 0;
    while (upper < xArray.cols - 1 && xArray.m[rowIndex][upper] < x)
    {
        ++upper;
    }
    if (upper == 0)
    {
        return yArray.m[rowIndex][0];
    }

    const double x0 = xArray.m[rowIndex][upper - 1];
    const double y0 = yArray.m[rowIndex][upper - 1];
    const double x1 = xArray.m[rowIndex][upper];
    const double y1 = yArray.m[rowIndex][upper];
    if (x > x1)
    {
        return y1;
    }
    if (x1 == x0)
    {
        return y0;
    }
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}

CMN::matrix CMN::matrixMultiply(matrix A, matrix B)
{
    if (!validDimensions(A) || !validDimensions(B) || A.cols != B.rows)
    {
        return makeMatrix(0, 0);
    }

    matrix result = makeMatrix(A.rows, B.cols);
    for (int row = 0; row < A.rows; ++row)
    {
        for (int column = 0; column < B.cols; ++column)
        {
            for (int inner = 0; inner < A.cols; ++inner)
            {
                result.m[row][column] += A.m[row][inner] * B.m[inner][column];
            }
        }
    }
    return result;
}

CMN::matrix CMN::matrixAdd(matrix A, matrix B, bool negate_b)
{
    if (!validDimensions(A) || !validDimensions(B) ||
        A.rows != B.rows || A.cols != B.cols)
    {
        return makeMatrix(0, 0);
    }

    matrix result = makeMatrix(A.rows, A.cols);
    const double sign = negate_b ? -1.0 : 1.0;
    for (int row = 0; row < A.rows; ++row)
    {
        for (int column = 0; column < A.cols; ++column)
        {
            result.m[row][column] = A.m[row][column] + sign * B.m[row][column];
        }
    }
    return result;
}

CMN::matrix CMN::matrixTranspose(matrix A)
{
    if (!validDimensions(A))
    {
        return makeMatrix(0, 0);
    }

    matrix result = makeMatrix(A.cols, A.rows);
    for (int row = 0; row < A.rows; ++row)
    {
        for (int column = 0; column < A.cols; ++column)
        {
            result.m[column][row] = A.m[row][column];
        }
    }
    return result;
}

CMN::matrix CMN::matrixInverse(matrix A)
{
    if (!validDimensions(A) || A.rows != A.cols)
    {
        return makeMatrix(0, 0);
    }

    const int size = A.rows;
    if (size == 0)
    {
        return makeMatrix(0, 0);
    }

    double augmented[CMN::matrix::maxDimension]
                    [2 * CMN::matrix::maxDimension]{};
    for (int row = 0; row < size; ++row)
    {
        for (int column = 0; column < size; ++column)
        {
            augmented[row][column] = A.m[row][column];
        }
        augmented[row][size + row] = 1.0;
    }

    for (int pivotColumn = 0; pivotColumn < size; ++pivotColumn)
    {
        int pivotRow = pivotColumn;
        for (int row = pivotColumn + 1; row < size; ++row)
        {
            if (abs(augmented[row][pivotColumn]) >
                abs(augmented[pivotRow][pivotColumn]))
            {
                pivotRow = row;
            }
        }
        if (abs(augmented[pivotRow][pivotColumn]) < 1e-12)
        {
            return makeMatrix(0, 0);
        }

        if (pivotRow != pivotColumn)
        {
            for (int column = 0; column < 2 * size; ++column)
            {
                const double temporary = augmented[pivotColumn][column];
                augmented[pivotColumn][column] = augmented[pivotRow][column];
                augmented[pivotRow][column] = temporary;
            }
        }

        const double pivot = augmented[pivotColumn][pivotColumn];
        for (int column = 0; column < 2 * size; ++column)
        {
            augmented[pivotColumn][column] /= pivot;
        }

        for (int row = 0; row < size; ++row)
        {
            if (row == pivotColumn)
            {
                continue;
            }
            const double factor = augmented[row][pivotColumn];
            for (int column = 0; column < 2 * size; ++column)
            {
                augmented[row][column] -= factor * augmented[pivotColumn][column];
            }
        }
    }

    matrix inverse = makeMatrix(size, size);
    for (int row = 0; row < size; ++row)
    {
        for (int column = 0; column < size; ++column)
        {
            inverse.m[row][column] = augmented[row][size + column];
        }
    }
    return inverse;
}

CMN::matrix CMN::crossProductMatrix(matrix A, matrix B)
{
    if (!validDimensions(A) || !validDimensions(B) ||
        A.rows != 3 || B.rows != 3 || A.cols != 1 || B.cols != 1)
    {
        return makeMatrix(0, 0);
    }

    matrix result = makeMatrix(3, 1);
    result.m[0][0] = A.m[1][0] * B.m[2][0] - A.m[2][0] * B.m[1][0];
    result.m[1][0] = A.m[2][0] * B.m[0][0] - A.m[0][0] * B.m[2][0];
    result.m[2][0] = A.m[0][0] * B.m[1][0] - A.m[1][0] * B.m[0][0];
    return result;
}
