#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <PS2X_lib.h> //Khai báo header từ thư viện PS2X
#include <Wire.h> 

// Số chân của cổng đầu vào PS2
#define PS2_ATT             15
#define PS2_CMD             13
#define PS2_DAT             12
#define PS2_CLK             14

// Kênh PWM (Chân của các servo và DC motor) điều khiển động cơ (Số chân của động cơ DC hay servo đều gấp đôi số kênh của động cơ đó)
#define PWM_DC0A            0
#define PWM_DC0B            1
#define PWM_DC1A            2
#define PWM_DC1B            3
#define PWM_DC2A            4
#define PWM_DC2B            5
#define PWM_DC3A            6
#define PWM_DC3B            7


// Khai báo tốc độ động cơ DC
#define SPD_FAST            

//Khai báo linh kiện 
Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver();
PS2X ps2;

void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  Serial.begin(115200); //Serial monitor là một bộ cài sẵn đùng để debug code 

  Serial.println("Welcome to the Mastodon Banhmi Console"); //In ra Serial dòng chữ trong ngoặc 



    while(ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT) != 0)
  {
    Serial.println("PS2 error");
    delay(500);
  }

  pwm.begin(); //Khởi tạo xung pwm
  pwm.setOscillatorFrequency(27000000);//Đặt tần số xung trong PCA9685 là 27000000 (27MHz) (27 triệu)
  pwm.setPWMFreq(50); //Đặt tần số giao động trên chân tối đa 50Hz (Để dùng cho cả Servo) (Pulse Width Modulation)
}

void ctrl_dc(uint8_t motor, int16_t speed) {
  switch(motor) {
    case 0:
      pwm.setPWM(PWM_DC0A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC0B, 0, (speed < 0) ? (-speed) : 0);
      break;
    case 1:
      pwm.setPWM(PWM_DC1A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC1B, 0, (speed < 0) ? (-speed) : 0);
      break;
    case 2:
      pwm.setPWM(PWM_DC2A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC2B, 0, (speed < 0) ? (-speed) : 0);
      break;
    case 3:
      pwm.setPWM(PWM_DC3A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC3B, 0, (speed < 0) ? (-speed) : 0);
      break;
  }
}

void loop() {

  ps2.read_gamepad(); //Khởi tạo đọc từ điều kiển bằng hàm read_gamepad()

  ctrl_dc(MOT_LEFT ,map(ps2.Analog(PSS_LY), 0, 255, -SPD_FAST, SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái
  ctrl_dc(MOT_RIGHT,map(ps2.Analog(PSS_RY), 0, 255, SPD_FAST, -SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái

}
