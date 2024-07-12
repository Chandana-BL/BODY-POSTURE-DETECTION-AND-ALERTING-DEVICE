# BODY-POSTURE-DETECTION-AND-ALERTING-DEVIC

## Body Posture Detection and Correction Device

This project aims to create a body posture detection and alerting device using an ESP32 microcontroller, 
MPU6050 accelerometer and gyroscope, OLED display, and a vibration motor. The device alerts the user with 
a vibration when poor posture is detected and displays the posture status on the OLED screen using graphics.

## Components Used for the device

- ESP32-WROOM-32
- MPU6050 Accelerometer and Gyroscope
- 1.3" OLED Display
- Vibration Motor
- LiPo Battery
- Resistor (220 Ohms)
- Connecting Wires

## Circuit Diagram

![Circuit Diagram](path/to/circuit-diagram.png)

## Wiring

- **MPU6050**
  - VCC to ESP32 3.3V
  - GND to ESP32 GND
  - SCL to ESP32 GPIO 22
  - SDA to ESP32 GPIO 21

- **OLED Display**
  - VCC to ESP32 3.3V
  - GND to ESP32 GND
  - SCL to ESP32 GPIO 22
  - SDA to ESP32 GPIO 21

- **Vibration Motor**
  - Positive terminal to ESP32 GPIO 4
  - Negative terminal to ESP32 GND
  - Resistor (220 Ohms) in series with the motor

- **LiPo Battery**
  - Positive terminal to ESP32 VIN
  - Negative terminal to ESP32 GND

## Installation for the project

### Prerequisites

- Arduino IDE
- ESP32 Board Package
- Adafruit MPU6050 Library
- u8g2 Library
- Adafruit GFX Library

### Steps

1. Install the ESP32 board package in Arduino IDE.
2. Install the required libraries from the Library Manager.
3. Clone this repository to your local machine.

```sh
git clone https://github.com/yourusername/body-posture-detection.git
cd body-posture-detection
```

4. Open the `body_posture_detection.ino` file in Arduino IDE.
5. Select the correct board and port.
6. Upload the code to the ESP32.

## Code Explanation

### Main Code

```cpp
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int vibrationPin = 16;

void setup() {
  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  
  pinMode(vibrationPin, OUTPUT);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (abs(a.acceleration.x) > 3 || abs(a.acceleration.y) > 3 || abs(a.acceleration.z) < 5) {
    digitalWrite(vibrationPin, HIGH);
    display.println("Poor Posture Detected");
  } else {
    digitalWrite(vibrationPin, LOW);
    display.println("Good Posture");
  }

  display.display();
  delay(500);
}
```

### Explanation

- The `setup` function initializes the MPU6050 and OLED display.
- The `loop` function continuously reads the accelerometer data and checks for poor posture.
- If poor posture is detected, the vibration motor is activated and a message is displayed on the OLED screen.

## Usage

- Power the device with the LiPo battery.
- Attach the device to your body.
- The device will monitor your posture and alert you with a vibration if poor posture is detected.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Adafruit for the MPU6050 and OLED libraries.
- Community contributions for similar projects and ideas.

---

Make sure to replace placeholders like `path/to/circuit-diagram.png` with the actual paths or URLs to your images and files. You can also add more sections if needed, such as troubleshooting tips or advanced configuration options.
