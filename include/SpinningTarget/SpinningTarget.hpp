//旋转装甲

#pragma once
#include"TrackingBase/TrackingBase.hpp"

namespace rm
{
class SpinningTarget : public  TrackingBase{   
    public:
    SpinningTarget(int id1,TargetType type1,double x1,double y1,double angle);
    void update(const Observation& obs,double dt) override;//这里应该是通过传进来的obs数据包更新
    protected :
        protected :
        double angle;
        double angular_velocity;
        double predicted_angle;
};
}