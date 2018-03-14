/************************************
 2.8 SPI A0 TFT Oscope Simple
 Reads the A0 analog input, 
 and shows the value on the screen.
 Created 27 july 2015 by Bob Davis
**************************************/
//#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"

// pin definition for the Uno LCD
#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13=clk, #11=mosi) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ILI9341 tft = Adafruit_ILI9341();

//// set up variables
int Input=0;
byte Sample[320];
int trigger=64;

void setup(){
  // initialize rotate and clear the display
  tft.begin();
  tft.fillScreen(ILI9341_BLACK); 
  tft.setRotation(1);
  // Set the font size
  tft.setTextSize(2);
}

void loop(){
  // Clear bit 2 of ADC pre-scalier from 125KHz to 2 MHz
  ADCSRA &= ~(1 << ADPS2);
  // wait for a positive going trigger
  for (int timeout=0; timeout < 1000; timeout++){
    Input = analogRead(A0);
    if (Input < trigger) break;  }
  for (int timeout=0; timeout < 1000; timeout++){
    Input = analogRead(A0);
    if (Input > trigger) break;  }
  // quickly collect the data with no delay
  for (int xpos=0; xpos <320; xpos++){
    Sample[xpos]=analogRead(A0);
  }
  // display the collected data
  for (int xpos=0; xpos <319; xpos++){
    // erase the old and draw new line
    tft.drawLine(xpos+1, 0, xpos+1, 240, ILI9341_BLACK);
    tft.drawLine(xpos, (Sample[xpos]*2), xpos+1, Sample[xpos+1]*2, ILI9341_WHITE);
  }
}
// End of program
