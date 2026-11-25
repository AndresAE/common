#pragma once
#include <iostream>

namespace minitest
{

    inline int tests_run = 0;
    inline int tests_failed = 0;

    inline void assert_near(double a, double b, double eps, const char *msg)
    {
        tests_run++;
        const double difference = a - b;
        if ((difference < 0.0 ? -difference : difference) > eps)
        {
            tests_failed++;
            std::cerr << "[FAIL] " << msg << " | expected " << b << " got " << a << "\n";
        }
    }

    inline void assert_true(bool cond, const char *msg)
    {
        tests_run++;
        if (!cond)
        {
            tests_failed++;
            std::cerr << "[FAIL] " << msg << "\n";
        }
    }

    inline void summary()
    {
        if (tests_failed == 0)
            std::cout << "[PASS] All " << tests_run << " tests passed.\n";
        else
            std::cout << "[FAIL] " << tests_failed << " of " << tests_run << " tests failed.\n";
    }

} // namespace minitest
