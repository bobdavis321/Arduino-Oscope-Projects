// 1.8 SPI TFT Quick Oscope
// Reads & Displays the value of analog input on A0 
// Created 15 January 2015 by Bob Davis

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
// pin definitions for the Uno
#define rst  8  
#define dc   9
#define cs   10
TFT TFTscreen = TFT(cs, dc, rst);
// set up variables
int Input=0;
byte Sample[160];
void setup(){
  // initialize the display
  TFTscreen.begin();
  }
void loop(){
  // quickly collect the data
  for (int xpos = 0; xpos <160; xpos++){
    Sample[xpos] = analogRead(A0)/8;
  }
  // erase the screen to start again
  TFTscreen.background(0, 0, 0); 
  // select the color white = B,G,R
  TFTscreen.stroke(250, 250, 250);
  // display the collected data
  for (int xpos = 0; xpos <159; xpos++){
    // draw the line (xPos1, yPos1, xPos2, yPos2);
    TFTscreen.line(xpos, Sample[xpos], xpos+1, Sample[xpos+1]);
  }
}

