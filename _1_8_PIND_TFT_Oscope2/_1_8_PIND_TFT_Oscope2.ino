/************************************
 1.8 SPI PIND TFT Oscope
 Reads the D0-D7 pins using PIND, 
 and shows the value on the screen.
 Created 7 july 2015 by Bob Davis
 Updated August 20 2015 gain in software
**************************************/
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
 
// pin definition for the Uno LCD
#define rst  8  
#define dc   9
#define cs   10
TFT TFTscreen = TFT(cs, dc, rst);

// set up variables
int xPos = 0;
char buf[12];
int Input=0;
byte Sample[160];
int StartSTime=0;
int EndSTime=0;
int STime=0;
int trigger=64;
int trigphase=1;
int tdelay=1;
int select=1;
int gain=1;

void setup(){
  // initialize the display
  TFTscreen.begin();
  // clear the screen 
  TFTscreen.background(0, 0, 0); 
  // Set the font size
  TFTscreen.setTextSize(2);
  // A to D input pins
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  // Push button switches
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
}

void loop(){
  // wait for a positive going trigger
  if (trigphase==1){
    for (int timeout=0; timeout < 1000; timeout++){
      Input = PIND;
      if (Input < trigger) break;  }
    for (int timeout=0; timeout < 1000; timeout++){
      Input = PIND;
      if (Input > trigger) break;  }
    }
  // wait for a negative going trigger
  if (trigphase==0){
    for (int timeout=0; timeout < 1000; timeout++){
      Input = PIND;
      if (Input > trigger) break;  }
    for (int timeout=0; timeout < 1000; timeout++){
      Input = PIND;
      if (Input < trigger) break;  }
    }
  // quickly collect the data with no delay
  if (tdelay==-1){
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
    Sample[130]=PIND;   
    EndSTime = micros();
  }
  // Collect the data with a no delay
  // It will not allow a delay of 0 so this is here to do that
  if (tdelay ==0){
    StartSTime = micros();
    for (int xpos=0; xpos <130; xpos++){
      Sample[xpos]=PIND;
    }
    EndSTime = micros();
  }
  // Collect the data with a variable delay
  if (tdelay > 0){
    StartSTime = micros();
    for (int xpos=0; xpos <130; xpos++){
      Sample[xpos]=PIND;
      delayMicroseconds(tdelay);
    }
    EndSTime = micros();
  }
  STime = EndSTime - StartSTime;
  // display the collected data
  for (int xpos = 0; xpos <160; xpos++){
    // select the color black = B,G,R
    TFTscreen.stroke(0, 0, 0);
    // erase the old line
    TFTscreen.line(xpos+1, 0, xpos+1, 160);
    // select the color white = B,G,R
    TFTscreen.stroke(255, 255, 255);
    // draw the trace line (xPos1, yPos1, xPos2, yPos2);0
    // if (xpos<128)TFTscreen.line(xpos, (Sample[xpos]/2), xpos+1, Sample[xpos+1]/2);
    if (xpos<128){
      if (gain==1){
        TFTscreen.line(xpos, (128-Sample[xpos]/2), xpos+1, 128-Sample[xpos+1]/2);
      }
      if (gain==2){
        TFTscreen.line(xpos, (192-Sample[xpos]*1), xpos+1, 192-Sample[xpos+1]*1);
      }
      if (gain==3){
        TFTscreen.line(xpos, (320-Sample[xpos]*2), xpos+1, 320-Sample[xpos+1]*2);
      }
      if (gain==4){
        TFTscreen.line(xpos, (448-Sample[xpos]*3), xpos+1, 448-Sample[xpos+1]*3);
      }
      if (gain==5){
        TFTscreen.line(xpos, (576-Sample[xpos]*4), xpos+1, 576-Sample[xpos+1]*4);
      }
    }

    // Set font color to green
    TFTscreen.stroke(0, 255, 0);
    // draw the green lines
    TFTscreen.line(xpos, 0, xpos+1, 0);
    TFTscreen.line(xpos, 32, xpos+1, 32);
    TFTscreen.line(xpos, 64, xpos+1, 64);
    TFTscreen.line(xpos, 96, xpos+1, 96);
    TFTscreen.line(xpos, 127, xpos+1, 127);
    // draw top to bottom green lines
    if (xpos==0) TFTscreen.line(xpos, 0, xpos,160);
    if (xpos==32) TFTscreen.line(xpos, 0, xpos,160);
    if (xpos==64) TFTscreen.line(xpos, 0, xpos,160);
    if (xpos==96) TFTscreen.line(xpos, 0, xpos,160);
    if (xpos==127) TFTscreen.line(xpos, 0, xpos,160);
  }
  
  // check the status of push button switches
  // now circular so only two switeches are required
  if (digitalRead(17) == 0) select++;
  if (digitalRead(16) == 0) select--;
  if (select >4) select=1;
  if (select <1) select=4;
  // update the trigger level
  if (select==1){
    if (digitalRead(18)==0) trigger++;
    if (digitalRead(19)==0) trigger--;
    if (trigger > 128) trigger=1;
    if (trigger < 1) trigger=128;
  }
  // change the trigger phase
  if (select==2){
    if (digitalRead(18)==0) trigphase++;
    if (digitalRead(19)==0) trigphase--;
    if (trigphase < 0) trigphase=1;
    if (trigphase > 1) trigphase=0;
  }
  // Change the amount of delay
  if (select==3){
    // increase delay
    if (digitalRead(18)==0){
      if (tdelay==500) tdelay=-1;
      if (tdelay==200) tdelay=500;
      if (tdelay==100) tdelay=200;
      if (tdelay==50) tdelay=100;
      if (tdelay==20) tdelay=50;
      if (tdelay==10) tdelay=20;
      if (tdelay==5) tdelay=10;
      if (tdelay==2) tdelay=5;
      if (tdelay==1) tdelay=2;
      if (tdelay==0) tdelay=1;
      if (tdelay==-1) tdelay=0;
    }
    if (digitalRead(19)==0){
      // decrease delay
      if (tdelay==-1) tdelay=500;
      if (tdelay==0) tdelay=-1;
      if (tdelay==1) tdelay=0;
      if (tdelay==2) tdelay=1;
      if (tdelay==5) tdelay=2;
      if (tdelay==10) tdelay=5;
      if (tdelay==20) tdelay=10;
      if (tdelay==50) tdelay=20;
      if (tdelay==100) tdelay=50;
      if (tdelay==200) tdelay=100;
      if (tdelay==500) tdelay=200;
    }
  }
  // Change the amount of gain
  if (select==4){
    if (digitalRead(18)==0) gain++;
    if (digitalRead(19)==0) gain--;
    if (gain > 5) gain=1;
    if (gain < 1) gain=5;
  }
  
  // Update the text on the right side
  // Set font color to bright blue
  TFTscreen.stroke(255, 100, 100);
  // if selected set font color to red
  if (select == 1)TFTscreen.stroke(0, 0, 255);
  TFTscreen.text( "Trg", 129, 3);
  TFTscreen.text( itoa(64-trigger, buf, 10), 129, 18);
  // Set font color to bright blue
  TFTscreen.stroke(255, 100, 100);
  // if selected set font color to red
  if (select == 2)TFTscreen.stroke(0, 0, 255);
  TFTscreen.text( "Pha", 129, 35);
  TFTscreen.text( itoa(trigphase, buf, 10), 129, 50);
  // Set font color to bright blue
  TFTscreen.stroke(255, 100, 100);
  // if selected set color to red
  if (select == 3)TFTscreen.stroke(0, 0, 255);
  TFTscreen.text( "Del", 129, 67);
  TFTscreen.text( itoa(tdelay, buf, 10), 129, 82);
  // Set font color to bright blue
  TFTscreen.stroke(255, 100, 100);
  // if selected set font color to red
  if (select == 4)TFTscreen.stroke(0, 0, 255);
  TFTscreen.text( "Amp", 130, 98);
  TFTscreen.text( itoa(gain, buf, 10), 130, 113);
  // display the sample time
  TFTscreen.stroke(0, 0, 255);
  TFTscreen.text( "Ms", 35, 113);
  TFTscreen.text( itoa(STime, buf, 10), 70, 113);
}
// End of program
