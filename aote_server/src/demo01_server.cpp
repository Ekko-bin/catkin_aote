#include<ros/ros.h>
#include<aote_server/Addints.h>



// bool 返回值由于标志是否处理成功
bool doReq(aote_server::Addints::Request& req,
          aote_server::Addints::Response& resp)
{
    int num1 = req.num1;
    int num2 = req.num2;

    ROS_INFO("服务器接收到的请求数据为:num1 = %d, num2 = %d",num1, num2);

    //逻辑处理
    if (num1 < 0 || num2 < 0)
    {
        ROS_ERROR("提交的数据异常:数据不可以为负数");
        return false;
    }

    //如果没有异常，那么相加并将结果赋值给 resp
    resp.sum11 = num1 + num2;
    ROS_INFO("求和结果sum = %d",  resp.sum11);
    return true;

}
 int main(int argc, char*argv[])
 {
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "heisui");
    ros::NodeHandle nh;
   
    ros::ServiceServer server = nh.advertiseService("AddInts",doReq);
    ROS_INFO("服务已经启动....");
    //     5.回调函数处理请求并产生响应
    //     6.由于请求有多个，需要调用 ros::spin()
    ros::spin();


   return 0;
 }