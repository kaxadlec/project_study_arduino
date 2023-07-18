int led_red = D2;
int led_blue = D3;
int led_green = D4;
int led_yellow = D5;

int btn_red = D6;
int btn_blue = D7;
int btn_yellow = D9;
int btn_green = D8;

int btn_red_val = 0;  // 스위치 현재
int btn_red_old_val = 1;  // 스위치 이전
int led_red_status = 0; // led 상태 

int btn_blue_val = 0;  // 스위치 현재
int btn_blue_old_val = 1;  // 스위치 이전
int led_blue_status = 0; // led 상태 

int btn_green_val = 0;  // 스위치 현재
int btn_green_old_val = 1;  // 스위치 이전
int led_green_status = 0; // led 상태 

int btn_yellow_val = 0;  // 스위치 현재
int btn_yellow_old_val = 1;  // 스위치 이전
int led_yellow_status = 0; // led 상태 


void setup() {
  Serial.begin(115200);

  pinMode(btn_red, INPUT);
  pinMode(btn_blue, INPUT);
  pinMode(btn_green, INPUT);
  pinMode(btn_yellow, INPUT);

  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);

}

void loop() {
//  int btn_red_status = digitalRead(btn_red);
//  int btn_blue_status = digitalRead(btn_red);
//  int btn_yellow_status = digitalRead(btn_red);
//  int btn_green_status = digitalRead(btn_red);

  int btn_red_status = digitalRead(btn_red);
  
  if(btn_red_status == LOW && btn_red_old_val == HIGH){ // Low가 눌린현상임.
    Serial.println("빨강버튼 눌려서 LED ON");
    digitalWrite(led_red, HIGH);

    btn_red_status = 1 - btn_red_status;
    //btn_red_old_val = 0;
  }
  btn_red_old_val = btn_red_val;

  if(btn_red_status == HIGH){
   Serial.println("빨강버튼 눌려서 LED ON");
   digitalWrite(led_red, LOW);
  }
  else{
   Serial.println("빨강버튼 눌려서 LED OFF");
   digitalWrite(led_red, HIGH);

  }
  delay(100);
}
 