#! /usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
from  aote_server.srv import *
import sys

if __name__ == "__main__":

  if len(sys.argv) != 3:  #3个指的是文件名称，参数1 参数2
    rospy.logerr("请正确提交参数")
    sys.exit(1)
    
  rospy.init_node("dddd")
  client = rospy.ServiceProxy("jiabin",Addints)

  ## 请求前，等待服务已经就绪
  client.wait_for_service()

  # 方式1
  #resp = client.call(11, 22)

   # 方式2
   # resp = client(AddIntsRequest(1,5))

   # 方式3
  req = AddintsRequest()
  req.num1 = int(sys.argv[1])
  req.num2 = int(sys.argv[2]) 
  resp = client.call(req)
  
  rospy.loginfo("相应的数据 %d" ,resp.sum11)
   
  