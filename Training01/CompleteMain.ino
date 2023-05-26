//Khai báo thư viện
#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <PS2X_lib.h> //Khai báo header từ thư viện PS2X

//Khai báo linh kiện 
Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver();
PS2X ps2;


void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial monitor là một bộ cài sẵn đùng để debug code 

  Serial.println("Welcome to the Mastodon Banhmi Console"); //In ra Serial dòng chữ trong ngoặc 


  while(ps2.config_gamepad(13, 11, 10, 12) != 0)
  {
    Serial.println("PS2 error");
    delay(500);
  } //Test config của tay cầm ps2 qua các cổng. Khi giá trị của một trong các cổng của tay cầm = 0 
  // thì in ra dòng chữ PS2 error để nhận biết cho người dùng đang có lỗi với port kết nối của controllẻ 

  pwm.begin(); //Khởi tạo xung pwm
  pwm.setOscillatorFrequency(27000000);//Đặt tần số giao động liên tục là 27000000 (27 triệu)
  pwm.setPWMFreq(50); //Đặt tần số giao động trên chân tối đa 50Hz (Pulse Width Modulation)
  Serial.println("OK"); //In ra OK một khi code đã ổn

}

void loop() {


  int v = ps2.Analog(PSS_LY); //Tạo cần analog giá trị của cần Analog chạy từ 0 - 255 
  
  //Set speed và chiều quay cho động cơ
  v = map(v, 0, 255, 4095, -4095); //Vì giá trị của cần Analog không tương xứng với giá trị của xung dùng để điều hướng motor
  //Ta dùng hàm map để gán hai khoảng giới hạn để input động cơ sẽ hoạt động đồng thời và trùng khợp khi ta kéo cần analog
  if (v > 0)
  {
    pwm.setPWM(0, 0, v); //Giả dụ một motor có 2 kênh tương đương với 2 chân (2 dây với 2 cổng là 0 và 1) thì đặt xung vào 1 dây dây còn lại ko có xung
    pwm.setPWM(1, 0, 0);
  } else {
    pwm.setPWM(0, 0, 0); //Tương tự code động cơ còn lại (4 bánh cũng tương tự như vậy)
    pwm.setPWM(1, 0, -v);
  }

}


