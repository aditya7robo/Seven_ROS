#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
class tester {
public:
	ros::NodeHandle nh;
	std_msgs::String _msg;
	ros::Publisher pub;
	tester(const std_msgs::String& msg)
		:_msg{msg}
	{
		pub = nh.advertise<std_msgs::String>("hello",100);
	}

	void spin(void){
			ros::Rate r(10);
		while(ros::ok()){
			pub.publish(_msg);
			r.sleep();
		}
	}

};

int main(int argc,char** argv)
{
	std_msgs::String hello;
  hello.data="Hello World";
	ros::init(argc,(char**) argv,"test_node");	
	tester test_node(hello);
  test_node.spin();

	return 0;	
}
