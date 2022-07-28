#include<ros/ros.h>
#include"aote_topic/jiabin.h"



int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");
   ros::init(argc, argv, "dada");
   ros::NodeHandle nh;
   ros::Publisher pub = nh.advertise<aote_topic::jiabin>("pub" , 100);

    ros::Rate r(10);
    aote_topic::jiabin s1;
    s1.age = 18;
    s1.height = 1.88;
    s1.name = "jiabin";
    int count =  0 ;
   while (ros::ok())
   {
      
       pub.publish(s1);
       ROS_INFO("发布名字%s 年林%d  身高%f  %d ",s1.name.c_str(), s1.age, s1.height, count);
       ros::spinOnce();
       count ++ ;
       r.sleep();
   }
   


    return 0;
}