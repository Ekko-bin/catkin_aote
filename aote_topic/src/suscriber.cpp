#include<ros/ros.h>
#include<std_msgs/String.h>


void doMsg(const std_msgs::String::ConstPtr &ptrd)
{
   ROS_INFO("订阅%s", ptrd->data.c_str());
}
int main(int argc,  char *argv[])
{
   setlocale(LC_ALL,"");
   ros::init(argc, argv , "surscer");
   ros::NodeHandle nh;
   ros::Subscriber s1 = nh.subscribe<std_msgs::String>("chatter11", 10, doMsg);
   ros::spin();

    return 0;
}