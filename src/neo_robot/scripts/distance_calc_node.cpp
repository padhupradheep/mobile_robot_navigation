#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/console.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <cmath> 
#include <iomanip>

int sizes = 0; //Global variable
geometry_msgs::PoseArray PA;
geometry_msgs::Pose pose1;

double dist = 0;
void pose_logger(const nav_msgs::Odometry msg)
{
	int i = 1;
	double x1,x2,y1,y2;
	pose1.position.x = msg.pose.pose.position.x;
	pose1.position.y = msg.pose.pose.position.y;
	pose1.position.z = msg.pose.pose.position.z;
	pose1.orientation.w = msg.pose.pose.orientation.w;
	PA.poses.push_back(pose1);
	sizes = PA.poses.size()+i;
	/* Eucledian distances */
	x1 = round(PA.poses[sizes-i].position.x);
	x2 = round(PA.poses[sizes-2].position.x);
	y1 = round(PA.poses[sizes-i].position.y);
	y2 = round(PA.poses[sizes-2].position.y);
	/* Calculating eucledian distance */
	double x = x1 - x2; //calculating number to square in next step
	double y = y1 - y2;
	double dist1;

	dist1 = round(pow(x, 2) + pow(y, 2)); 
	dist = round(sqrt(dist1)+dist);                  
	ROS_INFO_STREAM_THROTTLE(20,"Total distance travelled uptil now in meters: "<<dist);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "distance_calc_node");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("I'm here");
	ros::Subscriber sub = nh.subscribe<nav_msgs::Odometry>("/husky_velocity_controller/odom", 1, pose_logger);
	ros::Rate r(10);

	while(ros::ok())
	{
	ros::spin();
	r.sleep();
	}
}