#include "ros/ros.h"

/*
    修改参数服务器中的乌龟GUI背景色
*/

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "change_bgColor");
    //方式一：
    // ros::param::set("/turtlesim/background_b", 0);
    // ros::param::set("/turtlesim/background_g", 0);
    // ros::param::set("/turtlesim/background_r", 0);
    //方式二：
    ros::NodeHandle nh("turtlesim");//可以在创建句柄时设置命名空间 这样往后设置参数就不用写命名空间了
    nh.setParam("background_b", 255);
    nh.setParam("background_g", 255);
    nh.setParam("background_r", 255);
    return 0;
}
