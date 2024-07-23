#include "rclcpp/rclcpp.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

class JointTrajectoryPublisher : public rclcpp::Node {
public:
  JointTrajectoryPublisher() : Node("joint_trajectory_publisher") {
    publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>("/joint_trajectory_controller/joint_trajectory", 10);

    // Publiez immédiatement le trajet après la création du publisher, sans utiliser un timer.
    publishTrajectory();
  }

private:
  void publishTrajectory() {
    trajectory_msgs::msg::JointTrajectory msg;

    // msg.header.stamp = this->get_clock()->now();
    msg.header.stamp.sec = 0;
    msg.header.stamp.nanosec = 0;
    msg.joint_names = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};
    
    trajectory_msgs::msg::JointTrajectoryPoint point;
    point.positions = {0.0, 1.0, 1.0, 1.0, 1.0, 1.0}; // Remplacez ces valeurs par celles souhaitées
    point.velocities = {};
    point.accelerations = {};
    point.effort = {};
    point.time_from_start = rclcpp::Duration::from_seconds(5.0);

    msg.points.push_back(point);

    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Publishing Joint Trajectory");
  }

  rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<JointTrajectoryPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
