
// 10:20:59.604 -> MAC Address: F4:65:0B:47:87:E8
// 10:21:04.592 -> MAC Address: F4:65:0B:47:87:E8
// 10:21:09.599 -> MAC Address: F4:65:0B:47:87:E8

#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>

Servo servo1, servo2, servo3;



void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  String msg = "";
  for (int i = 0; i < len; i++) msg += (char)incomingData[i];
  Serial.println("Received: " + msg);

  if (msg.startsWith("SERVO1:")) {
    int angle = msg.substring(7).toInt();
    servo1.write(angle);
    Serial.println("Servo1 -> " + String(angle));
  }
  else if (msg.startsWith("SERVO2:")) {
    int angle = msg.substring(7).toInt();
    servo2.write(angle);
    Serial.println("Servo2 -> " + String(angle));
  }
  else if (msg.startsWith("SERVO3:")) {
    int angle = msg.substring(7).toInt();
    servo3.write(angle);
    Serial.println("Servo3 -> " + String(angle));
  }
}

void setup() {
  Serial.begin(115200);

  // Attach servos
servo1.attach(12);
servo2.attach(14);
servo3.attach(27);
servo1.write(0);  // move servo1 to 0 degrees
servo2.write(0);  // move servo2 to 0 degrees
servo3.write(0);  // move servo3 to 0 degrees


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {i
    Serial.println("ESP-NOW Init Failed");
    while (true);
  }

  esp_now_register_recv_cb(onDataRecv);

  Serial.println("Servo ESP32 Ready, MAC: " + WiFi.macAddress());
}

void loop() {
  // Nothing here, everything handled by callback
}
