/* 
    静态坐标变换发布方:
        发布关于 laser 坐标系的位置信息 


    所谓静态坐标变换，是指两个坐标系之间的相对位置是固定的 
    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建静态坐标转换广播器
        4.创建坐标系信息
        5.广播器发布坐标系信息
        6.spin()
*/


// 1.包含头文件
#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    // 2.初始化 ROS 节点
    ros::init(argc,argv,"static_brocast");

     
    ros::NodeHandle nh;


    // 3.创建静态坐标转换广播器
    tf2_ros::StaticTransformBroadcaster   broadcaster;

    // 4.创建坐标系信息  消息类型
    geometry_msgs::TransformStamped ts;

    //----设置头信息
    ts.header.seq = 100;  //可以不管
    ts.header.stamp = ros::Time::now();
    ts.header.frame_id = "base_link";  //相对坐标系中被参考的那个 



    //----设置子级坐标系
    ts.child_frame_id = "laser";
    
    //----设置子级相对于父级的偏移量 子级在父级坐标系下的坐标
    ts.transform.translation.x = 0.2;
    ts.transform.translation.y = 0.0;
    ts.transform.translation.z = 0.5;

    //----设置四元数:将 欧拉角数据转换成四元数
    tf2::Quaternion qtn;  //创建四元数对象
    qtn.setRPY(0,0,0);  //设置欧拉角，这个对象可以将欧拉角转化为四元数  单位弧度
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();


    ROS_INFO("输出父级坐标变换",ts.header.frame_id.c_str());
    ROS_INFO("输出父级坐标变换",ts.header.stamp);
    ROS_INFO("输出父级坐标变换",ts.transform.translation.x);
    // 5.广播器发布坐标系信息
    broadcaster.sendTransform(ts);
    

    ros::spin();
    return 0;
}
