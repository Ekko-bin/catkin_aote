cmake_minimum_required(VERSION 3.0.2)
project(aote_server)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  
)



## Generate services in the 'srv' folder
add_service_files(
  FILES
  Addints.srv
)



## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES aote_server
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_executable(AddInts_Server src/demo01_server.cpp)
add_dependencies(AddInts_Server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(AddInts_Server
  ${catkin_LIBRARIES}
)



add_executable(AddInts_Client src/demo02_client.cpp)
add_dependencies(AddInts_Client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(AddInts_Client
  ${catkin_LIBRARIES}
)


catkin_install_python(PROGRAMS
  scripts/srv01_server.py
  scripts/srv01_client.py
 # scripts/msg01_pub.py
 # scripts/msg01_sub.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)



