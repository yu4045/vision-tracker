#include "ArmorTarget/ArmorTarget.hpp"

namespace rm
{
    //实现update函数
    ArmorTarget::ArmorTarget(int id1,TargetType type1,double x1,double y1)
        : TrackingBase(id1,type1,x1,y1){}
    void ArmorTarget::update(const Observation& obs,double dt){//&是引用 obs是我用的别名 dt是delra time，代表间隔时间
        //obs是学长给我的数据
        id=obs.id;
        type=obs.type;
        if(status == TargetStatus::LOST){
            velocity_x=0;
            velocity_y=0;
            x=obs.x;
            y=obs.y;
        }
        else{
            double x1=x;
            double y1=y;//存储老坐标
            x=obs.x;
            y=obs.y;
            velocity_x=(x-x1)/dt;
            velocity_y=(y-y1)/dt;
            //普通装甲没有角度
        }
        predicted_x = x+velocity_x*dt;
        predicted_y = y+velocity_y*dt;
        missed_count = 0;//若接受到新坐标，说明没丢失
        status=TargetStatus::TRACK;//
    }
}
