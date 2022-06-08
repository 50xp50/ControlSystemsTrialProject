#include "led.h"

int redPin1 = 7, greenPin1 = 6, bluePin1 = 5, redPin2 = 4, greenPin2 = 3, bluePin2 = 2; // setting up pins for the two RGB LED's

void setupLEDS(){
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);
}

void colorLED(int bulb, int color){
  if (bulb == 1){
    digitalWrite(redPin1, LOW);
    digitalWrite(greenPin1, LOW);
    digitalWrite(bluePin1, LOW);
    if (color == 1) digitalWrite(redPin1, HIGH);
    else if (color == 2) digitalWrite(greenPin1, HIGH);
    else digitalWrite(bluePin1, HIGH);
  }
  else{
    digitalWrite(redPin2, LOW);
    digitalWrite(greenPin2, LOW);
    digitalWrite(bluePin2, LOW);
    if (color == 1) digitalWrite(redPin2, HIGH);
    else if (color == 2) digitalWrite(greenPin2, HIGH);
    else digitalWrite(bluePin2, HIGH);
  }
}

int decideColor(float num){
  if (num < 100 && num > 80) return 3;
  if (num > 100) return 2;
  if (num < 80) return 1;
}
