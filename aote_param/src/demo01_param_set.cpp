#include"ros/ros.h"


 int main(int argc, char *argv[])
 {

    setlocale(LC_ALL,"");
    ros::init(argc, argv, "set_param");
    ros::NodeHandle nh;
    
    //参数增加
    //方案1  用NodeHandle
    nh.setParam("type", "jiabin");
    nh.setParam("value", 11);
    //方案2

    ros::param::set("type_param", "jiabin2");
    ros::param::set("value_param", 22);


    nh.setParam("value", 0.11);
    ros::param::set("value_param", 0.22);



     return 0;
 }