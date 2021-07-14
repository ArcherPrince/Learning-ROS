#include "ros/ros.h"

/*
    需要实现参数的新增与修改
    需求：
        设置机器人共享参数：类型、半径
        修改半径 0.15-->0.2米
    实现：
        方法一：ros::NodeHandle
                setParam("键", 值);
        方法二：ros::param
                set("键", 值);
        修改 只需继续调用setParam或set函数 保证键是已经存在的 值会自动覆盖
*/
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "set_param_cpp");

    ros::NodeHandle nh;
    // 新增参数-----------------------------------------
    // 方法一：
    nh.setParam("type", "yellow_car");
    nh.setParam("radius", 0.15);
    // 方法二：
    ros::param::set("type_param", "white_car");
    ros::param::set("radius_param", 0.15);
    // 修改参数-----------------------------------------
    // 方法一：
    nh.setParam("radius", 0.2);
    // 方法二：
    ros::param::set("radius_param", 0.25);

    return 0;
}
