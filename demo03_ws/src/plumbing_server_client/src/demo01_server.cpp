#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
/*
    服务端实现：解析客户端提交的数据 运算产生响应
    1.包含头文件
    2.初始化ROS节点
    3.创建节点句柄
    4.实例化服务对象
    5.处理请求并产生响应
    6.spin()
*/

// 注意这里的回调函数返回值是bool
bool doNums(plumbing_server_client::AddInts::Request &req, 
            plumbing_server_client::AddInts::Response &res){
    // 1. 处理请求
    int num1 = req.num1;
    int num2 = req.num2;
    ROS_INFO("收到的请求数据：num1 = %d, num2 = %d", num1, num2);
    // 2. 组织响应
    int sum = num1 + num2;
    res.sum = sum;
    ROS_INFO("求和结果：sum = %d", sum);

    return true;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    
    // 2.初始化ROS节点
    ros::init(argc, argv, "Computer");
    // 3.创建节点句柄
    ros::NodeHandle nh;
    // 4.实例化服务对象
    ros::ServiceServer server = nh.advertiseService("addInts", doNums);
    // 5.处理请求并产生响应
    ROS_INFO("服务器已启动...");
    // 6.spin()
    ros::spin();

    return 0;
}
