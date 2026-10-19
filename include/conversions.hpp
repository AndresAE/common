#pragma once

namespace common {

class Conversions {
public:
    // Angle conversions
    static double deg2rad(double deg);
    static double rad2deg(double rad);

    // Speed conversions
    static double mps2knots(double mps);
    static double knots2mps(double knots);

    // Pressure conversions
    static double pa2psi(double pa);
    static double psi2pa(double psi);

    // Length conversions
    static double meters2feet(double m);
    static double feet2meters(double ft);
};

} // namespace common