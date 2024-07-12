# BODY-POSTURE-DETECTION-AND-ALERTING-DEVICE

   ##  ![image](https://github.com/user-attachments/assets/a22e43c8-ef94-4bb7-83fc-b7a0e417d2ef)
## Body Posture Detection and Correction Device

This project aims to create a body posture detection and alerting device using an ESP32 microcontroller, 
MPU6050 accelerometer and gyroscope, OLED display, and a vibration motor. The device alerts the user with 
a vibration when poor posture is detected and displays the posture status on the OLED screen using graphics.

## ⚙Components Used for the device

- ESP32-WROOM-32
- MPU6050 Accelerometer and Gyroscope
- 1.3" OLED Display
- Vibration Motor
- LiPo Battery
- Resistor (220 Ohms)
- Connecting Wires

## ⚡Circuit Diagram

[Circuit Diagram](Body-posture-detection-circuit-diagram.png)

## 🔌 Wiring

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

## ⏬ Installation for the project

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
4. Open the `body_posture_detection.ino` file in Arduino IDE.
5. Select the correct board and port.
6. Upload the code to the ESP32.

## © Code Details

### Main Code
[Code File](Body-posture-main-code.ino)

### Header File
[Code File](bitmapheader.h)

### 📝Explanation

- The `setup` function initializes the MPU6050 and OLED display.
- The `loop` function continuously reads the accelerometer data and checks for poor posture.
- If poor posture is detected, the vibration motor is activated and a message is displayed on the OLED screen.

## Usage

- Power the device with the LiPo battery.
- Attach the device to your body.
- The device will monitor your posture and alert you with a vibration if poor posture is detected.

## 🪪License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝Acknowledgments

- Adafruit for the MPU6050 and OLED libraries.
- Community contributions for similar projects and ideas.
- Team members for the dedication and constant involvement.



