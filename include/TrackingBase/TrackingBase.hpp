//  Trackingbase 跟踪基类
//头文件只声明变量，具体操作到cpp再写
//data type 有 targettype目标类型 observation观测的目标坐标，板子状态 
//inputframe输入帧 targetsnapshot目标快照（用于结果输出）

//test frame 有 testframes函数返回数据，28帧测试序
#pragma once
#include "data_types.hpp"

namespace rm//学长的命名空间也是rm
{
class TrackingBase {
protected://跟踪基类里应该是普通和旋转装甲都有的变量，里面的变量为成员变量
    int id;
    int missed_count;//丢失次数
    double x,y;
    double velocity_x,velocity_y;
    double predicted_x, predicted_y;//坐标xy xy方向速度，xy方向预测速度
    TargetType type;//目标类型
    TargetStatus status;//当前跟踪状态

public:
    TrackingBase(int id1,TargetType type1,double x1,double y1);//构造函数内的变量为参数
    
    virtual ~TrackingBase() = default;//声明一个空的析构函数
    //virtual能删除对象的时候既清理基类也调用子类的清理程序，防止内存泄漏说是
    virtual void update(const Observation& obs,double dt) = 0;
    
    TargetSnapshot getSnapshot() const;
    int getId() const { return id; }
    TargetType getType() const { return type; }
    TargetStatus getStatus() const{ return status; }//分别获得id 类型 状态的函数
    void addMissedCount() { missed_count++; }//增加丢失次数的函数
    int getMissedCount() const { return missed_count; }//用于判断的返回丢失次数的函数
    void markLost() //达到了设定丢失次数就调用的标记丢失函数
    {
        status = TargetStatus::LOST;
        x=0;
        y=0;
        velocity_x=0;
        velocity_y=0;
        predicted_x=0;
        predicted_y=0;
    }
};
}