#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

void doPerson(const plumbing_pub_sub::Person::ConstPtr &person){
    ROS_INFO("订阅的人的信息为：%s, %d, %.2f", person->name.c_str(), person->age, person->height);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    //1.初始化 ROS 节点
    ros::init(argc, argv, "Listener");
    //2.创建 ROS 句柄
    ros::NodeHandle nh;
    //3.创建订阅对象
    ros::Subscriber sub = nh.subscribe("student_info", 10, doPerson);
    //4.回调函数中处理 person
    ros::spin(); // 有回调函数必需

    
    return 0;
}
