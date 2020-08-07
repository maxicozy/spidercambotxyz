#include <Stepper.h>
#include <math.h>

const float xaxis = 2320;
const float yaxis = 3355; 
const float zaxis = 2000;

float boxDelay = 40;

float cl1 = 2630.00;
float cl2 = 2630.00;
float cl3 = 2630.00;
float cl4 = 2630.00;
float cl5 = 1700.00;

float dl1 = cl1;
float dl2 = cl2;
float dl3 = cl3;
float dl4 = cl4;
float dl5 = cl5;        

const int frac = 250;
const float stepLength = 2.62;
const float schmalzStepLength = 0.625;

const int stepsPerRevolution = 48;  // change this to fit the number of steps per revolution
// for your motor

Stepper motor1(stepsPerRevolution, 14, 15, 16, 17);
Stepper motor2(stepsPerRevolution, 6, 7, 8, 9);
Stepper motor3(stepsPerRevolution, 18, 19, 4, 5);
Stepper motor4(stepsPerRevolution, 10, 11, 12, 13);

const int powerDir = 2;
const int powerStep = 3;
//stromversorgung macht 3 cm mit einer umdrehung a 384 steps

int x ;
int y ;
int z;


void getLengths(){    
    dl1 = sqrt(z * z + (y-boxDelay) * (y-boxDelay) + (xaxis - (x+boxDelay)) * (xaxis - (x+boxDelay)));
    dl2 = sqrt(z * z + (x-boxDelay) * (x-boxDelay) + (y-boxDelay) * (y-boxDelay));
    dl3 = sqrt(z * z + (yaxis - (y+boxDelay)) * (yaxis - (y+boxDelay)) + (x-boxDelay) * (x-boxDelay));
    dl4 = sqrt(z * z + (yaxis - (y+boxDelay)) * (yaxis - (y+boxDelay)) + (xaxis - (x+boxDelay)) * (xaxis - (x+boxDelay)));
    dl5 = sqrt(z * z + (x-(xaxis/2))*(x-(xaxis/2)) + (y-(yaxis/2))*(y-(yaxis/2)));
    Serial.print(dl1);
    Serial.print(dl2); 
    Serial.print(dl3);
    Serial.print(dl4);
    Serial.println(dl5);
}

void setup() {
  // initialize the serial port:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);            
}

void loop() {
    while(Serial.available() > 0) {
       x = Serial.parseInt();
       y = Serial.parseInt();
       z = Serial.parseInt();
       Serial.print(x);
       Serial.print(y);
       Serial.println(z);
       if(Serial.read() == '\n') {
          if (x > xaxis || y > yaxis || z > zaxis) {
             Serial.println("cant go there sowwy pal UwU");
             return;
          } else {
             getLengths();
          }
          if (dl1 > 2630 || dl2 >  2630 || dl3 > 2630|| dl4 > 2630) {
             Serial.println("cant go there sowwy pal UwU");
             return;
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
    if (cl3 < dl3 - stepLength) {
      motor3.step(-1);
      cl3 += stepLength;
      delay(10);
    }
    if (cl3 > dl3  + stepLength ) {
      motor3.step(1);
      cl3 -= stepLength;
      delay(10);
    }
    if (cl4 < dl4 - stepLength) {
      motor4.step(-1);
      cl4 += stepLength;
      delay(10);
    }
    if (cl4 > dl4  + stepLength ) {
      motor4.step(1);
      cl4 -= stepLength;
      delay(10);
    }
    if (cl5 < dl5 - schmalzStepLength) {
      digitalWrite(2, HIGH);
      cl5 += schmalzStepLength;
      for (int i = 0; i<=8; i++) {
        digitalWrite(3, HIGH);
        delay(1);
        digitalWrite(3, LOW);
        delay(1);
      }
    }
    if (cl5 > dl5  + schmalzStepLength) {
      digitalWrite(2, LOW);
      cl5 -= schmalzStepLength;
      for (int i = 0; i<=8; i++) {
        digitalWrite(3, HIGH);
        delay(1);
        digitalWrite(3, LOW);
        delay(1);
      }
    }
}
