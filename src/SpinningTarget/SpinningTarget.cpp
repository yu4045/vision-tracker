#include "SpinningTarget/SpinningTarget.hpp"

namespace rm
{
    SpinningTarget::SpinningTarget(int id1,TargetType type1,double x1,double y1,double angle1)
        : TrackingBase(id1,type1,x1,y1)
        {
            angle = angle1;
            angular_velocity=0;
            predicted_angle=0;

        }
    void SpinningTarget::update(const Observation& obs,double dt){
        id=obs.id;
        type=obs.type;
        if(status == TargetStatus::LOST){
            velocity_x=0;
            velocity_y=0;
            angular_velocity = 0;
            angle = obs.angle;
            x=obs.x;
            y=obs.y;
        }
        else{
            double x1=x;
            double y1=y;//存储老坐标
            double angle1=angle;
            x=obs.x;
            y=obs.y;
            angle = obs.angle;
            velocity_x=(x-x1)/dt;
            velocity_y=(y-y1)/dt;
            angular_velocity=(angle-angle1)/dt;
            
        }
        predicted_x = x+velocity_x*dt;
        predicted_y = y+velocity_y*dt;
        predicted_angle = angle+angular_velocity*dt;
        missed_count = 0;//若接受到新坐标，说明没丢失
        status=TargetStatus::TRACK;//
    }
}
