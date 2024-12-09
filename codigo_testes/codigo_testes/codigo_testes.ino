#include <ESP32Servo.h>

Servo servoPitch;

#define outputServopitch 2
#define outputServoYAW 4

void setup() {
  Serial.begin(115200);
  servoPitch.attach(outputServopitch, 500, 2500);
}

void loop() {
  servoPitch.writeMicroseconds(100);
  Serial.println("Parado");
  delay(2000);
  servoPitch.writeMicroseconds(2500);
  Serial.println("Horario");
  delay(2000);
  servoPitch.writeMicroseconds(1500);
  Serial.println("Parado");
  delay(2000);
  servoPitch.writeMicroseconds(500);
  Serial.println("Anti-Horario");
  delay(2000);
}
