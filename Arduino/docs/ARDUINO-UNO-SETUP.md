# Arduino UNO Development Setup on CachyOS

Companion to `KIT-COMPONENTS.md`. Built around `arduino-cli` (the official CLI)
with editor support in **Helix** and the **official Arduino IDE 2**.

Verified working on this machine.

---

## Status

| Check           | Result                                                               |
| --------------- | -------------------------------------------------------------------- |
| Board detection | Arduino UNO R3, `2341:0043`, auto-identified as `arduino:avr:uno`    |
| udev rule       | ✅ `/dev/ttyACM0` at `0666` — the `[08][023]*` glob matched          |
| Toolchain       | `arduino-cli` 1.5.1, AVR core installed, 381 MB in `~/.arduino15`    |
| Libraries       | 10 pre-installed, all compile-tested                                 |
| Compile         | 2266 bytes (7%) flash, 252 bytes (12%) RAM for the diagnostic sketch |
| Flash + execute | ✅ LED blinking on D13                                               |
| Serial          | ✅ `=== DIAG START ===` / `LED D13 = HIGH`                           |
| Helix LSP       | ✅ `.ino` highlighted, Arduino autocomplete                          |

---

## 1. Packages

```bash
sudo pacman -S arduino-cli arduino-language-server arduino-fwuploader
```

All three are in `cachyos-extra-v3` — no AUR, no building. `clangd` is already
installed at `/usr/bin/clangd`.

## 2. USB permissions

The Arch `arduino-cli` package ships **zero** udev rules, and this account is not
in the `dialout` group. Without these rules every upload fails.

| Vendor  | ID          | Chip                    | Typical port   |
| ------- | ----------- | ----------------------- | -------------- |
| Arduino | `2341:0043` | ATmega16U2 (official)   | `/dev/ttyACM0` |
| WCH     | `1a86:7523` | CH340 (**most clones**) | `/dev/ttyUSB0` |
| FTDI    | `0403:6001` | FT232R                  | `/dev/ttyUSB0` |

```bash
sudo tee /etc/udev/rules.d/99-arduino.rules > /dev/null << 'EOF'
SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="[08][023]*", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1", ENV{ID_MM_PORT_IGNORE}="1"
SUBSYSTEM=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1", ENV{ID_MM_PORT_IGNORE}="1"
SUBSYSTEM=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d3", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1", ENV{ID_MM_PORT_IGNORE}="1"
SUBSYSTEM=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d4", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1", ENV{ID_MM_PORT_IGNORE}="1"
SUBSYSTEM=="usb", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="60[01][104]", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1", ENV{ID_MM_PORT_IGNORE}="1"
EOF
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Then replug the board. **Verified:** your board came up `crw-rw-rw-`.

## 3. CLI setup

```bash
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
```

The Arch package ships only the binary with no bundled index, so `update-index`
downloads from `downloads.arduino.cc` on first run. That takes a minute — it is
not a hang.

## 4. Always resolve the port

**Never hardcode `/dev/ttyACM0`.** The UNO's auto-reset toggles DTR when any
program opens the serial port, which resets the ATmega16U2 and forces USB
re-enumeration. The device renumbers itself — `ttyACM0` became `ttyACM1` after the
first upload. A hardcoded port works once, then fails in a way that looks like a
dead board.

```bash
PORT=$(arduino-cli board list | awk '/ttyACM|ttyUSB/{print $1; exit}')
```

## 5. Command cheat sheet

```bash
# Board
arduino-cli board list
arduino-cli board listall | grep -i uno

# Libraries (all installed offline already)
arduino-cli lib list
arduino-cli lib search "dht"
arduino-cli lib install "Servo"

# Compile / flash — always via $PORT
arduino-cli compile -b arduino:avr:uno ~/Arduino/MyProject
arduino-cli upload  -p "$PORT" -b arduino:avr:uno ~/Arduino/MyProject
arduino-cli compile --upload -p "$PORT" -b arduino:avr:uno ~/Arduino/MyProject

# Serial — note: --config, NOT -b
arduino-cli monitor -p "$PORT" --config 9600
```

### arduino-cli 1.x gotchas

- **Baud rate moved to `--config`.** `-b` is now the FQBN. The old
  `monitor -b 9600` fails with `Invalid FQBN: not a FQBN: 9600`.
- **The monitor resets the board and drops the CDC connection**, so the first read
  returns nothing. Run it again against a freshly resolved port — it works on the
  second attempt.
- **Sketch folder name must match the `.ino` name.** `dht/dht.ino` works;
  `dht/t_dht.ino` fails.

## 6. Libraries installed

`DHT sensor library`, `Adafruit Unified Sensor`, `Servo`, `LiquidCrystal`,
`LiquidCrystal_I2C`, `Keypad`, `IRremote`, `MFRC522`, `NewPing`,
`Adafruit NeoPixel` — all in `~/Arduino/libraries/`.

A sketch using all six tested libraries compiles to 17.4 KB flash (53%) and 973 B
RAM (47%). **RAM is the tighter limit.**

### Two version traps

**Keypad 3.1.1 uses the old API.** The templated form in every tutorial is 4.x
and will not compile:

```cpp
// WRONG (4.x syntax)
Keypad keypad(KEYPAD4x4, rowPins, colPins, keys);

// RIGHT for 3.1.1
char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},
                   {'7','8','9','C'},{'*','0','#','D'}};
const byte rowPins[4] = {2, 3, 4, 5};
const byte colPins[4] = {6, 7, 8, 9};
Keypad keypad(makeKeymap(keys), (byte*)rowPins, (byte*)colPins, 4, 4);
```

**IRremote 4.x renamed the entry points.** `irrecv()` / `decode_results` are v3:

```cpp
IrReceiver.begin(pin);
if (IrReceiver.decode()) { IrReceiver.decodedIRdata; IrReceiver.resume(); }
```

## 7. Helix

Three pieces:

**`~/.local/bin/arduino-lsp`** — an LSP proxy. `arduino-language-server` line 184
does `ideParams.RootURI.AsPath()` with no nil check; an empty `rootUri` returns nil
and segfaults. Arduino IDE 2 always sends one, Helix never does. The bug is still
present on upstream `main`. The proxy injects `rootUri` from `$ARDUINO_SKETCH`,
falling back to the most recently modified sketch in `~/Arduino`.

**`~/.config/helix/runtime/queries/arduino`** → symlink to
`/usr/lib/helix/runtime/queries/cpp`. `.ino` is C++, so it gets identical
highlighting.

**`languages.toml`** — a separate entry, leaving your existing `cpp` block
untouched:

```toml
[language-server.arduino]
command = "arduino-lsp"

[[language]]
name = "arduino"
scope = "source.cpp"
injection-regex = "arduino"
grammar = "cpp"
file-types = ["ino"]
language-servers = ["arduino"]
comment-token = "//"
block-comment-tokens = { start = "/*", end = "*/" }
indent = { tab-width = 2, unit = "  " }
```

Usage — plain `hx` picks the newest sketch; override when you have two open:

```bash
ARDUINO_SKETCH=~/Arduino/MyProject hx ~/Arduino/MyProject/MyProject.ino
```

After switching sketches: `:LspRestart`.

### Why a separate language entry

A language needs both a parser _and_ query files, both resolved by **language
name**. Naming it `arduino` without the symlink means `queries/arduino/` doesn't
exist and you get no highlighting — `grammar = "cpp"` alone is not enough, because
it only fixes the parser.

## 8. VS Code

Arduino publishes no standalone LSP extension. Use the generic client:

```bash
code --install-extension llllvvuu.llllvvuu-glspc
```

```json
{
  "files.associations": { "*.ino": "cpp" },
  "glspc.languageId": "cpp",
  "glspc.serverCommand": "arduino-lsp"
}
```

That extension registers exactly one server, so it conflicts with `clangd` for
ordinary C++. Prefer Helix, which handles both separately.

## 9. Arduino IDE 2 (optional GUI)

```bash
paru -S arduino-ide-bin libusb python-pyserial
```

`libusb` and `python-pyserial` are optdepends that make upload more reliable. It
reads the same `~/.arduino15` and `~/Arduino`, so every library and core installed
via the CLI is already present.

## 10. Troubleshooting

| Symptom                           | Cause                            | Fix                                    |
| --------------------------------- | -------------------------------- | -------------------------------------- |
| `Invalid FQBN: not a FQBN: 9600`  | old `monitor` syntax             | use `--config 9600`                    |
| Port disappeared after upload     | UNO auto-reset re-enumerates USB | re-resolve `$PORT`                     |
| Monitor shows nothing first time  | reset dropped the CDC connection | run it again                           |
| `error opening port /dev/ttyUSB0` | udev rules missing               | replug; re-run `udevadm trigger`       |
| Board not in `board list`         | charge-only cable, or bad port   | try a different cable first            |
| `avrdude: stk500_recv()`          | wrong port, or no auto-reset     | re-check `$PORT`; press RESET          |
| `board not found` on compile      | missing core                     | `arduino-cli core install arduino:avr` |
| Sketch folder "not found"         | folder name ≠ `.ino` name        | rename to match                        |
