//Library
#include<Servo.h>
#include<SoftwareSerial.h>

//Pin Config
int rxBT = 3;
int txBT = 2;
int resetPin = 4;
int tMotorPin = 5;
int atModePin = 6;
int connectLed = 12;
int powerLed = 13;


//Declare
Servo tMotor;
SoftwareSerial BT(rxBT, txBT);

int resolution = 5;
int minLimit = 500;
int maxLimit = 2300;

char btRead;
int pos;
int newVal;
int origVal = 1400;


//
//Setup
//
void setup() {
  digitalWrite(powerLed, HIGH);
  Serial.begin(9600);
  BT.begi n(9600);

  tMotor.attach(tMotorPin);
  tMotor.writeMicroseconds(1400);
}

//
//Main Loop
//
void loop() {
  btCom();
  //Serial.print("Status: ");
  turnMotor();

  if (Serial.available() > 0) {
    origVal = Serial.parseInt();
    tMotor.writeMicroseconds(origVal);
  }

  if (digitalRead(resetPin) == HIGH) {
    origVal = 1400;
    btRead = 's';
    tMotor.writeMicroseconds(origVal);
  }
  //Serial.println();
}


//BT Protocol
void btCom() {
  if (BT.available() > 0) {
    btRead = BT.read();
    digitalWrite(connectLed, HIGH);
    Serial.print("BT: ");
    Serial.println(btRead);

  }
}

//Motor Algo
void turnMotor() {
  if (btRead == 's') {
    tMotor.writeMicroseconds(origVal);
    //Serial.println("Stop");
  }

  if (btRead == 'l') {
    for (pos = origVal; pos < maxLimit; pos += resolution ) {
      btCom();
      if (btRead == 's') {
        break;
      }
      tMotor.writeMicroseconds(pos);
      origVal = pos;
      delay(50);
      //Serial.println("Turn Left");
    }
  }

  if (btRead == 'r') {
    for (pos = origVal; pos > minLimit; pos -= resolution) {
      btCom();
      if (btRead == 's') {
        break;
      }
      tMotor.writeMicroseconds(pos);
      origVal = pos;
      delay(50);
      //Serial.println("Turn Right");
    }
  }
  else {
    //Serial.println("No Signal");
  }
}


