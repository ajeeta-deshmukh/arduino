void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  float millvolts = (sensorValue/1024.0) * 5000;
  float celsius = millvolts/10;
  Serial.println(celsius);
  delay(1000);
}
