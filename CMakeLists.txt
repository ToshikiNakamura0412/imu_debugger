cmake_minimum_required(VERSION 3.0.2)
project(imu_debugger)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  tf2_ros
  tf2_sensor_msgs
)
catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES imu_test
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)
include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(imu_debugger src/imu_debugger.cpp)
add_dependencies(imu_debugger ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(imu_debugger ${catkin_LIBRARIES})
