#include "mpuFunctions.h"

void initializeMPU(){
  Wire.beginTransmission(0x68); // accessing MPU
  Wire.write(0x6B); // accessing the power management register
  Wire.write(0x00); // setting the Sleep bit in the power management register to low
  Wire.endTransmission();
  Wire.beginTransmission(0x68); // accessing MPU
  Wire.write(0x1C); // accessing the accelerometer configuration register
  Wire.write(0x00); // setting accelerometer full-scale range to +-2g's
  Wire.endTransmission();
  Wire.beginTransmission(0x68); // accessing MPU
  Wire.write(0x1B); // accessing the gyroscope configuration register
  Wire.write(0x00); // setting the gyroscope full-scale range to +-250deg/s
  Wire.endTransmission();
}

void grabAccelerometerData(mpuData &var){
  Wire.beginTransmission(0x68); // accessing MPU
  Wire.write(0x3B); // location for the first of the 6 registers for the acceleration data
  Wire.endTransmission();
  Wire.requestFrom(0x68,6); // grab data from 6 registers starting at 3B
  while(Wire.available() < 6);// waits for all 6 bytes of data first, then reads them
  var.rawAccelX = Wire.read()<<8 | Wire.read(); // stores the first 2 bytes (which are the x-axis registers) into the xout
  var.rawAccelY = Wire.read()<<8 | Wire.read(); // stores the next 2 bytes (which are the y-axis registers)into the yout
  var.rawAccelZ = Wire.read()<<8 | Wire.read(); // stores the final 2 bytes(which are the z-axis registers)into the zout
  // the raw data for each axis is 16bit, with 8bits (1 byte) in each register.
  // that is why we shift the first registers data for each axis by 8 bits, since it is 
  // supposed to represent the most significant 8bits.
  
  var.accelX = (var.rawAccelX / 16384.0) -0.08; // find the g-force for x-axis with given accuracy constant for selected full-scale range.
  var.accelY = (var.rawAccelY / 16384.0) + 0.02; // find the g-force for y-axis with given accuracy constant for selected full-scale range.
  var.accelZ = (var.rawAccelZ / 16384.0)+ 0.12; // find the g-force for z-axis with given accuracy constant for selected full-scale range.
  // the addition/subtraction with constants is to try to zero out and calibrate the specific mpu being used
}

void grabGyroscopeData(mpuData &var){
  Wire.beginTransmission(0x68); // accessing MPU
  Wire.write(0x43); // location for the first of the 6 registers for the gyroscope data
  Wire.endTransmission();
  Wire.requestFrom(0x68,6); // grab data from 6 registers starting at 43
  while(Wire.available() < 6);// waits for all 6 bytes of data first, then reads them
  var.rawGyroX = Wire.read()<<8 | Wire.read(); // stores the first 2 bytes (which are the x-axis registers) into the xout
  var.rawGyroY = Wire.read()<<8 | Wire.read(); // stores the next 2 bytes (which are the y-axis registers)into the yout
  var.rawGyroZ = Wire.read()<<8 | Wire.read(); // stores the final 2 bytes(which are the z-axis registers)into the zout
  // the raw data for each axis is 16bit, with 8bits (1 byte) in each register.
  // that is why we shift the first registers data for each axis by 8 bits, since it is 
  // supposed to represent the most significant 8bits. they are then OR'd with the following
  // 8 bits in order to make the complete 16bit number
  
  var.gyroX = var.rawGyroX / 131.0; // find the angular velocity for x-axis with given accuracy constant for selected full-scale range
  var.gyroY = var.rawGyroY / 131.0; // find the angular velocity for y-axis with given accuracy constant for selected full-scale range
  var.gyroZ = var.rawGyroZ / 131.0; // find the angular velocity for z-axis with given accuracy constant for selected full-scale range
}

void printMPU(mpuData &var){
  Serial.print("Acceleration (G's): ");
  Serial.print("X = ");
  Serial.print(var.accelX);
  Serial.print(" Y = ");
  Serial.print(var.accelY);
  Serial.print(" Z = ");
  Serial.print(var.accelZ);
  Serial.print(" Rotational Force (rad/s): ");
  Serial.print("X = ");
  Serial.print(var.gyroX);
  Serial.print(" Y = ");
  Serial.print(var.gyroY);
  Serial.print(" Z = ");
  Serial.println(var.gyroZ);
}
