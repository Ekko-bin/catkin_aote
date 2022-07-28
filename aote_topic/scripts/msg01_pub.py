#! /usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
from aote_topic.msg import jiabin

if __name__ == "__main__":
    rospy.init_node("dada")
    pub = rospy.Publisher("chatting", jiabin, queue_size=10)
    p = jiabin()
    p.age = "jiabin"
    p.height = 180
    p.age = 18

    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        pub.publish(p)
        rospy.loginfo("%s %d %0.2f", p.name , p.age, p.height)
        rate.sleep()
