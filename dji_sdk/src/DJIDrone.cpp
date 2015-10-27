#include "dji_sdk.h"
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h> 
#include <actionlib/client/terminal_state.h> 


class DJIDrone
{
	std::string ns;
	ros::NodeHandle nh;

	actionlib::SimpleActionClient<dji_sdk::DroneTaskAction> drone_task_action_client;
	actionlib::SimpleActionClient<dji_sdk::LocalPositionNavigationAction> local_position_navigation_action_client;
	actionlib::SimpleActionClient<dji_sdk::GlobalPositionNavigationAction> global_position_navigation_action_client;
	actionlib::SimpleActionClient<dji_sdk::WaypointNavigationAction> waypoint_navigation_action_client;

	ros::ServiceClient attitude_control_service;
    ros::ServiceClient camera_action_control_service;
    ros::ServiceClient drone_task_control_service;
    ros::ServiceClient gimbal_angle_control_service;
    ros::ServiceClient gimbal_speed_control_service;
    ros::ServiceClient global_position_control_service;
    ros::ServiceClient local_position_control_service;
    ros::ServiceClient sdk_permission_control_service;
    ros::ServiceClient velocity_control_service;

	DJIDrone(std::string ns): ns(ns), nh(ns)
	{
		drone_task_action_client = actionlib::SimpleActionClient<dji_sdk::DroneTaskAction>(nh, "dji_sdk/drone_task_action", true);
		local_position_navigation_action_client = actionlib::SimpleActionClient<dji_sdk::LocalPositionNavigationAction>(nh, "dji_sdk/local_position_navigation_action", true);
		global_position_navigation_action_client = actionlib::SimpleActionClient<dji_sdk::GlobalPositionNavigationAction>(nh, "dji_sdk/global_position_navigation_action", true);
		waypoint_navigation_action_client = actionlib::SimpleActionClient<dji_sdk::WaypointNavigationAction>(nh, "dji_sdk/waypoint_navigation_action", true);

	    attitude_control_service = nh.serviceClient<dji_sdk::AttitudeControl>("dji_sdk/attitude_control");
	    camera_action_control_service = nh.serviceClient<dji_sdk::CameraActionControl>("dji_sdk/camera_action_control");
	    drone_task_control_service = nh.serviceClient<dji_sdk::DroneTaskControl>("dji_sdk/drone_task_control");
	    gimbal_angle_control_service = nh.serviceClient<dji_sdk::GimbalAngleControl>("dji_sdk/gimbal_angle_control");
	    gimbal_speed_control_service = nh.serviceClient<dji_sdk::GimbalSpeedControl>("dji_sdk/gimbal_speed_control");
	    global_position_control_service = nh.serviceClient<dji_sdk::GlobalPositionControl>("dji_sdk/global_position_control");
	    local_position_control_service = nh.serviceClient<dji_sdk::LocalPositionControl>("dji_sdk/local_position_control");
	    sdk_permission_control_service = nh.serviceClient<dji_sdk::SDKPermissionControl>("dji_sdk/sdk_permission_control");
	    velocity_control_service = nh.serviceClient<dji_sdk::VelocityControl>("dji_sdk/velocity_control");
	}

	bool takeoff()
	{
		dji_sdk::DroneTaskControl drone_task_control;
		drone_task_control.request.task = 4;
		return drone_task_control_service.call(drone_task_control) && drone_task_control.response.result;
	}

	bool land()
	{
		dji_sdk::DroneTaskControl drone_task_control;
		drone_task_control.request.task = 6;
		return drone_task_control_service.call(drone_task_control) && drone_task_control.response.result;
	}

	bool gohome()
	{
		dji_sdk::DroneTaskControl drone_task_control;
		drone_task_control.request.task = 1;
		return drone_task_control_service.call(drone_task_control) && drone_task_control.response.result;
	}

	bool take_picture()
	{
		dji_sdk::CameraActionControl camera_action_control;
		camera_action_control.request.action = 0;
		return camera_action_control_service.call(camera_action_control) && camera_action_control.response.result;
	}

	bool record_video()
	{
		dji_sdk::CameraActionControl camera_action_control;
		camera_action_control.request.action = 1;
		return camera_action_control_service.call(camera_action_control) && camera_action_control.response.result;
	}
	
	bool stop_video()
	{
		dji_sdk::CameraActionControl camera_action_control;
		camera_action_control.request.action = 2;
		return camera_action_control_service.call(camera_action_control) && camera_action_control.response.result;
	}

	bool gimbal_speed_control(int roll_rate, int pitch_rate, int yaw_rate)
	{
		dji_sdk::GimbalSpeedControl gimbal_speed_control;
		gimbal_speed_control.request.roll_rate = roll_rate;
		gimbal_speed_control.request.pitch_rate = pitch_rate;
		gimbal_speed_control.request.yaw_rate = yaw_rate;
		return gimbal_speed_control_service.call(gimbal_speed_control) && gimbal_speed_control.response.result;

	}

	bool gimbal_angle_control(unsigned char ctrl_flag, int roll, int pitch, int yaw, int duration)
	{
		dji_sdk::GimbalAngleControl gimbal_angle_control;
		gimbal_angle_control.request.flag = ctrl_flag;
		gimbal_angle_control.request.roll = roll;
		gimbal_angle_control.request.pitch = pitch;
		gimbal_angle_control.request.yaw = yaw;
		gimbal_angle_control.request.duration= duration;
		return gimbal_angle_control_service.call(gimbal_angle_control) && gimbal_angle_control.response.result;

	}
	
	bool sdk_permission_control(unsigned char request)
	{
		dji_sdk::SDKPermissionControl sdk_permission_control;
		sdk_permission_control.control_enable = request;
		
		return sdk_permission_control_service.call(sdk_permission_control) && sdk_permission_control.respoinse.result;

	}
	bool attitude_control(unsigned char ctrl_flag, float x, float y, float z, float yaw)
	{
		dji_sdk::AttitudeControl attitude_control;
		attitude_control.request.flag = ctrl_flag;
		attitude_control.request.x = x;
		attitude_control.request.y = y;
		attitude_control.request.z = z;
		attitude_control.request.yaw = yaw;

		return attitude_control_service.call(attitude_control) && attitude_control.response.result;
	}

<<<<<<< HEAD
	
=======
	bool velocity_control(int frame, float x, float y, float z, float yaw)
	{
		dji_sdk::VelocityControl velocity_control;
		velocity_control.request.frame = frame;
		velocity_control.request.x = x;
		velocity_control.request.y = y;
		velocity_control.request.z = z;
		velocity_control.request.yaw = yaw;
	
		return velocity_control_service.call(veloctiy_control) && velocity_control.response.result;

	}

	bool local_position_control(float x, float y, float z, float yaw)
	{
		dji_sdk::LocalPositionControl local_position_control;
		local_position_control.request.x = x;
		local_position_control.request.y = y;
		local_position_control.request.z = z;
		local_position_control.request.yaw = yaw;
		
		return local_position_control_service.call(local_position_control) && local_position_control.respoinse.result;

	}
>>>>>>> 58c115a... garbage

	bool global_position_control(double latitude, double longitude, float altitude, float yaw)
	{
		dji_sdk::GlobalPositionControl global_position_control;
		global_position_control.request.latitude = latitude;
		global_position_control.request.longitude = longitude;
		global_position_control.request.altitude = altitude;
		global_position_control.request.yaw = yaw;

		return global_position_control_service.call(global_position_control) && global_position_contrl.response.result;
	}


	bool local_position_navigation(float x, float y, float z)
	{
		dji_sdk::LocalPostionNavigationGoal local_position_navigation_goal;
		local_position_navigation_goal.x = x;
		local_position_navigation_goal.y = y;
		local_position_navigation_goal.z = z;
		local_position_navigation_action_client.sendGoal(local_position_navigation_goal);

	}

	bool global_position_navigation()
	{

	}

	bool waypoint_navigation()
	{

	}

};
int main() {

}