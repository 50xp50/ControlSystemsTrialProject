# ControlSystemsTrialProject

The goal of this project is to build a IMU (mpu6050) controlled double-axis (x and y axis) laser turret.

Rules:
1) You must use an Arduino
  - Purchase of the official version is not necessary
2) The project must be written in C++
  - This is the standard language in the Arduino IDE, and what we use on the team.
3) You may ONLY use the standard libraries provided in the Arduino IDE (you may NOT use the mpu6050 library). 
  - Addition of other libraries will result in automatic disqualification. 
4) You must use the GY-521 MPU-6050 accelerometer for orientation feedback.
  - Header pins must be solder to the board (Soldering station available @ SCE)
5) Orientation feedback must be printed to the Arduino serial monitor
  - Print out the x, y, and z accelerometer axis data
6) You must be able to control the laser turret by sending serial commands to the Arduino via the arduino serial port The product must support the following commands
  - Set target orientation for yaw & pitch
7) You may use any servos or motors of your choice to build your device.
8) You must publish your gimbal project code into a GitHub repository.
  - Bonus points for employing a feature branching workflow
9) You must work alone on this project. Working in teams is strictly forbidden.
