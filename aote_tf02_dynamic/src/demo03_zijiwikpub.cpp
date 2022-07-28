#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"  //动态发布，静态是"tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h" 
#include "tf2/LinearMath/Quaternion.h"
#include <nav_msgs/Odometry.h>

int main(int argc, char** argv)
{
 ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf2_ros::TransformBroadcaster odom_broadcaster;
 
     double x = 0.0;
     double y = 0.0;
     double th = 0.0;
   
     double vx = 0.1;
     double vy = 0;
     double vth = 0.1;
   
     ros::Time current_time, last_time;
     current_time = ros::Time::now();
     last_time = ros::Time::now();
   
     ros::Rate r(1.0);
     while(n.ok())
     {

       setlocale(LC_ALL,"");
       ROS_INFO("程序开始了");
       
       current_time = ros::Time::now();
   
       //compute odometry in a typical way given the velocities of the robot
       double dt = (current_time - last_time).toSec();
       double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
       double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
       double delta_th = vth * dt;
   
       x += delta_x;
       y += delta_y;
       th += delta_th;
   
       //since all odometry is 6DOF we'll need a quaternion created from yaw
       
       
       geometry_msgs::TransformStamped odom_trans;
       odom_trans.header.stamp = current_time;
       odom_trans.header.frame_id = "odom";
       odom_trans.child_frame_id = "base_link";
   

      //----设置子级相对于父级的偏移量 子级在父级坐标系下的坐标
       odom_trans.transform.translation.x = x;
       odom_trans.transform.translation.y = y;
       odom_trans.transform.translation.z = 0.0;


       tf2::Quaternion qtn;
       qtn.setRPY(0,0,th);
        //----设置子级相对于父级的位姿 
       odom_trans.transform.rotation.x = qtn.getX();
       odom_trans.transform.rotation.y = qtn.getY();
       odom_trans.transform.rotation.z = qtn.getZ();
       odom_trans.transform.rotation.w = qtn.getW();
       
   
       //send the transform
       odom_broadcaster.sendTransform(odom_trans);
   



       //next, we'll publish the odometry message over ROS  接下来,我们将发布量距消息/ ROS
       nav_msgs::Odometry odom;
       odom.header.stamp = current_time;
       odom.header.frame_id = "odom";
   
       //set the position
       odom.pose.pose.position.x = x;
       odom.pose.pose.position.y = y;
       odom.pose.pose.position.z = 0.0;

       odom.pose.pose.orientation.x = qtn.getX();
       odom.pose.pose.orientation.y = qtn.getY();
       odom.pose.pose.orientation.z = qtn.getZ();
       odom.pose.pose.orientation.w = qtn.getW();
   
       //set the velocity
       odom.child_frame_id = "base_link";
       odom.twist.twist.linear.x = vx;
       odom.twist.twist.linear.y = vy;
       odom.twist.twist.angular.z = vth;
   
       //publish the message
       odom_pub.publish(odom);
   
       last_time = current_time;

       ros::spinOnce();               // check for incoming messages
       r.sleep();
     }
   }