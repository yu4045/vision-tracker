#pragma once
#include "data_types.hpp" 
#include "ArmorTarget/ArmorTarget.hpp"
#include "SpinningTarget/SpinningTarget.hpp"


namespace rm
{
class TargetManager {
public:
Result onFrame(const InputFrame& frame);
    
private:
    int last_frame_id = -1;
    long long last_timestamp_ns = -1;//时间戳很小所以类型不用double而用longlong
    std::vector<TrackingBase*> targets;//创建一个装着指向Trackingbase的指针数组
};
}
