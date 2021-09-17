#include "ros/ros.h"
#include "tf2_ros/transform_listener.h" //订阅对象
#include "tf2_ros/buffer.h" //订阅数据缓存成buffer 二者结合使用
#include "geometry_msgs/PointStamped.h" //坐标点对象
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
/* 
    需求：订阅发布的坐标系相对关系 并传入一个坐标点 调用tf实现转换

    流程：
    1、头文件
    2、初始化 订阅方的NodeHandle()是必须的
    3、创建订阅对象 ---->订阅坐标系相对关系
    4、组织一个坐标点数据
    5、转换算法 调用tf内置实现
    6、输出结果
 */
int main(int argc, char *argv[])
{
    // 2、初始化 订阅方的NodeHandle()是必须的
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_sub");
    ros::NodeHandle nh;
    // 3、创建订阅对象 ---->订阅坐标系相对关系
        // 3.1 创建buffer缓存
    tf2_ros::Buffer buffer;
        // 3.2 创建监听对象（存入buffer）
    tf2_ros::TransformListener listener(buffer);
    // 4、组织一个坐标点数据
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "radar";
    ps.header.stamp = ros::Time::now();
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    // 添加休眠
    // ros::Duration(2).sleep();
    // 5、转换算法 调用tf内置实现
    ros::Rate rate(10);
    while (ros::ok)
    {
        //核心逻辑----将ps转换成相对于base_link的坐标点
        geometry_msgs::PointStamped ps_out;
        
        /*
            调用了buffe的转换函数：transform
            参数1：被转换的坐标点
            参数2：目标坐标系
            返回值：输出的坐标点 

            注意：
            1、调用时必须包含头文件：tf2_geometry_msgs/tf2_getmetry_msgs.h
            2、运行时存在的问题，抛出一个异常：base_link不存在
                原因：订阅数据是耗时操作 可能在调用transform函数时 消息还没有订阅到 因此出现异常
                解决：方案一：在调用transform之前休眠一段时间 
                     方案二：异常处理(推荐)

         */
        try //异常处理
        {
            ps_out = buffer.transform(ps, "base_link"); // ！！！！！！核心代码
            // 6、输出结果
            ROS_INFO("转换后的坐标值：(%.2f, %.2f, %.2f), 参考的坐标系：%s", 
                        ps_out.point.x, 
                        ps_out.point.y, 
                        ps_out.point.z, 
                        ps_out.header.frame_id.c_str());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            ROS_INFO("异常消息：%s", e.what());
        }
        rate.sleep();
        ros::spinOnce();
    }
    
    
    return 0;
}
