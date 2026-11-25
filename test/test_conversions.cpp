#include "../include/conversions.hpp"
#include "minitest.hpp"

using namespace common;
using namespace minitest;

int main()
{

    assert_near(Conversions::deg2rad(180.0), 3.141592653589793, 1e-12,
                "deg2rad(180)");

    assert_near(Conversions::rad2deg(3.141592653589793), 180.0, 1e-12,
                "rad2deg(pi)");

    assert_near(Conversions::deg2sc(180), 1.0, 1e-12,
                "deg2sc(pi)");

    assert_near(Conversions::sc2deg(1.0), 180.0, 1e-12,
                "sc2deg(pi)");

    assert_near(Conversions::m2ft(1.0), 3.280839895013123, 1e-12,
                "m2ft(1)");

    assert_near(Conversions::ft2m(3.280839895013123), 1.0, 1e-12,
                "ft2m(3.280839...)");

    assert_near(Conversions::mps2fps(1.0), 3.280839895013123, 1e-12,
                "mps2fps(1)");

    assert_near(Conversions::fps2mps(3.280839895013123), 1.0, 1e-12,
                "fps2mps(3.280839...)");

    assert_near(Conversions::psf2psi(144.0), 1.0, 1e-12, "psf2psi(144)");
    assert_near(Conversions::psi2psf(1.0), 144.0, 1e-12, "psi2psf(1)");
    assert_near(Conversions::pa2psf(47.88025898033584), 1.0, 1e-12,
                "pa2psf(47.88025898033584)");
    assert_near(Conversions::psf2pa(1.0), 47.88025898033584, 1e-12,
                "psf2pa(1)");

    assert_near(Conversions::ft2nmi(6076.115485564304), 1.0, 1e-12,
                "ft2nmi(6076.115485564304)");
    assert_near(Conversions::nmi2ft(1.0), 6076.115485564304, 1e-12,
                "nmi2ft(1)");
    assert_near(Conversions::ft2mi(5280.0), 1.0, 1e-12, "ft2mi(5280)");
    assert_near(Conversions::mi2ft(1.0), 5280.0, 1e-12, "mi2ft(1)");

    assert_near(Conversions::g2sfps2(1.0), 32.17404855643044, 1e-12,
                "g2sfps2(1)");
    assert_near(Conversions::fps2_2_g(32.17404855643044), 1.0, 1e-12,
                "fps2_2_g(32.17404855643044)");

    assert_near(Conversions::min2sec(1.0), 60.0, 1e-12, "min2sec(1)");
    assert_near(Conversions::ms2sec(1000.0), 1.0, 1e-12, "ms2sec(1000)");
    assert_near(Conversions::mus2sec(1000000.0), 1.0, 1e-12,
                "mus2sec(1000000)");
    assert_near(Conversions::sec2min(60.0), 1.0, 1e-12, "sec2min(60)");
    assert_near(Conversions::sec2ms(1.0), 1000.0, 1e-12, "sec2ms(1)");
    assert_near(Conversions::sec2mus(1.0), 1000000.0, 1e-12,
                "sec2mus(1)");

    summary();
    return tests_failed;
}
