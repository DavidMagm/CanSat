# AGENTS.md

CanSat telemetry firmware: 4 independent Arduino `.ino` sketches. No build system, tests, or CI — each file is compiled/flashed separately via the Arduino IDE or `arduino-cli`.

## Critical: sketch folder rule
The Arduino toolchain requires each sketch to be inside a folder with the **exact same name**. As laid out flat here, `arduino-cli compile` fails. To build, copy each file into its own dir first, e.g. `mkdir 1_Lora_ESP32 && cp 1_Lora_ESP32.ino 1_Lora_ESP32/`.

## Sketches
- `1_Barometro_calibracion_AHT20BMP280.ino` — AHT20 (humidity/temp, `0x38`) + BMP280 (pressure/altitude, `0x76` then `0x77`). Uses `Adafruit_AHTX0` + `Adafruit_BMP280` (+ `Adafruit Unified Sensor`). Calibrates ground pressure over 20 samples in `setup()` (stored in hPa for `readAltitude`); sensor must be stationary on ground during the 3s+delay before calibration.
- `1_Medidas_sin_procesar.ino` — MPU6050 raw accel (needs `I2Cdev` + `MPU6050` libs). Address `0x68` (AD0->GND) or `0x69` (AD0->3.3V).
- `1_Lora_ESP32.ino` — LoRa transmitter.
- `2_Lora_Arduino_uno.ino` — LoRa receiver, prints RSSI.

## Hardware gotchas (ESP32 vs Uno)
- ESP32 I2C is forced to `Wire.begin(21, 22)` (SDA=21, SCL=22); MPU6050 also sets 400kHz clock.
- LoRa pins differ by board: ESP32 `NSS=5,RST=14,DIO0=2`; Uno `NSS=10,RST=9,DIO0=2`.
- LoRa frequency is hardcoded `433E6`; change for 868/915 modules.
- ESP32 serial is `115200`; Uno LoRa is `9600`.
- ESP32 needs `delay()` in setup to avoid brownout on power-up.

## Conventions
- Code comments and Serial output are in **Spanish**. Keep that when editing.
- No shared headers — each sketch is self-contained; changing pin defs means editing each file.
