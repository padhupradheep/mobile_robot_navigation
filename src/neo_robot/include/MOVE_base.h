/*
 *  Created on: December, 2017
 *      Authors: Djordje Vukcevic, Pradheep Krishna Muthukrishnan Padmanabhan
 */
#include "ros/ros.h"
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include "std_msgs/String.h"
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib_msgs/GoalID.h>
#include <geometry_msgs/PoseStamped.h>
#ifndef MOVEBASE_H_
#define MOVEBASE_H_

using namespace std;
class MOVE_base
{
    protected:
        int sign(double x);

    public:
        MOVE_base();
        ~MOVE_base();
        bool stop_flag;
        void simple_client(const geometry_msgs::Pose msg);
        ros::Subscriber sub_status;
        ros::Subscriber sub;
        void status_cb(const actionlib_msgs::GoalStatusArray::ConstPtr& msg);
        void pose_logger(const nav_msgs::Odometry msg);
        void distance_calculation();
        std::string GA;
        geometry_msgs::PoseStamped pose;
        geometry_msgs::Pose poses;
        geometry_msgs::PoseArray PA;
        std::string goals;
        std::string status;
        float distance;
    };

#endif