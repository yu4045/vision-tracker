//普通装甲
#pragma once
#include"TrackingBase/TrackingBase.hpp"

namespace rm//继承父类的命名空间
{
class ArmorTarget : public  TrackingBase{
    public:
    //构造函数声明变量传递父类的变量
    ArmorTarget(int id1,TargetType type1,double x1,double y1);
    void update(const Observation& obs,double dt) override;//这里应该是通过传进来的obs数据包更新
};
}

