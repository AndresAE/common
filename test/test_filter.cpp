 #include "../include/filter.hpp"
 #include "minitest.hpp"

 using namespace minitest;

 int main()
 {
     FILTER identityFilter(100);

     assert_near(identityFilter.dt_s, 0.01, 1e-12,
                 "filter sample period");
     assert_near(identityFilter.step(3.0), 3.0, 1e-12,
                 "identity filter constant input");
     assert_near(identityFilter.step(-2.0), -2.0, 1e-12,
                 "identity filter changing input");

     identityFilter.resetHist(5.0);
     assert_near(identityFilter.step(5.0), 5.0, 1e-12,
                 "reset history initial condition");
     assert_near(identityFilter.step(7.0, true), 7.0, 1e-12,
                 "step reset flag");

     assert_true(identityFilter.binom(5, 0) == 1,
                 "binomial coefficient n choose zero");
     assert_true(identityFilter.binom(5, 2) == 10,
                 "binomial coefficient n choose two");
     assert_true(identityFilter.binom(5, 5) == 1,
                 "binomial coefficient n choose n");
     assert_true(identityFilter.binom(5, 6) == 0,
                 "binomial coefficient out of range");

     FILTER gainFilter(100);
     gainFilter.num[0] = 2.0;
     gainFilter.init();
     assert_near(gainFilter.step(3.0), 6.0, 1e-12,
                 "constant gain numerator");

     FILTER lowPassFilter(100);
     lowPassFilter.den[1] = 1.0;
     lowPassFilter.init();
     assert_near(lowPassFilter._Bcoef[0], 1.0 / 201.0, 1e-12,
                 "low-pass feedforward coefficient zero");
     assert_near(lowPassFilter._Bcoef[1], 1.0 / 201.0, 1e-12,
                 "low-pass feedforward coefficient one");
     assert_near(lowPassFilter._Acoef[1], -199.0 / 201.0, 1e-12,
                 "low-pass feedback coefficient one");

     lowPassFilter.resetHist(0.0);
     assert_near(lowPassFilter.step(1.0), 1.0 / 201.0, 1e-12,
                 "low-pass first sample");
     assert_near(lowPassFilter.step(1.0),
                 2.0 / 201.0 + (199.0 / 201.0) * (1.0 / 201.0),
                 1e-12, "low-pass second sample");

     summary();
     return tests_failed;
 }