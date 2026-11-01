// Seven-segment display driver controlled by a potentiometer.
//
// Wiring:
//   Segments A-G  -> Arduino digital pins 2-8 (each via 330Ω resistor)
//   DP (decimal)  -> pin 9 (unused but configured as output)
//   Potentiometer -> A0 (wiper), 5V (one end), GND (other end)
//
// Behaviour: turning the pot smoothly maps 0-9 onto the display.

// Segment pin assignments
#define SEG_A  2  // top horizontal bar
#define SEG_B  3  // top-right vertical bar
#define SEG_C  4  // bottom-right vertical bar
#define SEG_D  5  // bottom horizontal bar
#define SEG_E  6  // bottom-left vertical bar
#define SEG_F  7  // top-left vertical bar
#define SEG_G  8  // middle horizontal bar
#define SEG_DP 9  // decimal point (not driven in this sketch)

// Lookup table mapping each digit (0-9) to its segment bitmask.
//
// Bit positions:  6 5 4 3 2 1 0
// Segment names:  G F E D C B A
const byte DIGITS[10] = {
  0b0111111,  // 0  A B C D E F -
  0b0000110,  // 1  - - B C - - -
  0b1011011,  // 2  A B - D E - G
  0b1001111,  // 3  A B C D - - G
  0b1100110,  // 4  - B C - - F G
  0b1101101,  // 5  A - C D - F G
  0b1111101,  // 6  A   C D E F G
  0b0000111,  // 7  A B C - - - -
  0b1111111,  // 8  A B C D E F G
  0b1101111,  // 9  A B C D - F G
};

// All seven segment pins in order A-G so we can loop over them.
const int SEG_PINS[7] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };

// Analog pin connected to the potentiometer wiper.
const int POT_PIN = A0;

// Drive the seven-segment display to show digit n (0-9).
//
// Reads the bitmask for n out of DIGITS[], then writes each segment
// pin in a single pass. Bit i of the mask = state of SEG_PINS[i].
// Writing all pins in one pass (instead of clearing first then setting)
// eliminates the visible flicker that a clear-then-draw approach causes.
void printNumber(unsigned int n) {
  if (n > 9) return;               // ignore out-of-range values
  byte mask = DIGITS[n];
  for (int i = 0; i < 7; i++) {
    // shift the mask right by i to get the bit for segment i,
    // then mask off everything except bit 0 to get HIGH or LOW.
    digitalWrite(SEG_PINS[i], (mask >> i) & 1);
  }
}

void setup() {
  // Configure all segment pins as outputs.
  for (int i = 0; i < 7; i++) {
    pinMode(SEG_PINS[i], OUTPUT);
  }
  pinMode(SEG_DP, OUTPUT);   // decimal point — wired but not used here
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer (0-1023, 10-bit ADC).
  int potVal = analogRead(POT_PIN);

  // Map the 0-1023 range onto 0-9.
  // map(value, fromLow, fromHigh, toLow, toHigh) does linear scaling:
  int digit = map(potVal, 0, 1023, 0, 9);

  // Log both the raw ADC value and the mapped digit for debugging.
  Serial.print("Pot: ");
  Serial.print(potVal);
  Serial.print("  -> digit: ");
  Serial.println(digit);

  printNumber(digit);
  delay(100);
}
