cmake_minimum_required(VERSION 2.8.3)
project(neo_int_ws)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  interactive_markers
  std_msgs
)

include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS geometry_msgs roscpp std_msgs
   trajectory_msgs
   sensor_msgs
 #DEPENDS system_lib
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${catkin_INCLUDE_DIRS}
)

add_executable(move_base
    #src/visualise_goal.cpp
    scripts/move_base_node.cpp
)

target_link_libraries(move_base
  ${catkin_LIBRARIES}
)

add_dependencies(move_base
  ${catkin_EXPORTED_TARGETS}
)

install(
  TARGETS
   move_base
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
   PATTERN ".svn" EXCLUDE
)

