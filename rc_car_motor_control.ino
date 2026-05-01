/*
  RC Car Motor Control System

  Features:
  - Forward, backward, left, right, and stop control
  - Speed control using PWM
  - Serial command control
  - Auto-stop safety if no command is received

  Board: Arduino Uno
  Language: Embedded C/C++
*/
#include <ctype.h>
// ----- Motor Driver Pins -----
const int leftMotorForward = 5;
const int leftMotorBackward = 6;
const int rightMotorForward = 9;
const int rightMotorBackward = 10;

// ----- Speed Settings -----
int motorSpeed = 180;
const int minSpeed = 0;
const int maxSpeed = 255;
const int speedStep = 25;

// ----- Safety Timer -----
const unsigned long commandTimeout = 1500;
unsigned long lastCommandTime = 0;

void setup() {
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  stopCar();

  Serial.begin(9600);
  Serial.println("RC Car Ready");
  Serial.println("Commands: F B L R S + -");
}

void loop() {
  handleSerialCommands();
  handleSafetyStop();
}

void handleSerialCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    command = toupper(command);

    lastCommandTime = millis();

    if (command == 'F') {
      moveForward();
      Serial.println("Moving forward");
    }
    else if (command == 'B') {
      moveBackward();
      Serial.println("Moving backward");
    }
    else if (command == 'L') {
      turnLeft();
      Serial.println("Turning left");
    }
    else if (command == 'R') {
      turnRight();
      Serial.println("Turning right");
    }
    else if (command == 'S') {
      stopCar();
      Serial.println("Stopped");
    }
    else if (command == '+') {
      increaseSpeed();
    }
    else if (command == '-') {
      decreaseSpeed();
    }
  }
}

void handleSafetyStop() {
  if (millis() - lastCommandTime > commandTimeout) {
    stopCar();
  }
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  if (leftSpeed > 0) {
    analogWrite(leftMotorForward, leftSpeed);
    analogWrite(leftMotorBackward, 0);
  }
  else if (leftSpeed < 0) {
    analogWrite(leftMotorForward, 0);
    analogWrite(leftMotorBackward, -leftSpeed);
  }
  else {
    analogWrite(leftMotorForward, 0);
    analogWrite(leftMotorBackward, 0);
  }

  if (rightSpeed > 0) {
    analogWrite(rightMotorForward, rightSpeed);
    analogWrite(rightMotorBackward, 0);
  }
  else if (rightSpeed < 0) {
    analogWrite(rightMotorForward, 0);
    analogWrite(rightMotorBackward, -rightSpeed);
  }
  else {
    analogWrite(rightMotorForward, 0);
    analogWrite(rightMotorBackward, 0);
  }
}

void moveForward() {
  setMotorSpeed(motorSpeed, motorSpeed);
}

void moveBackward() {
  setMotorSpeed(-motorSpeed, -motorSpeed);
}

void turnLeft() {
  setMotorSpeed(-motorSpeed, motorSpeed);
}

void turnRight() {
  setMotorSpeed(motorSpeed, -motorSpeed);
}

void stopCar() {
  setMotorSpeed(0, 0);
}

void increaseSpeed() {
  motorSpeed += speedStep;

  if (motorSpeed > maxSpeed) {
    motorSpeed = maxSpeed;
  }

  Serial.print("Speed increased to: ");
  Serial.println(motorSpeed);
}

void decreaseSpeed() {
  motorSpeed -= speedStep;

  if (motorSpeed < minSpeed) {
    motorSpeed = minSpeed;
  }

  Serial.print("Speed decreased to: ");
  Serial.println(motorSpeed);
}
