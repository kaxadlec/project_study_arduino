int temperature_sensor = A2;

void setup(){
  Serial.begin(115200);
}
void loop(){
  int result = analogRead(temperature_sensor);
  Serial.println(result);
  delay(500);
}