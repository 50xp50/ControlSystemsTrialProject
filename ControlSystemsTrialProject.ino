#include "mpuFunctions.h"
#include "led.h"
#include <Servo.h>

int choice; // variable for user menu selection
float roll = 90, pitch = 90; // roll and pitch angle variables for servos
bool rollGiven = false, pitchGiven = false; // validation variables for roll and pitch angles for manual option

Servo rollServo, pitchServo; // servo declarations
mpuData mpu1; // mpu declaration

void setup() {
  Serial.begin(9600); // start serial transmission
  Wire.begin(); // start I2C communication

  // setup both servos, and initialize their locations
  rollServo.attach(9);
  pitchServo.attach(10);
  rollServo.write(roll);
  pitchServo.write(pitch);

  // setting up LED's
  setupLEDS();
  colorLED(1, 3);
  colorLED(2, 3);
  
  initializeMPU(); // setup and initialize mpu
  
  printMenu(); // print main menu
}

void loop() {
  while(!Serial.available())choice = Serial.parseInt(); // takes user input to choose which mode for turret
  
  while (choice == 1){ // manual mode for turret
    
    if (!rollGiven){ // takes roll input if there isnt already one
      rollGiven = true;
      Serial.println("What would you like the roll to be? (From -90 to 90)");
      clearSerialBuffer();
      while(!Serial.available())roll = Serial.parseFloat();
    }
    
    if (!pitchGiven){ // takes pitch input if there isnt already one
      pitchGiven = true;
      Serial.println("What would you like the pitch to be? (From -90 to 90)");
      clearSerialBuffer();
      while(!Serial.available())pitch = Serial.parseFloat();
    }

    // writes the given angles to the two servos
    rollServo.write(90 + roll);
    pitchServo.write(90 + pitch);

    // updates LED's to appropriate color for angle
    colorLED(1, decideColor(90 + roll));
    colorLED(2, decideColor(90 + pitch)); 
  }
  
  while (choice == 2){ // automatic mode for turret
    
    // grabs accelerometer and gyrometer data, and prints it out to serial monitor
    grabAccelerometerData(mpu1);
    grabGyroscopeData(mpu1);
    printMPU(mpu1);

    // calculates the roll and pitch angles using trig and the accelerometer data
    roll = (atan2((-mpu1.rawAccelX), sqrt(mpu1.rawAccelY * mpu1.rawAccelY  + mpu1.rawAccelZ * mpu1.rawAccelZ)) * 180.0 / PI);
    pitch = (atan2(mpu1.rawAccelY, mpu1.rawAccelZ) * 180.0 / PI);

    // sets the servo's to orient themselves to mirror the mpu's movement
    rollServo.write(90 - roll);
    pitchServo.write(90 - pitch);

    // updates LED's to appropriate color for angle
    colorLED(1, decideColor(90 - roll));
    colorLED(2, decideColor(90 - pitch)); 

    // time delay for each sample from mpu
    delay(100);  
  }
}

// basic main menu function to display options
void printMenu(){
  Serial.println("What would you like to do?");
  Serial.println("1) Manually Asssign Turret Coords");
  Serial.println("2) Have an automatic turret");
  Serial.println("[Enter which number]");
}

// clears the serial data buffer, so "!serial.available()" will continue to work with multiple sequential data inputs
void clearSerialBuffer(){
  Serial.end();
  Serial.begin(9600);
}
