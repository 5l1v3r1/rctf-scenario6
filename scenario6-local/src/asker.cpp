#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
using namespace std;

string answer = "Who I am? Use the force Luke.";

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    string correct_answer = "Your father";
    string flag = "Correct! Here's your password: Cx,^kj53R,<uk{</";
    if (msg->data.c_str() == correct_answer) {
        answer = flag;
    }
}

int main(int argc, char **argv)
{
  int user_topic = 17;
  int total_topics = 50;
  ros::Publisher fake_topics[50];
  std::string base_topic_name = "user_answer_";
  std_msgs::String incorrect_topic_msg;
  incorrect_topic_msg.data = "Not the topic you are looking for.";
  ros::init(argc, argv, "node_rctf");
  ros::NodeHandle n;

  for( int i = 0; i < total_topics; i++) {
    if (i != user_topic) {
      std::stringstream topic_name;
      topic_name << base_topic_name << i;
      ros::Publisher fake_topic = n.advertise<std_msgs::String>(topic_name.str(), 1000);
      fake_topics[i] = fake_topic;
    }
  }
  std::stringstream user_topic_name;
  user_topic_name << base_topic_name << user_topic;
  ros::Subscriber sub = n.subscribe(user_topic_name.str(), 1000, chatterCallback);
  ros::Publisher flag_pub = n.advertise<std_msgs::String>("flag", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok()){
    std_msgs::String msg;
    std::stringstream ss;
    ss << answer;
    msg.data = ss.str();
    flag_pub.publish(msg);
    for (int i = 0; i < total_topics; i++) {
      if (i != user_topic) {
        fake_topics[i].publish(incorrect_topic_msg);
      }
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
