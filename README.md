# mobile_robot_navigation

This is a simple implementation of move_base sending multiple goals.
ROS Distro : Kinetic

### Platform used : Husky 
Clone all the packages from this repo https://github.com/husky/husky

Create a catkin workspace, clone the existing repo. 

Do not forget to source the files.

There are 2 nodes available
  1. Performing the basic move_base operation and reaching the goal.
  2. Calculating the distance travelled.

Run 

#### roscore

Run the husky gazebo simulation, which brings up all the required components.

####roslaunch husky_gazebo husky_playpen.launch 

Now bring up the move_base

#### roslaunch husky_navigation move_base.launch 

Now bring up the amcl for the localization of the robot. (Map -> base_link transformation)
 
 #### roslaunch husky_navigation amcl.launch
 
Now run the node that was developed

#### roslaunch neo_int_ws move_robot.launch
 
Incase if you want to change the goal positions, change the goals.yaml file in the configuration folder.
