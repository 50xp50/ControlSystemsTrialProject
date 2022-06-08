#ifndef LED_H
#define LED_H

#include <Arduino.h> // default Arduino Library

void setupLEDS(); // initializes the LED's on breadboard to appropriate pins
void colorLED(int bulb, int color); // sets given LED to specified color
int decideColor(float num); // determines color for LED based on given number

#endif
