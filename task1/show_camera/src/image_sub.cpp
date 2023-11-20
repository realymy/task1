#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

cv::Mat image;

void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
  ROS_INFO_STREAM("Get Msg");
  try
  {
    image = cv_bridge::toCvShare(msg, "16UC1")->image;
    cv::imshow("view", image);
  }
  catch (cv_bridge::Exception &e)
  {
    ROS_ERROR("Could not convert from '%s' to '16UC1'.", msg->encoding.c_str());
  }
  cv::waitKey(1);
}
void imageCallback2(const sensor_msgs::ImageConstPtr &msg)
{
  ROS_INFO_STREAM("Get Msg");
  try
  {
    image = cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::imshow("view2", image);
  }
  catch (cv_bridge::Exception &e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
  cv::waitKey(1);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::namedWindow("view2");
  // cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/camera/depth/image_rect_raw", 1, imageCallback);
  image_transport::Subscriber sub2 = it.subscribe("/camera/color/image_raw", 1, imageCallback2);
  ros::spin();
  // cv::destroyWindow("view");
  cv::waitKey(0);
  return 0;
}
