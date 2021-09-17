#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc, argv, "hello");
    // ros::NodeHandle nh;

    //核心：设置不同类型的话题
    //1 全局 ----话题名称需要以斜杠‘/’开头（也可以设置自己的命名空间） 和节点（命名空间以及名称）没有任何关系
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/chat", 1000);
    // ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chat", 1000);
    //2 相对 ----非‘/’开头
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chat", 1000);
    // ros::Publisher pub = nh.advertise<std_msgs::String>("yyy/zzz/hhh/qqq/kkk/chat", 1000);
    
    //3 私有 ---需要创建特定NodeHandle "~"
    ros::NodeHandle nh("~");
    // ros::Publisher pub = nh.advertise<std_msgs::String>("chat", 1000);
    ros::Publisher pub = nh.advertise<std_msgs::String>("/yyy/chat", 1000);

    // 注意： 如果私有的nh创建的话题以‘/’开头 则为全局话题
    // 全局话题优先级更高
    while (ros::ok())
    {
        /* code */
    }
    

    return 0;
}
