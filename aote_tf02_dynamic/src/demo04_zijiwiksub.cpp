#include<ros/ros.h>
#include <nav_msgs/Odometry.h>


void doturtle(const  nav_msgs::Odometry::ConstPtr  &p1)
{
    ROS_INFO("base_link位置:%d, %d, %d",p1->pose.pose.position.x , p1->pose.pose.position.y, p1->pose.pose.position.z); 
   
}

int main(int argc, char *argv[])
{

   setlocale(LC_ALL, "");
   ros::init(argc, argv, "subbb");
   ros::NodeHandle nh;
   ros::Subscriber sub = nh.subscribe<nav_msgs::Odometry>("odom", 100 , doturtle);
   ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom111", 50);
   
   

   ros::spin();


    return 0;   
}