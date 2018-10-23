#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>
#include <sstream>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
int main(int argc, char **argv)
{
  ros::init(argc, argv, "map_baselink_transform");
  ros::NodeHandle n;

  int publish_rate_ = 100;
  ROS_INFO("Inside the transformation node");
  tf::TransformBroadcaster tf_br_;
  tf::StampedTransform tf_map_to_base_link_;

  // set up parent and child frames
  tf_map_to_base_link_.frame_id_ = std::string("/map");
  tf_map_to_base_link_.child_frame_id_ = std::string("/base_link");

  // set up publish rate
  ros::Rate loop_rate(publish_rate_);

  // main loop
  while (ros::ok())
  {
    // time stamp
    tf_map_to_base_link_.stamp_ = ros::Time::now();

    // specify actual transformation vectors from odometry
    // NOTE: zeros have to be substituted with actual variable data
    tf_map_to_base_link_.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
    tf_map_to_base_link_.setRotation(tf::Quaternion(0.0, 0.0, 0.0));  

    // broadcast transform
    tf_br_.sendTransform(tf_map_to_base_link_);

    ros::spinOnce();
    loop_rate.sleep();
  }
    return true;
  }