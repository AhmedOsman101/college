// Turn the LED on and hold it for 5 seconds, then blink forever.
//
// The one-shot happens in setup(); the repeating part lives in loop().
// setup() runs once at power-on, loop() runs forever after that.

const int LED        = 13;
const int HOLD_MS    = 5000;   // how long to stay on before blinking
const int BLINK_MS   = 5000;    // on/off interval once blinking

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  delay(2000);                 // let the serial monitor attach before we talk

  Serial.println("--- LED ON for 5 seconds ---");
  digitalWrite(LED, HIGH);
  delay(HOLD_MS);

  Serial.println("--- Now blinking ---");
  digitalWrite(LED, LOW);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println("ON");
  delay(BLINK_MS);

  digitalWrite(LED, LOW);
  Serial.println("OFF");
  delay(BLINK_MS);
}
