# Hướng dẫn chi tiết cách cài đặt Arduino IDE, ESP32, và các thư viện:


 **Bước 1:** Truy cập vào trang https://www.arduino.cc/en/software -> Chọn installer tương ứng hiểu điều hành bạn đang sử dụng

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/252be1d2-d8b5-4762-9803-6eb867861d2b)

 **Bước 2:** Sau khi cài đặt thành công chuyển qua cài các thư viện và firmware hõ trợ ESP32
+ Cài đặt các thư viện qua [link](https://drive.google.com/file/d/1VkmcY8CSZpBvxIFzZDxDbCaMXLNusBLa/view?usp=share_link) và giải nén zip sau khi tải thành công. 
+ Sau khi cài đặt thành công, copy paste hoặc chia đôi cửa sổ kéo thả từ thư mục mới giải nén vào đường folder có đường dẫn Documents\Arduino\libraries. **Lưu ý: Khi không có thư mục libraries trong Arduino thì tự tạo một thư mục libraries và kéo thả vào/ paste bình thường**
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/bf3455ab-7863-4ea0-8e4c-92a33ef7898b)
+ Cài đặt firmware của ESP32: Copy đường dẫn https://dl.espressif.com/dl/package_esp32_index.json vào mục Additional Boards Manager URLs trong mục File/Preferences của Aruino IDE rồi bấm OK
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/263ce00b-5975-409a-98c6-dc81d0c9678f)
+ Sau khi cài xong bấm vào ô mục thứ 2 (Board Manager) và tiến hành tìm kiếm và bấm vào nút Install (ở cùng vị trí với nút Remove theo màn hình của người đã cài)
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/b03e6783-c7c7-4e6a-b9fb-869650369ea9)
+ Tiến hành chọn loại mạch. **Mạch bánh mì sử dụng mạch điều khiển ESP32-WROVER-E 16MB nên ta sẽ chọn ESP32 Wrover Module trong mục Board**
 ![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/6e82dd9e-50e0-4a6f-b9de-050cecb7ea9a)

**ALL DONE ^^ Bạn đã có thể tiến hành viết code trên Text Editor Arduino IDE. Chúc may các bạn mắn và không gặp BUG kaka =)))))** 

# Một số các lỗi thường gặp:
  
+  Khi không upload được code lên mạch Bánh Mì sau khi đã thử chuyển hết tất cả các cổng thì lập tức cài đặt driver [Driver CP210X](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) để hỗ trơ đọc cổng cho mạch Bánh Mì.
+ Cách nhận biết rõ ràng nhất khi máy tính đã nhận mạch hay chưa là vào Device Manager **(Khi đã nhận được tín hiệu từ cổng thì sẽ xuất hiện chân của CP210X trong mục Port)**
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/b58a7d23-818d-4d74-bfb0-6a7f09ef65f3)


# Hướng dẫn cách sử dụng các hàm và giải mã code mẫu:

**Giới thiệu về điều khiển PS2:**

 Ở trong code **PS2Controller.ino** của thư mục Training01 ta sẽ được giới thiệu qua về những điều cơ bản của chiếc điều khiển PS2:
 
 + **Bước 1:** Tiến hành khai báo thư viện: (Thư viện và tất cả hàm liên quan của PS2X sẽ được nhập trực tiếp qua code)

```#include <PS2X_lib.h> ```

+ **Bước 2:** Tiến hành tạo vật thể PS2 và khai chân PWM (Dành cho điều khiển động cơ):

```PS2X ps2; //Tạo vật thể ps2```
```Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver(); để tạo chân PWM```

+ **Bước 3:** Khai chân cổng tín hiệu dành cho PS2
```
#define PS2_ATT             10
#define PS2_CMD             11
#define PS2_DAT             12
#define PS2_CLK             13
```
Trên ổ căm mạch VIA đều có 4 cổng tương đương với 4 loại tín hiệu khác nhau

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/af1d8f29-48c4-440b-b58a-9774e43ecfba)

Chân của jack cắm của tay cầm tới mạch VIA cũng như vậy:

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/363f65d3-6e0b-49b6-aaa1-a149e8198eff)

+ **Mục đích:** chúng ta có thể tiến hành sử dụng các thông số này để check xem tất cả các đầu tín hiệu của điều khiển này đã hoạt động hay chưa qua hàm ```ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT)``` ở **Bước 4**

+ **Bước 4:** Điều chỉnh hàm ```setup()```:
Hàm ```setup``` dùng để khai báo những loại hàm dùng 1 lần (Tức là khi khởi động bot ta cần set up những gì).

```
void setup() { //Hàm set up chạy khởi tạo một lần khi khởi động mạch 
  // put your setup code here, to run once:
  Serial.begin(115200); //Serial monitor là một bộ cài sẵn đùng để debug code 

  Serial.println("Welcome to the Mastodon Banhmi Console"); //In ra Serial dòng chữ trong ngoặc 


  while(ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT) != 0)
  {
    Serial.println("PS2 error");
    delay(500);
  } //Test config của tay cầm ps2 qua các cổng. Khi giá trị của một trong các cổng của tay cầm = 0 
  // thì in ra dòng chữ PS2 error để nhận biết cho người dùng đang có lỗi với port kết nối của controller

}
```

+ **Bước 5:** Điều chỉnh hàm ```loop()```
Hàm ```loop()``` dùng để code và tiến hành các chương trình liên tục và không ngừng tới khi tắt bot. (Giống như ```while(True)``` trong C++ )

```

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
```

+ **Giải mã code:** 
``` ps2.read_gamepad();``` là hàm dùng để bắt đầu cho tay cầm hoạt dộng và thực hiện đọc các output từ điều khiển
```if (ps2.Button(PSB_PAD_UP)) ``` nghĩa là mỗi khi bấm nút đi  lên của tay cầm PS2 thì sẽ thực hiệnd diều gì. Phần còn lại trong khối lệnh ```{}``` vui lòng đọc chú thích trong đó.
Format chính của bấm nút đó là ```ps2.Button(Tên nút muốn nhấn)```

Bảng các nút để và các phân loại của các nút:

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/89735ee7-d863-4ed6-bbaf-bc290a035b6a)
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/d8e0dd79-81f4-46e7-af6e-8548273a204d)
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/187b1c4a-39cf-4fb5-814e-537d1cc41f88)

+ **Bước 6:** Đọc giá trị từ cần điều khiển Analog (Joystick):

```    Serial.println(ps2.Analog(PSS_LX), DEC); ``` là hàm dùng để đọc giá trị từ cần Analog (Joystick) bên trái. Nó sẽ trả ra giá trị từ 0 -> 255 

+ **Mở rộng**: Cách điều khiển động cơ Motor bằng cần Analog: (Tham khảo code DC Motor)







