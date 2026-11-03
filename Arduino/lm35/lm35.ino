const int LM35 = A0;

int rawTempValue;
float tempValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  rawTempValue = analogRead(LM35);
  tempValue = rawTempValue * (5.0 / 1024.0) * 100.0;
  // tempValue = (rawTempValue * 4.88) / 10.0;

  Serial.print("Temperature = ");
  Serial.print(tempValue);
  Serial.println(" C");

  delay(1000);
}
