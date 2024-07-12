#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "bitmapheader.h"

Adafruit_MPU6050 mpu;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//#define MPU6050_ADDRESS 0x68  delete this later if not needed
//#define OLED_ADDRESS 0x3C
#define VIBRATION_PIN 5

// Threshold values for detecting poor posture with MPU6050 placed vertically
const float FORWARD_THRESHOLD = -5.0;  
const float BACKWARD_THRESHOLD = 5.0;  
const float LEFT_THRESHOLD = -5.0;     
const float RIGHT_THRESHOLD = 5.0;    

//Setup function 
void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);        // wait for serial port to connect. Needed for native USB

  Wire.begin(21, 22); // SDA pin 21, SCL pin 22

  if (!mpu.begin(MPU6050_ADDRESS, &Wire)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 Found!");
  delay(10);

  u8g2.setBusClock(400000); // Optional: Set I2C bus speed for OLED
  u8g2.begin();
  u8g2.clearBuffer(); // Clearing the display buffer
  u8g2.setFont(u8g2_font_ncenB08_tr); // Font for a message
  u8g2.drawStr(0, 10, "Posture"); // Displaying a message
  u8g2.drawStr(0, 11, "Detection");
  u8g2.drawStr(0, 13, "&");
  u8g2.drawStr(0, 16, "Correction");
  u8g2.drawStr(0, 17, "Device");
  u8g2.sendBuffer(); // Sending the buffer to the display

  // Initialize]ing vibration motor pin
  pinMode(VIBRATION_PIN, OUTPUT);
  digitalWrite(VIBRATION_PIN, LOW);
}

//Loop function
void loop() {
  sensors_event_t a, g;
  mpu.getEvent(&a, &g);

  // Printing acceleration values for debugging
  Serial.print("AccelX: ");
  Serial.print(a.acceleration.x);
  Serial.print(", AccelY: ");
  Serial.print(a.acceleration.y);
  Serial.print(", AccelZ: ");
  Serial.print(a.acceleration.z);
  
   // Check posture with vertical placement
   //Leaning forward
    if (a.acceleration.z < FORWARD_THRESHOLD) {
      u8g2.clearBuffer();
      const int epd_bitmap_allArray_LEN = 1;
      const unsigned char* epd_bitmap_allArray[1] = {
	      epd_bitmap_nck_bnd_spn
      };// function calling for the bitmap
      u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_nck_bnd_spn);
      digitalWrite(VIBRATION_PIN, HIGH);  // Turning on vibration motor
      Serial.println("Leaning Forward");
      u8g2.drawStr(50,40,"Leaning ");
      u8g2.drawStr(50,50, "Forward");
      u8g2.sendBuffer();
    } 
    // Leaning backward
    else if (a.acceleration.z > BACKWARD_THRESHOLD) {
      u8g2.clearBuffer();
      const int epd_bitmap_allArray_LEN = 1;
      const unsigned char* epd_bitmap_allArray[1] = {
	      epd_bitmap_bck_bnd_spn
      };
      u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_bck_bnd_spn);
      digitalWrite(VIBRATION_PIN, HIGH);  // Turning on vibration motor
      Serial.println("Leaning Backward");
      u8g2.drawStr(50,40,"Leaning ");     //Setting the position and printing the message
      u8g2.drawStr(50, 50, "Backward");
      u8g2.sendBuffer();
    } 
    // Leaning left
    else if (a.acceleration.y > RIGHT_THRESHOLD) {
      u8g2.clearBuffer();
      const int epd_bitmap_allArray_LEN = 1;
      const unsigned char* epd_bitmap_allArray[1] = {
	      epd_bitmap_lft_crs_spn
      };
    u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_lft_crs_spn);
    digitalWrite(VIBRATION_PIN, HIGH);  // Turn on vibration motor
    Serial.println("Leaning Left");
    u8g2.drawStr(50,40,"Leaning ");
    u8g2.drawStr(50, 50, "Left");
    u8g2.sendBuffer();
  } 
  // Leaning right
  else if (a.acceleration.y < LEFT_THRESHOLD) {
    u8g2.clearBuffer();
    const int epd_bitmap_allArray_LEN = 1;
    const unsigned char* epd_bitmap_allArray[1] = {
	    epd_bitmap_rght_crs_spn
    };
    u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_rght_crs_spn);
    digitalWrite(VIBRATION_PIN, HIGH);  // Turn on vibration motor
    Serial.println("Leaning Right");
    u8g2.drawStr(65,40,"Leaning");
    u8g2.drawStr(65, 50,"Right");
    u8g2.sendBuffer();
  }
  //Good posture
  else {
    u8g2.clearBuffer(); 
    const int epd_bitmap_allArray_LEN = 1;
    const unsigned char* epd_bitmap_allArray[1] = {
	    epd_bitmap_stght_spn
    };
    digitalWrite(VIBRATION_PIN, LOW); 
    u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_stght_spn);
    Serial.println("Good Posture");
    u8g2.drawStr(60, 40, "Good"); 
    u8g2.drawStr(60, 50, "Posture");
    u8g2.sendBuffer();
  }

  delay(500); // delay of 500 mili second
}
/*void displayMessage(const char *message) {
  u8g2.clearBuffer();          // Clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a suitable font
  u8g2.drawStr(0, 10, message); // Write the message
  u8g2.sendBuffer();           // Transfer internal memory to the display
*/
// above function is node needed it seems delete it by confirming once
