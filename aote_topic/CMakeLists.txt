cmake_minimum_required(VERSION 3.0.2)
project(aote_topic)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)




add_message_files(
  FILES
  jiabin.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES aote_topic
  CATKIN_DEPENDS roscpp rospy std_msg 
#  DEPENDS system_lib 
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(talker  src/talker.cpp)
add_executable(suscriber  src/suscriber.cpp)
add_executable(jiabinpublish  src/jiabinpublish.cpp)
add_executable(jiabinsub  src/jiabinsub.cpp)

add_dependencies(jiabinpublish ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(jiabinsub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


target_link_libraries(talker
  ${catkin_LIBRARIES}
)
target_link_libraries(suscriber
  ${catkin_LIBRARIES}
)
target_link_libraries(jiabinsub
  ${catkin_LIBRARIES}
)
target_link_libraries(jiabinpublish
  ${catkin_LIBRARIES}
)

catkin_install_python(PROGRAMS
  scripts/demo1_pub.py
  scripts/dem01_sub.py
  scripts/msg01_pub.py
  scripts/msg01_sub.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)



