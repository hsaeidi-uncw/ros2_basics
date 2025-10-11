#include<iostream>
#include<rclcpp/rclcpp.hpp>
#include<geometry_msgs/msg/twist.hpp>
#include<turtlesim/msg/pose.hpp>


class TurtleControl : public rclcpp::Node {

public:
	//constructor
	TurtleControl():Node("turtle_control"){
	        kp = 1.0;
		//the timer for regular control loop
		timer_ = this->create_wall_timer(
			std::chrono::milliseconds(static_cast<int>(100)),
			std::bind(&TurtleControl::timer_callback,this));
		publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
		pos_sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10, std::bind(&TurtleControl::pose_callback,this, std::placeholders::_1));
		
			
	}
	
	
private:
	void timer_callback(){
		RCLCPP_INFO(this->get_logger(), "call_back %d", this->counter);
		t_cmd.linear.x = kp*(8.0 -xt);
		
		publisher_->publish(t_cmd);
		
		this->counter++;
	}
	
	void pose_callback(const turtlesim::msg::Pose msg){
	  //RCLCPP_INFO(this->get_logger(), "x_t %f", msg.x);
	  this->xt = msg.x;
	}
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
	rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pos_sub_;
	geometry_msgs::msg::Twist t_cmd;
	float kp;
	float xd;
	float xt;
	
	int counter = 1;
	

};

int main(int argc, char ** argv){
	//turtle_cpp_control::test();
//test();
	rclcpp::init(argc, argv);
	//TurtleControl tc_;
	//tc_.test();
	//tc_.show_vars();
	auto node = std::make_shared<TurtleControl>();
	rclcpp::spin(node);
	rclcpp::shutdown();
	std::cout<<"main function\n";

 	return 0;

}



