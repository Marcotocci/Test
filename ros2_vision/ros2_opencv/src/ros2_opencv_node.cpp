#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/header.hpp"
#include <chrono>
#include <cv_bridge/cv_bridge.h> // cv_bridge converts between ROS 2 image messages and OpenCV image representations.
#include <image_transport/image_transport.hpp> // Using image_transport allows us to publish and subscribe to compressed image streams in ROS2
#include <opencv2/opencv.hpp> // We include everything about OpenCV as we don't care much about compilation time at the moment.
 
using namespace std::chrono_literals;
using std::placeholders::_1;
 
class MinimalImagePublisher : public rclcpp::Node {
public:
  MinimalImagePublisher() : Node("opencv_image_publisher"), count_(0) {
    publisher_ =
        this->create_publisher<sensor_msgs::msg::Image>("random_image", 10);


    subscriber_ =
        this->create_subscription<sensor_msgs::msg::Image>(
          "/camera", 10, std::bind(&MinimalImagePublisher::topic_callback, this, _1));
  }

 
private:
  
    void topic_callback(const sensor_msgs::msg::Image & msg_) //Secondo me qua dentro va messo msg_, se vedete l'api mi pare ci sia un puntatore, verificate
    {
      cv_bridge::CvImagePtr cv_ptr;

      cv_ptr = cv_bridge::toCvCopy(&msg_, sensor_msgs::msg::Image )
  }

  // Setup SimpleBlobDetector parameters.
  cv::SimpleBlobDetector::Params params;
 
  // Soglia di colori, 0 indica nero, 255 indica bianco
  params.minThreshold = 10;
  params.maxThreshold = 200;
  
  // Filter by Area, intende l'area dei pixel
  params.filterByArea = true;
  params.minArea = 1500;
  
  // Filter by Circularity
  params.filterByCircularity = true;
  params.minCircularity = 0.1;
  
  // Filter by Convexity
  params.filterByConvexity = true;
  params.minConvexity = 0.87;
  
  // Filter by Inertia
  params.filterByInertia = true;
  params.minInertiaRatio = 0.01;

  sensor_msgs::msg::Image::SharedPtr msg_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
};
 
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  // create a ros2 node
  auto node = std::make_shared<MinimalImagePublisher>();
 
  // process ros2 callbacks until receiving a SIGINT (ctrl-c)
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
