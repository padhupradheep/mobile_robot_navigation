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
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int id = 0;


MOVE_base::MOVE_base(){}

MOVE_base::~MOVE_base(){}

/* Determing te status part is incomplete */

void MOVE_base::status_cb(const actionlib_msgs::GoalStatusArray::ConstPtr &msg)
{
	GA = msg->status_list[0].text;
	status = msg->status_list[0].text;
}



void MOVE_base::simple_client(const geometry_msgs::Pose msg)
{

/* 
Move base client is being called up in this function

Here we send the goals
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
   	
   	ROS_INFO("Hooray, the base moved to the desired goal");

  else

    ROS_INFO("The base failed to move to the desired goal");

}



int main(int argc, char **argv)
{
	MOVE_base MB; //Creating an object
	ros::init(argc, argv, "move_base_node");
	ros::NodeHandle n;
	ros::Rate loop_rate_markers(20);

    int step_counter = 0;
    visualization_msgs::Marker marker;
    visualization_msgs::MarkerArray markers;
    marker.id = 0;

    ros::Publisher marker_pub = \
	n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 100); // Creating an array

//Using XmlRpcValue to parse the XML file
	XmlRpc::XmlRpcValue my_list;
	n.getParam("move_base_node/my_list", my_list);
	ROS_INFO_STREAM("size:"<<my_list.size());
	ros::Rate r(10);

	ROS_INFO_STREAM("The marker publisher has connected to subscribers.");

	/* Visualizing the marker */
	/*This will work well with a new node*/
	for(int i = 0; i<my_list.size(); i++)
	{	
		marker.header.frame_id = "/map";
	    marker.type = visualization_msgs::Marker::SPHERE;
	    marker.action = visualization_msgs::Marker::ADD;
	    marker.pose.position.x = my_list[i][0];
	    marker.pose.position.y = my_list[i][0];
	    marker.pose.position.z = 0.0;
	    marker.pose.orientation.x = 0.0;
	    marker.pose.orientation.y = 0.0;
	    marker.pose.orientation.z = 0.0;
	    marker.pose.orientation.w = 0.0;
	    marker.scale.x = 0.2;
	    marker.scale.y = 0.2;
	    marker.scale.z = 0.2;
	    marker.color.r = 0.0;
	    marker.color.g = 2.0;
	    marker.color.b = 0.0;
	    marker.color.a = 1.0;
	    marker.lifetime = ros::Duration();
	    marker.id+=1;
		markers.markers.push_back(marker);
   	}

	for(int j = 0; j<my_list.size(); j++)
		{
		ROS_INFO_STREAM("The goals that the Robot will travel are: " << my_list[j]);
		marker_pub.publish(markers); 
		MB.poses.position.x = my_list[j][0];
		MB.poses.position.y = my_list[j][1];
		MB.poses.orientation.z = my_list[j][2];
		MB.simple_client(MB.poses);
		ros::spinOnce();
		r.sleep();
		}
	 ros::shutdown();
}