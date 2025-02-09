#include <Ps3Controller.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <EEPROM.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo Configuration with Homing
struct ServoConfig {
  uint8_t channel;
  int min_angle;
  int max_angle;
  int step_size;
  int current_pos;
  int home_pos;  // Added home position
};

// EEPROM Configuration
#define EEPROM_SIZE 512
#define EEPROM_SIGNATURE 0x55AA

struct SavedPositions {
  uint16_t signature;
  int positions[6];
};

ServoConfig servos[] = {
  // Channel, Min, Max, Step, CurrentPos, Home
  {0,   0, 180, 2, 90, 90},   // Base (MG996)
  {8,  30, 150, 2, 90, 90},   // Arm1 (MG995)
  {10, 20, 160, 2, 90, 90},   // Arm2 (MG996)
  {7,  10, 170, 2, 90, 90},   // Pre-gripper (SG90)
  {2,   0, 180, 2, 90, 90},   // Gripper1 (SG90)
  {4,   0, 180, 2, 90, 90}    // Gripper2 (MG996)
};

// PWM Configuration
const int SERVO_FREQ = 50;
const int SERVOMIN = 150;
const int SERVOMAX = 600;

// Control Variables
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 20;
const int HOMING_DELAY = 50;
const int HOMING_SPEED = 1;

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

void performHoming() {
  Serial.println("\n=== Starting Homing Sequence ===");
  
  // Move to safe minimum positions
  for(int i = 0; i < 6; i++) {
    while(servos[i].current_pos > servos[i].min_angle) {
      servos[i].current_pos -= HOMING_SPEED;
      pwm.setPWM(servos[i].channel, 0, 
                map(servos[i].current_pos, 0, 180, SERVOMIN, SERVOMAX));
      delay(HOMING_DELAY);
    }
  }

  // Move to home positions
  for(int i = 0; i < 6; i++) {
    while(servos[i].current_pos != servos[i].home_pos) {
      int step = (servos[i].home_pos > servos[i].current_pos) ? 1 : -1;
      servos[i].current_pos += step;
      pwm.setPWM(servos[i].channel, 0, 
                map(servos[i].current_pos, 0, 180, SERVOMIN, SERVOMAX));
      delay(HOMING_DELAY);
    }
  }
  
  Serial.println("Homing complete!");
}

void savePositions() {
  SavedPositions save;
  save.signature = EEPROM_SIGNATURE;
  
  for(int i = 0; i < 6; i++) {
    save.positions[i] = servos[i].current_pos;
  }

  EEPROM.put(0, save);
  EEPROM.commit();
  Serial.println("Positions saved to EEPROM");
}

bool loadPositions() {
  SavedPositions save;
  EEPROM.get(0, save);

  if(save.signature != EEPROM_SIGNATURE) {
    Serial.println("No valid positions found");
    return false;
  }

  for(int i = 0; i < 6; i++) {
    servos[i].current_pos = constrain(save.positions[i],
                                     servos[i].min_angle,
                                     servos[i].max_angle);
    pwm.setPWM(servos[i].channel, 0,
              map(servos[i].current_pos, 0, 180, SERVOMIN, SERVOMAX));
  }
  
  Serial.println("Positions loaded from EEPROM");
  return true;
}

void notify() {
  // Existing controller mapping
  ctrlState.base = 0;
  if(Ps3.data.button.r1) ctrlState.base = 1;
  if(Ps3.data.button.l1) ctrlState.base = -1;

  ctrlState.arm1 = 0;
  if(Ps3.data.button.r2) ctrlState.arm1 = 1;
  if(Ps3.data.button.l2) ctrlState.arm1 = -1;

  ctrlState.arm2 = 0;
  if(Ps3.data.button.right) ctrlState.arm2 = 1;
  if(Ps3.data.button.left) ctrlState.arm2 = -1;

  ctrlState.pre_gripper = 0;
  if(Ps3.data.button.up) ctrlState.pre_gripper = 1;
  if(Ps3.data.button.down) ctrlState.pre_gripper = -1;

  ctrlState.gripper1 = 0;
  ctrlState.gripper2 = 0;
  if(Ps3.data.button.square) ctrlState.gripper1 = 1;
  if(Ps3.data.button.circle) ctrlState.gripper1 = -1;
  if(Ps3.data.button.triangle) ctrlState.gripper2 = 1;
  if(Ps3.data.button.cross) ctrlState.gripper2 = -1;

  // Add calibration shortcut (SELECT + START)
  if(Ps3.data.button.select && Ps3.data.button.start) {
    performHoming();
    savePositions();
    //Ps3.setLed(0, 0, 100); // Blue confirmation
  }
}

void onConnect() {
  Serial.println("PS3 Controller Connected!");
  //Ps3.setLed(0, 100, 0); // Green light
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  
  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);
  
  // PWM Initialization
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(500); // Allow capacitors to charge

  // Position Initialization
  if(digitalRead(0) == LOW) { // Use FLASH button for calibration
    Serial.println("Entering calibration mode");
    performHoming();
    savePositions();
  } else {
    if(!loadPositions()) {
      performHoming();
      savePositions();
    }
  }

  // PS3 Controller Setup
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("44:d8:32:6d:91:c0");
}

void loop() {
  if(millis() - lastUpdate > UPDATE_INTERVAL) {
    updateServo(servos[0], ctrlState.base);
    updateServo(servos[1], ctrlState.arm1);
    updateServo(servos[2], ctrlState.arm2);
    updateServo(servos[3], ctrlState.pre_gripper);
    updateServo(servos[4], ctrlState.gripper1);
    updateServo(servos[5], ctrlState.gripper2);

    lastUpdate = millis();
  }

  if(!Ps3.isConnected()) {
    Serial.println("Controller disconnected");
    delay(2000);
  }
}