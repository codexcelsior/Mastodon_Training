#include <PS2X_lib.h> //Khai báo header từ thư viện PS2X


// 1. Chân cắm đầu thu tay cầm PS2
#define PS2_ATT             10
#define PS2_CMD             11
#define PS2_DAT             12
#define PS2_CLK             13

//Khai báo linh kiện
Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver();
PS2X ps2;

void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial monitor là một bộ cài sẵn đùng để debug code 

  Serial.println("Welcome to the Mastodon Banhmi Console"); //In ra Serial dòng chữ trong ngoặc 


  while(ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT) != 0)
  {
    Serial.println("PS2 error");
    delay(500);
  } //Test config của tay cầm ps2 qua các cổng. Khi giá trị của một trong các cổng của tay cầm = 0 
  // thì in ra dòng chữ PS2 error để nhận biết cho người dùng đang có lỗi với port kết nối của controllẻ 

}

void loop() { //Vòng lặp mang tên loop chạy liên tục vì bot cũng chạy liên tục và không kết thúc cho tới khi tắt mạch
  // put your main code here, to run repeatedly:
  ps2.read_gamepad(); //Khởi tạo đọc từ điều kiển bằng hàm read_gamepad()
  if (ps2.Button(PSB_PAD_UP)) //Khởi tạo hàm if để check khi nút có được ấn xuống hay không
  {
    Serial.println("Up is pressed");
    Serial.println(ps2.Analog(PSS_LX), DEC); //Khởi tạo hàm chạy Analog để đánh dấu khi kéo cần Analog thì nó sẽ cho ra giá trị như thế nào
    // Vì giá trị gốc sử dụng khó để đọc nên convert sang hệ cơ số Decimal để người dùng dễ đọc hơn
    Serial.println(' '); //Cách bằng 1 khoảng trắng để hiện thị các thành phần trong tọa độ
    Serial.println(ps2.Analog(PSS_LY), DEC);
    Serial.println(' ');
    Serial.println(ps2.Analog(PSS_RX), DEC);
    Serial.println(' ');
    Serial.println(ps2.Analog(PSS_LX), DEC);
  }

}