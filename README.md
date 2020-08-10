# SLAM_Error_Calculator
This repo will calculate the error in different SLAM pipelines

## How to Run
- Clone this repo in your src folder of catkin workspace
- Run 
```
catkin_make
```
- Run 2 bag files where the ground truth tf and calculated tf is running
- Make neccessary changes in frame names in [code file](src/error-calculator.cpp)
- Run this node 
```
rosrun tf_error error_calc
```
- A distance.txt file will be created. Check that for error results
