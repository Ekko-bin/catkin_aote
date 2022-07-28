#! /usr/bin/env python
# -*- coding: UTF-8 -*-


import rospy
from aote_topic.msg import jiabin


def doperson(p):
   name = p.name
   age =  p.age
   rospy.loginfo("%s %d %f", p.name, p.age, p.height)


if __name__ == "__main__":
    rospy.init_node("dadsssa")
    sub = rospy.Subscriber("chatting",jiabin,doperson,queue_size=10)
    rospy.spin()