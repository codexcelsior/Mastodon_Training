
//Import headers của các thư viện 
#include <PS2X_lib.h>  
#include <Adafruit_PWMServoDriver.h> 
#include <Wire.h>

//Set up các chân tín hiệu của tay cầm PS2
#define PS2_ATT 15
#define PS2_CMD 13
#define PS2_DAT 12
#define PS2_CLK 14


// Kênh PWM (Chân của các servo và DC motor) điều khiển động cơ (Số chân của động cơ DC hay servo đều gấp đôi số kênh của động cơ đó)
#define PWM_DC1A 1
#define PWM_DC1B 2
#define PWM_DC2A 3
#define PWM_DC2B 4
#define PWM_DC3A 5
#define PWM_DC3B 6
#define PWM_DC4A 7
#define PWM_DC4B 8

// Động cơ DC
#define MOT_LEFT 1
#define MOT_RIGHT 2

// set tốc độ động cơ
#define SPD_FAST 2047

//Khai báo linh kiện
Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver();
PS2X ps2;

void setup() {  //Hàm set up chạy khởi tạo một lần khi khởi động mạch
  Serial.begin(115200); //Bật serial monitor ở tốc độ 115200

  Serial.println("Mastodon's BanhMi Connected To PC. Proceeding to connect PS2 Controller");

  while (ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT) != 0) {
    Serial.println("Err: PS2 Controller Not Connected");
    delay(500);
  } //Check xem có chân tín hiệu nào của điều khiển nhận đc hay ko

  Serial.println("Controller works normally");

  pwm.begin();                           //Khởi tạo xung pwm
  pwm.setOscillatorFrequency(27000000);  //Đặt tần số xung trong PCA9685 là 27000000 (27MHz) (27 triệu)
  pwm.setPWMFreq(50);                    //Đặt tần số giao động trên chân tối đa 50Hz (Để dùng cho cả Servo) (Pulse Width Modulation)
}

void ctrl_dc(uint8_t motor, int16_t speed) {
  switch (motor) {
    case 1:
      pwm.setPWM(PWM_DC1A, 0, ((speed > 0) ? speed : 0) );  //Kênh PWM_DC1A, vị trí bắt đầu = 0, xung của 1 chiều là 50% đạt được sau thời gian = 2047 micro second
      pwm.setPWM(PWM_DC1B, 0, ((speed < 0) ? (-speed) : 0) );
      break;
    case 2:  //Cho bánh bên tay trái
      pwm.setPWM(PWM_DC2A, 0, ((speed > 0) ? speed : 0) );
      pwm.setPWM(PWM_DC2B, 0, ((speed < 0) ? (-speed) : 0) ) ;
      break;
    case 3:  //Cho bánh bên tay phải
      pwm.setPWM(PWM_DC3A, 0, ((speed > 0) ? speed : 0) );
      pwm.setPWM(PWM_DC3B, 0, ((speed < 0) ? (-speed) : 0) );
      break;
    case 4:
      pwm.setPWM(PWM_DC4A, 0, ((speed > 0) ? speed : 0) );
      pwm.setPWM(PWM_DC4B, 0, ((speed < 0) ? (-speed) : 0) );
      break;
  }
}


void loop() {

  ps2.read_gamepad();  //Khởi tạo đọc từ điều kiển bằng hàm read_gamepad()

  ctrl_dc(MOT_LEFT, map(ps2.Analog(PSS_LY), 0, 255, -SPD_FAST, SPD_FAST));
  ctrl_dc(MOT_RIGHT, map(ps2.Analog(PSS_RY), 0, 255, SPD_FAST, -SPD_FAST));
}
