#include "ros/ros.h"
#include "auvros/Navigator.h"

bool navigate(auvros::Navigator::Request &req,auvros::Navigator::Response &res){
	long int a = 0;
	long int b = 1;
	if(req.n > 1) {
		for(int i = 0 ; i < req.n-1;i++){
			long int temp = b;
			b = a + b;
			a = temp;

		}	
	}else{
		if(req.n < 1 ){
			ROS_ERROR("Invalid Input n < 1");
                	return false;	
		}
	}
	res.out = a;

	ROS_INFO("request: n=%ld", (long int)req.n);
	ROS_INFO("sleeping for 5 seconds.");

	ros::Duration(5.0).sleep();


  	ROS_INFO("sending back response: [%ld]", (long int)res.out);
	return true;
	
}

int main(int argc,char **argv){
	ros::init(argc,argv,"navigator_server");

	ros::NodeHandle n;
	
	ros::ServiceServer service  = n.advertiseService("navigator",navigate);
	ROS_INFO("ready to navigate");
	ros::spin();

	return 0;
}
