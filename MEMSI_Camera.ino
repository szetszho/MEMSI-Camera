//Library
#include<Servo.h>
#include<SoftwareSerial.h>

//Pin Config
int rxBT = 2;
int txBt = 3;
int resetPin = 4;
int tMotorPin = 5;
int detectLed = 11;
int connectLed = 12;
int powerLed = 13;

//IR Pin Config
int ir_LL_Pin = 0;
int ir_L_Pin = 1;
int ir_ML_Pin = 2;
int ir_MR_Pin = 3;
int ir_R_Pin = 4;
int ir_RR_Pin = 5;

//Declare
Servo tMotor;
SoftwareSerial BT(rxBT,txBT);

int btRead;
int tMval = 1500;

int llBase;
int lBase;
int mlBase;
int rlBase;
int rBase;
int rrBase;

int llRead;
int lRead;
int mlRead;
int mrRead;
int rRead;
int rrRead;

int llAct;
int lAct;
int mlAct;
int mrAct;
int rAct;
int rrAct;

//Setup
void setup() {
  digitalWrite(powerLed,HIGH);
  Serial.begin(9600);
  BT.begin(9600);

  tMotor.attach(tMotorPin);
  tMotor.writeMicroseconds(1500);

  //irInit();
}

//Main Loop
void loop() {
  btCom();
  //irRead();
  //irAlgo();

  if (digitalRead(resetPin) == HIGH){
    tMotor.writeMicroseconds(1500);
    delay(1000);
    //irInit();
  }
}


//BT Protocol
void btCom() {
  if (BT.available()>0){
    btRead = BT.read();
    Serial.println(btRead);
    digitalWrite(connectLed,HIGH);
  }
}
/*
//IR Initialize
void irInit(){
  llBase = analogRead(ir_LL_Pin);
  lBase = analogRead(ir_L_Pin);
  mlBase = analogRead(ir_ML_Pin);
  mrBase = analogRead(ir_MR_Pin);
  rBase = analogRead(ir_R_Pin);
  rrBase = analogRead(ir_RR_Pin);
}

//IR Tracking
void irRead(){
  llRead = analogRead(ir_LL_Pin);
  lRead = analogRead(ir_L_Pin);
  mlRead = analogRead(ir_ML_Pin);
  mrRead = analogRead(ir_MR_Pin);
  rRead = analogRead(ir_R_Pin);
  rrRead = analogRead(ir_RR_Pin);
}

//IR Algo
void irAlgo(){
  llAct = llRead - llBase;
  lAct = lRead - lBase;
  mlAct = mlRead - mlBase;
  mrAct = mrRead - mrBase;
  rAct =  rRead - rBase;
  rrAct = rrRead - rrBase;
}
*/
