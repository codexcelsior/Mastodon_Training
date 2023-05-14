//Khai báo thư viện
#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <PS2X_lib.h> //Khai báo header từ thư viện PS2X

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

  Serial.println("OK"); //In ra OK một khi code đã ổn

}