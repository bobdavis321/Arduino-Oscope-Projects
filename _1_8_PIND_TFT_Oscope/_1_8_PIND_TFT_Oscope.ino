/************************************
 1.8 SPI PIND TFT Oscope
 Reads the analog pins using PIND, 
 and shows the value on the screen.
 Created 7 july 2015 by Bob Davis
**************************************/

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
 
 // pin definition for the Uno
#define rst  8  
#define dc   9
#define cs   10
TFT TFTscreen = TFT(cs, dc, rst);

// set up variables
//int xPos = 0;
//int value = 0;
char buf[12];
int Input=0;
byte Sample[160];
int StartSTime=0;
int EndSTime=0;
float SampleTime=0;
int trigger;
int tdelay;
int volts;

void setup(){
  // initialize the display
  TFTscreen.begin();
  // clear the screen 
  TFTscreen.background(0, 0, 0); 
  // Set the font size
  TFTscreen.setTextSize(2);
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
// wait for trigger of a positive input
  while (Input == 0){
    Input = PIND;
    }
// quickly collect the data
  StartSTime = micros();
    Sample[0]=PIND;
    Sample[1]=PIND;     Sample[2]=PIND;    Sample[3]=PIND;    
    Sample[4]=PIND;     Sample[5]=PIND;    Sample[6]=PIND;
    Sample[7]=PIND;     Sample[8]=PIND;    Sample[9]=PIND;
    Sample[10]=PIND;    Sample[11]=PIND;    Sample[12]=PIND;
    Sample[13]=PIND;    Sample[14]=PIND;    Sample[15]=PIND;
    Sample[16]=PIND;    Sample[17]=PIND;    Sample[18]=PIND;
    Sample[19]=PIND;    Sample[20]=PIND;    Sample[21]=PIND;
    Sample[22]=PIND;    Sample[23]=PIND;    Sample[24]=PIND;
    Sample[25]=PIND;    Sample[26]=PIND;    Sample[27]=PIND;
    Sample[28]=PIND;    Sample[29]=PIND;    Sample[30]=PIND;
    Sample[31]=PIND;    Sample[32]=PIND;    Sample[33]=PIND;
    Sample[34]=PIND;    Sample[35]=PIND;    Sample[36]=PIND;
    Sample[37]=PIND;    Sample[38]=PIND;    Sample[39]=PIND;
    Sample[40]=PIND;    Sample[41]=PIND;    Sample[42]=PIND;
    Sample[43]=PIND;    Sample[44]=PIND;    Sample[45]=PIND;
    Sample[46]=PIND;    Sample[47]=PIND;    Sample[48]=PIND;
    Sample[49]=PIND;    Sample[50]=PIND;    Sample[51]=PIND;
    Sample[52]=PIND;    Sample[53]=PIND;    Sample[54]=PIND;
    Sample[55]=PIND;    Sample[56]=PIND;    Sample[57]=PIND;
    Sample[58]=PIND;    Sample[59]=PIND;    Sample[60]=PIND;
    Sample[61]=PIND;    Sample[62]=PIND;    Sample[63]=PIND;
    Sample[64]=PIND;    Sample[65]=PIND;    Sample[66]=PIND;
    Sample[67]=PIND;    Sample[68]=PIND;    Sample[69]=PIND;
    Sample[70]=PIND;    Sample[71]=PIND;    Sample[72]=PIND;
    Sample[73]=PIND;    Sample[74]=PIND;    Sample[75]=PIND;
    Sample[76]=PIND;    Sample[77]=PIND;    Sample[78]=PIND;
    Sample[79]=PIND;    Sample[80]=PIND;    Sample[81]=PIND;
    Sample[82]=PIND;    Sample[83]=PIND;    Sample[84]=PIND;
    Sample[85]=PIND;    Sample[86]=PIND;    Sample[87]=PIND;
    Sample[88]=PIND;    Sample[89]=PIND;    Sample[90]=PIND;
    Sample[91]=PIND;    Sample[92]=PIND;    Sample[93]=PIND;
    Sample[94]=PIND;    Sample[95]=PIND;    Sample[96]=PIND;
    Sample[97]=PIND;    Sample[98]=PIND;    Sample[99]=PIND;
    Sample[100]=PIND;    Sample[101]=PIND;    Sample[102]=PIND;
    Sample[103]=PIND;    Sample[104]=PIND;    Sample[105]=PIND;
    Sample[106]=PIND;    Sample[107]=PIND;    Sample[108]=PIND;
    Sample[109]=PIND;    Sample[110]=PIND;    Sample[111]=PIND;
    Sample[112]=PIND;    Sample[113]=PIND;    Sample[114]=PIND;
    Sample[115]=PIND;    Sample[116]=PIND;    Sample[117]=PIND;
    Sample[118]=PIND;    Sample[119]=PIND;    Sample[120]=PIND;
    Sample[121]=PIND;    Sample[122]=PIND;    Sample[123]=PIND;
    Sample[124]=PIND;    Sample[125]=PIND;    Sample[126]=PIND;
    Sample[127]=PIND;    Sample[128]=PIND;    Sample[129]=PIND;
    Sample[130]=PIND;    Sample[131]=PIND;    Sample[132]=PIND;
    Sample[133]=PIND;    Sample[134]=PIND;    Sample[135]=PIND;
    Sample[136]=PIND;    Sample[137]=PIND;    Sample[138]=PIND;
    Sample[139]=PIND;    Sample[140]=PIND;    Sample[141]=PIND;
    Sample[142]=PIND;    Sample[143]=PIND;    Sample[144]=PIND;
    Sample[145]=PIND;    Sample[146]=PIND;    Sample[147]=PIND;
    Sample[148]=PIND;    Sample[149]=PIND;    Sample[150]=PIND;
    Sample[151]=PIND;    Sample[152]=PIND;    Sample[153]=PIND;
    Sample[154]=PIND;    Sample[155]=PIND;    Sample[156]=PIND;
    Sample[157]=PIND;    Sample[158]=PIND;    Sample[159]=PIND;

  EndSTime = micros();
  SampleTime = EndSTime - StartSTime;
  // display the collected data
  for (int xpos = 0; xpos <159; xpos++){
  // select the color black = B,G,R
  TFTscreen.stroke(0, 0, 0);
  // erase old line
  TFTscreen.line(xpos+1, 0, xpos+1, 160);
  // select the color white = B,G,R
  TFTscreen.stroke(250, 250, 255);
  // draw the line (xPos1, yPos1, xPos2, yPos2);0
  TFTscreen.line(xpos, Sample[xpos], xpos+1, Sample[xpos+1]);
  // Set font color to green
  TFTscreen.stroke(0, 255, 0);
  // draw the lines
  TFTscreen.line(xpos, 0, xpos+1, 0);
  TFTscreen.line(xpos, 32, xpos+1, 32);
  TFTscreen.line(xpos, 64, xpos+1, 64);
  TFTscreen.line(xpos, 96, xpos+1, 96);
  TFTscreen.line(xpos, 127, xpos+1, 127);
  if (xpos==0) TFTscreen.line(xpos, 0, xpos,160);
  if (xpos==40) TFTscreen.line(xpos, 0, xpos,160);
  if (xpos==80) TFTscreen.line(xpos, 0, xpos,160);
  if (xpos==120) TFTscreen.line(xpos, 0, xpos,160);

  // Set font color to bright blue
  TFTscreen.stroke(255, 100, 100);
  // Write the text values
  if (xpos==0) TFTscreen.text( "Trg", 125, 3);
  if (xpos==0) TFTscreen.text( itoa(trigger, buf, 10), 125, 18);
  if (xpos==0) TFTscreen.text( "Del", 125, 35);
  if (xpos==0) TFTscreen.text( itoa(tdelay, buf, 10), 125, 50);
  if (xpos==0) TFTscreen.text( "MV", 125, 67);
  if (xpos==0) TFTscreen.text( itoa(volts, buf, 10), 125, 82);
  if (xpos==0) TFTscreen.text( "MS", 125, 98);
  if (xpos==0) TFTscreen.text( itoa(SampleTime, buf, 10), 125, 113);
  }
}

