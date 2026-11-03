#include <cstdint>
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

enum MICRO_PARTS {
	FL_SHOULDER = 0,
	FL_UPLIMB = 1,
	FL_LEG = 2,
	FR_SHOULDER = 3,
	FR_UPLIMB = 4,
	FR_LEG = 5,
	RL_SHOULDER = 6,
	RL_UPLIMB = 7,
	RL_LEG = 8,
	RR_SHOULDER = 9,
	RR_UPLIMB = 10,
	RR_LEG = 11 
};

int angle_to_pwm(float angle) {
	float pwm_target{};
	pwm_target = MIN_PWM + (((angle - MIN_ANGLE) / (MAX_ANGLE - MIN_ANGLE)) * (MAX_PWM - MIN_PWM));
	pwm_target = (int)pwm_target;
	return pwm_target;
}

void move_to_angle(int servoNum,float angle) {
  int pw = angle_to_pwm(angle);

  pwm.setPWM(servoNum,0,pw);
}

// NOTE: Works only if the target angle is less than the current angle i need to fix it
void sweep(float current_angle,float target_angle,int servoNum) {
	int current_pwm = angle_to_pwm(current_angle); 
	int target_pwm = angle_to_pwm(target_angle);

	for(int i = current_pwm; i <= target_pwm; i++) {
    pwm.setPWM(servoNum,0,i);
	}

	delay(500);
	// Sweep back 
	for(int i = target_pwm; i >= current_pwm; i--) {
    pwm.setPWM(servoNum,0,i);
	}
}

void stand() {
	// Stiffen all shoulders and upper legs 


	// Move legs upright
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(I2C_SDA, I2C_SCL);

  pwm.begin();
  pwm.setPWMFreq(60);
  delay(500);  

}

void loop() {
  
}
