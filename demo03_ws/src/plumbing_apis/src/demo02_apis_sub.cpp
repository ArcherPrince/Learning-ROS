#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr & msg){
    ROS_INFO("订阅到的信息为：%s", msg->data.c_str());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "subscriber", ros::init_options::AnonymousName);

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("person_info", 10, doMsg);

    ros::spin();
    ROS_INFO("spin后的语句"); //进入自身的循环 无限执行回调函数 且不会执行后面的语句

    return 0;
}
