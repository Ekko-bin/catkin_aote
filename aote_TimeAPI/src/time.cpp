
#include<iostream>
#include<ros/ros.h>

using namespace std;

//定时器的回调函数
void doSomeThing(const ros::TimerEvent &event)
{
    ROS_INFO("-------------");
    ROS_INFO("函数被调用的时刻event: %d",event.current_real.toSec());
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"hello_time");
    ros::NodeHandle nh;//必须创建句柄，否则时间没有初始化，导致后续API调用失败
    ros::Time right_now = ros::Time::now();//将当前时刻封装成对象

    //两个API一样的，一个是float，一个是int
    ROS_INFO("当前时刻:%.2f",right_now.toSec());//获取距离 1970年01月01日 00:00:00 的秒数
    ROS_INFO("当前时刻:%d",right_now.sec);//获取距离 1970年01月01日 00:00:00 的秒数
    
    //参数1:秒数  参数2:纳秒  距离1970年01月01日 00:00:00 的秒数的时间
    ros::Time someTime(100, 100000000);// 
    ROS_INFO("时刻:%.2f",someTime.toSec()); //100.10

    //直接传入 double 类型的秒数
    ros::Time someTime2(100.3);
    ROS_INFO("时刻:%.2f",someTime2.toSec()); //100.30


    //持续时间
    ROS_INFO("当前时刻:%.2f",ros::Time::now().toSec());

    ros::Duration(10).sleep();  //直接休眠

    ros::Time sec1 = ros::Time::now();
    ros::Duration du(10);//持续10秒钟,参数是double类型的，以秒为单位
    du.sleep();//按照指定的持续时间休眠，这句话才休眠
    ros::Time sec2 = ros::Time::now();
    double time = sec2.toSec() -sec1.toSec();
    ROS_INFO("持续时间 %d", time);

    ROS_INFO("持续时间:%.2f",du.toSec());//将持续时间换算成秒
    ROS_INFO("当前时刻:%.2f",ros::Time::now().toSec());
    

    //时间运算
    ROS_INFO("时间运算");
    ros::Time now = ros::Time::now();
    ros::Duration du1(10);
    ros::Duration du2(20);
    ROS_INFO("当前时刻:%.2f",now.toSec());
    //1.time 与 duration 运算
    ros::Time after_now = now + du1;
    ros::Time before_now = now - du1;
    ROS_INFO("当前时刻之后:%.2f",after_now.toSec());
    ROS_INFO("当前时刻之前:%.2f",before_now.toSec());

    //2.duration 之间相互运算
    ros::Duration du3 = du1 + du2;
    ros::Duration du4 = du1 - du2;
    ROS_INFO("du3 = %.2f",du3.toSec());
    ROS_INFO("du4 = %.2f",du4.toSec());
    //PS: time 与 time 不可以运算
    // ros::Time nn = now + before_now;//异常
    


    //定时器
    ros::NodeHandle nhs;//必须创建句柄，否则时间没有初始化，导致后续API调用失败

    // ROS 定时器
    /**
    * \brief 创建一个定时器，按照指定频率调用回调函数。
    *
    * \param period 时间间隔
    * \param callback 回调函数
    * \param oneshot 如果设置为 true,只执行一次回调函数，设置为 false,就循环执行。
    * \param autostart 如果为true，返回已经启动的定时器,设置为 false，需要手动启动。
    */
    //Timer createTimer(Duration period, const TimerCallback& callback, bool oneshot = false,
    //                bool autostart = true) const;

    // ros::Timer timer = nh.createTimer(ros::Duration(0.5),doSomeThing);

    //！每隔0.5s执行一个操作。
    ros::Timer timer = nhs.createTimer(ros::Duration(0.5),doSomeThing,true);//只执行一次
     
    
    // ros::Timer timer = nh.createTimer(ros::Duration(0.5),doSomeThing,false,false);//需要手动启动
    // timer.start();
    ros::spin(); //必须 spin
     


     
    //关闭节点
    ros::shutdown();
    return 0;
}




