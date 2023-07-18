int photoresister_sensor = A1;
int led_red = D2;
int brightness = 0;
int fade_amount = 5; 

void setup() {
  Serial.begin(115200); // ET보드의 시리얼 통신 속도
  ledcAttachPin(led_red, 0);
  ledcSetup(0, 4000, 0);
}

void loop() {
  brightness = 225 - map(analogRead(photoresister_sensor), 0, 4095, 0, 255);
  Serial.println(brightness);
  ledcWrite(0, brightness);

}
