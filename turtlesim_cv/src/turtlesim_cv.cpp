#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;


//methods to move and rotate the robot for the C and V
void movec();
void movev();
void rotate(double angular_speed, double relative_angle, bool clockwise);



int main(int argc, char **argv)
{
    // Initiate new ROS node named "turtlesim_cv"
    ros::init(argc, argv, "turtlesim_cv");
    ros::NodeHandle n;

    //Generate publisher for Twist messages
    velocity_publisher=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);


    //Sequence of movements for C and V
    ros::Rate loop_rate(0.5);
    loop_rate.sleep();
    rotate(2,2.5,1);
    movec();
    rotate(2,0.47,1);
    movev();
    rotate(2,2,0);
    movev();



}

void movec(){
    geometry_msgs::Twist vel_msg;

    // Define times for how long message should be published
    double t0=ros::Time::now().toSec();
    double t1;
    ros::Rate loop_rate(10);


    //set linear velocity
    vel_msg.linear.x=2;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;

    //set angular velocity
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=-1.8;


    // Publish velocity as long as time is not exceeded
    do{
    // Publish velocity
    velocity_publisher.publish(vel_msg);

    // Update time t1
    t1=ros::Time::now().toSec();

    ros::spinOnce();
    loop_rate.sleep();


    }while((t1-t0)<2.3);


    // Publish velovity to stop the turtlesim
    vel_msg.linear.x=0;
    vel_msg.angular.z=0;
    velocity_publisher.publish(vel_msg);

}

void rotate(double angular_speed, double relative_angle, bool clockwise){
    geometry_msgs::Twist vel_msg;


    //set linear velocity
    vel_msg.linear.x=0;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;

    //set angular velocity
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;

    if (clockwise==1)
        vel_msg.angular.z=-abs(angular_speed);
    else
        vel_msg.angular.z=abs(angular_speed);


    // Define times and current_angle
    double current_angle=0.0;
    double t0=ros::Time::now().toSec();
    double t1;

    // Publish velocity as long as relative_angle is not exceeded
    do{

        // Publish velocity
        velocity_publisher.publish(vel_msg);

        //Update time and angle
        t1=ros::Time::now().toSec();
        current_angle=angular_speed*(t1-t0);

        ros::spinOnce();

    }while(current_angle<relative_angle);

    // Publish velocity to stop the turtlesim
    vel_msg.angular.z=0;
    velocity_publisher.publish(vel_msg);
}


void movev(){
    geometry_msgs::Twist vel_msg;

     // Define times for how long message should be published
    double t0=ros::Time::now().toSec();
    double t1;
    ros::Rate loop_rate(10);

    //set linear velocity
    vel_msg.linear.x=2;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;

    //set angular velocity
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;

     // Publish velocity as long as time is not exceeded
    do{

    // Publish velocity
    velocity_publisher.publish(vel_msg);

    // Update time
    t1=ros::Time::now().toSec();

    ros::spinOnce();
    loop_rate.sleep();


    }while((t1-t0)<1.01);


    // Publish velocity to stop the turtlesim
    vel_msg.linear.x=0;
    velocity_publisher.publish(vel_msg);

}


