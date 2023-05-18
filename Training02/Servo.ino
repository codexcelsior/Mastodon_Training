#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <Wire.h>

Adafruit_PWMServoDriver pwm; //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver(); khi chạy hoặc upload code ko đc

// Kênh PWM (Chân của các servo và DC motor) điều khiển động cơ
#define PWM_DC0A            0
#define PWM_DC0B            1
#define PWM_DC1A            2
#define PWM_DC1B            3
#define PWM_DC2A            4
#define PWM_DC2B            5
#define PWM_DC3A            6
#define PWM_DC3B            7

#define PWM_SERVO0          8
#define PWM_SERVO1          9
#define PWM_SERVO2          10
#define PWM_SERVO3          11
#define PWM_SERVO4          12

// Độ rộng xung cho servo 360 (đã calibrate)
#define SRV_360_T1          698 // độ rộng xung mà tại đó servo quay nhanh nhất theo 1 chiều
#define SRV_360_T2          1362 // biên dưới của khoảng servo dừng quay
#define SRV_360_T3          1440 // biên trên của khoảng servo dừng quay
#define SRV_360_T4          2104 // độ rộng xung mà tại đó servo quay nhanh nhất theo chiều còn lại

// Cổng của servo
#define SRV_INTAKE          0
#define SRV_DOOR            

// Tốc độ động cơ
#define SPD_INTAKE          100 // servo


void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  // put your setup code here, to run once:
  pwm.begin(); //Khởi tạo xung pwm
  pwm.setOscillatorFrequency(27000000);//Đặt tần số xung trong PCA9685 là 27000000 (27MHz) (27 triệu)
  pwm.setPWMFreq(50); //Đặt tần số giao động trên chân tối đa 50Hz (Để dùng cho cả Servo) (Pulse Width Modulation)

}


// Hàm điều khiển vị trí servo 180 (nhận số động cơ servo từ 0->4 ứng với kênh PWM 8->12, giá trị góc từ 0 đến 180)
void ctrl_servo180(uint8_t motor, float angle) {
  uint16_t us = (uint16_t) (1000 * (1.0 + angle / 180.0));
  switch(motor) {
    case 0: pwm.writeMicroseconds(PWM_SERVO0, us); break; //writeMicrosecond dùng để cho Servo biét cần phải quay bao nhiều ms để quay đc 1 góc cần và đủ
    case 1: pwm.writeMicroseconds(PWM_SERVO1, us); break;
    case 2: pwm.writeMicroseconds(PWM_SERVO2, us); break;
    case 3: pwm.writeMicroseconds(PWM_SERVO3, us); break;
    case 4: pwm.writeMicroseconds(PWM_SERVO4, us); break;
  }
}

// Hàm điều khiển tốc độ servo 360 (nhận số động cơ servo từ 0->4 ứng với kênh PWM 8->12, giá trị tốc độ từ -100 đến 100)
void ctrl_servo360(uint8_t motor, float speed) {
  uint16_t us = (SRV_360_T2 + SRV_360_T3) / 2;
  if(speed > 0) 
    us = SRV_360_T3 + (speed / 100) * (SRV_360_T4 - SRV_360_T3);
  else if(speed < 0) 
    us = SRV_360_T2 + (speed / 100) * (SRV_360_T2 - SRV_360_T1);
  switch(motor) {
    case 0: pwm.writeMicroseconds(PWM_SERVO0, us); break;
    case 1: pwm.writeMicroseconds(PWM_SERVO1, us); break;
    case 2: pwm.writeMicroseconds(PWM_SERVO2, us); break;
    case 3: pwm.writeMicroseconds(PWM_SERVO3, us); break;
    case 4: pwm.writeMicroseconds(PWM_SERVO4, us); break;
  }
}


void loop() {
    // put your main code here, to run repeatedly: 
    
    bool intake = True;
    bool door = True;

    //Hàm mẫu để sử dụng Servo 
    
    ctrl_servo360(SRV_INTAKE, (intake) ?  SPD_INTAKE : 0);
    //ctrl_servo180(cổng, tốc quay);
    
    ctrl_servo180(SRV_DOOR, (door) ? 90 : 0);
    //ctrl_servo180(cổng, góc quay);
}