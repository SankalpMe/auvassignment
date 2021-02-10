#include "ros/ros.h"

#include "auvros/Navigator.h"

#include "std_msgs/Int64.h"

class AutoPose{
	
		
	
		ros::ServiceClient client;
		ros::Subscriber sub;
		long int x;
		public:
		
			void init(ros::NodeHandle &n){
					x = -1;
					client = n.serviceClient<auvros::Navigator>("navigator");
				
				 sub  = n.subscribe("autopose", 1000, &AutoPose::callback,this);
			}
			
			void callback(const std_msgs::Int64::ConstPtr &msg){
				
					std::cout  << "input:" << msg->data << std::endl;
					x = msg->data;
					
					auvros::Navigator navSrv;
					
					navSrv.request.n = x;
					
					if(client.call(navSrv)){
							std::cout << "Fibonacii:" << navSrv.response.out << std::endl;
					}
			}
};

int main(int argc,char **argv){
	ros::init(argc,argv,"autopose");
	
	ros::NodeHandle n;
	AutoPose ap;
	ap.init(n);
	
	
	ros::spin();
	

	
}
