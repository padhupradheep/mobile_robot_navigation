#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>
#include <sstream>
#include <MOVE_base.h>
#include <fstream>
#include <iostream>
#include <tinyxml.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

MOVE_base::MOVE_base(){}

MOVE_base::~MOVE_base(){}

void MOVE_base::Position_callback(const geometry_msgs::Pose msg)
{

  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "/base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = msg.position.x;
  // goal.target_pose.pose.position.y = msg.position.y;
  // goal.target_pose.pose.position.z = msg.position.z;
  goal.target_pose.pose.orientation.w = 0.05;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");	
}


int main(int argc, char **argv)
{
	MOVE_base MB;
	ros::init(argc, argv, "move_base_node");
	ros::NodeHandle n;

	n.getParam("move_base_node/goal1",MB.goals);
	XmlRpc::XmlRpcValue my_list;
	n.getParam("move_base_node/my_list", my_list);
	ROS_INFO_STREAM("size:"<<my_list.size());
	ros::Rate r(10);
	for(int i = 0; i<my_list.size(); i++)
	{
		MB.poses.position.x = my_list[i][0];
		MB.poses.position.y = my_list[i][1];
		MB.poses.position.z = my_list[i][2];
		MB.Position_callback(MB.poses);
		ROS_INFO_STREAM("The goals that the Robot will travel are: " << my_list[i]);
		r.sleep();
		ros::spinOnce();
	} 

	return true;

}
	