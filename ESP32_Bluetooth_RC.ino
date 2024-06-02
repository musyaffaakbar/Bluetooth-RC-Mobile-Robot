#include "BluetoothSerial.h"
#include <Arduino.h>
BluetoothSerial serialBT;
char BT;
int Speed = 100;
//driver kanan
int R1PWM = 19;
int R2PWM = 21;
//driver kiri
int L1PWM = 23;
int L2PWM = 22;

#define rmf 0
#define rmb 1
#define lmf 2
#define lmb 3

void setup() {
  Serial.begin(115200);
  serialBT.begin("MUSYAFFAAB_RC");  //nama bluetooth espnya
  pinMode(R1PWM, OUTPUT);
  pinMode(R2PWM, OUTPUT);
  pinMode(L1PWM, OUTPUT);
  pinMode(L2PWM, OUTPUT);
  // Setup channel utk PWM
  ledcSetup(rmf, 5000, 8); 
  ledcAttachPin(R1PWM, rmf);
  ledcSetup(rmb, 5000, 8);  
  ledcAttachPin(R2PWM, rmb);
  ledcSetup(lmf, 5000, 8);  
  ledcAttachPin(L1PWM, lmf);
  ledcSetup(lmb, 5000, 8);
  ledcAttachPin(L2PWM, lmb);
}

void loop() {
  while (serialBT.available()) {
    BT = serialBT.read();
//utk mengatur kecepatan di aplikasi
    if (BT == '0') Speed = 100;
    if (BT == '1') Speed = 110;
    if (BT == '2') Speed = 120;
    if (BT == '3') Speed = 130;
    if (BT == '4') Speed = 140;
    if (BT == '5') Speed = 150;
    if (BT == '6') Speed = 180;
    if (BT == '7') Speed = 200;
    if (BT == '8') Speed = 220;
    if (BT == '9') Speed = 240;
    if (BT == 'q') Speed = 255;
// gerakan 
    if (BT == 'F') go_forward();
    else if (BT == 'B') go_backward();
    else if (BT == 'L') go_left();
    else if (BT == 'R') go_right();
    else if (BT == 'S') stop();
    else if (BT == 'I') forward_right();
    else if (BT == 'J') backward_right();
    else if (BT == 'G') forward_left();
    else if (BT == 'H') backward_left();
  }
}

/*
  rmf : motor kanan maju
  rmb : motor kanan mundur
  lmf : motor kiri maju
  lmb : motor kiri mundur

  arah PWM motor diatur pake "speed". jadi kalo mau ngatur arah tinggal dikasi di sebelah PWMnya
*/
void go_forward() { //gerakan robot maju
  ledcWrite(rmf, Speed);  
  ledcWrite(rmb, 0);      
  ledcWrite(lmf, Speed);  
  ledcWrite(lmb, 0);      
}
void go_backward() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}
void go_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, Speed);
  ledcWrite(lmb, 0);
}
void go_right() {
  ledcWrite(rmf, Speed);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}
void stop() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void forward_right() {
  ledcWrite(rmf, Speed);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void backward_right() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void forward_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, Speed);
  ledcWrite(lmb, 0);
}
void backward_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}
