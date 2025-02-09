#include <Ps3Controller.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo Configuration - Adjust these based on your mechanical limits!
struct ServoConfig {
  uint8_t channel;
  int min_angle;
  int max_angle;
  int step_size;
  int current_pos;
};

ServoConfig servos[] = {
  // Channel, Min, Max, Step, CurrentPos
  {0,  0, 180, 2, 90},   // Base (MG996)
  {8,  30, 150, 2, 90},    // Arm1 (MG995)
  {10, 20, 160, 2, 90},   // Arm2 (MG996)
  {7,  10, 170, 2, 90},   // Pre-gripper (SG90)
  {2,  0, 180, 2, 90},    // Gripper1 (SG90)
  {4,  0, 180, 2, 90}     // Gripper2 (MG996)
};

// PWM Configuration - Calibrate for your servos!
const int SERVO_FREQ = 50;  // Hz (SG90: 50Hz, MG996: 50Hz)
const int SERVOMIN = 150;   // 0.75ms pulse (150 * 4.88μs = 0.732ms)
const int SERVOMAX = 600;   // 3.0ms pulse (600 * 4.88μs = 2.928ms)

// Control Variables
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 20;  // ms (50Hz)

// PS3 Control Mapping
struct ControllerState {
  int base = 0;
  int arm1 = 0;
  int arm2 = 0;
  int pre_gripper = 0;
  int gripper1 = 0;
  int gripper2 = 0;
} ctrlState;

void updateServo(ServoConfig &servo, int direction) {
  int new_pos = servo.current_pos + (direction * servo.step_size);
  new_pos = constrain(new_pos, servo.min_angle, servo.max_angle);
  
  if(new_pos != servo.current_pos) {
    servo.current_pos = new_pos;
    pwm.setPWM(servo.channel, 0, map(new_pos, 0, 180, SERVOMIN, SERVOMAX));
  }
}

void notify() {
  // Base Control (L1/R1)
  ctrlState.base = 0;
  if(Ps3.data.button.r1) ctrlState.base = 1;
  if(Ps3.data.button.l1) ctrlState.base = -1;

  // Arm1 Control (L2/R2)
  ctrlState.arm1 = 0;
  if(Ps3.data.button.r2) ctrlState.arm1 = 1;
  if(Ps3.data.button.l2) ctrlState.arm1 = -1;

  // Arm2 Control (Left/Right)
  ctrlState.arm2 = 0;
  if(Ps3.data.button.right) ctrlState.arm2 = 1;
  if(Ps3.data.button.left) ctrlState.arm2 = -1;

  // Pre-gripper Control (Up/Down)
  ctrlState.pre_gripper = 0;
  if(Ps3.data.button.up) ctrlState.pre_gripper = 1;
  if(Ps3.data.button.down) ctrlState.pre_gripper = -1;

  // Gripper Controls (Buttons)
  ctrlState.gripper1 = 0;
  ctrlState.gripper2 = 0;
  if(Ps3.data.button.square) ctrlState.gripper1 = 1;
  if(Ps3.data.button.circle) ctrlState.gripper1 = -1;
  if(Ps3.data.button.triangle) ctrlState.gripper2 = 1;
  if(Ps3.data.button.cross) ctrlState.gripper2 = -1;
}

void onConnect() {
  Serial.println("PS3 Controller Connected!");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("44:d8:32:6d:91:c0");
}

void loop() {
  if(millis() - lastUpdate > UPDATE_INTERVAL) {
    // Update all servos
    updateServo(servos[0], ctrlState.base);
    updateServo(servos[1], ctrlState.arm1);
    updateServo(servos[2], ctrlState.arm2);
    updateServo(servos[3], ctrlState.pre_gripper);
    updateServo(servos[4], ctrlState.gripper1);
    updateServo(servos[5], ctrlState.gripper2);

    lastUpdate = millis();
  }

  if(!Ps3.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(2000);
  }
}