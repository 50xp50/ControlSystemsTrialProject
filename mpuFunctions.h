#ifndef MPUFUNCTIONS_H
#define MPUFUNCTIONS_H

#include <Arduino.h> // default Arduino Library
#include <Wire.h> // library for I2C Communication

struct  mpuData{
  long rawAccelX, rawAccelY, rawAccelZ;
  float accelX, accelY, accelZ;
  long rawGyroX, rawGyroY, rawGyroZ;
  float gyroX, gyroY, gyroZ;
};

void initializeMPU(); // sets up and initializes mpu with specified ranges and accuracy
void grabAccelerometerData(mpuData &var); // recieves the raw accelerometer data and stores it, while also converting it to find the g-forces
void grabGyroscopeData(mpuData &var); // recieves the raw gyrometer data and stores it, while also converting it to find the angular velocity
void printMPU(mpuData &var); // prints out formatted accelerometer and gyrometer data to serial monitor

#endif
