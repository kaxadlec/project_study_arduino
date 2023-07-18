int light

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  pinMode(trigPin, OUTPUT); // 초음파 출력 트리거
  pinMode(echoPin, INPUT); // 초음파 입력 

  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
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

  if(distance <= 4){

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.print("cm,  물건이 통과했습니다. 총"); 
    Serial.print(cnt);
    Serial.println("개입니다.");
    cnt = cnt + 1;
    digitalWrite(red_led, LOW);
    digitalWrite(green_led,HIGH);
    delay(500);
  }else{
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println("cm"); 
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, HIGH);
    delay(300);
  }
  
  
}
