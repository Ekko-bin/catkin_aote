#! /usr/bin/env python
# -*- coding: UTF-8 -*-

from warnings import resetwarnings
import rospy
from  aote_server.srv import *

def donum(request):
    num1 = request.num1
    num2 = request.num2
    sum = num2 + num1

    respond = AddintsResponse() #类名
    respond.sum11 = sum

    rospy.loginfo("add = %d " ,sum)
    return respond

if __name__ == "__main__":
    rospy.init_node("kkk")
    server = rospy.Service("jiabin",Addints,donum)
    rospy.loginfo("服务器启动")
    rospy.spin()
