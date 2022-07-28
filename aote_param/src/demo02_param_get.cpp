#include"ros/ros.h"

 int main(int argc, char *argv[])
 {

     setlocale(LC_ALL,"");
     ros::init(argc, argv, "get_param");
     ros::NodeHandle nh;
     double radius = nh.param("radius", 5);  //没有就默认
     double value = nh.param("value", 2.0);   //没有就默认

     ROS_INFO("radius = %f", radius);
     ROS_INFO("value = %f", value);

    double radius2 = 0.3;
    bool result = nh.getParam("value111", radius2); //没有就默认
    if(result)
    {
        ROS_INFO("cunzai, value = %f", radius2 );
    }
    else
    {
         ROS_INFO("bu cunzai , value" );
    }


    std::vector<std::string> param_names1;
    nh.getParamNames(param_names1);

    // for (auto &name  param_names1)
    // {
    //    //ROS_INFO("名称解析name = %s",name.c_str());        
    // }
    ROS_INFO("----------------------------");
   

     bool flag1 = nh.hasParam("value");
     bool flag2 = nh.hasParam("value333");
     ROS_INFO("村在吗 %d", flag1);
     ROS_INFO("村在吗 %d", flag2);


      std::string s1;
      nh.searchParam("value", s1);
      ROS_INFO("搜索结果 %s", s1.c_str()); //搜索结果 /value

     return 0;
 }