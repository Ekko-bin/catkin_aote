#include<ros/ros.h>
#include<std_msgs/String.h>

int main(int argc, char  *argv[])
{
   
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "jiabin");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<std_msgs::String>("chatter11", 10);

    ros::Rate r(10);
    std_msgs::String msg;
    std::string msg_front = "Hello 你好！"; //消息前缀
    int count = 0;
    //休眠一下
    ros::Duration(3).sleep();

    while(ros::ok())
    {
        std::stringstream ss;
        ss << msg_front << count;
        msg.data = ss.str();
        //发布消息
        pub.publish(msg);
        //加入调试，打印发送的消息
        ROS_INFO("发送的消息:%s",msg.data.c_str());

        //根据前面制定的发送贫频率自动休眠 休眠时间 = 1/频率；
        r.sleep();
        count++;//循环结束前，让 count 自增
        //暂无应用
        ros::spinOnce();
    }
    return 0;
}
