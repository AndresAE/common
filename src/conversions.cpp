#include "conversions.hpp"

namespace common
{

    // ---------------- Angle ----------------

    double Conversions::deg2rad(double deg)
    {
        return deg * 0.017453292519943295; // π/180
    }

    double Conversions::rad2deg(double rad)
    {
        return rad * 57.29577951308232; // 180/π
    }

    // ---------------- Speed ----------------

    double Conversions::mps2knots(double mps)
    {
        return mps * 1.9438444924406046;
    }

    double Conversions::knots2mps(double knots)
    {
        return knots * 0.5144444444444444;
    }

    // ---------------- Pressure ----------------

    double Conversions::pa2psi(double pa)
    {
        return pa * 0.00014503773773;
    }

    double Conversions::psi2pa(double psi)
    {
        return psi * 6894.757293168;
    }

    // ---------------- Length ----------------

    double Conversions::meters2feet(double m)
    {
        return m * 3.280839895013123;
    }

    double Conversions::feet2meters(double ft)
    {
        return ft * 0.3048;
    }

} // namespace common
