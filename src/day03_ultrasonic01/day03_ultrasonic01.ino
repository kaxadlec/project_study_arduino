int trigPin = D9;
int echoPin = D8;

long duration;
int distance;

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  pinMode(trigPin, OUTPUT); // 초음파 출력 트리거
  pinMode(echoPin, INPUT); // 초음파 입력 
}

void loop() {
  // 데이터 시트에 있는 규격대로 조작
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // 10us
  digitalWrite(trigPin, LOW);
  // Sonic wave 8 times

  duration = pulseIn(echoPin, HIGH);  // Receive sonic wave
  //distance = duration * 0.017; 
  distance = duration * 17/1000; // Convert to cm

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("cm");  
  delay(500);
}
