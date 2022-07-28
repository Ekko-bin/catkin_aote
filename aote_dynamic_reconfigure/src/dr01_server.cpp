#include<ros/ros.h>
#include"dynamic_reconfigure/server.h"
#include"aote_dynamic_reconfigure/drConfig.h"
/*  
    动态参数服务端: 参数被修改时直接打印
    实现流程:
        1.包含头文件
        2.初始化 ros 节点
        3.创建服务器对象
        4.创建回调对象(使用回调函数，打印修改后的参数)
        5.服务器对象调用回调对象
        6.spin()
*/

//解析动态参数
void cb(aote_dynamic_reconfigure::drConfig &config, uint32_t level)
{     
   ROS_INFO("修改后的整形数据是%d, %.2f, %s, %d ",
             config.int_param,
             config.double_param, 
             config.string_param.c_str(),
             config.bool_param
              ); //dr.cfg里面的参数 config.list_param?d

}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 2.初始化 ros 节点
    ros::init(argc, argv, "sr_server");
    // 3.创建服务器对象
    dynamic_reconfigure::Server<aote_dynamic_reconfigure::drConfig> server;
    // 4.创建回调对象(使用回调函数，打印修改后的参数)
//void setCallback(const boost::function<void (aote_dynamic_reconfigure::drConfig &, uint32_t level)> &callback)
    server.setCallback(boost::bind(&cb, _1, _2));
    // 5.服务器对象调用回调对象

   ///12
    ros::spin();
    // 6.spin()

    return 0;
}