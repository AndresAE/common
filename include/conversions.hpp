#pragma once

namespace common
{

    class Conversions
    {
    public:
        // angle conversions
        static constexpr double _PI = 3.141592653589793;
        static constexpr double CELSIUS_TO_KELVIN = 273.15;
        static double deg2rad(double deg);
        static double rad2deg(double rad);
        static double deg2sc(double deg);
        static double sc2deg(double sc);

        // speed conversions
        static double mps2fps(double mps);
        static double fps2mps(double fps);
        static double mps2knots(double mps);
        static double knots2mps(double knots);

        // pressure conversions
        static double pa2psi(double pa);
        static double psi2pa(double psi);
        static double psf2psi(double psf);
        static double psi2psf(double psi);
        static double pa2psf(double pa);
        static double psf2pa(double psf);

        // length conversions
        static double m2ft(double m);
        static double ft2m(double ft);
        static double ft2nmi(double ft);
        static double nmi2ft(double nmi);
        static double ft2mi(double ft);
        static double mi2ft(double ft);

        // acceleration
        static double g2sfps2(double g);
        static double fps2_2_g(double fps2);

        // time
        static double min2sec(double min);
        static double ms2sec(double ms);
        static double mus2sec(double mus);
        static double sec2min(double sec);
        static double sec2ms(double sec);
        static double sec2mus(double sec);

        // temperature
        static double celsius2fahrenheit(double c);
        static double fahrenheit2celsius(double f);

        // density
        static double kgm3_2_slugft3(double kgm3);
        static double slugft3_2_kgm3(double slugft3);
    };

} // namespace common