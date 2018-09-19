#include <Servo.h>

Servo servos[2];  // create two servo objects to control servos
// twelve servo objects can be created on most boards

int servo_pins[] = {9, 10};  // pins for servos
int target_angles[] = {0, 0}; // variable to store target position for servos
int sleep_time = 20;  // sleeping time until the loop checks again for new targets

void setup() {
  Serial.begin(9600); // initialize serial  
  servos[0].attach(servo_pins[0]);  // attaches the servo object to the given pin
  servos[1].attach(servo_pins[1]);  // attaches the servo object to the given pin
}

void read_targets() {
  while (Serial.available() > 0) {
    String str_num1 = Serial.readStringUntil(',');
    String str_num2 = Serial.readString();
    target_angles[0] = constrain(str_num1.toInt(), 0, 180);
    target_angles[1] = constrain(str_num2.toInt(), 0, 180);
  }
}

void loop() {
  if (Serial.available() > 0) {
    // read in new target values
    read_targets();
    // send them to the servos
    servos[0].write(target_angles[0]);
    servos[1].write(target_angles[1]);
  }
  delay(sleep_time);
}
