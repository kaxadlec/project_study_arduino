int led_red = D2;
int led_blue = D3;
int led_green = D4;
int led_yellow = D5;

int sw_red = D6;
int sw_blue = D7;
int sw_green = D8;
int sw_yellow = D9;

int sw_red_value = 0;  // 빨강 스위치 현재상태
int sw_red_old_value = 1;  // 빨강 스위치 이전상태
int led_red_status = 0; // 빨강 led 상태 

int sw_blue_value = 0;  // 파랑 스위치 현재상태
int sw_blue_old_value = 1;  // 파랑 스위치 이전상태
int led_blue_status = 0; // 파랑 led 상태 

int sw_green_value = 0;  // 초록 스위치 현재상태
int sw_green_old_value = 1;  // 초록 스위치 이전상태
int led_green_status = 0; // 초록 led 상태 

int sw_yellow_value = 0;  // 노랑 스위치 현재상태
int sw_yellow_old_value = 1;  // 노랑 스위치 이전상태
int led_yellow_status = 0; // 노랑 led 상태 


void setup() {
  // 시리얼 통신
  Serial.begin(115200);
  // 핀모드 설정
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);

  pinMode(sw_red, INPUT);
  pinMode(sw_blue, INPUT);
  pinMode(sw_green, INPUT);
  pinMode(sw_yellow, INPUT);
}

// 1. 처음에 스위치를 누르지 않음 -> 
//    sw_red_value = 1
//    (sw_red_old_value = 1)
//    led_red_status = 0 이므로 
//    digitalWrite(led_red, LOW); 
//    delay 0.1초
// 2. 스위치를 누르고 있을 때 -> 
//    sw_red_value = 0
//    if문 sw_red_value == 0 && sw_red_old_value == 1 이므로 
//    led_red_status = 1
//    (sw_red_old_value = 0)
//    digitalWrite(led_red, HIGH);
//    delay 0.1초
// 3. 스위치를 떼면 ->
//    sw_red_value = 1
//    (sw_red_old_value = 1)
//    그대로 led_red_status = 1
//    digitalWrite(led_red, HIGH);
//    delay 0.1초

void loop() {
  int sw_red_value = digitalRead(sw_red); // 스위치가 닫히는 순간만 0
  //Serial.println(sw_red_value); // 스위치가 누를때 시리얼모니터에 0이 출력되는지 확인 
  
  // sw_red_old_value 초기값 1(스위치 열림)
  // led_red_status 초기값 0(LED OFF)
  // LOW, 0: 스위치 닫힘  // HIGH,1: 스위치 열림
  
  if(sw_red_value == 0 && sw_red_old_value == 1){  // 현재 스위치가 눌리고, 과거 스위치가 열렸을때 
    led_red_status = 1 - led_red_status;  // LED 상태 전환
  }

  sw_red_old_value = sw_red_value;  // 스위치 현재값이 과거값이 됨.

  if(led_red_status == 1){  
   digitalWrite(led_red, HIGH);
  }
  else if(led_red_status == 0){
   digitalWrite(led_red, LOW);
  }
  delay(100);

  // 위와 동일. 색만 바뀜
  int sw_green_value = digitalRead(sw_green); // 스위치가 닫히는 순간만 0
 
  if(sw_green_value == 0 && sw_green_old_value == 1){  // 현재 스위치가 눌리고, 과거 스위치가 열렸을때 
    led_green_status = 1 - led_green_status;  // LED 상태 전환
  }

  sw_green_old_value = sw_green_value;  // 스위치 현재값이 과거값이 됨.

  if(led_green_status == 1){  
   digitalWrite(led_green, HIGH);
  }
  else if(led_green_status == 0){
   digitalWrite(led_green, LOW);
  }
  delay(100);

  int sw_yellow_value = digitalRead(sw_yellow); // 스위치가 닫히는 순간만 0

  if(sw_yellow_value == 0 && sw_yellow_old_value == 1){  // 현재 스위치가 눌리고, 과거 스위치가 열렸을때 
    led_yellow_status = 1 - led_yellow_status;  // LED 상태 전환
  }

  sw_yellow_old_value = sw_yellow_value;  // 스위치 현재값이 과거값이 됨.

  if(led_yellow_status == 1){  
   digitalWrite(led_yellow, HIGH);
  }
  else if(led_yellow_status == 0){
   digitalWrite(led_yellow, LOW);
  }
  delay(100);

  int sw_blue_value = digitalRead(sw_blue); // 스위치가 닫히는 순간만 0

  if(sw_blue_value == 0 && sw_blue_old_value == 1){  // 현재 스위치가 눌리고, 과거 스위치가 열렸을때 
    led_blue_status = 1 - led_blue_status;  // LED 상태 전환
  }

  sw_blue_old_value = sw_blue_value;  // 스위치 현재값이 과거값이 됨.

  if(led_blue_status == 1){  
   digitalWrite(led_blue, HIGH);
  }
  else if(led_blue_status == 0){
   digitalWrite(led_blue, LOW);
  }
  delay(100);
}
 