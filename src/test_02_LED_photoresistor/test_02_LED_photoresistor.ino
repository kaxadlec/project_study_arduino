int leds[] = {D2, D3, D4, D5}; // LED 핀 번호 배열(red, blue, green, yellow)
int num_leds = 4;              // LED 개수
int photoresister_sensor = A1; // 조도센서


void initializeLEDs() { // LED 초기화 함수
  for (int i = 0; i < num_leds; i++) {
    pinMode(leds[i], OUTPUT); // 모든 LED 핀을 출력 모드로 설정
  }
}

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  initializeLEDs(); // LED 초기화 함수 호출
} 


void loop() {
  controlLEDs(); // LED 제어 함수 호출
  readSensorValue(); // 조도 측정 함수 호출 

}

void controlLEDs() {  // LED 제어 함수

}

void readSensorValue(){ // 조도 측정 함수
  int sensor_value = analogRead(photoresister_sensor);   // 센서가 측정한 값 저장
  //Serial.println(sensor_value);
} 

