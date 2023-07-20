#include "oled_u8g2.h" // OLED 제어를 위한 라이브러리 불러오기
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "ID";  // WIFI ID
const char* password = "PW";  // WIFI PW

OLED_U8G2 oled; // OLED 객체 생성  
WebServer server(80);  // 웹서버 객체 생성  

//-------------------------------------------------------------------------------------------
// ETBoard 핀번호 설정, 관련된 변수 설정 
//-----------------------------------------------------------------------------------------
int leds[] = {D2, D3, D4, D5}; // LED 핀 번호 배열(red, blue, green, yellow)
int num_leds = 4;              // LED 개수
int photoresister_sensor = A1; // 조도센서
int temperature_sensor = A2;   // 온도센서
// 현재 온도를 계산하기 위한 변수들
int Vo;
double R1 = 10000;
double logR2, R2, T, Tc, Tf;
double c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int reset_pin = D6; // 카운트 리셋핀 (D6 = 빨강 버튼)
int trig_pin = D9;      // TRIG 핀 설정 (초음파 보내는 핀)
int echo_pin = D8;      // ECHO 핀 설정 (초음파 받는 핀)
int count = 0;      // 카운터용 변수
int pre_time = 0;   // 이전에 물건이 지나간 시간



void setupLEDs() { // LED 초기화 함수
  for (int i = 0; i < num_leds; i++) {
    pinMode(leds[i], OUTPUT); // 모든 LED 핀을 출력 모드로 설정
  }
}

void setupHardware() { //카운트리셋, 초음파 핀 설정 
  pinMode(reset_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void setupWiFi() {
  WiFi.mode(WIFI_STA);    // Set connection mode
  WiFi.begin(ssid, password);  // try to access WIFI
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {  // wait for connection 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // print assigned IP address when it connected
}

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  setupLEDs(); // LED 초기화 함수 호출
  setupHardware(); // 초음파 핀 설정 함수 호출
  oled.setup();
  setupWiFi(); // Wi-Fi 설정 함수 호출

  server.on("/", handleRootEvent);  // (root, event handling function);
  server.begin();
  Serial.println("WEB server started");   
} 


void loop() {
  controlLEDs(); // LED 제어 함수 호출
  readPhotoResister(); // 조도 측정 함수 호출 
  readTemperature(); // 온도 측정 함수 호출 
  updateCountAndDistance(); // 물체인식 카운트 함수 호출       
  resetButtonCheck();  // 리셋버튼 함수 호출 
  Serial.print("count : ");             
  Serial.println(count);
  Serial.println("---------------------");
  displayOLED();  // OLED 디스플레이 함수 호출 

  server.handleClient(); // clients process
  delay(2);
  
}

void controlLEDs() {  // LED 제어 함수

}

void readPhotoResister(){ // 조도 측정 함수
  int sensor_value = analogRead(photoresister_sensor);   // 조도센서가 측정한 값 저장
  Serial.print("Photoresister: ");
  Serial.println(sensor_value);
} 

void readTemperature() { // 온도 측정 후 섭씨 온도, 화씨온도로 변환하는 함수 
  int Vo = analogRead(temperature_sensor); // 온도센서의 값을 읽고 온도로 변환
  R2 = R1 * (4095.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0/5.0) + 32.0;
  Serial.print("Temperature: ");
  Serial.print(Tc); // 섭씨온도
  Serial.print(" C,  ");
  Serial.print(Tf); // 화씨온도
  Serial.print(" F");
}

void updateCountAndDistance() { // 초음파센서를 통해 물체 인식 후 카운트하는 함수 
    long duration, distance;
    digitalWrite(trig_pin, LOW);                
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);                

    duration = pulseIn (echo_pin, HIGH);        
    distance = ((34 * duration) / 1000) / 2;    
    Serial.print("distance : ");
    Serial.print(distance);
    Serial.println("cm");

    if(distance > 2 && distance < 5)            
    {
        int now_time = millis();
        if(now_time - pre_time > 500)           
        {
            count += 1;                         
            pre_time = now_time;                
        }
    }

}

void resetButtonCheck() { // 리셋 버튼 함수(여기에서는 카운트 변수를 리셋) 
  if (digitalRead(reset_pin) == LOW) {
    Serial.println("count reset");
    count = 0;
  }
}

void displayOLED() {  // OLED 디스플레이 함수
  char text1[32] = "count : ";
  char value1[32];
  String str1 = String(count, DEC);
  str1.toCharArray(value1, 6);
  strcat(text1, value1);

  oled.setLine(1, "*Smart Factory");
  oled.setLine(2, text1);
  oled.setLine(3, "---------------------");
  oled.display();
}

void handleRootEvent() {           // function to access through root                   
  Serial.println("main page from ");     // info to access page with serial      
  String clientIP = server.client().remoteIP().toString(); // client's IP address 
  String maskedIP = maskIPAddress(clientIP);    // 고객 아이피 일부 가리기 위한 변수 

  readTemperature(); // 온도 측정 함수 호출
            
  String message = "HyeonJin SmartFactory WebServer\n\n";
  message += "Your IP address: " + maskedIP + "\n";
  message += "Temperature: " + String(Tc) + "C, " + String(Tf) + "F\n";  
  message += "Photoresistor Value: " + String(sensor_value) + "\n";
  message += "Object Count: " + String(count);

  server.send(200, "text/plain", message); // status code 200(ok) , format, message
  Serial.println(message); // monitoring
}

String maskIPAddress(String ip_address) {
  String masked_ip;

  // IP 주소의 중간 부분 가리기
  int first_dot = ip_address.indexOf('.');
  int second_dot = ip_address.indexOf('.', first_dot + 1);

  masked_ip += ip_address.substring(0, first_dot + 1);
  masked_ip += "***";
  masked_ip += ip_address.substring(second_dot);

  return masked_ip;
}

