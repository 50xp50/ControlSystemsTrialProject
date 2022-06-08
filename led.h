#ifndef LED_H
#define LED_H

#include <Arduino.h> // default Arduino Library

void setupLEDS();
void colorLED(int bulb, int color);
int decideColor(float num);

#endif
