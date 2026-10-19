#include "filter.hpp"

FILTER::FILTER(int sampleRate_Hz)
    : sampleRate_Hz(sampleRate_Hz)
{
    dt_s = 1 / static_cast<double>(sampleRate_Hz);
    resetHist(0.0);
    init();
}

void FILTER::resetHist(double IC)
{
    for (int i = 0; i < 5; ++i)
    {
        _x_hist[i] = IC;
        _y_hist[i] = IC;
    }
}

void FILTER::init()
{
    const double k = 2.0 / dt_s;

    // Temporary polynomial accumulators
    double Nb[5] = {0};
    double Da[5] = {0};

    double c[5][5] = {0};

    for (int i = 0; i <= 4; ++i)
    {
        for (int p = 0; p <= i; ++p)
        {
            for (int q = 0; q <= 4 - i; ++q)
            {
                int j = p + q;
                double term =
                    ((p % 2) ? -1.0 : 1.0) *
                    binom(i, p) *
                    binom(4 - i, q);
                c[i][j] += term;
            }
        }
    }
    // Build discrete numerator and denominator
    for (int j = 0; j <= 4; ++j)
    {
        for (int i = 0; i <= 4; ++i)
        {
            Nb[j] += num[i] * pow(k, i) * c[i][j];
            Da[j] += den[i] * pow(k, i) * c[i][j];
        }
    }

    // Normalize so A[0] = 1
    double a0 = Da[0];
    for (int i = 0; i < 5; ++i)
    {
        _Bcoef[i] = Nb[i] / a0;
        _Acoef[i] = Da[i] / a0;
    }
}

double FILTER::step(double x, bool reset_b)
{
    if (reset_b)
    {
        resetHist(x);
    }

    // Shift histories
    for (int i = 4; i > 0; --i)
    {
        _x_hist[i] = _x_hist[i - 1];
        _y_hist[i] = _y_hist[i - 1];
    }
    _x_hist[0] = x;

    // Compute output
    double y = 0.0;

    // Feedforward
    for (int i = 0; i < 5; ++i)
        y += _Bcoef[i] * _x_hist[i];

    // Feedback (skip A[0] = 1)
    for (int i = 1; i < 5; ++i)
        y -= _Acoef[i] * _y_hist[i];

    _y_hist[0] = y;
    return y;
}

int FILTER::binom(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    int r = 1;
    for (int i = 1; i <= k; ++i)
        r = r * (n - (k - i)) / i;
    return r;
}
