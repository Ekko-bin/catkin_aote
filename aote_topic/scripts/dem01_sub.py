#! /usr/bin/env python
# -*- coding: UTF-8 -*-



# 需求: 实现基本的话题通信，一方发布数据，一方接收数据，
#          实现的关键点:
#          1.发送方
#          2.接收方
#          3.数据(此处为普通文本)


#     消息订阅方:
#         订阅话题并打印接收到的消息

#     实现流程:
#         1.导包 
#         2.初始化 ROS 节点:命名(唯一)
#         3.实例化 订阅者 对象
#         4.处理订阅的消息(回调函数)
#         5.设置循环调用回调函数

import rospy
from std_msgs.msg import String

def domsg(msg):
    rospy.loginfo("%s", msg.data)
  

#使用python发布
if __name__ == "__main__":
     rospy.init_node("sub_pub")
     sub = rospy.Subscriber("che",String, domsg , buff_size=10)
     rospy.spin()

