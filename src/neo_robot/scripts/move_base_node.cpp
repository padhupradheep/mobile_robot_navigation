#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>
#include <sstream>
#include <MOVE_base.h>
#include <fstream>
#include <iostream>
#include <tinyxml.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


void MOVE_base::Position_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  ROS_INFO_STREAM("Position->"<< msg->pose.pose.position.x);

}


int main(int argc, char **argv)
{
	typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
	ros::init(argc, argv, "move_base_node");
	ros::NodeHandle n;
	// std::string goals;
	// n.getParam("move_base_node/goal1",goals);
	// XmlRpc::XmlRpcValue my_list;
	// n.getParam("move_base_node/my_list", my_list);
	// ROS_INFO_STREAM("size:"<<my_list.size());
	// ros::Rate rate(2);
	// for(int i = 0; i<my_list.size(); i++)
	// {
	// 	ROS_INFO_STREAM("The goals that the Robot will travel are: " << my_list[i]);
	// }

	// ros::Publisher velocity = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1);
	// ros::Subscriber sub = n.subscribe("/odom", 1, Position_callback);
	// ros::spin();

	// ROS_INFO_STREAM("pose: "<<pose_x);
	// while (ros::ok())
 //  {
 //  	geometry_msgs::Twist msg;
 //  	msg.linear.x = -0.5;
 //  	msg.linear.y = 0.5;
 //  	velocity.publish(msg);
	

 //  }
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x =  0.05;
  goal.target_pose.pose.orientation.w = 0.05;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
	  

	return true;
}
	