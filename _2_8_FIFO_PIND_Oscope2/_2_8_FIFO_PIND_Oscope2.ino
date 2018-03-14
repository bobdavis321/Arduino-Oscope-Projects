/************************************
 2.8 SPI FIFO PIND Oscope
 Reads the D0-D7 pins using PIND, 
 and shows the value on the screen.
 Created 10 july 2015 by Bob Davis
**************************************/
//#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"

// pin definition for the Uno LCD
#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13=clk, #12=nc, #11=mosi) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ILI9341 tft = Adafruit_ILI9341();

// set up variables
int xPos = 0;
char buf[12];
int Input=0;
byte Sample[240];
int StartSTime=0;
int EndSTime=0;
float SampleTime=0;
int trigger=64;
int trigphase=1;
int tdelay=0;
int volts;
int select=0;
int gain=0;

void setup(){
  // initialize the display
  tft.begin();
  // rotate and clear the screen 
  tft.fillScreen(ILI9341_BLACK); 
  tft.setRotation(1);
  // Set the font size
  tft.setTextSize(2);
  // A to D input pins
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  // FIFO pins and push button switches
  pinMode(8, OUTPUT);  //Next
  pinMode(17, OUTPUT); //Reset
  pinMode(14, OUTPUT); //Clock Sel
  pinMode(15, OUTPUT); //Clock Sel
  pinMode(16, OUTPUT); //Clock Sel
//  pinMode(17, INPUT_PULLUP); //Switch
  pinMode(18, INPUT_PULLUP); //Switch
  pinMode(19, INPUT_PULLUP); //Switch
}

void loop(){
  // Reset the FIFO
  digitalWrite(17,LOW);
  digitalWrite(17,HIGH);
  // No available pin to see if FIFO is full?
  // Collect the data while toggleing next
  for (int xpos=0; xpos <240; xpos++){
    Sample[xpos]=PIND;
    digitalWrite(8,LOW);
    digitalWrite(8,HIGH);
  }
  // display the collected data
  for (int xpos = 0; xpos <320; xpos++){
    // erase the old line
    tft.drawLine(xpos+1, 0, xpos+1, 240, ILI9341_BLACK);
    // draw the trace line (xPos1, yPos1, xPos2, yPos2, color);
    if (xpos<240)tft.drawLine(xpos, (Sample[xpos]*2), xpos+1, Sample[xpos+1]*2, ILI9341_WHITE);
    // draw the green lines
    tft.drawLine(xpos, 0, xpos+1, 0, ILI9341_GREEN);
    tft.drawLine(xpos, 60, xpos+1, 60, ILI9341_GREEN);
    tft.drawLine(xpos, 120, xpos+1, 120, ILI9341_GREEN);
    tft.drawLine(xpos, 180, xpos+1, 180, ILI9341_GREEN);
    tft.drawLine(xpos, 239, xpos+1, 239, ILI9341_GREEN);
    // draw top to bottom green lines
    if (xpos==0) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==60) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==120) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==180) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==240) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
  }
  // Update the text on the right side
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 1) tft.setTextColor(ILI9341_RED);
  tft.setCursor(242, 10);
  tft.println( "Triger");
  tft.setCursor(242, 30);
  tft.println( itoa(trigger, buf, 10));
  // if selected set font color to red
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 2) tft.setTextColor(ILI9341_RED);
  tft.setCursor(242, 70);
  tft.println( "Phase");
  tft.setCursor(242, 90);
  tft.println( itoa(trigphase, buf, 10));
  // if selected set color to red
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 3) tft.setTextColor(ILI9341_RED);
  tft.setCursor(242, 130);
  tft.println( "Delay");
  tft.setCursor(242, 150);
  tft.println( itoa(tdelay, buf, 10));
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 4) tft.setTextColor(ILI9341_RED);
  tft.setCursor(242, 190);
  tft.println( "TimeMs");
  tft.setCursor(242, 210);
  tft.println( itoa(SampleTime, buf, 10));
  // check the status of push button switches
  if (digitalRead(17) == 0) select++;
  if (digitalRead(16) == 0) select--;
  if (select > 4) select=4;
  if (select==0) select=1;
  // update the trigger level
  if (select==1){
    if (digitalRead(18)==0) trigger++;
    if (digitalRead(19)==0) trigger--;
    if (trigger > 128) trigger=128;
    if (trigger < 1) trigger=1;
  }
  // change the trigger phase
  if (select==2){
    if (digitalRead(18)==0) trigphase=1;
    if (digitalRead(19)==0) trigphase=0;
  }
  // Change the amount of delay
  if (select==3){
    if (digitalRead(18)==0) tdelay++;
    if (digitalRead(19)==0) tdelay--;
    if (tdelay > 128) tdelay=128;
    if (tdelay < 0) tdelay=0;
  }
  // Change the amount of gain
  if (select==3){
    if (digitalRead(18)==0) gain++;
    if (digitalRead(19)==0) gain--;
    if (gain > 2) gain=2;;
    if (gain < 0) gain=0;
  }
}
// End of program
