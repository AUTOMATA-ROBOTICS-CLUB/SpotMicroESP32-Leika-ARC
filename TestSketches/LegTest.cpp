#include <cstdint>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <cstdlib>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>

#define I2C_SDA 8  
#define I2C_SCL 9  

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define MIN_PWM 100
#define MAX_PWM 440
#define MIN_ANGLE 0
#define MAX_ANGLE 180

int angle_to_pwm(float angle) {
	float pwm_target{};
	pwm_target = MIN_PWM + (((angle - MIN_ANGLE) / (MAX_ANGLE - MIN_ANGLE)) * (MAX_PWM - MIN_PWM));
	return (int)pwm_target;
}

void move_to_angle(int servoNum,angle) {
  auto pwm = angle_to_pwm(angle);
  pwm.setPWM(servoNum,0,pwm);
}

// NOTE: Works only if the target angle is less than the current angle i need to fix it
void sweep(float current_angle,float target_angle,int servoNum) {
	int current_pwm = angle_to_pwm(current_angle); 
	int target_pwm = angle_to_pwm(target_angle);

	for(int i = current_pwm; i <= target_pwm; i++) {
    	pwm.setPWM(servoNum,0,i);
	}

	// Sweep back 
	for(int i = target_pwm; i >= current_pwm; i--) {
    	pwm.setPWM(servoNum,0,i);
	}
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(I2C_SDA, I2C_SCL);

  pwm.begin();
  pwm.setPWMFreq(50);
  delay(500);  
  

}

void loop() {
  
}
