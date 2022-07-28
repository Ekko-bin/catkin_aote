#include<ros/ros.h>
#include"aote_topic/jiabin.h"



void doPerson(const aote_topic::jiabin::ConstPtr &p1)
{
    ROS_INFO("订阅的人信息:%s, %d, %.2f", p1->name.c_str(), p1->age, p1->height);
}

int main(int argc, char *argv[])
{

   setlocale(LC_ALL, "");
   ros::init(argc, argv, "subbb");
   ros::NodeHandle nh;
   ros::Subscriber sub = nh.subscribe<aote_topic::jiabin>("pub", 100 , doPerson);

   ros::spin();


    return 0;   
}