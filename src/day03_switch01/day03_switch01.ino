int led_red = D2;
int led_blue = D3;
int led_green = D4;
int led_yellow = D5;
int btn_red = D6;
int btn_blue = D7;
int btn_yellow = D9;
int btn_green = D8;


void setup() {
  Serial.begin(115200);
  pinMode(btn_red, INPUT);

}

void loop() {
 int btn_red_status = digitalRead(btn_red);

 if(btn_red_status == LOW){ // Low가 눌린현상임.
   //Serial.println("button pushed"); 
 }
 else{
   Serial.println("no");
 }

 delay(100); 
}
