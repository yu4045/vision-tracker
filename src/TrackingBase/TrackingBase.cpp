#include "TrackingBase/TrackingBase.hpp"

namespace rm
{
//构造函数的实现
    TrackingBase::TrackingBase(int id1,TargetType type1,double x1,double y1)
    {
        id = id1;
        type = type1;
        x = x1;
        y = y1;
        status = TargetStatus::TRACK;
        missed_count=0;
        velocity_x=0;
        velocity_y=0;
        predicted_x=0;
        predicted_y=0;
         
    }
//GetSnapshot快照函数的实现
    TargetSnapshot TrackingBase::getSnapshot() const
    {
        TargetSnapshot snap;
        snap.status=status;
        snap.type=type;
        snap.id=id;
        snap.x=x;
        snap.y=y;      
        snap.velocity_x=velocity_x;      
        snap.velocity_y=velocity_y;     
        snap.predicted_x=predicted_x;      
        snap.predicted_y=predicted_y;
        snap.angle=0;           
        snap.angular_velocity=0;
        snap.predicted_angle=0;  
        snap.missed_count=missed_count;
        return snap;
    }
} 
