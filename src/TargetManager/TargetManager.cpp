#include "TargetManager/TargetManager.hpp"

namespace rm{
    Result TargetManager::onFrame(const InputFrame&frame)//创建onFrame函数
    {
        if(frame.frame_id <= last_frame_id||frame.timestamp_ns <= last_timestamp_ns)
        {
            return Result{false, frame.frame_id, {}, 0, 0, 0, 0};
        }
        //到这里说明这一帧帧号和帧时间戳合法
        double dt=(frame.timestamp_ns - last_timestamp_ns)/1e9;
        if(dt <= 0) dt = 0.1;//排除dt过小算出0的情况

        std::vector<int> current_frame_ids;//记录id

        for(const auto&obs : frame.observations)//auto自己猜类型 从frame里拿变量出来起名叫obs
        {
            if (obs.id < 0) return Result{false, frame.frame_id, {}, 0, 0, 0, 0};
            for(int i=0;i<current_frame_ids.size();i++)
            {
                if(obs.id == current_frame_ids[i])
                {
                    return Result{false, frame.frame_id, {}, 0, 0, 0, 0};
                }
            }
                //找了一遍都没有相同的
            current_frame_ids.push_back(obs.id);//把这个id放到数组最后面
            //判断观测类型和目标类型是否一致 
            for(const auto&t : targets)
            {
                if(obs.id == t->getId() && obs.type != t->getType())
                {
                    return Result{false, frame.frame_id, {}, 0, 0, 0, 0};
                }
            }
            //判断完后接下来更新旧目标或者创建新目标
            bool found = false;
            for(const auto& t : targets)
            {
                if(t ->getId() == obs.id)
                {
                    found = true;//找到
                    t->update(obs, dt);//找到了让它自己更新状态就可以了，对于数据它自己会更新
                    break;
                }
            }
            //没找到就创建新目标
            if(found == false)
            {
                if (obs.type == TargetType::ARMOR) 
                { 
                    ArmorTarget* new_target = new ArmorTarget(obs.id,obs.type,obs.x,obs.y);
                    targets.push_back(new_target);
                }
                else if (obs.type == TargetType::SPINNING) 
                { 
                    SpinningTarget* new_target = new SpinningTarget(obs.id,obs.type,obs.x,obs.y,obs.angle);
                    targets.push_back(new_target);
                }
            }    
        }
        last_frame_id=frame.frame_id;
        last_timestamp_ns=frame.timestamp_ns;
        
        std::vector<TargetSnapshot> snapshots;
        int genzong = 0;
        int diushi = 0;
        int putong = 0;
        int xuanzhuan = 0;//观测到目标的特征的统计值
        //创建完目标我要制作我的result最后提交给main函数
        for(const auto& t : targets)
        {
            //判断目标是否丢失
            bool seen = false;//
            for(int id : current_frame_ids)//建立变量id，遍历这帧的id数组
            {
                if(t->getId() == id)
                {
                    seen = true;//看到了，即这个目标有对应的id，在这帧里面没有丢失
                }
            }
            if(seen == false)//如果目标在这帧丢了
            {
                if(t->getStatus() == TargetStatus::TRACK)//活着的再去调整miss_count
                {
                    if (t->getType() == TargetType::ARMOR)//普通
                    {
                        t->addMissedCount();
                        if(t->getMissedCount()>=3)
                        {
                            t->markLost();
                        }
                    }
                    else//旋转
                    {
                        t->addMissedCount();
                        if(t->getMissedCount()>=5)
                        {
                            t->markLost();
                        }
                    }
                }
            }
            //没丢的话
            snapshots.push_back(t->getSnapshot());//对目标使用快照函数
            if (t->getStatus() == TargetStatus::TRACK) genzong++;
            else diushi++;
            if (t->getType() == TargetType::ARMOR) putong++;
            else xuanzhuan++;
        }    
        return Result{true, frame.frame_id, snapshots, genzong, diushi, putong, xuanzhuan};
            //快照能保证数据安全和格式化输出说是。为什么？
            //提交的是快照而不是指针，因此想修改也修改的是快照，对原函数没影响，实现了数据隔离
            //格式化输出就是学长写的targetsnapshot结构体，输出了这个快照不管是哪个装甲格式都一样了
    }
}

