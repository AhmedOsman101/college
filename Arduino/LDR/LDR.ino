const int LDR = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(LDR);              // 0-1023
  float volts = raw * (5.0 / 1024.0);     // 0-4.995 V

  int percent = map(raw, 0, 1023, 0, 100);

  Serial.print("volts=");
  Serial.print(volts, 2);
  Serial.print("  light=");
  Serial.print(percent);
  Serial.println("%");

  delay(500);
}
