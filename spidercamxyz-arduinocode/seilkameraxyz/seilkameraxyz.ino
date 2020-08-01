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

float dl1;
float dl2;
float dl3;
float dl4;
float dl5;

const int frac = 250;
const float stepLength = 2.62;
const float schmalzStepLength = 30/384;

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

void shmove(){
  const float diff1 = dl1 - cl1;
  const float diff2 = dl2 - cl2;
  const float diff3 = dl3 - cl3;
  const float diff4 = dl4 - cl4;
  const float diff5 = dl5 - cl5;
  Serial.print(diff5);
  for (int i = 0; i <= frac; i++) {
    if ((cl1 <  dl1 - stepLength) || (cl1 > dl1 + stepLength)) {
      int step1 = (int) ceil((diff1/frac)/stepLength);
      Serial.println(step1);
      if (step1 > 0) {
        for (int j = 0; j <= abs(step1); j++) {
          motor1.step(-1);
          delay(10);
        }
      } else if (step1 < 0) {
        for (int j = 0; j <= abs(step1); j++) {
          motor1.step(1);
          delay(10);
        }
      }
      cl1 += step1*stepLength;
    }
    if ((cl2 < dl2 - stepLength) || (cl2 > dl2 + stepLength)) {
      int step2 = (int) ceil((diff2/frac)/stepLength);
      Serial.println(step2);
      if (step2 > 0) {
        for (int j = 0; j <= abs(step2); j++) {
          motor2.step(-1);
          delay(10);
        }
      } else if (step2 < 0) {
        for (int j = 0; j <= abs(step2); j++) {
          motor2.step(1);
          delay(10);
        }
      }
      cl2 += step2*stepLength;
    }
    if ((cl3 < dl3 - stepLength) || (cl3 > dl3 + stepLength)) {
      int step3 = (int) ceil((diff3/frac)/stepLength);
      Serial.println(step3);
      if (step3 > 0) {
        for (int j = 0; j <= abs(step3); j++) {
          motor3.step(-1);
          delay(10);
        }
      } else if (step3 < 0) {
        for (int j = 0; j <= abs(step3); j++) {
          motor3.step(1);
          delay(10);
        }
      }
      cl3 += step3*stepLength;
    }
    if ((cl4 < dl4 - stepLength) || (cl4 > dl4 + stepLength)) {
      int step4 = (int) ceil((diff4/frac)/stepLength);
      Serial.println(step4);
      if (step4 > 0) {
        for (int j = 0; j <= abs(step4); j++) {
          motor4.step(-1);
          delay(10);
        }
      } else if (step4 < 0) {
        for (int j = 0; j <= abs(step4); j++) {
          motor4.step(1);
          delay(10);
        }
      }
      cl4 += step4*stepLength;
    }
    if (!(cl5 < dl5 - schmalzStepLength) || !(cl5 > dl5 + schmalzStepLength)) {
      int step5 = (int) round((diff5)/schmalzStepLength);
      Serial.println(step5);
      if (step5 < 0) {
        digitalWrite(2, HIGH);
        cl5 += step5* schmalzStepLength;
      } else if (step5 > 0) {
        digitalWrite(2, LOW);
        cl5 += step5* schmalzStepLength;
      }
      for(int j = 0; j <= abs(step5); j++) {
        digitalWrite(3, HIGH);
        delay(1);
        digitalWrite(3, LOW);
        delay(1);
      }
    }
    delay(10);
  }
  Serial.println();
  Serial.print(cl1);
  Serial.print(cl2);
  Serial.print(cl3);
  Serial.print(cl4);
  Serial.println(cl5);
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
             shmove();
          }
       }
    } 
}
