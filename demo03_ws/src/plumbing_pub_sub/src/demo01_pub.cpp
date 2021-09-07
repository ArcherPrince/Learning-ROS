#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

/**
 * 发布方实现：
 *  1 包含头文件
 *      ROS中的文本类型---> std_msgs/String.h
 *  2 初始化ROS节点
 *  3 创建节点句柄
 *  4 创建发布者对象
 *  5 编写发布逻辑并发布数据
 **/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 1.初始化ROS节点
    ros::init(argc, argv, "talker"); // 节点名不能有空格 不能重名 必须唯一
    // 2.实例化 节点句柄
    ros::NodeHandle nh;
    // 3.实例化 发布者对象
    // 泛型: 发布的消息类型
    //参数1: 要发布到的话题
    //参数2: 队列中最大保存的消息数，超出此阀值时，先进的先销毁(时间早的先销毁)
    ros::Publisher pub = nh.advertise<std_msgs::String>("House", 10);
    // 4.编写发布逻辑并发布数据
    // 要求以10Hz的频率发布出去 并且文本和要添加编号
    // 先创建被发布的消息
    std_msgs::String msg;
    // 发布频率
    ros::Rate rate(10);
    // 设置编号
    int count = 0;
    // 5.编写循环 循环中发布数据
    ros::Duration(3).sleep(); // 延迟3秒再发布数据
    while (ros::ok) // 节点活着 循环继续
    {
        count ++;
        // msg.data = "hello";
        // 实现字符串拼接数字
        std::stringstream ss;
        ss << "hello ---->" << count;
        msg.data = ss.str(); // 将stringstream提取为字符串
        
        pub.publish(msg);

        ROS_INFO("发布的数据是: %s", ss.str().c_str());

        rate.sleep();
        ros::spinOnce(); // 官方建议添加 处理回调函数 调用回调函数队列中第一个callback函数
    }

    

    return 0;
}
