# Hướng dẫn chi tiét cách cài đặt Arduino IDE, ESP32, và các thư viện


 **Bước 1:** Truy cập vào trang https://www.arduino.cc/en/software -> Chọn installer tương ứng hiểu điều hành bạn đang sử dụng

![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/252be1d2-d8b5-4762-9803-6eb867861d2b)

 **Bước 2:** Sau khi cài đặt thành công chuyển qua cài các thư viện và firmware hõ trợ ESP32
+ Cài đặt các thư viện qua [link](https://drive.google.com/file/d/1VkmcY8CSZpBvxIFzZDxDbCaMXLNusBLa/view?usp=share_link) và giải nén zip sau khi tải thành công. 
+ Sau khi cài đặt thành công, copy paste hoặc chia đôi cửa sổ kéo thả từ thư mục mới giải nén vào đường folder có đường dẫn Documents\Arduino\libraries. **Lưu ý: Khi không có thư mục libraries trong Arduino thì tự tạo một thư mục libraries và kéo thả vào/ paste bình thường**
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/bf3455ab-7863-4ea0-8e4c-92a33ef7898b)
+ Cài đặt firmware của ESP32: Copy đường dẫn https://dl.espressif.com/dl/package_esp32_index.json vào mục Additional Board Manager URLS trong mục File/Preferences của Aruino IDE rồi bấm OK
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/263ce00b-5975-409a-98c6-dc81d0c9678f)
+ Sau khi cài xong bấm vào ô mục thứ 2 (Board Manager) và tiến hành tìm kiếm và bấm vào nút Install (ở cùng vị trí với nút Remove theo màn hình của người đã cài)
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/b03e6783-c7c7-4e6a-b9fb-869650369ea9)
+ Tiến hành chọn loại mạch. **Mạch bánh mì sử dụng mạch điều khiển ESP32-WROVER-E 16MB nên ta sẽ chọn ESP32 WROVER MODULE trong mục Board**
 ![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/6e82dd9e-50e0-4a6f-b9de-050cecb7ea9a)

**ALL DONE ^^ Bạn đã có thể tiến hành viết code trên Text Editor Arduino IDE. Chúc may các bạn mắn và không gặp BUG kaka =)))))** 

# Một số các lỗi thường gặp:
  
+  Khi không upload được code lên mạch Bánh Mì sau khi đã thử chuyển hết tất cả các cổng thì lập tức cài đặt driver [Driver CP210X](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) để hỗ trơ đọc cổng cho mạch Bánh Mì.
+ Cách nhận biết rõ ràng nhất khi máy tính đã nhận mạch hay chưa là vào Device Manager **(Khi đã nhận được tín hiệu từ cổng thì sẽ xuất hiện chân của CP210X trong mục Port)**
![image](https://github.com/codexcelsior/Mastodon_Training/assets/91497379/b58a7d23-818d-4d74-bfb0-6a7f09ef65f3)



