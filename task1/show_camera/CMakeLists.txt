set(OpenCV_DIR /usr/share/OpenCV) 
find_package(catkin REQUIRED COMPONENTS
  roscpp
  OpenCV
  cv_bridge
  image_transport
)
project(usb_cam)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

catkin_package()

include_directories(
  include 
  
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


add_executable(image_sub  src/image_sub.cpp)
target_link_libraries(image_sub  ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})

