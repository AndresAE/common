#include "conversions.hpp"

namespace common
{
    // angle
    double Conversions::deg2rad(double deg)
    {
        return deg * 0.017453292519943295; // π/180
    }

    double Conversions::rad2deg(double rad)
    {
        return rad * 57.29577951308232; // 180/π
    }

    double Conversions::deg2sc(double deg)
    {
        return deg / 180; // 1/180
    }

    double Conversions::sc2deg(double sc)
    {
        return sc * 180; // 180
    }

    // speed
    double Conversions::mps2fps(double mps)
    {
        return mps * 3.280839895013123;
    }

    double Conversions::fps2mps(double fps)
    {
        return fps / 3.280839895013123;
    }

    double Conversions::mps2knots(double mps)
    {
        return mps * 1.9438444924406046;
    }

    double Conversions::knots2mps(double knots)
    {
        return knots * 0.5144444444444444;
    }

    // acceleration

    // pressure
    double Conversions::pa2psi(double pa)
    {
        return pa * 0.00014503773773;
    }

    double Conversions::psi2pa(double psi)
    {
        return psi * 6894.757293168;
    }

    double Conversions::psf2psi(double psf)
    {
        return psf / 144.0;
    }

    double Conversions::psi2psf(double psi)
    {
        return psi * 144.0;
    }

    double Conversions::pa2psf(double pa)
    {
        return pa * 0.020885434233150127;
    }

    double Conversions::psf2pa(double psf)
    {
        return psf * 47.88025898033584;
    }

    // length

    double Conversions::m2ft(double m)
    {
        return m * 3.280839895013123;
    }

    double Conversions::ft2m(double ft)
    {
        return ft * 0.3048;
    }

    double Conversions::ft2nmi(double ft)
    {
        return ft / 6076.115485564304;
    }

    double Conversions::nmi2ft(double nmi)
    {
        return nmi * 6076.115485564304;
    }

    double Conversions::ft2mi(double ft)
    {
        return ft / 5280.0;
    }

    double Conversions::mi2ft(double mi)
    {
        return mi * 5280.0;
    }

    // acceleration
    double Conversions::g2sfps2(double g)
    {
        return g * 32.17404855643044;
    }

    double Conversions::fps2_2_g(double fps2)
    {
        return fps2 / 32.17404855643044;
    }

    // time
    double Conversions::min2sec(double min)
    {
        return min * 60.0;
    }

    double Conversions::ms2sec(double ms)
    {
        return ms / 1000.0;
    }

    double Conversions::mus2sec(double mus)
    {
        return mus / 1000000.0;
    }

    double Conversions::sec2min(double sec)
    {
        return sec / 60.0;
    }

    double Conversions::sec2ms(double sec)
    {
        return sec * 1000.0;
    }

    double Conversions::sec2mus(double sec)
    {
        return sec * 1000000.0;
    }

    double Conversions::celsius2fahrenheit(double c)
    {
        return (c * 9.0 / 5.0) + 32.0;
    }

    double Conversions::fahrenheit2celsius(double f)
    {
        return (f - 32.0) * 5.0 / 9.0;
    }

    double Conversions::kgm3_2_slugft3(double kgm3)
    {
        return kgm3 * 0.00194032033;
    }

    double Conversions::slugft3_2_kgm3(double slugft3)
    {
        return slugft3 * 515.378818;
    }

} // namespace common
