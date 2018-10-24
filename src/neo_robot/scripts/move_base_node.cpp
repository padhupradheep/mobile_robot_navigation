#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
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
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int id = 0;


MOVE_base::MOVE_base(){}

MOVE_base::~MOVE_base(){}

void MOVE_base::status_cb(const actionlib_msgs::GoalStatusArray::ConstPtr &msg)
{
	GA = msg->status_list[0].text;
	status = msg->status_list[0].text;
}



void MOVE_base::simple_client(const geometry_msgs::Pose msg)
{

/* 
Move base client is being called up in this function
*/	

	MoveBaseClient ac("move_base", true);
	while(!ac.waitForServer(ros::Duration(5.0)))
	{
	ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = msg.position.x;
	goal.target_pose.pose.position.y = msg.position.y;
	goal.target_pose.pose.orientation.w = msg.orientation.z;

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
	ros::MultiThreadedSpinner spinner(2);
	// n.getParam("move_base_node/goal1",MB.goals);
	XmlRpc::XmlRpcValue my_list;
	n.getParam("move_base_node/my_list", my_list);
	ROS_INFO_STREAM("size:"<<my_list.size());
	ros::Rate r(10);
	// MB.sub_status = n.subscribe<actionlib_msgs::GoalStatusArray>("/move_base/status", 1, &MOVE_base::status_cb, &MB);
	int i = 0;
	for(int i = 0; i<my_list.size(); i++)
		{
		ROS_INFO_STREAM("The goals that the Robot will travel are: " << my_list[i]);
		MB.poses.position.x = my_list[i][0];
		MB.poses.position.y = my_list[i][1];
		MB.poses.orientation.z = my_list[i][2];
		MB.simple_client(MB.poses);
		ros::spinOnce();
		r.sleep();
		}

}