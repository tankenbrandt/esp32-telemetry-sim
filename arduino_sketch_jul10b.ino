void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting telemetry simulation...")

}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 2.4;
  float humidity = 50.1;
  float accelX = 0.12;

  Serial.print("TEMP: ");
  Serial.print(temp);
  Serial.print(" C | HUM: ");
  Serial.print(humidity);
  Serial.print(" % | ACCEL X: ");
  Serial.println(accelX);

  delay(1000);
}


