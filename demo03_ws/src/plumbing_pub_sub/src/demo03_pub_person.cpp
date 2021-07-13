#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ROS_INFO("这里是消息的发布方。");
    // 1. 包含头文件
    // 2. 初始化ROS节点
    ros::init(argc, argv, "Teacher");
    // 3. 创建节点句柄
    ros::NodeHandle nh;
    // 4. 创建发布者对象
    ros::Publisher pub = nh.advertise<plumbing_pub_sub::Person>("student_info", 10);
    // 5. 编写发布逻辑（发布Person类型）
    // 5.1 创建数据
    plumbing_pub_sub::Person person;
    person.name = "张三";
    person.age = 17;
    person.height = 1.80;
    // 5.2 设置发布频率
    ros::Rate rate(1);
    // 5.3 循环发布
    while (ros::ok)
    {
        person.age += 1;
        // 核心： 数据发布
        pub.publish(person);
        ROS_INFO("发布的消息：%s, %d, %.2f", person.name.c_str(), person.age, person.height);

        rate.sleep(); //休眠

        ros::spinOnce();
    }
    


    return 0;
}
