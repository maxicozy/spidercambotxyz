#include <Stepper.h>
#include <math.h>

const int xaxis = 1950;
const int yaxis = 1800; 

float cl1 = 2600.00;
float cl2 = 2600.00;

float dl1 = cl1;
float dl2 = cl2;; 

const float stepLength = 2.62;

const int stepsPerRevolution = 48;  // change this to fit the number of steps per revolution
// for your motor

Stepper motor1(stepsPerRevolution, 2, 3, 4, 5);
Stepper motor2(stepsPerRevolution, 9, 10, 11, 12);

float x;
float y;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
    while(Serial.available() > 0) {
        x = Serial.parseInt();
        y = Serial.parseInt();
        if(Serial.read() == '\n') {
          if ((x > xaxis) || (y > yaxis) || (y < 50)) {
             Serial.println("cant go there sowwy pal UwU");
             return;
          } else {
             getLengths();
          }
          if ((dl1 > 2600) || (dl2 > 2600)) {
             Serial.println("cant go there sowwy pal UwU");
             return;Stepper motor2(stepsPerRevolution, 9, 10, 11, 12);
          } else {
             Serial.println("okay lad ill be there in no time");
          }
        }
    }
    if (cl1 < dl1 - stepLength) {
      motor1.step(-1);
      cl1 += stepLength;
      delay(10);
    }
    if (cl1 > dl1  + stepLength ) {
      motor1.step(1);
      cl1 -= stepLength;
      delay(10);
    }
    if (cl2 < dl2 - stepLength) {
      motor2.step(-1);
      cl2 += stepLength;
      delay(10);
    }
    if (cl2 > dl2  + stepLength ) {
      motor2.step(1);
      cl2 -= stepLength;
      delay(10);
    }  
}

void getLengths(){    
    dl1 = sqrt(y * y + (x-40) * (x-40));
    dl2 = sqrt(y * y + (xaxis - (x+40)) * (xaxis - (x+40)));
}
