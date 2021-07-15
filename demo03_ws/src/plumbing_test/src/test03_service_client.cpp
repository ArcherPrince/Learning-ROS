#include "ros/ros.h"
#include "turtlesim/Spawn.h"

/*
    需求：向服务端发送请求，生成新的小乌龟
        话题：/spawn
        消息：turtlesim/Spawn
    
    实现：
        创建客户端对象
        组织数据并发送
        处理响应
*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "service_call");

    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    //组织数据并发送数据
    //1.组织数据
    turtlesim::Spawn spawn;
    spawn.request.x = 1.0;
    spawn.request.y = 2.0;
    spawn.request.theta = -1.57;
    spawn.request.name = "hahaha";
    //2.发送请求
    // 判断服务器状态
    // ros::service::waitForService("/spawn");
    client.waitForExistence();
    bool flag = client.call(spawn); // flag用来判断响应状态 其结果被设置到spawn对象中
    //处理响应
    if(flag){
        ROS_INFO("乌龟生成成功，名字叫：%s", spawn.response.name.c_str());
    }else{
        ROS_INFO("乌龟生成失败！");
    }


    return 0;
}
