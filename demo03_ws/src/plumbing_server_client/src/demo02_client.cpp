#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"

/*
    客户端：提交两个整数 并处理响应的结果
    1.包含头文件
    2.初始化ROS节点
    3.创建节点句柄
    4.实例化客户端对象
    5.提交请求并处理响应

    实现参数的动态提交：
        1.格式： rosrun 包名 节点名 参数1 参数2
        2.节点执行时，需要获取命令中的参数 并组织进request
    
    问题：
        如果先启动客户端 会发生异常
    需求：
        先启动客户端 不要抛出异常 而是挂起等待服务器启动，再正常请求
    解决：
        再ROS提供了内置函数 可以让客户端启动后挂起 等待服务器启动
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    // 优化实现  获取命令行中的参数
    if(argc != 3){
        ROS_INFO("提交的参数个数错误！");
        return 1;
    }
    // 2.初始化ROS节点
    ros::init(argc, argv, "User");
    // 3.创建节点句柄
    ros::NodeHandle nh;
    // 4.实例化客户端对象(无回调函数)
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addInts");
    // 5.提交请求并处理响应
    plumbing_server_client::AddInts ai;
    //  5.1 组织请求
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]); 
    //  5.2 处理响应(访问服务器之后才有响应)
    // 调用判断服务器状态的函数
    // function1
    // client.waitForExistence(); // 等待并挂起
    // function2
    ros::service::waitForService("addInts");

    bool flag = client.call(ai); // 自动将结果封装到response
    if(flag){
        ROS_INFO("响应成功");
        //获取结果
        ROS_INFO("响应结果 = %d", ai.response.sum);
    }else{
        ROS_INFO("处理失败...");
    }

    return 0;
}
