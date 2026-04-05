// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>         // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"
// OR #include "SH1106Wire.h"   // legacy: #include "SH1106.h"

#include "pins_arduino.h"


// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED);  // ADDRESS, SDA, SCL  -  SDA_OLED and SCL_OLED are the pins from pins_arduino.h where the Heltec connects the OLED display

/******************
 * VextOn and VextOff are
 * take right from Heltec.cpp.
 * These functions turn power 
 * to the diplay on and off.
 *
 * displayReset() is from 
 * HT_Display.cpp in the Heltec
 * code.  It resets the display
 *****************/
void VextON(void) {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void)  //Vext default OFF
{
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);
}

void displayReset(void) {
  // Send a reset
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
  digitalWrite(RST_OLED, LOW);
  delay(1);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
}

void displaysetup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println();
  Serial.println();

  // This turns on and resets the OLED on the Heltec boards
  VextON();
  displayReset();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}


void displayloop() {
  // clear the display
  display.clear();
  display.setFont(ArialMT_Plain_24);
 // display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(15, 0, "PD7BOR");
   display.setFont(ArialMT_Plain_16); 
  display.drawString(20, 30, "Burst Control");
  // write the buffer to the display
  display.display();

  delay(10);
}

void burst() {
  // clear the display
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 20, " >BURST<");
  delay(500);
  display.display();
  delay(2000);
  displayloop();
}
