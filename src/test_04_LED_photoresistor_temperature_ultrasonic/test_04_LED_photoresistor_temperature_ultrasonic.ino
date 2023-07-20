#include "oled_u8g2.h" // OLED 제어를 위한 라이브러리 불러오기
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

OLED_U8G2 oled; // OLED 객체 생성  

//-------------------------------------------------------------------------------------------
// ETBoard 핀번호 설정, 관련된 변수 설정 
//-----------------------------------------------------------------------------------------
int leds[] = {D2, D3, D4, D5}; // LED 핀 번호 배열(red, blue, green, yellow)
int num_leds = 4;              // LED 개수
int photoresister_sensor = A1; // 조도센서
int temperature_sensor = A2;   // 온도센서
// 현재 온도를 계산하기 위한 변수들
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int reset_pin = D6; // 카운트 리셋핀 (D6 = 빨강 버튼)
int trig_pin = D9;      // TRIG 핀 설정 (초음파 보내는 핀)
int echo_pin = D8;      // ECHO 핀 설정 (초음파 받는 핀)
int count = 0;      // 카운터용 변수
int pre_time = 0;   // 이전에 물건이 지나간 시간



void initializeLEDs() { // LED 초기화 함수
  for (int i = 0; i < num_leds; i++) {
    pinMode(leds[i], OUTPUT); // 모든 LED 핀을 출력 모드로 설정
  }
}

void initializeHardware() { //카운트리셋, 초음파 핀 설정 
  pinMode(reset_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}
 

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  initializeLEDs(); // LED 초기화 함수 호출
  oled.setup();
  initializeHardware(); // 초음파 핀 설정 함수 호출 
} 


void loop() {
  controlLEDs(); // LED 제어 함수 호출
  readPhotoResister(); // 조도 측정 함수 호출 
  readTemperature(); // 온도 측정 함수 호출 
  updateCountAndDistance() // 물체인식 카운트 함수 호출       
  resetButtonCheck();  // 리셋버튼 함수 호출 
  Serial.print("count : ");             
  Serial.println(count);
  Serial.println("---------------------");
  displayOLED();  // OLED 디스플레이 함수 호출 
  delay(1000);
}

void controlLEDs() {  // LED 제어 함수

}

void readPhotoResister(){ // 조도 측정 함수
  int sensor_value = analogRead(photoresister_sensor);   // 조도센서가 측정한 값 저장
  Serial.print("Photoresister: ");
  Serial.println(sensor_value);
} 

void readTemperature() { // 온도 측정 후 섭씨 온도로 변환하는 함수 
  int Vo = analogRead(temperature_sensor); // 온도센서의 값을 읽고 온도로 변환
  R2 = R1 * (4095.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Serial.print("Temperature: ");
  Serial.print(Tc); // 변환한 온도값을 출력
  Serial.println(" C");
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

