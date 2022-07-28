#include<ros/ros.h>
#include<aote_server/Addints.h>

/*
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器实现:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建 客户端 对象
        5.请求服务，接收响应

*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    if(argc != 3)
    {
      ROS_INFO("参数输入错误 要输入2个值");
    }
    
    ros::init(argc, argv, "daBao");
    ros::NodeHandle nd;
    ros::ServiceClient client = nd.serviceClient<aote_server::Addints>("AddInts");
    
    aote_server::Addints ai;
    //atoi()代表的是ascii to integer，即“把字符串转换成有符号数字”
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);
    


    //等待服务启动成功  不然会挂掉
    //方式1
    //ros::service::waitForService("AddInts");
    //方式2  重要，没有这一句，就不能先启动客户端，得先启动服务端
    client.waitForExistence();

    // 6.发送请求,返回 bool 值，标记是否成功    
    bool flag = client.call(ai);
    if(flag)
    {
        ROS_INFO("响应成功");
        ROS_INFO("结果是 sum = %d", ai.response.sum11);
    }
    else
    {
        ROS_INFO("失败了");
    }

    return 0;
}






