#include <Servo.h>

#define MOTOR_PIN 5
#define STEERING_PIN 6

#define MAX_STEERING_FACTOR 0.45
#define MAX_MOTOR_FACTOR 0.60

Servo motor;
Servo steering;

int8_t currentSteering = 0;
int8_t currentMotor = 0;

void setup() {
  Serial.begin(9600);

  motor.attach(MOTOR_PIN);
  steering.attach(STEERING_PIN);

  setSteering(0);
  setMotor(0);
}

void loop() {

}

/** 
 *  Sets the steering to the given value. A value of 0 centers
 *  the steering. Negative values correspond to steering to the
 *  left, positive to the right.
 *  -100 or 100 resp. is steering fully to one side.
 */
void setSteering(int8_t value) {
  translateControl(steering, value, MAX_STEERING_FACTOR);
}

/** 
 *  Sets the motor speed to the given value. A value of 0 stops
 *  the motor. Negative values correspond to reverse, positive 
 *  to forward motion.
 *  -100 or 100 resp. is full speed in the corresponding direction.
 */
void setMotor(int8_t value) {
  translateControl(motor, value, MAX_MOTOR_FACTOR);
}

/**
 * Translates the given precentage into corresponding servo movements.
 */
void translateControl(Servo control, int8_t value, float max_factor) {
  if (value > 100) {
    value = 100;
  }

  if (value < -100) {
    value = -100;
  }
  
  uint8_t degrees = 90 + value * max_factor;

  control.write(degrees);
}
