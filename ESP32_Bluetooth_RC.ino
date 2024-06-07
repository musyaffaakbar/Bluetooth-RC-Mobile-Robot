// RC BLUETOOTH RC MBUH REVISI PIRO AKEH POKOK E 
// by Musyaffaab 
// Elektronika dan Instrumentasi 2022

#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial serialBT;

// Bluetooth signal stored in this variable
char btSignal;

// Initial Speed of the Bot
int Speed = 100;

/* FOR RIGHT MOTOR (Driver 1) */
int RPWM1 = 18; // RPWM for Motor 1
int LPWM1 = 27; // LPWM for Motor 1
int REN1 = 19;  // R_EN for Motor 1
int LEN1 = 23;  // L_EN for Motor 1

/* FOR LEFT MOTOR (Driver 2) */
int RPWM2 = 32; // RPWM for Motor 2
int LPWM2 = 33; // LPWM for Motor 2
int REN2 = 26;  // R_EN for Motor 2
int LEN2 = 4;   // L_EN for Motor 2

// Declare channel for PWM Output
#define R1 0
#define R2 1
#define L1 2
#define L2 3

void setup() {
  Serial.begin(115200);

  // Bluetooth Name
  serialBT.begin("ERC_PLN_ROBO");

  // Output pin declare
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(REN1, OUTPUT);
  pinMode(LEN1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(REN2, OUTPUT);
  pinMode(LEN2, OUTPUT);

  // Setup PWM channels
  ledcSetup(R1, 5000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(RPWM1, R1);
  ledcSetup(R2, 5000, 8);  // Channel 1 for Motor B, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(RPWM2, R2);
  ledcSetup(L1, 5000, 8);  // Channel 2 for Motor C, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(LPWM1, L1);
  ledcSetup(L2, 5000, 8);  // Channel 3 for Motor D, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(LPWM2, L2);
}

void loop() {
  while (serialBT.available()) {
    btSignal = serialBT.read();
    // Serial.println(btSignal);

    // Map the speed from 0-9 and 'q' to 0-100
    if (btSignal >= '0' && btSignal <= '9') {
      Speed = map(btSignal - '0', 0, 9, 0, 100);
    } else if (btSignal == 'q') {
      Speed = 100;
    }
    
    int pwmSpeed = map(Speed, 0, 100, 0, 255);

    if (btSignal == 'F') { // Forward
      digitalWrite(REN1, HIGH);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, pwmSpeed);
      ledcWrite(L1, 0);

      digitalWrite(REN2, HIGH);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, pwmSpeed);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'B') { // Backward
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, HIGH);
      ledcWrite(R1, 0);
      ledcWrite(L1, pwmSpeed);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, HIGH);
      ledcWrite(R2, 0);
      ledcWrite(L2, pwmSpeed);
    }

    else if (btSignal == 'L') { // Left
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, HIGH);
      ledcWrite(R1, 0);
      ledcWrite(L1, pwmSpeed);

      digitalWrite(REN2, HIGH);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, pwmSpeed);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'R') { // Right
      digitalWrite(REN1, HIGH);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, pwmSpeed);
      ledcWrite(L1, 0);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, HIGH);
      ledcWrite(R2, 0);
      ledcWrite(L2, pwmSpeed);
    }

    else if (btSignal == 'S') { // Stop
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, 0);
      ledcWrite(L1, 0);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, 0);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'I') { // Forward Right
      digitalWrite(REN1, HIGH);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, pwmSpeed);
      ledcWrite(L1, 0);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, 0);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'J') { // Backward Right
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, HIGH);
      ledcWrite(R1, 0);
      ledcWrite(L1, pwmSpeed);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, 0);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'G') { // Forward Left
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, 0);
      ledcWrite(L1, 0);

      digitalWrite(REN2, HIGH);
      digitalWrite(LEN2, LOW);
      ledcWrite(R2, pwmSpeed);
      ledcWrite(L2, 0);
    }

    else if (btSignal == 'H') { // Backward Left
      digitalWrite(REN1, LOW);
      digitalWrite(LEN1, LOW);
      ledcWrite(R1, 0);
      ledcWrite(L1, 0);

      digitalWrite(REN2, LOW);
      digitalWrite(LEN2, HIGH);
      ledcWrite(R2, 0);
      ledcWrite(L2, pwmSpeed);
    }
  }
}
