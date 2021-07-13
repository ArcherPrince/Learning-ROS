#include "ros/ros.h"

int main(int argc, char *argv[])
{
    /* code */
    // 解决乱码问题
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello_c");
    ROS_INFO("haha, 哈哈哈");


    return 0;
}
