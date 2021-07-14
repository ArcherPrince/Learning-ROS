#include "ros/ros.h"

/*
    演示参数查询
    实现：
        方法一：ros::NodeHandle---------------------------
        param(键,默认值) 
            存在，返回对应结果，否则返回默认值

        getParam(键,存储结果的变量)
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamCached键,存储结果的变量)--提高变量获取效率
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamNames(std::vector<std::string>)
            获取所有的键,并存储在参数 vector 中 

        hasParam(键)
            是否包含某个键，存在返回 true，否则返回 false

        searchParam(参数1，参数2)
            搜索键，参数1是被搜索的键，参数2存储搜索结果的变量(保存键的名称)
        
        方法二：ros::param--------------------------------
                
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "get_param_cpp");

    ros::NodeHandle nh;

    // 使用NodeHandle实现查询-------------------------
    // 1.param(key, value)
    double radius = nh.param("radius", 0.5); // 如果没有则返回0.5
    ROS_INFO("radius = %.2f", radius);
    // 2.getParam()
    double radius2 = 0;
    // bool result = nh.getParam("radiusxxx", radius2);
    // 3.getParamCached
    bool result = nh.getParamCached("radius", radius2);
    if(result){
        ROS_INFO("获取的半径是：%.2f", radius2);
    }else{
        ROS_INFO("被查询的变量不存在！");
    }
    // 4.getParamNames
    // std::vector<std::string> names;
    // nh.getParamNames(names);
    // for(auto &&name : names){
    //     ROS_INFO("get到的变量名称为：%s", name.c_str());
    // }
    // 5.hasParam
    // bool flag1 = nh.hasParam("radius");
    // bool flag2 = nh.hasParam("xxx");
    // ROS_INFO("radius存在吗？ 答：%d", flag1);
    // ROS_INFO("xxx存在吗？ 答：%d", flag2);
    // 6.searchParam
    // std::string key;
    // nh.searchParam("radius", key);
    // ROS_INFO("搜索结果：%s", key.c_str());

    // 使用ros::param实现查询---------------------------
    double rad = ros::param::param("radiusxx", 100.4);
    ROS_INFO("rad = %.2f", rad);

    std::vector<std::string> names_param;
    ros::param::getParamNames(names_param);
    for(auto && name : names_param){
        ROS_INFO("get到的变量名称为：%s", name.c_str());
    }

    return 0;
}
