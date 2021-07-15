#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

/*
    需求：发布速度消失控制乌龟运动
        话题：/turtle1/cmd_vel
        消息：geometry_msgs/Twist

    1.包含头文件
    2.初始化ros节点
    3.创建节点句柄
    4.创建发布对象
    5.发布逻辑
    6.spinOnce();
*/

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "my_control");

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate rate(10); //一秒十次

    geometry_msgs::Twist twist;
    // 线速度
    twist.linear.x = 1.0;
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    // 角速度
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = 1.0;

    while (ros::ok) // 节点不死
    {
        pub.publish(twist);
        //休眠
        rate.sleep();

        ros::spinOnce();
    }
    

    return 0;
}
