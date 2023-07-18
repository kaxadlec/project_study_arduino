int sensor = A2;                                         // 온도센서
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// 현재온도를 구하기 위한 값들입니다. 굳이 알 필요없으니 넘어가도 좋습니다.


void setup() {
  Serial.begin(115200);                                  // 통신속도
}


void loop() {
  Vo = analogRead(sensor);                               // 센서의 값을 읽고 온도로 변환
  R2 = R1 * (4095.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;  
 
  Serial.print(Tc);                                      // 변환한 온도값을 출력
  Serial.println(" C");
  
  delay(200);                                            // 0.2초대기
}