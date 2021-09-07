#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    /*
        init函数
            作用：ROS初始化函数
            参数：
                1.argc ---封装实参的个数 n+1
                2.argv ---封装参数的数组
                3.name ---为节点命名 保证唯一性
                4.options ---节点启动选项

                返回值 void

            使用细节：
                argc与argv的使用：
                    按照ROS中特定格式传入参数 则ROS可以加以使用 

                options的使用
                    节点需要保证唯一 同一个节点不能重复启动
                    若有重名节点启动 原节点会被挤掉

                    需求：
                        某些特定场景需要一个节点多次启动
                        ros::init_options::AnonymousName 创建ROS节点时 会在自定义节点名称后加入随机数 从而避免重名问题
    */
    ros::init(argc, argv, "publisher", ros::init_options::AnonymousName); // 可以解决重名问题 节点名后加随机数

    
    ros::NodeHandle nh;
    /*
        作用：创建发布者对象
        模板：被发布消息的类型
        参数：
            1.话题名称
            2.队列长度
            3.latch（可选）：默认为false 
                        若设置为true 则会保存发布方的最后一条消息 并且新的订阅者连接到发布者时 这条消息会发布给订阅者
        使用细节：
            在导航场景下 地图信息基本不变 若设置为固定频率发布地图 效率太低
            可以将latch设置为true 只发布一次地图信息 当有新的订阅者连接时 则将地图数据发布出去
    */
    ros::Publisher pub = nh.advertise<std_msgs::String>("person_info", 10, true);

    ros::Rate rate(1);

    std_msgs::String msg;

    ros::Duration(1).sleep();

    int count = 0;

    while(ros::ok){
        if(count >= 10){
            ros::shutdown();
        }
        count += 1;
        std::stringstream ss;
        ss << "I have a house " << count;
        msg.data = ss.str();

        // if(count <= 5){
        //     pub.publish(msg);
        ROS_INFO("发布的数据是：%s", ss.str().c_str());
        // }
        
        pub.publish(msg);
        
        rate.sleep();
        ros::spinOnce(); // 用于执行回调函数 只回调一次 然后执行后面的语句
        // ROS_INFO("一轮回调执行完毕。");
    }

    ros::shutdown();
    
    return 0;
}
