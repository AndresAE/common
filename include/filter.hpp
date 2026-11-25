#ifndef FILTER_HPP
#define FILTER_HPP

#include "cmn.hpp"

class FILTER
{
public:
    // Constructors
    FILTER(int sampleRate_Hz);

    // Public API
    void resetHist(double IC);
    void init();
    double step(double x, bool reset_b = false);
    int binom(int n, int k);

    double dt_s;
    int sampleRate_Hz;
    double num[5] = {1, 0, 0, 0, 0};    // continuous numerator
    double den[5] = {1, 0, 0, 0, 0};    // continuous denominator
    double _Bcoef[5] = {1, 0, 0, 0, 0}; // discrete numerator
    double _Acoef[5] = {1, 0, 0, 0, 0}; // discrete denominator
    double _x_hist[5] = {1, 0, 0, 0, 0};
    double _y_hist[5] = {1, 0, 0, 0, 0};

private:
    CMN cmn;
};

#endif // FILTER_HPP
