#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "scout_msgs/ScoutStatus.h"
#include "string.h"
#include <cmath>

double start_x, start_y;
bool isMove;
ros::Subscriber sub, sub2, sub3;
void setStartVelocity(const nav_msgs::Odometry::ConstPtr &msg)
{
	start_x = msg->pose.pose.position.x;
	start_y = msg->pose.pose.position.y;
	sub.shutdown();
}

void judgeMove(const scout_msgs::ScoutStatus::ConstPtr &msg)
{

	// ROS_INFO("CAR STARTING...");
	if (abs(msg->linear_velocity) > 0.01)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}
}

void showDistance(const nav_msgs::Odometry::ConstPtr &msg)
{
	double current_x = msg->pose.pose.position.x, current_y = msg->pose.pose.position.y;
	double move_distance = sqrt(abs(current_x - start_x) * abs(current_x - start_x) + abs(current_y - start_y) * abs(current_y - start_y));
	if (isMove)
	{
		ROS_INFO("move_distance=%.3f M", move_distance);
	}
}

int main(int argc, char **argv)
{

	ros::init(argc, argv, "odem");

	ros::NodeHandle n;

	sub = n.subscribe("/odom", 1, setStartVelocity);

	sub2 = n.subscribe("/scout_status", 1, judgeMove);
	sub3 = n.subscribe("/odom", 1, showDistance);
	ros::spin();

	return 0;
}
