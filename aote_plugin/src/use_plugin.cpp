#include<ros/ros.h>
#include <pluginlib/class_loader.h>
#include "../include/dbx_base.h"
/*
  创建类加载器，根据需求加载相关插件
    1。创建类记载器
    2。 使用类加载器实例化某个插件对象
    3。使用插件
*/
int main(int argc, char *argv[])
{          
  setlocale(LC_ALL, "");            
   // 1。创建类记载器                                   //包名 基类
   pluginlib::ClassLoader<dbx_base_ns::Dbx_Base>loader("aote_plugin", "dbx_base_ns::Dbx_Base");

   try
   {
     //2。 使用类加载器实例化某个插件对象                                      子类
    boost::shared_ptr<dbx_base_ns::Dbx_Base> san = loader.createInstance("dbx_plugin_ns::SiBian");
        
    //3。使用插件
    san->init(10);
    double length = san->getlength();
    ROS_INFO("三角形周长是%d", length);
   }
   catch(const std::exception& ex)
   {
       ROS_ERROR("加载错误The plugin failed to load for some reason. Error: %s", ex.what());
   }
   
  
  return 0;
}   