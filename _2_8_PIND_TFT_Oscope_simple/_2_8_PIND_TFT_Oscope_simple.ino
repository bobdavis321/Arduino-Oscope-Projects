/************************************
 2.8 SPI PIND TFT Oscope Simple
 Reads the D0-D7 pins using PIND, 
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
  // D input pins
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop(){
  // wait for a positive going trigger
  for (int timeout=0; timeout < 1000; timeout++){
    Input = PIND;
    if (Input < trigger) break;  }
  for (int timeout=0; timeout < 1000; timeout++){
    Input = PIND;
    if (Input > trigger) break;  }
  // quickly collect the data with no delay
  for (int xpos=0; xpos <320; xpos++){
    Sample[xpos]=PIND;
  }
  // display the collected data
  for (int xpos=0; xpos <319; xpos++){
    // erase the old and draw new line
    tft.drawLine(xpos+1, 0, xpos+1, 240, ILI9341_BLACK);
    tft.drawLine(xpos, (Sample[xpos]*2), xpos+1, Sample[xpos+1]*2, ILI9341_WHITE);
  }
}
// End of program
