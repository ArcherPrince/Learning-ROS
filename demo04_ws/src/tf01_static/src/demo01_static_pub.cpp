#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/*
    需求：发布两个坐标系的相对关系

    流程：1、头文件
        2、初始化操作
        3、创建发布对象
        4、组织被发布的消息
        5、发布数据
        6、spin()
 */

int main(int argc, char *argv[])
{
    // 2、初始化操作
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_pub");
    // ros::NodeHandle nh;
    // 3、创建发布对象
    tf2_ros::StaticTransformBroadcaster pub;
    // 4、组织被发布的消息
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link"; //相对坐标系关系中 被参考的那一个
    tfs.child_frame_id = "radar";
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;
      // 需要根据欧拉角转换
    tf2::Quaternion qtn; //创建四元数对象
        //设置欧拉角 该对象可以将欧拉角转化为四元数
    qtn.setRPY(0, 0, 0); // roll:翻滚值 pitch：俯仰 yaw：偏航 欧拉角的单位是弧度
    
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();
    // 5、发布数据
    pub.sendTransform(tfs);
    // 6、spin()
    ros::spin();
    /* code */
    return 0;
}
