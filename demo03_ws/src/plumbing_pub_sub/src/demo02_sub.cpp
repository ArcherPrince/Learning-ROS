#include "ros/ros.h"
#include "std_msgs/String.h"

/**
 * 订阅方实现：
 *  1 包含头文件
 *      ROS中的文本类型---> std_msgs/String.h
 *  2 初始化ROS节点
 *  3 创建节点句柄
 *  4 创建订阅者对象
 *  5 处理订阅到的数据
 **/

// 回调函数
void doMsg(const std_msgs::String::ConstPtr &msg){ // 参数：消息指针的引用
    ROS_INFO("翠花订阅的数据：%s", msg->data.c_str());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
//  2 初始化ROS节点
    ros::init(argc, argv, "listener"); // 节点名不能和发布者同名
//  3 创建节点句柄
    ros::NodeHandle nh;
//  4 创建订阅者对象
    ros::Subscriber sub = nh.subscribe("House", 10, doMsg); // 订阅者关注的话题需与发布者的对应
    //                               可以不添加泛型 可以自动根据收到的消息推断类型
//  5 处理订阅到的数据
    // (必需！！！)
    ros::spin(); // 进入死循环 在回调函数队列中不断执行回调函数
    /**
     * ros::spin() will enter a loop, pumping callbacks.  With this version, all
     * callbacks will be called from within this thread (the main one).  ros::spin()
     * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
    */

    return 0;
}
