#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
	string baseLinkCalculated='laser_predict';
	string worldCalculated='world';
	string baseLinkActual='vehicle/085/lidar/front';
	string worldActual='map';

	ros::init(argc, argv, "error_calc");

  	ros::NodeHandle node;

  	tf::TransformListener listener;
  	ros::Rate rate(10.0);

  	ofstream DistanceFile("distance.txt");

  	DistanceFile<<"X_diff\tY_diff\tZ_diff\tdistance\ttimestamp\n";

  	tf::StampedTransform transformCalculated,transformActual,initial_transformCalculated,initial_transformActual;
  	bool isInit=false;
  	ros::Time timestamp_now,timestamp_prev;
  	tf::Vector3 translationCalculated,translationActual;
	float distance,X_diff,Y_diff,Z_diff;

  	while (node.ok()){
  
  		timestamp_prev=transform1.stamp_;

	    try{
	    	listener.waitForTransform(baseLinkActual,worldActual,
	                              ros::Time(0), ros::Duration(3.0));
	      	listener.lookupTransform(baseLinkActual,worldActual,
	                              ros::Time(0), transformActual);
	      	listener.waitForTransform(baseLinkCalculated,worldCalculated,
	                              ros::Time(0), ros::Duration(3.0));
	      	listener.lookupTransform(baseLinkCalculated,worldCalculated,
	                              ros::Time(0), transformCalculated);
	      	if(!isInit){
	      		initial_transformCalculated=transformCalculated;
	      		initial_transformActual=transformActual;
	      		isInit=true;
	      	}
	    }
	    catch (tf::TransformException ex){
	      ROS_ERROR("%s",ex.what());
	      ros::Duration(1.0).sleep();
	    }

	    timestamp_now=transformActual.stamp_;

	    if(timestamp_now!=timestamp_prev){
			translationActual=transformActual.getOrigin()-initial_transformActual.getOrigin();
			translationCalculated=transformCalculated.getOrigin()-initial_transformCalculated.getOrigin();

			X_diff=translationActual.x()-translationCalculated.x();
			Y_diff=translationActual.y()-translationCalculated.y();
			Z_diff=translationActual.z()-translationCalculated.z();
			distance=translation1.distance(translation2);

			DistanceFile<<X_diff<<"\t"<<Y_diff<<"\t"<<Z_diff<<"\t"<<distance<<"\t"<<timestamp_now<<"\n";

	    }

	    rate.sleep();
  }

	return 0;
}