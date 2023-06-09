#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <Wire.h>


// Kênh PWM (Chân của các servo và DC motor) điều khiển động cơ (Số chân của động cơ DC hay servo đều gấp đôi số kênh của động cơ đó)
#define PWM_DC0A            0
#define PWM_DC0B            1
#define PWM_DC1A            2
#define PWM_DC1B            3
#define PWM_DC2A            4
#define PWM_DC2B            5
#define PWM_DC3A            6
#define PWM_DC3B            7

// Động cơ DC
#define MOT_LEFT            1
#define MOT_RIGHT           2

// set tốc độ động cơ
#define SPD_FAST            2047

// Vận tốc đạt ở 2047 giây tức 50% chu kỳ. Tính toán thời gian để đạt tại 1 chu kỳ n% 
//bằng cách lấy (4095 nhân n%) -1 

//Khai báo linh kiện 
Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver();
PS2X ps2;

void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial monitor là một bộ cài sẵn đùng để debug code 

  Serial.println("Welcome to the Mastodon Banhmi Console"); //In ra Serial dòng chữ trong ngoặc 
 //Các hàm check lỗi nếu có

  pwm.begin(); //Khởi tạo xung pwm
  pwm.setOscillatorFrequency(27000000);//Đặt tần số xung trong PCA9685 là 27000000 (27MHz) (27 triệu)
  pwm.setPWMFreq(50); //Đặt tần số giao động trên chân tối đa 50Hz (Để dùng cho cả Servo) (Pulse Width Modulation)
}

// Hàm điều khiển động cơ DC (nhận số động cơ từ 0->3 ứng với cặp kênh PWM 0-1/2-3/4-5/6-7, giá trị tốc độ từ -4095 đến 4095)
void ctrl_dc(uint8_t motor, int16_t speed) { 
  switch(motor) {
    case 0:
      pwm.setPWM(PWM_DC0A, 0, (speed > 0) ? speed : 0); //Kênh PWM_DC0A, vị trí bắt đầu = 0, xung của 1 chiều là 50% đạt được sau thời gian = 2047 micro second
      pwm.setPWM(PWM_DC0B, 0, (speed < 0) ? (-speed) : 0); 
      break;
    case 1: //Cho bánh bên tay trái
      pwm.setPWM(PWM_DC1A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC1B, 0, (speed < 0) ? (-speed) : 0);
      break;
    case 2: //Cho bánh bên tay phải
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
  //LẬP TRÌNH ĐỘNG CƠ BẢN (CÁC HÀM CƠ BẢN)

  //Phần này là phần giải thích rời rạc không cần phải code phải code hẳn ra 

  //Khi code động cơ thì 1 chân có xung và 1 chân ko có xung 
  pwm.setPWM(0, 0, 2047); //Kênh, vị trí bắt đầu, xung của 1 chiều (0 -> 4095) 50% tốc độ là 4095 / 2 - 1
  pwm.setPWM(1, 0, 0); //Ko có xung

  int v = ps2.Analog(PSS_LY); //giá trị của cần Analog chạy từ 0 - 255 
  
  //Set speed và chiều quay cho động cơ
  v = map(v, 0, 255, 4095, -4095); //Vì giá trị của cần Analog không tương xứng với giá trị của xung dùng để điều hướng motor
  //Ta dùng hàm map để gán hai khoảng giới hạn để input động cơ sẽ hoạt động đồng thời và trùng khợp khi ta kéo cần analog



  //Hướng dẫn sử dùng hàm điều khiển DC Motor:

  ctrl_dc(MOT_LEFT, 0); //gọi hàm ctrl_dc ra -> gán kênh của động cơ Motor trái, gán tốc độ bằng 0 (Tức là chưa chạy)

  //Cách ghép hàm đẻ sử dụng DC Motor với điều khiển PS2:
  ctrl_dc(MOT_LEFT ,map(ps2.Analog(PSS_LY), 0, 255, -SPD_FAST, SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái
  ctrl_dc(MOT_RIGHT,map(ps2.Analog(PSS_RY), 0, 255, SPD_FAST, -SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái


}

