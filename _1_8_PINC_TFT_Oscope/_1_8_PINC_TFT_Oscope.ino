/************************************
 1.8 SPI PINC TFT Oscope
 Reads the analog pins using PINC, 
 and shows the value on the screen.
 Created 15 January 2014 by Bob Davis
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
 
void setup(){
  // initialize the display
  TFTscreen.begin();
  // clear the screen 
  TFTscreen.background(0, 0, 0); 
  // Set the font size
  TFTscreen.setTextSize(2);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
}

void loop(){
// wait for trigger of a positive input
  while (Input == 0){
    Input = digitalRead(A1);
    }
// quickly collect the data
  StartSTime = micros();
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
    Sample[100]=PINC;    Sample[101]=PINC;    Sample[102]=PINC;
    Sample[103]=PINC;    Sample[104]=PINC;    Sample[105]=PINC;
    Sample[106]=PINC;    Sample[107]=PINC;    Sample[108]=PINC;
    Sample[109]=PINC;    Sample[110]=PINC;    Sample[111]=PINC;
    Sample[112]=PINC;    Sample[113]=PINC;    Sample[114]=PINC;
    Sample[115]=PINC;    Sample[116]=PINC;    Sample[117]=PINC;
    Sample[118]=PINC;    Sample[119]=PINC;    Sample[120]=PINC;
    Sample[121]=PINC;    Sample[122]=PINC;    Sample[123]=PINC;
    Sample[124]=PINC;    Sample[125]=PINC;    Sample[126]=PINC;
    Sample[127]=PINC;    Sample[128]=PINC;    Sample[129]=PINC;
    Sample[130]=PINC;    Sample[131]=PINC;    Sample[132]=PINC;
    Sample[133]=PINC;    Sample[134]=PINC;    Sample[135]=PINC;
    Sample[136]=PINC;    Sample[137]=PINC;    Sample[138]=PINC;
    Sample[139]=PINC;    Sample[140]=PINC;    Sample[141]=PINC;
    Sample[142]=PINC;    Sample[143]=PINC;    Sample[144]=PINC;
    Sample[145]=PINC;    Sample[146]=PINC;    Sample[147]=PINC;
    Sample[148]=PINC;    Sample[149]=PINC;    Sample[150]=PINC;
    Sample[151]=PINC;    Sample[152]=PINC;    Sample[153]=PINC;
    Sample[154]=PINC;    Sample[155]=PINC;    Sample[156]=PINC;
    Sample[157]=PINC;    Sample[158]=PINC;    Sample[159]=PINC;

  EndSTime = micros();
  // erase the screen to start again
  TFTscreen.background(0, 0, 0); 
  // display the collected data
  for (int xpos = 0; xpos <159; xpos++){
  // select the color = B,G,R
  TFTscreen.stroke(250, 250, 255);
  // draw the line (xPos1, yPos1, xPos2, yPos2);
  TFTscreen.line(xpos, Sample[xpos]*2, xpos+1, Sample[xpos+1]*2);
  // Set font color to green
  TFTscreen.stroke(0, 255, 0);
  // Write the text value of the sensor
  SampleTime = EndSTime - StartSTime;
  if (xpos==0) TFTscreen.text( itoa(SampleTime, buf, 10), 10, 110);
  if (xpos==0) TFTscreen.text( "ms", 50, 110);
  }
}

