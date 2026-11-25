#pragma once
#include "cmn.hpp"

namespace common
{

    class Transform
    {
    public:
        CMN::matrix euler2quat(CMN::matrix quat, CMN::matrix euler);
        CMN::matrix quat2euler(CMN::matrix euler, CMN::matrix quat);
        CMN::matrix getNed2body(CMN::matrix ned2body, double roll_d, double pitch_d, double yaw_d);
        CMN::matrix getBody2ned(CMN::matrix body2ned, double roll_d, double pitch_d, double yaw_d);
        CMN::matrix getNed2ecef(CMN::matrix ned2ecef, double latG_d, double lon_d);
        CMN::matrix getEcef2ned(CMN::matrix ecef2ned, double latG_d, double lon_d);
        CMN::matrix getBody2ecef(CMN::matrix body2ecef, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d);
        CMN::matrix getEcef2body(CMN::matrix ecef2body, double latG_d, double lon_d, double roll_d, double pitch_d, double yaw_d);
    };

} // namespace common