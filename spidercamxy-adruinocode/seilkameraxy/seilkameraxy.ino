#include <Stepper.h>
#include <math.h>

const int xaxis = 1950;
const int yaxis = 1800; 

float cl1 = 2600.00;
float cl2 = 2600.00;

float dl1;
float dl2;

const int frac = 350;
const float stepLength = 2.62;

const int stepsPerRevolution = 48;  // change this to fit the number of steps per revolution
// for your motor

Stepper motor1(stepsPerRevolution, 2, 3, 4, 5);
Stepper motor2(stepsPerRevolution, 9, 10, 11, 12);

float x;
float y;

void setup() {
  // initialize the serial port:
    x = 1000;
    y = 1000;
    getLengths();
    shmove();
  Serial.begin(9600);
}

void loop() {
    while(Serial.available() > 0) {
        x = Serial.parseInt();
        y = Serial.parseInt();
        if(Serial.read() == '\n') {
          if ((x > xaxis) || (y > yaxis) || (y < 1000)) {
             Serial.println("cant go there sowwy pal UwU");
             return;
          } else {
             getLengths();
          }
          if ((dl1 > 2600) || (dl2 > 2600)) {
             Serial.println("cant go there sowwy pal UwU");
             return;
          } else {
             Serial.println("okay lad ill be there in no time");
             shmove();
          }
        }
    }   
}

void shmove(){
  const float diff1 = dl1 - cl1;
  const float diff2 = dl2 - cl2;
  for (int i = 0; i <= frac; i++) {
    if ((cl1 <  dl1 - stepLength) || (cl1 > dl1 + stepLength)) {
      int step1 = (int) ceil(diff1/frac)/stepLength;
      Serial.println(step1);
      if (step1 > 0) {
        for (int j = 0; j <= abs(step1); j++) {
          motor1.step(-1);
          delay(50);
          cl1 -= stepLength;
        }
      } else if (step1 < 0) {
        for (int j = 0; j <= abs(step1); j++) {
          motor1.step(1);
          delay(50);          
          cl1 += stepLength;
          
        }
      }
      cl1 += step1*stepLength;
    }
    if ((cl2 < dl2 - stepLength) || (cl2 > dl2 + stepLength)) {
      int step2 = (int) ceil(diff2/frac)/stepLength;
      Serial.println(step2);
      if (step2 > 0) {
        for (int j = 0; j <= abs(step2); j++) {
          motor2.step(-1);
          delay(20);
          cl2 =- stepLength;
        }
      } else if (step2 < 0) {
        for (int j = 0; j <= abs(step2); j++) {
          motor2.step(1);
          delay(50);
          cl2 += stepLength;
        }
      }
    }
  delay(50);
  }
}

void getLengths(){    
    dl1 = sqrt(y * y + (x-40) * (x-40));
    dl2 = sqrt(y * y + (xaxis - (x+40)) * (xaxis - (x+40)));
}
