/*  
    订阅坐标系信息，生成一个相对于 子级坐标系的坐标点数据，转换成父级坐标系中的坐标点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 TF 订阅节点
        4.生成一个坐标点(相对于子级坐标系)
        5.转换坐标点(相对于父级坐标系)
        6.spin()
*/
//1.包含头文件
#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"   //对应"tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/buffer.h"              //是个缓存 ，订阅的数据缓存在这里面

//转换坐标点
#include "geometry_msgs/PointStamped.h"  //坐标点数据
#include "tf2_geometry_msgs/tf2_geometry_msgs.h" //注意: 调用 transform 必须包含该头文件

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"tf_sub");
    ros::NodeHandle nh;    //必须的


    // 3.创建 TF 订阅节点
    tf2_ros::Buffer buffer;   //创建一个buffer缓存
    //相当于subscribe订阅者
    tf2_ros::TransformListener listener(buffer);  //创建监听对象，订阅数据传入buffer

    //设置转换频率
    ros::Rate rate(10);


    while (ros::ok())
    {
    // 4.生成一个坐标点(相对于子级坐标系)
        geometry_msgs::PointStamped  point_laser;  //
        point_laser.header.frame_id = "laser";
        point_laser.header.stamp = ros::Time::now();

        point_laser.point.x = 1;
        point_laser.point.y = 2;
        point_laser.point.z = 5.0;

      //设置休眠
        //ros::Duration(2).sleep();   //设置休眠2S 让pub先运行缓存，不然会找不到base_link
                                    //或者下面的设置异常，也能解决
    

        // 5.转换坐标点(相对于父级坐标系)
        //新建一个坐标点，用于接收转换结果  
        //--------------使用 try 语句或休眠，否则可能由于缓存接收延迟而导致坐标转换失败------------------------
        //因为订阅数据是一个耗时操作，可能在调用transform时候，坐标系相对关系还没有订阅到，所以出现异常
        try
        {
            geometry_msgs::PointStamped point_base;
            //把point_laser的点转化为相对base_link的坐标点，会返回另外转化后的点
            //转换后的坐标点信息                           //被转换的坐标点  父级坐标系
            point_base = buffer.transform(point_laser,"base_link"); //头文件#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
             
            ROS_INFO("转换后的数据:%.2f,%.2f,%.2f ,   参考的坐标系是%s:",
                                                    point_base.point.x,
                                                    point_base.point.y,
                                                    point_base.point.z,
                                                    point_base.header.frame_id.c_str());

        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            ROS_INFO("程序异常%s.....", e.what());
        }

        rate.sleep();  
        ros::spinOnce();
    }


    return 0;
}
