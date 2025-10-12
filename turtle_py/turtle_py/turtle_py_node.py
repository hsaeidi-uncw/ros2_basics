#!/usr/bin/end/ python

import rclpy
from rclpy.node import Node

from turtlesim.msg import Pose 

from geometry_msgs.msg import Twist

from rclpy.qos import ReliabilityPolicy, QoSProfile

class TurtlePyNode(Node):

    def __init__(self):
        super().__init__('turtle_py_node')
        self.create_timer(0.1, self.timer_callback)
        self.subscriber = self.create_subscription(
        Pose, 
        '/turtle1/pose', self.pose_callback, 
        QoSProfile(depth = 10, reliability=ReliabilityPolicy.RELIABLE))
        self.publisher_ = self.create_publisher(Twist, '/turtle1/cmd_vel',10)
        self.kp = 1
        
    def timer_callback(self):
        ros_time_stamp = self.get_clock().now()
        #self.get_logger().info(str(ros_time_stamp))
        cmd_msg = Twist()
        cmd_msg.linear.x = self.kp*(8.0 - self.xt)
        self.publisher_.publish(cmd_msg)
        
    def pose_callback(self, msg):
        #self.get_logger().info(f'got x: {msg.x:.2f} meters')
        self.xt = msg.x

def main(args=None):
    rclpy.init(args = args)
    
    node = TurtlePyNode()
    rclpy.spin(node)
    print("Node started!")
    
    rclpy.shutdown()
    
    
if __name__ == '__main__':
    main()

