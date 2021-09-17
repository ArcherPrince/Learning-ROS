#include "ros/ros.h"

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc, argv, "hello");
    ros::NodeHandle nh;

    /*
        使用ros::param设置参数
    */
    // 1.全局
    ros::param::set("/radiusA", 100);
    // 2.相对
    ros::param::set("radiusB", 101);
    // 3.私有
    ros::param::set("~radiusC", 102);
    /*
        使用nh设置参数
    */
   nh.setParam("/radius_nh_A", 1000);
   nh.setParam("radius_nh_B", 1000);
   ros::NodeHandle nh_private("~");
    nh_private.setParam("radius_nh_C", 1200);

    return 0;
}
