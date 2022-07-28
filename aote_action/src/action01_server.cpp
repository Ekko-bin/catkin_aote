#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "aote_action/AddIntsAction.h"
/*  
    需求:
        创建两个ROS节点，服务器和客户端，
        客户端可以向服务器发送目标数据N（一个整型数据）
        服务器会计算1到N之间所有整数的和，这是一个循环累加的过程，返回给客户端，
        这是基于请求响应模式的，
        又已知服务器从接收到请求到产生响应是一个耗时操作，每累加一次耗时0.1s，
        为了良好的用户体验，需要服务器在计算过程中，
        每累加一次，就给客户端响应一次百分比格式的执行进度，使用action实现。

    流程:
        1.包含头文件;
        2.初始化ROS节点;
        3.创建NodeHandle;
        4.创建action服务对象;
        5.处理请求,产生反馈与响应;
        6.spin().

*/
typedef actionlib::SimpleActionServer<aote_action::AddIntsAction> Server ; //重命名

// 5.处理请求,产生反馈与响应;                   客户端提供的goal action的服务
void cb(const aote_action::AddIntsGoalConstPtr &goalptr, Server* server )
{
   //1. 解析提交的目标值
   int goal_num = goalptr->num;
   ROS_INFO("客户端的目标值%d", goal_num);
   //2. 产生连续反馈
    int result = 0;
    ros::Rate r(10);
    ROS_INFO("连续反馈中");
    for(int i = 1 ; i <= goal_num; i++)
    {
       result += i;
       //组织数据并且发布进度
       aote_action::AddIntsFeedback feed;
       
       feed.progress_bar = i / (double)goal_num ;
       server->publishFeedback(feed);
       r.sleep();
    } 
   
   //3. 最终结果响应    
   ROS_INFO("最终响应结果%d", result);
   aote_action::AddIntsResult re;
   re.result = result ; 
   server->setSucceeded(re);
   ROS_INFO("最终结果是%d", re.result);
   
}



 int main(int argc, char*argv[])
 {
    setlocale(LC_ALL,"");
    // 2.初始化ROS节点;
    ros::init(argc, argv, "addint");
    // 3.创建NodeHandle;
    ros::NodeHandle nh;
    // 4.创建action服务对象;
    /*                                          
       SimpleActionServer(ros::NodeHandle n, std::string name, ExecuteCallback execute_callback,
                          bool auto_start);
                          参数1 ： 句柄
                          参数2 ： 话题名称
                          参数3 ： 回调函数
                          参数4 ： 是否自动启动
    */                                        //_1是占位 传入的是goal
    Server server(nh,"addInts",boost::bind(&cb,_1, &server),false);
    ROS_INFO("server还没启动");
    server.start() ;  //如果auto_start为false，需要手动调用该函数启动服务
    ROS_INFO("server 已经启动");
    // 5.处理请求,产生反馈与响应; 

    // 6.spin().   
    ros::spin();
 
    return 0;
 }