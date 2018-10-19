#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TwistStamped.h>
#include <ros/console.h>
#include <sstream>
#include <move_base.h>
#include <fstream>
#include <iostream>
#include <tinyxml.h>
using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "move_base_node");
	ros::NodeHandle n;
	// std::string goals;
	// n.getParam("move_base_node/goal1",goals);
	XmlRpc::XmlRpcValue my_list;
	n.getParam("move_base_node/my_list", my_list);
	ROS_INFO_STREAM("size:"<<my_list.size());
	// ROS_INFO_STREAM("goals: " << my_list[0]);
	// ROS_INFO_STREAM("goals: " << my_list[1]);
	for(int i = 0; i<my_list.size(); i++)
	{
		ROS_INFO_STREAM("goals: " << my_list[i]);
	}
	ros::spin();
	return true;
}