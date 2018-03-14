/***********************************
128 by 64 LCD Oscilloscope ext atod speed select
By Bob Davis
Uses Universal 8bit Graphics Library, http://code.google.com/p/u8glib/
  Copyright (c) 2012, olikraus@gmail.com  All rights reserved.

********************************************/
#include "U8glib.h"

// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_128X64_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16); 
// NOTE taht the pins have bee rearranged
U8GLIB_ST7920_128X64_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 1, 2, 3); 

byte Sample[100];
//int Sample[100];
int Input=0;
int OldInput=0;
long StartSample=0;
long EndSample=0;
long SampleTime=0;
int MaxSample=0;
int MinSample=0;
int SampleSize=0;
int dTime=0;
int mode=0;

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void DrawMarkers(void) {
  u8g.drawFrame (0,0,128,64);
  u8g.drawFrame (100,0,128,64);
  u8g.drawPixel (25,16);
  u8g.drawPixel (50,16);
  u8g.drawPixel (75,16);
  u8g.drawPixel (25,32);
  u8g.drawPixel (50,32);
  u8g.drawPixel (75,32);
  u8g.drawPixel (25,48);
  u8g.drawPixel (50,48);
  u8g.drawPixel (75,48);
}

void get_mode(void) {
    if (digitalRead(13) == 0) mode++;
    if (digitalRead(12) == 0) mode--;
    if (mode > 9) mode = 0;
    if (mode < 0) mode = 9;
// Select delay times for loop modes
    if (mode == 0) dTime=0;
    if (mode == 1) dTime=0;
    if (mode == 2) dTime=1;
    if (mode == 3) dTime=5;
    if (mode == 4) dTime=10;
    if (mode == 5) dTime=50;
    if (mode == 6) dTime=100;
    if (mode == 7) dTime=500;
    if (mode == 8) dTime=1000;
    if (mode == 9) dTime=5000;
}

void sample_data(void){
// wait for a trigger of a positive going input
  while (digitalRead(A0)==0) {  }
// collect the analog data into an array

// mode 0 will use verbose method
if (mode == 0) {
  StartSample = micros();
    Sample[0]=PINC;
    Sample[1]=PINC;     Sample[2]=PINC;    Sample[3]=PINC;    
    Sample[4]=PINC;     Sample[5]=PINC;    Sample[6]=PINC;
    Sample[7]=PINC;     Sample[8]=PINC;    Sample[9]=PINC;
    Sample[10]=PINC;    Sample[11]=PINC;    Sample[12]=PINC;
    Sample[13]=PINC;    Sample[14]=PINC;    Sample[15]=PINC;
    Sample[16]=PINC;    Sample[17]=PINC;    Sample[18]=PINC;
    Sample[19]=PINC;    Sample[20]=PINC;    Sample[21]=PINC;
    Sample[22]=PINC;    Sample[23]=PINC;    Sample[24]=PINC;
    Sample[25]=PINC;    Sample[26]=PINC;    Sample[27]=PINC;
    Sample[28]=PINC;    Sample[29]=PINC;    Sample[30]=PINC;
    Sample[31]=PINC;    Sample[32]=PINC;    Sample[33]=PINC;
    Sample[34]=PINC;    Sample[35]=PINC;    Sample[36]=PINC;
    Sample[37]=PINC;    Sample[38]=PINC;    Sample[39]=PINC;
    Sample[40]=PINC;    Sample[41]=PINC;    Sample[42]=PINC;
    Sample[43]=PINC;    Sample[44]=PINC;    Sample[45]=PINC;
    Sample[46]=PINC;    Sample[47]=PINC;    Sample[48]=PINC;
    Sample[49]=PINC;    Sample[50]=PINC;    Sample[51]=PINC;
    Sample[52]=PINC;    Sample[53]=PINC;    Sample[54]=PINC;
    Sample[55]=PINC;    Sample[56]=PINC;    Sample[57]=PINC;
    Sample[58]=PINC;    Sample[59]=PINC;    Sample[60]=PINC;
    Sample[61]=PINC;    Sample[62]=PINC;    Sample[63]=PINC;
    Sample[64]=PINC;    Sample[65]=PINC;    Sample[66]=PINC;
    Sample[67]=PINC;    Sample[68]=PINC;    Sample[69]=PINC;
    Sample[70]=PINC;    Sample[71]=PINC;    Sample[72]=PINC;
    Sample[73]=PINC;    Sample[74]=PINC;    Sample[75]=PINC;
    Sample[76]=PINC;    Sample[77]=PINC;    Sample[78]=PINC;
    Sample[79]=PINC;    Sample[80]=PINC;    Sample[81]=PINC;
    Sample[82]=PINC;    Sample[83]=PINC;    Sample[84]=PINC;
    Sample[85]=PINC;    Sample[86]=PINC;    Sample[87]=PINC;
    Sample[88]=PINC;    Sample[89]=PINC;    Sample[90]=PINC;
    Sample[91]=PINC;    Sample[92]=PINC;    Sample[93]=PINC;
    Sample[94]=PINC;    Sample[95]=PINC;    Sample[96]=PINC;
    Sample[97]=PINC;    Sample[98]=PINC;    Sample[99]=PINC;
//    Sample[100]=PINC;
  EndSample = micros();
}  

// mode 1 will use loop with no delay
if (mode ==1) {
  StartSample = micros();
  for(int xpos=0; xpos<100; xpos++) {
    Sample[xpos]=PINC;
//    delayMicroseconds(dTime);
  } 
  EndSample = micros();
}  

// mode 2 or more will use loop with delay
if (mode >= 2) {
  StartSample = micros();
  for(int xpos=0; xpos<100; xpos++) {
    Sample[xpos]=PINC;
    delayMicroseconds(dTime);
  } 
  EndSample = micros();
}  }

void draw(void) {
  char buf[12];
  u8g_prepare();
  DrawMarkers(); 
// display the collected analog data from array
  for(int xpos=1; xpos<99; xpos++) {
//  For Oscope more use this line
    u8g.drawLine (xpos, Sample[xpos], xpos+1, Sample[xpos+1]);
//  For logic analizer use the next 6 lines instead    
//    u8g.drawLine (xpos, ((Sample[xpos]&B00000001)*4)+4, xpos, ((Sample[xpos+1]&B00000001)*4)+4);
//    u8g.drawLine (xpos, ((Sample[xpos]&B00000010)*2)+14, xpos, ((Sample[xpos+1]&B00000010)*2)+14);
//    u8g.drawLine (xpos, ((Sample[xpos]&B00000100)*1)+24, xpos, ((Sample[xpos+1]&B00000100)*1)+24);
//    u8g.drawLine (xpos, ((Sample[xpos]&B00001000)/2)+34, xpos, ((Sample[xpos+1]&B00001000)/2)+34);
//    u8g.drawLine (xpos, ((Sample[xpos]&B00010000)/4)+44, xpos, ((Sample[xpos+1]&B00010000)/4)+44);
//    u8g.drawLine (xpos, ((Sample[xpos]&B00100000)/8)+54, xpos, ((Sample[xpos+1]&B00100000)/8)+54);

  }  
  SampleTime=EndSample-StartSample;
  if (SampleTime < 9999) u8g.drawStr(102, 2, "uS");
  if (SampleTime > 9999) {
    SampleTime=SampleTime/1000;
    u8g.drawStr(102, 2, "mS");
  }
  u8g.drawStr(102, 12, itoa(SampleTime, buf, 10));
  u8g.drawStr(102, 22, "Mode");
  u8g.drawStr(102, 32, itoa(mode, buf, 10));
//  Determine sample voltage peak to peak
  MaxSample = Sample[10];
  MinSample = Sample[10];
  for(int xpos=0; xpos<100; xpos++) {
//    OldSample[xpos] = Sample[xpos];  
    if (Sample[xpos] > MaxSample) MaxSample=Sample[xpos];
    if (Sample[xpos] < MinSample) MinSample=Sample[xpos];
    }  
  // Range of 0 to 64 * 78 = 4992 mV
  SampleSize=(MaxSample-MinSample)*78;
  u8g.drawStr(102, 42, "mV");
  u8g.drawStr(102, 52, itoa(SampleSize, buf, 10));
}

void setup(void) {
  // set up input pins
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // RGB=white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    u8g.setColorIndex(3);       // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    u8g.setColorIndex(1);       // pixel on, black
}

void loop(void) {
// Set up the mode
  get_mode();
// collect the data
  sample_data();
// show collected data 
  u8g.firstPage();  
  do { draw(); }  
  while( u8g.nextPage() );
// rebuild the picture after some delay
  delay(500);
}


