#include "ros/ros.h"
#include "scout_msgs/ScoutStatus.h"
#include "string.h"
#include "iostream"
using namespace std;

void read(const scout_msgs::ScoutStatus::ConstPtr &msg)
{

    cout << "linear_velocity=" << msg->linear_velocity << "   angular_velocity=" << msg->angular_velocity << endl;
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "velocity");

    ros::NodeHandle n;
    ros::Subscriber sub;
    sub = n.subscribe("/scout_status", 1, read);

    ros::spin();

    return 0;
}
