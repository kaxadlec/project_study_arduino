int red_led = D2;
int blue_led = D3;
int yellow_led = D5;
int green_led = D4;


void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

void loop() {
  digitalWrite(red_led,HIGH);
  delay(1000);
  digitalWrite(blue_led,HIGH);
  delay(1000);
  digitalWrite(yellow_led,HIGH);
  delay(1000);
  digitalWrite(green_led,HIGH);
  delay(1000);
  digitalWrite(red_led,LOW);
  digitalWrite(blue_led,LOW);
  digitalWrite(yellow_led,LOW);
  digitalWrite(green_led,LOW);
  delay(1000);
}
