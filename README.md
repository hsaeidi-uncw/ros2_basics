# ros2_basics

Example of testing controllers after building the package

run one of the cpp or python nodes, then, in a new terminal

ros2 service call /turtle1/p_control t_control_interfaces/srv/ControlParams "{xd : 1.0, kp : 5}"
