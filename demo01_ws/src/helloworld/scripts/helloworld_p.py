#! /usr/bin/python3

import rospy

if __name__ == "__main__":
	rospy.init_node("hello_p")
	rospy.loginfo("hello world! by python")