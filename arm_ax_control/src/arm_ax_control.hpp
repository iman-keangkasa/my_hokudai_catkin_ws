#ifndef FOLLOW_JOINT_TRAJECTORY_CLIENT
#define FOLLOW_JOINT_TRAJECTORY_CLIENT

#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/JointState.h>
#include <trajectory_msgs/JointTrajectory.h>

#include <chrono>
#include <sstream>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_model_loader/robot_model_loader.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

namespace arm_ax_control
{
  typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> TrajClient;

  class FollowJointTrajectoryClient
  {
  public:
    FollowJointTrajectoryClient();
    virtual ~FollowJointTrajectoryClient();

    void startTrajectory(control_msgs::FollowJointTrajectoryGoal goal);
    control_msgs::FollowJointTrajectoryGoal makeArmUpTrajectory(std::vector<double> joints_obj);
    actionlib::SimpleClientGoalState getState();

void PrintPose(std::string workspace,  geometry_msgs::Pose req_pose);
  
bool ReqMovement_byPose(geometry_msgs::Pose pose_req, robot_state::RobotStatePtr &kinematic_state, robot_state::JointModelGroup *joint_model_group, FollowJointTrajectoryClient &arm);
  
  private:
    ros::NodeHandle nh_;
    TrajClient traj_client_;
    ros::Subscriber joint_state_sub_;
    std::vector<std::string> joint_names_;
    bool got_joint_state_;
    std::vector<double> current_joint_state_;
    ros::AsyncSpinner spinner_;

    void jointStateCB(const sensor_msgs::JointState::ConstPtr &msg);
  };

  
} // namespace arm_ax_control
#endif /* FOLLOW_JOINT_TRAJECTORY_CLIENT */
