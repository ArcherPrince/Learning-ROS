#include "ros/ros.h"


/*
    需求1：演示时间相关操作（获取当前时刻 + 设置指定时刻）
    实现：
        1.准备操作（头文件 节点 ....）
        2.获取当前时刻
        3.设置指定时刻

    需求2：让程序执行中停顿5秒
    实现：
        1.创建持续时间对象
        2.休眠

    需求3：已知程序开始运行的时刻和运行时间 求结束时刻
    实现：
        1.获取开始执行时刻
        2.设置运行时间
        3.计算结束时刻 = 开始 + 持续时间

    需求4：每隔一秒钟 输出一段文本
    实现：
        方法一、使用ros::Rate()
        方法二、定时器
*/

void cb(const ros::TimerEvent &event){
    // ROS_INFO("hahaha");
    ROS_INFO("函数被调用的时刻：%.2f", event.current_real.toSec());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    //-----------------------------------------------------------------
    ROS_INFO("-------------时刻--------------");
    // 1.准备操作（时间相关头文件已经在ros.h中了）
    ros::init(argc, argv, "hello_time");
    ros::NodeHandle nh; //此步骤必需!!!! 否则时间api调用失败
    // 2.获取当前时刻
    ros::Time right_now = ros::Time::now(); // 将当前时刻封装并返回 参考系:1970年1月1日 00:00:00
    ROS_INFO("当前时刻为：%.2f", right_now.toSec()); // 将时间转换为秒
    ROS_INFO("当前时刻为：%d", right_now.sec); // sec字段返回整形
    // 3.设置指定时刻
    ros::Time t1(20, 412342134);
    ros::Time t2(100.35);
    // ROS_INFO("t1 =  %.2f", t1.toSec());
    // ROS_INFO("t1 =  %.2f", t2.toSec());

    //-----------------------------------------------------------------
    ROS_INFO("------------持续时间-------------");
    // auto start = ros::Time::now();
    // ROS_INFO("开始休眠：%d", start.sec);

    // ros::Duration du(4.5);
    // du.sleep(); // 睡4.5秒
    // auto end = ros::Time::now();
    // ROS_INFO("休眠结束：%d", end.sec);
    // ROS_INFO("睡眠持续时间：%d", end.sec - start.sec);

    //-----------------------------------------------------------------
    ROS_INFO("------------时间运算-------------");
    // 时刻与持续时间的运算 加减都可以
    ros::Time begin = ros::Time::now();
    ros::Duration du1(5);
    ros::Time stop = begin + du1;
    ROS_INFO("开始时刻：%.2f", begin.toSec());
    ROS_INFO("结束时刻：%.2f", stop.toSec());
    // 时刻与时刻的运算
    // 只能减 不能加
    // 持续时间之间可加可减
    //-----------------------------------------------------------------
    ROS_INFO("------------定时器-------------");
    /* 创建定时器函数详情
        ros::Timer createTimer(ros::Duration period, // 时间间隔
                 const ros::TimerCallback &callback, // 回调函数
                 bool oneshot = false,               // 是否一次性
                 bool autostart = true)              // 是否自动启动
    */
    ros::Timer timer = nh.createTimer(ros::Duration(1), cb, false, false);
    timer.start(); //手动启动
    ros::spin(); //有回调函数就需要spin

    return 0;
}