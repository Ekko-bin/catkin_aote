#! /usr/bin/env python
# -*- coding: UTF-8 -*-


import rospy
from std_msgs.msg import String

#使用python发布
if __name__ == "__main__":
    rospy.init_node("jiabin")
    pub = rospy.Publisher("che", String ,queue_size=10)
    msg = String()

    #发布频率
    rate = rospy.Rate(10)
    #设置计数器
    count = 0
    #休眠一下
    rospy.sleep(3)
    while not rospy.is_shutdown():
        count +=1
        msg.data = " i am jiabin" + str(count)
        pub.publish(msg)
        rospy.loginfo("发布的数据 %s" , msg.data)
        rate.sleep()