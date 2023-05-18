# Giới thiệu về cách sử dụng và code điều khiển PS2:

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

```Serial.println(ps2.Analog(PSS_LX), DEC); ``` là hàm dùng để đọc giá trị từ cần Analog (Joystick) bên trái. Nó sẽ trả ra giá trị từ 0 -> 255 tương ứng với giới hạn của mỗi trục X và Y trên cần Analog (Joystick) của PS4.

+ **Mở rộng**: Cách điều khiển động cơ Motor bằng cần Analog: (Tham khảo code DC Motor) trong Training01

# Giới thiệu về cách sử dụng và code DC Motor:

Ở trong code **MotorControl.ino** của thư mục Training01 ta sẽ được giới thiệu qua về những điều cơ bản của DC Motor:

+ Tìm hiểu về cấu tạo của động cơ DC motor: Động cơ DC (DC Motor) có cấu tạo gồm 2 dây dẫn âm (-) dương (+) dùng để kích điện và tạo xung cho nam châm và chạy đơn vị thời gian là microsecond (micro giây hay um s)

**Hình ảnh cấu tạo của động cơ DC:** 

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/ec233d34-c216-4380-a6dd-c71c1263b43a)

**Hình ảnh của xung:**

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/9b094618-4674-49e9-92dd-9aef49955750)

Thông thường thời gian hoạt động của xung tương đương với thời gian hoạt động của motor. Khi ta quy định xung ta quy định cho công xuất của motor chạy ở mức độ bao nhiêu phần trăm. **Ví dụ:** Xung 75% sẽ có thời gian hoạt động là 75% (hay công suất 75%) và 25% nghỉ. Các xung còn lại tương tự như vậy.

**Hướng dẫn code một DC Motor:**
- Cấu thành của việc code một motor gồm có: 2 chân điện để đặt xung (Kênh PWM), Tên motor và kênh tương ứng (Kênh Motor của PCA9685 - Khi người dùng cắm vào mạch Bánh Mì), tốc độ của Motor (Được quy định theo khoảng thời gian từ -4095 tới 4095 microsecond) (**Tại sao lại là -4095 ???? Điều này sẽ được giải thích tại phần code chuẩn hóa** 

**Lưu ý:** khi cần code tên motor và cổng tương ứng trên PCA9685 nên đặt tên dễ nhớ và thống nhất phương thức đặt tên với những coder khác.

**Các cổng tương ứng của vi mạch Bánh Mì:**

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/8a680ed3-22f1-4cda-8863-3f923a3cd72c)

**Tiến hành code DC Motor:**

 + **Bước 1:** Tiến hành khai báo thư viện: (Thư viện và tất cả hàm liên quan của PWM , PS2X (Ta sẽ dùng để code điều khiẻn sau đó) sẽ được nhập trực tiếp qua code)
```
#include <Adafruit_PWMServoDriver.h> //Khai báo header từ thư việt Adafruit
#include <Wire.h>
```

+ **Bước 2:** Tiến hành tạo vật thể PS2 và khai chân PWM (Dành cho điều khiển động cơ):

```PS2X ps2; //Tạo vật thể ps2```
```Adafruit_PWMServoDriver pwm;  //Hoặc Adafruit_PWMServoDriver pwm = new Adafruit_PWMServoDriver(); để tạo chân PWM```

+ **Bước 3:** Khai chân PWM (Chân để gán xung): 

**Lưu ý:** Vì mỗi DC Motor đều có 2 chân âm dương nên khi khai số chân thì phải khai đủ số chân (Ví dụ như trong việc sử dụng 4 chiếc Motor thì cần 8 chân PWM)
Người code có thể gán số tùy thích vì chưa cần phải tham chiếu với các hàm 

```
#define PWM_DC0A            0
#define PWM_DC0B            1
#define PWM_DC1A            2
#define PWM_DC1B            3
#define PWM_DC2A            4
#define PWM_DC2B            5
#define PWM_DC3A            6
#define PWM_DC3B            7
```

+ **Bước 4:** Setup (Tương tự như điều khiển PS2 có thể đọc lại nếu quên)

+ **Bước 5:** Chuẩn hóa hàm Motor DC để tái sử dụng nhiều lần và giải thích code 

Việc sử dụng đi sử dụng lại hàm ```setPWM()``` để phải khai từng chân có thể khiến bạn bị rối vì mõi Motor cũng phải khai 2 chân.
Trong khi đó ta ưu tiên những hàm thuận tiện để sử dụng lại trong ```loop()```

```

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

```

+ **Giải thích code:** 
Vận tốc hóa thời gian được cho đó là thời gian từ -4095 tới 4095.  Khi ta nói vận tốc (```speed```) 4095 tức là vận tốc tại thời điểm chạy ở 4095 microsecond. Câu trả lời là: Không đối với cả vận tốc và thời gian và néu vận tốc âm thì Motor. **Tại sao?** Code trên có giải thích mọi thứ.

```
      pwm.setPWM(PWM_DC1A, 0, (speed > 0) ? speed : 0);
      pwm.setPWM(PWM_DC1B, 0, (speed < 0) ? (-speed) : 0);
```

**Giải thích:** Nếu vận tốc dương thì chân PWM_DC1A của Motor DC1 hoạt động ở tốc độ 4095 (hoặc tùy vào v mong muốn của coder miễn nó dương) và chân bên PWM_1B bên kia chạy ở tốc độ 0. Nếu vận tốc âm thì chân PWM_DC1A của động cơ DC Motor 1 sẽ không chạy do điều kiện vận tốc phải dương, chân PWM_DC1B sẽ chạy nhờ vào điều kiện vận tốc âm và nhưng thực tế vẫn chạy ở vận tốc dương vì là ```-speed```.

**Ghi Nhớ: VIỆC VẬN TỐC ÂM CHỈ DÙNG ĐỂ KÍCH HOẠT ĐIỀU KIỆN TA THAY ĐỔI CHUIỀU CHỨ KHÔNG TÁC DỤNG TRONG VIỆC QUY ĐỊNH VẬN TỐC VÀ THỜI GIAN THỰC TÉ VÌ VẬN TỐC VÀ THỜI GIAN LUÔN DƯƠNG. NÊN SAU ĐÓ TA THẤY TRONG HÀM Ở ```setPƯM()``` THỨ 2 LÀ  ```(-speed)``` CHỨ KHÔNG PHẢI ```(speed)```  ĐỂ NGHỊCH ĐẢO LẠI TRẠNG THÁI ÂM CỦA ```speed``` VỀ VẬN TỐC VÀ THỜI GIAN DƯƠNG ĐỂ MOTOR CHẠY ĐƯỢC. Tóm gọn lại: VẬN TỐC ÂM DÙNG ĐẺ QUY ĐỊNH CHIỀU QUAY**

**Sau khi đọc xong bạn có thể quên đống code ở trên cũng được vì chúng ta có thể hoàn toàn copy và paste. Việc sử dụng hàm ```ctrl_dc();``` ở ```loop()``` quan trọng hơn.

+ **Bước 6**: Xử lý hàm trong ```loop()``` và khai công suất (chu kỳ) của DC Motor:


Ngoài ra ta có thể khải báo trước tốc độ ví dụ như muốn công suất bao nhiêu % (chu kỳ hoạt động bao nhiêu %) bằng cách define lên trên đầu

```
// Kênh PWM (Chân của các servo và DC motor) điều khiển động cơ (Số chân của động cơ DC hay servo đều gấp đôi số kênh của động cơ đó)

#define PWM_DC0A            0
#define PWM_DC0B            1
#define PWM_DC1A            2
#define PWM_DC1B            3
#define PWM_DC2A            4
#define PWM_DC2B            5
#define PWM_DC3A            6
#define PWM_DC3B            7

#define SPD_FAST            2047
// Vận tốc đạt ở 2047 giây tức 50% chu kỳ. Tính toán thời gian để đạt tại 1 chu kỳ n% 
//bằng cách lấy (4095 nhân n%) -1 
```

Sử dụng hàm 

+ Hàm ```ctrl_dc``` có cách sử dụng là:

```ctrl_dc(Motor thứ tự mấy trên mạch Bánh Mì, tốc độ lấy từ Joystck hay nút bấm tùy)```


![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/8a680ed3-22f1-4cda-8863-3f923a3cd72c)

+ Khi khai Motor trái ```MOT_LEFT``` ở cổng nào thì nhớ ở cổng đó và đối chiếu lại bảng trên phòng trừ trường hợp khai nhầm và chạy nhầm Motor

```
void loop() {

  ctrl_dc(MOT_LEFT, 0); //gọi hàm ctrl_dc ra -> gán kênh của động cơ Motor trái, gán tốc độ bằng 0 (Tức là chưa chạy)

  //Cách ghép hàm đẻ sử dụng DC Motor với điều khiển PS2:
  ctrl_dc(MOT_LEFT ,map(ps2.Analog(PSS_LY), 0, 255, -SPD_FAST, SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái
  ctrl_dc(MOT_RIGHT,map(ps2.Analog(PSS_RY), 0, 255, SPD_FAST, -SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái

}
```
+ Sử dụng hàm ``map()``:

```map(ps2.Analog(PSS_LY), 0, 255, -SPD_FAST, SPD_FAST)``` đồng nhất tỉ lệ của tốc độ động cơ với hệ trục xy của cần Analog (Joystick) của điều khiển PS4. Thông thường ta sẽ phải khai chiều quay nếu là Motor trái như trên thì phải quay từ tốc độ từ âm qua dương. Còn với bánh bên tay phải thì hoàn toàn ngược lại từ dương qua âm hay ```SPD_FAST, -SPD_FAST``` giống như hàm dưới:

```
  ctrl_dc(MOT_RIGHT,map(ps2.Analog(PSS_RY), 0, 255, SPD_FAST, -SPD_FAST)); // Lấy giá trị Y từ cần Analog bên tay trái
```






