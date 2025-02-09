#include <Ps3Controller.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Define motor control pins


// Define motor parameters




// Create the PWM driver object for the PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int SERVOMIN = 150;  // Minimum pulse length count (out of 4096)
const int SERVOMAX = 600;  // Maximum pulse length count (out of 4096)

int servobase = 0;  // PCA9685 channel to which the servo is connected
int servo_bras_1=8;
int servo_bras_2=10;
int servo_pre_gripper = 7;
int servo_gripper_1 = 2;
int servo_gripper_2 = 4;


int ser;
int pos_base = 90; 
int pos_bras_1 = 0; // Variable to store the servo position in degrees
int pos_bras_2 =90;
int pos_pre_gripper = 0;
int pos_gripper_1 = 0;
int pos_gripper_2 = 0;

// Callback function for PS3 controller notifications
void notify() {
  //buzzer
  /*if (Ps3.data.button.cross){
      tone(buzzer, 1000);
      delay(50);
      noTone(buzzer);
  
  }*/
  if (Ps3.data.button.cross) {
    
    //Ps3.setRumble(100.0);
  } else {
    
    //Ps3.setRumble(0.0);
  }
  //arm 3 servo motor
  if (Ps3.data.button.up) {
      //if (pos_pre_gripper<180)
        //{
          pos_pre_gripper++;
          pwm.setPWM(servo_pre_gripper, 0, map(pos_pre_gripper, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing arm 3 position to " + String(pos_pre_gripper));
        }  // Increase servo position by 10 degrees
      //else if (pos_pre_gripper > 180) {}  // Limit to 180 degrees
      
    //}

    // Check if Left button is pressed
  if (Ps3.data.button.down) {
      //if (pos_pre_gripper>0)
        //{
          pos_pre_gripper--;
          pwm.setPWM(servo_pre_gripper, 0, map(pos_pre_gripper, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("L1 pressed: Decreasing arm 3 position to " + String(pos_pre_gripper));
        }  // Decrease servo position by 10 degrees
      //else if (pos_pre_gripper < 0) {}  // Limit to 0 degrees
      
    //}
  //arm 2 servo motor
  if (Ps3.data.button.right) {
      //if (pos_bras_2 <180)
      //  {
          pos_bras_2 ++;
          pwm.setPWM(servo_bras_2, 0, map(pos_bras_2 , 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing arm 2 position to " + String(pos_bras_2 ));
        }  // Increase servo position by 10 degrees
      //else if (pos_bras_2  > 180) {}  // Limit to 180 degrees
      
    //}

    // Check if Left button is pressed
  if (Ps3.data.button.left) {
      //if (pos_bras_2 >0)
        //{
          pos_bras_2 --;
          pwm.setPWM(servo_bras_2, 0, map(pos_bras_2 , 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("L1 pressed: Decreasing arm 2 position to " + String(pos_bras_1));
        }  // Decrease servo position by 10 degrees
      //else if (pos_bras_2  < 0) {}  // Limit to 0 degrees
      
    //}
  //arm 1 servo motor
  if (Ps3.data.button.r2 ) {
      //if (pos_bras_1<180)
        //{
          pos_bras_1++;
          pwm.setPWM(servo_bras_1, 0, map(pos_bras_1, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing arm 1 position to " + String(pos_bras_1));
        }  // Increase servo position by 10 degrees
      //else if (pos_bras_1 > 180) {}  // Limit to 180 degrees
      
    //}

    // Check if L1 button is pressed
  if (Ps3.data.button.l2) {
      //if (pos_bras_1>0)
        //{
          pos_bras_1--;
          pwm.setPWM(servo_bras_1, 0, map(pos_bras_1, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("L1 pressed: Decreasing arm 1 position to " + String(pos_bras_1));
        }  // Decrease servo position by 10 degrees
      //else if (pos_bras_1 < 0) {}  // Limit to 0 degrees
      
    //}
  //base servo motor
  //if (Ps3.data.button.r1) {
    if (Ps3.data.button.r1){
      //if (pos_base<180)
        //{
          pos_base ++;
          pwm.setPWM(servobase, 0, map(pos_base, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing position to " + String(pos_base));
        }  // Increase servo position by 10 degrees
      //if (pos > 180) pos_base = 180;  // Limit to 180 degrees
      //else if (pos_base > 180) {} 
      
    //}

    // Check if L1 button is pressed
  if (Ps3.data.button.l1 ) {
    //if (pos_base >0)
      //{
        pos_base --;
        pwm.setPWM(servobase, 0, map(pos_base, 0, 180, SERVOMIN, SERVOMAX));
        Serial.println("L1 pressed: Decreasing position to " + String(servobase));
      }  // Decrease servo position by 10 degrees
    //if (pos < 0) pos_base = 0;  // Limit to 0 degrees
    //else if (pos_base < 0){}
      
    //}


       if (Ps3.data.button.square){
      //if (pos_gripper_1<180)
        //{
          pos_gripper_1 ++;
          pwm.setPWM(servo_gripper_1, 0, map(pos_gripper_1, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing position to " + String(pos_gripper_1));
        }  // Increase servo position by 10 degrees
      //if (pos > 180) pos_base = 180;  // Limit to 180 degrees
      //else if (pos_gripper_1 > 180) {} 
      
    //}

    // Check if L1 button is pressed
  if (Ps3.data.button.circle) {
    //if (pos_gripper_1 >0)
      //{
        pos_gripper_1 --;
        pwm.setPWM(servo_gripper_1, 0, map(pos_gripper_1, 0, 180, SERVOMIN, SERVOMAX));
        Serial.println("L1 pressed: Decreasing position to " + String(pos_gripper_1));
      }  // Decrease servo position by 10 degrees
    //if (pos < 0) pos_base = 0;  // Limit to 0 degrees
    //else if (pos_gripper_1 < 0){}
      
    //}


           if (Ps3.data.button.triangle){
      //if (pos_gripper_2<180)
        //{
          pos_gripper_2 ++;
          pwm.setPWM(servo_gripper_2, 0, map(pos_gripper_2, 0, 180, SERVOMIN, SERVOMAX));
          Serial.println("R1 pressed: Increasing position to " + String(pos_gripper_2));
        }  // Increase servo position by 10 degrees
      //if (pos > 180) pos_base = 180;  // Limit to 180 degrees
      //else if (pos_gripper_2 > 180) {} 
      
    //}

    // Check if L1 button is pressed
  if (Ps3.data.button.cross) {
    //if (pos_gripper_2 >0)
      //{
        pos_gripper_2 --;
        pwm.setPWM(servo_gripper_2, 0, map(pos_gripper_2, 0, 180, SERVOMIN, SERVOMAX));
        Serial.println("L1 pressed: Decreasing position to " + String(pos_gripper_2));
      }  // Decrease servo position by 10 degrees
    //if (pos < 0) pos_base = 0;  // Limit to 0 degrees
    //else if (pos_gripper_2 < 0){}
      
    //}
  // Get Joystick value
  //rightX = (Ps3.data.analog.stick.rx);
  //rightY = (Ps3.data.analog.stick.ry);
}




// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}


void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  //Wire.setPins(14, 13); // Set the I2C pins before begin
  Wire.begin();
  Wire.setClock(400000);
  // Attach the PS3 controller callbacks
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("44:d8:32:6d:91:c0");

  // Initialize motor control pins




  // Initialize the PWM driver for the servo
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz

  // Attach onPress callback

}

void loop() {
  // Main loop
  if (!Ps3.isConnected()) {
    Serial.println("Not connected yet!..");
    delay(2000);
  }
}
