

int leds[] = {D2, D3, D4, D5}; // LED 핀 번호 배열(red, blue, green, yellow)
int num_leds = 4;              // LED 개수
int photoresister_sensor = A1; // 조도센서
int temperature_sensor = A2;   // 온도센서
// 현재 온도를 계산하기 위한 변수들
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;



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
  readPhotoResister(); // 조도 측정 함수 호출 
  readTemperature(); // 온도 측정 함수 호출 
  delay(1000);
}

void controlLEDs() {  // LED 제어 함수

}

void readPhotoResister(){ // 조도 측정 함수
  int sensor_value = analogRead(photoresister_sensor);   // 조도센서가 측정한 값 저장
  // Serial.println(sensor_value);
} 

void readTemperature() {
  int Vo = analogRead(temperature_sensor); // 온도센서의 값을 읽고 온도로 변환
  R2 = R1 * (4095.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  // Serial.print(Tc); // 변환한 온도값을 출력
  // Serial.println(" C");
}

