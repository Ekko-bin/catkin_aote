#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
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
        4.创建action客户端对象;
        5.发送目标，处理反馈以及最终结果;
          a: 链接建立   -- 回调函数
          b: 处理连续反馈  --回调函数
          c: 处理最终响应  --回调函数
        6.spin()

*/
typedef actionlib::SimpleActionClient<aote_action::AddIntsAction> Client;
//处理最终响应的
void done_cb(const actionlib::SimpleClientGoalState &state, const aote_action::AddIntsResultConstPtr &result)
{
    //响应状态是否成功
   if (state.state_ == state.SUCCEEDED)
    {
        ROS_INFO("最终结果:%d",result->result);
    } 
    else 
    {
        ROS_INFO("任务失败！");
    }


}
//b: 处理连续反馈  --回调函数
void  feedback_cb(const aote_action::AddIntsFeedbackConstPtr &feedback)
{
    ROS_INFO("连续反馈开始");
    ROS_INFO("当前进度:%.2f",feedback->progress_bar);
}

//链接建立的回调
void  active_cb()
{
    ROS_INFO("客户端与服务端链接建立， 服务已经被激活....");
}



int main(int argc, char *argv[])
{

    setlocale(LC_ALL,"");
    // 2.初始化ROS节点;
    ros::init(argc, argv, "addintsclient");
    // 3.创建NodeHandle;
    ros::NodeHandle nh;
    // 4.创建action客户端对象;
    Client client(nh, "addInts", true);

    // 5.发送目标，处理反馈以及最终结果;
    //注意：要等待服务端先启动
    ROS_INFO("等待服务器的启动");
    client.waitForServer();
    //发送请求
    
    //   a: 链接建立   -- 回调函数
    //   b: 处理连续反馈  --回调函数
    //   c: 处理最终响应  --回调函数
   // void sendGoal(const aote_action::AddIntsGoal &goal,  //设置目标值
    //                  boost::function<void (const actionlib::SimpleClientGoalState &state, 
    //  处理最终响应的    const aote_action::AddIntsResultConstPtr &result)> done_cb,
    //  链接建立         boost::function<void ()> active_cb, 
    //  处理连续反馈      boost::function<void (const aote_action::AddIntsFeedbackConstPtr &feedback)> feedback_cb)
    //参数1：  设置目标值
    aote_action::AddIntsGoal goal;
    goal.num = 100;


    client.sendGoal(goal, &done_cb, &active_cb, &feedback_cb) ;

    // 6.spin()
    ros::spin();
    return 0;
}