# Electronics Kit — What Every Component Does

Companion to `ARDUINO-UNO-SETUP.md`.

---

## Status: you are ready

Verified on this machine:

- **Toolchain** — `arduino-cli` 1.5.1, AVR core installed, 381 MB in `~/.arduino15`.
- **Libraries** — ten pre-installed and **compile-tested**: `DHT sensor library`,
  `Adafruit Unified Sensor`, `Servo`, `LiquidCrystal`, `LiquidCrystal_I2C`,
  `Keypad`, `IRremote`, `MFRC522`, `NewPing`, `Adafruit NeoPixel`.
  No internet needed for any of them.
- **Ready-to-run sketches** — six in `~/Arduino/_verified/`, each verified to
  compile: `dht`, `lcd`, `keypad`, `ir`, `rfid`, `servo`. Open one and change the
  pin numbers rather than writing from scratch.
- **Board** — genuine Arduino UNO R3 (`2341:0043`), upload and serial both
  confirmed working.
- **Headroom** — a sketch using all six tested libraries compiles to 17.4 KB
  flash (53%) and 973 B RAM (47%). **RAM is the tighter limit.**

---

## The three things you must understand first

### 1. Every pin is one of three kinds

| Kind        | What it does              | Reading it in code                | Pins                              |
| ----------- | ------------------------- | --------------------------------- | --------------------------------- |
| **Digital** | on/off only               | `digitalRead(pin)` → `HIGH`/`LOW` | D0–D13                            |
| **Analog**  | reads continuous voltage  | `analogRead(A0)` → **0–1023**     | A0–A5                             |
| **PWM**     | digital that fakes analog | `analogWrite(pin, 0–255)`         | **D3, D5, D6, D9, D10, D11 only** |

Analog reads are 0–**1023**, not 0–255. Using the wrong range is a classic
beginner bug — permanently wrong by 4×:

```cpp
int value = analogRead(A0);
int percent = map(value, 0, 1023, 0, 100);
```

Only those six pins do PWM. A servo or motor on any other pin simply won't move.

### 2. Every module has VCC + GND + signal

Almost every component is a breakout with the same labelling. **UNO GND to every
module's GND** — non-negotiable, and the single most common cause of "nothing
works".

### 3. The UNO's limits

```
Flash   32,256 bytes      Per-pin current  40 mA max (20 recommended)
SRAM     2,048 bytes      Total all pins    200 mA
Logic 5V
```

**The 5V pin cannot power motors or servos** (~500 mA total; one servo pulls
100–200 mA). Power them from the battery and **join the grounds**:

```
Battery +  ──► motor/servo VCC
Battery −  ──► module GND
             └──► Arduino GND     ← this shared wire is mandatory
Arduino 5V ──► never to a motor
```

---

## Pin budget: you cannot plug in everything

20 usable pins (D0–D13 + A0–A5), and D0/D1 are reserved for serial.

| Component                                   | Pins      |
| ------------------------------------------- | --------- |
| 4×4 keypad                                  | 8         |
| 7-segment display                           | 7–8       |
| RFID (RC522)                                | 4–5 (SPI) |
| 5 LEDs                                      | 5         |
| Ultrasonic                                  | 2         |
| HC-05 Bluetooth                             | 2         |
| I2C LCD                                     | 2         |
| Each analog sensor (LDR, soil, rain, flame) | 1         |
| DHT11, PIR, relay, button                   | 1 each    |

Keypad + 7-segment + 5 LEDs already exceeds 20. **Choosing which sensors to
combine _is_ the project design.** A realistic combination:

```
I2C LCD   A4, A5      display
DHT11     D2          temperature + humidity
LDR       A0          light
Soil      A1          moisture
Servo     D3          PWM required
Button    D4
LED       D5, D6      PWM
```

Nine pins for a full environmental monitor, leaving room for one more sensor.
Pick sensors first, then check they fit.

---

## Sensors (input)

| Component                | Measures                       | Type                  | Library              |
| ------------------------ | ------------------------------ | --------------------- | -------------------- |
| **Ultrasonic (HC-SR04)** | distance via sound bounce      | Digital, 2 pins       | none (or `NewPing`)  |
| **LDR**                  | brightness                     | **Analog** + resistor | none                 |
| **DHT11**                | air temperature _and_ humidity | Digital               | `DHT sensor library` |
| **IR sensor**            | proximity (infrared)           | Digital               | none                 |
| **PIR**                  | motion, via body heat          | Digital               | none                 |
| **Flame**                | flame / IR flicker             | **Analog**            | none                 |
| **Rain**                 | wetness                        | **Analog**            | none                 |
| **Soil moisture**        | how wet the soil is            | **Analog**            | none                 |
| **5K / 10K pots**        | a knob you turn                | **Analog**, 3 pins    | none                 |

An LDR and a potentiometer are the same circuit — a variable resistor plus a
fixed one. That's why both are in the kit: the pot lets you test analog-reading
code before you have the sensor.

```cpp
// Universal analog reader - works for LDR, soil, rain, flame, potentiometer
int raw = analogRead(A0);
int percent = map(raw, 0, 1023, 0, 100);
Serial.println(percent);
```

**LDR needs a divider.** The LDR alone is just a resistor:

```
5V ---[ LDR ]---+
                +--- A0   (read here)
5V ---[ 5kΩ ]---+
                |
               GND
```

More light → LDR resistance drops → **reading goes up**. On a soil sensor, wetter
soil conducts better → **reading goes up** (unless the module inverts it — test and
invert if it feels backwards).

### DHT11

```cpp
#include <DHT.h>
DHT dht(2, DHT11);            // data pin D2, model DHT11

void setup() { Serial.begin(9600); dht.begin(); }

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT read failed - check wiring");
  } else {
    Serial.print("Humidity:    "); Serial.print(humidity);    Serial.println(" %");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
  }
  delay(2000);     // DHT11 can only be read every ~2 seconds
}
```

Reading it in a tight loop returns stale or `NaN` values. Always check the return
value. `readTemperature()` is Celsius. The DHT22 is the upgrade (±0.5 °C).

### PIR

Outputs `HIGH` on motion. Has a **~1 minute warm-up** after power-on before it
stabilises. Two onboard potentiometers set sensitivity and re-trigger mode.

---

## Outputs

| Component            | Does                                     | Type                   | Library |
| -------------------- | ---------------------------------------- | ---------------------- | ------- |
| **LEDs ×5**          | emit light                               | **PWM** for brightness | none    |
| **Relay**            | switches a high-power circuit            | Digital                | none    |
| **Servo 180°**       | rotates to an exact angle                | **PWM**                | `Servo` |
| **Servo 360°**       | spins continuously — angle becomes speed | **PWM**                | `Servo` |
| **DC motors**        | spin continuously                        | **PWM** + H-bridge     | none    |
| **H-bridge (L298N)** | drives 2 DC motors, reversible           | 4 digital + 2 PWM      | none    |
| **Seven segment**    | shows one digit                          | 7–8 digital            | none    |

### Servo 180° vs 360°

Same wiring, opposite code:

```cpp
#include <Servo.h>
Servo myservo;

void setup() { myservo.attach(3); }   // MUST be a PWM pin

void loop() {
  myservo.write(90);   // 180° servo: go to 90 degrees
  delay(1000);
  myservo.write(0);    // 180° servo: go to 0 degrees
  delay(1000);
}
```

On a **360°** servo, `write()` sets _speed_: `0` stopped, `180` full one way, `90`
full the other. `write(90)` on a 360° servo makes it spin flat out — it does not
centre it.

### H-bridge (L298N)

A motor driven straight from a pin spins one way only. The H-bridge flips polarity:

```cpp
#define IN1 8
#define IN2 9
#define ENA 6      // PWM pin

void setup(){ pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT); pinMode(ENA,OUTPUT); }

void spinForward(int speed){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); analogWrite(ENA,speed);
}
void spinReverse(int speed){
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); analogWrite(ENA,speed);
}
void stopMotor(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); analogWrite(ENA,0);
}
```

Power the L298N from the battery via its `+12V`/`GND` terminals, **not** the UNO's
5V. It has a 5V regulator jumper for when you're _not_ powering it externally.

**A servo needs no H-bridge.** It takes a PWM signal directly.

### Resistor reality check

- **Every LED needs one 330Ω in series.** Connecting an LED straight to a pin cooks
  the pin. You have exactly 5 resistors and 5 LEDs — matched on purpose.
- **A seven-segment needs one per segment** — 7 or 8, not one for the display. You
  only have 5. Some kits arrive with them pre-soldered; check. Otherwise you can
  light 5 segments (enough for most numbers) or drive them directly and accept
  uneven brightness.
- **An LED on D13 without a resistor** bypasses the UNO's onboard resistor (which
  only feeds the _built-in_ LED), so full ~40 mA flows through it. It'll be very
  bright and slightly overdriven. Use a 330Ω.

### Relay

A switch you control with a small signal. Most modules are **active-LOW**:
`digitalWrite(pin, LOW)` turns it ON, `HIGH` turns it OFF. This inverts what you
expect. Relay modules need their own supply for the load side.

---

## Input + output

| Component             | Does                  | Interface                | Library                    |
| --------------------- | --------------------- | ------------------------ | -------------------------- |
| **Push button**       | momentary switch      | Digital + `INPUT_PULLUP` | none                       |
| **Matrix keypad 4×4** | 16 buttons in 8 pins  | 8 digital                | `Keypad`                   |
| **Remote + IR**       | sends infrared codes  | Digital                  | `IRremote`                 |
| **LCD 16×2 parallel** | text display          | 6 digital                | `LiquidCrystal`            |
| **LCD 16×2 I2C**      | same display, 4 wires | **A4, A5**               | `LiquidCrystal_I2C`        |
| **RFID (RC522)**      | reads a card/tag ID   | **SPI D10–D13, 3.3V**    | `MFRC522`                  |
| **Bluetooth HC-05**   | wireless serial       | 2 digital                | `SoftwareSerial` (bundled) |

### Push button

No resistor needed — `INPUT_PULLUP` is built in, and it **inverts the logic**:

```cpp
const int BUTTON = 2;
void setup(){
  pinMode(BUTTON, INPUT_PULLUP);   // internal pull-up
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop(){
  // Reads LOW when pressed, because the pull-up holds it HIGH otherwise
  digitalWrite(LED_BUILTIN, digitalRead(BUTTON) == LOW ? HIGH : LOW);
}
```

### LCD

**Prefer the I2C version.** Parallel needs 6 pins; I2C needs 2 (A4/A5) plus power,
and has a backlight. "I2C" on the parts list is very likely a separate I2C LCD
module.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // 0x27 or 0x3F - see below

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0); lcd.print("Hello");
  lcd.setCursor(0,1); lcd.print("Arduino UNO");
}
void loop(){}
```

**The 0x27 vs 0x3F gotcha:** I2C LCD clones ship with different addresses
depending on batch. Blank display? Try the other. If two I2C devices are in the
project, addresses must not collide.

**I2C is always A4 (SDA) and A5 (SCL). SPI is always D10–D13.**

### RFID (RC522) — the sharpest trap

It is a **3.3V device** while the UNO speaks 5V. Power from `3.3V` and ideally
level-shift the SPI lines. Direct wiring often works short-range, but
_intermittent_ tag reads mean the hardware, not your code. Confirm your board is
actually RC522 — some kits ship 125 kHz readers, a completely different animal
with no MFRC522 support.

```cpp
#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(10, 9);    // SS = D10, RST = D9

void setup(){
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Place a tag on the reader");
}

void loop(){
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("Tag UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(":");
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1500);
}
```

### HC-05 Bluetooth

A serial port over radio. Uses `SoftwareSerial`, bundled with the board core. The
UNO has only one hardware serial port (used for USB upload and the monitor), so
Bluetooth must be software serial on other pins. TX/RX are 3.3V logic — works
directly at short range, though that's outside spec.

```cpp
#include <SoftwareSerial.h>
SoftwareSerial bt(10, 11);   // HC-05 TX → D10, RX → D11

void setup(){
  Serial.begin(9600);       // USB serial monitor
  bt.begin(9600);           // must match the HC-05 baud
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  if (bt.available()) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if (Serial.available()) bt.write(Serial.read());
}
```

### IR remote

IRremote **4.x** — most tutorials online still show v3 and will not compile:

```cpp
#include <IRremote.hpp>
const int IR_PIN = 2;

void setup(){ Serial.begin(9600); IrReceiver.begin(IR_PIN); }

void loop(){
  if (IrReceiver.decode()) {
    Serial.print("Code: 0x");
    Serial.println(IrReceiver.decodedIRdata, HEX);
    IrReceiver.resume();    // required, or it stops after one code
  }
}
```

Run it with a remote pointed at the receiver and note the hex codes — that number
is the button you later act on.

---

## Wiring rules that prevent 90% of problems

1. **UNO GND to every module's GND.**
2. **Check module voltage.** Most of this kit is 5V; RFID is 3.3V. Read the
   silkscreen, not the wire colour.
3. **Every LED needs a 330Ω in series.** 7-segment needs 7–8.
4. **Motor/servo power from the battery, not the 5V pin, and join the grounds.**
5. **When it doesn't work: power and ground first**, then swap the signal wire,
   then question the code. Wiring is wrong more often than code.
6. **Unplug before rewiring.** Reversing a connector on a live UNO can destroy a pin.
7. **Read the adaptor's label before connecting it.** 12V into the 5V pin destroys
   the board.

---

## The moment you arrive

```bash
# Resolve the port EVERY TIME - never hardcode it.
# Opening the port resets the UNO, which re-enumerates USB and renumbers the device.
PORT=$(arduino-cli board list | awk '/ttyACM|ttyUSB/{print $1; exit}')

ls -l "$PORT"    # expect crw-rw-rw- (0666)
arduino-cli upload -p "$PORT" -b arduino:avr:uno ~/Arduino/Blink
```

If `board list` is empty: try a **different USB cable** first — charge-only cables
are invisible to the computer, and it's the most common cause.

Then keep the serial monitor open all session:

```bash
PORT=$(arduino-cli board list | awk '/ttyACM|ttyUSB/{print $1; exit}')
arduino-cli monitor -p "$PORT" --config 9600
```

Note `--config`, not `-b`. The monitor resets the board and drops the CDC
connection, so the first read returns nothing — run it again.

`Serial.println` output saves enormous amounts of time versus guessing.

---

## Writing code

```bash
hx ~/Arduino/_verified/servo/servo.ino
```

Arduino autocomplete works — `digitalWrite`, `pinMode`, real signatures. Copy an
existing sketch and change pin numbers; faster and safer than starting blank.

```bash
ARDUINO_SKETCH=~/Arduino/MyProject hx ~/Arduino/MyProject/MyProject.ino
```

Left unset, it uses the most recently modified sketch. `:LspRestart` after switching.

Working Keypad and IRremote sketches (correct for the installed versions) are in
`~/Arduino/_verified/keypad/` and `~/Arduino/_verified/ir/`.
