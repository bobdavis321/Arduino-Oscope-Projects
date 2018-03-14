/************************************
 2.8 SPI PIND TFT Oscope
 Reads the D0-D7 pins using PIND, 
 and shows the value on the screen.
 Created 7 july 2015 by Bob Davis
**************************************/
//#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"

// pin definitions for the ILI9341 2.8 LCD
#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13=clk, #12=nc, #11=mosi) and the above for CS/DC
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ILI9341 tft = Adafruit_ILI9341();

// set up the variables
int xPos=0;
char buf[12];
int Input=0;
byte Sample[250];
int StartSTime=0;
int EndSTime=0;
int stime=0;
int trigger=128;
int trigphase=1;
int tdelay=1;
int select=1;
int gain=1;

void setup(){
  // Initialize the display
  tft.begin();
  // Rotate and clear the screen 
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
    Sample[160]=PIND;    Sample[161]=PIND;    Sample[162]=PIND;
    Sample[163]=PIND;    Sample[164]=PIND;    Sample[165]=PIND;
    Sample[166]=PIND;    Sample[167]=PIND;    Sample[168]=PIND;
    Sample[169]=PIND;    Sample[170]=PIND;    Sample[171]=PIND;
    Sample[172]=PIND;    Sample[173]=PIND;    Sample[174]=PIND;
    Sample[175]=PIND;    Sample[176]=PIND;    Sample[177]=PIND;
    Sample[178]=PIND;    Sample[179]=PIND;    Sample[180]=PIND;
    Sample[181]=PIND;    Sample[182]=PIND;    Sample[183]=PIND;
    Sample[184]=PIND;    Sample[185]=PIND;    Sample[186]=PIND;
    Sample[187]=PIND;    Sample[188]=PIND;    Sample[189]=PIND;
    Sample[190]=PIND;    Sample[191]=PIND;    Sample[192]=PIND;
    Sample[193]=PIND;    Sample[194]=PIND;    Sample[195]=PIND;
    Sample[196]=PIND;    Sample[197]=PIND;    Sample[198]=PIND;
    Sample[199]=PIND;    Sample[200]=PIND;    Sample[201]=PIND;
    Sample[202]=PIND;    Sample[203]=PIND;    Sample[204]=PIND;
    Sample[205]=PIND;    Sample[206]=PIND;    Sample[207]=PIND;
    Sample[208]=PIND;    Sample[209]=PIND;    Sample[210]=PIND;
    Sample[211]=PIND;    Sample[212]=PIND;    Sample[213]=PIND;
    Sample[214]=PIND;    Sample[215]=PIND;    Sample[216]=PIND;
    Sample[217]=PIND;    Sample[218]=PIND;    Sample[219]=PIND;
    Sample[220]=PIND;    Sample[221]=PIND;    Sample[222]=PIND;
    Sample[223]=PIND;    Sample[224]=PIND;    Sample[225]=PIND;
    Sample[226]=PIND;    Sample[227]=PIND;    Sample[228]=PIND;
    Sample[229]=PIND;    Sample[230]=PIND;    Sample[231]=PIND;
    Sample[232]=PIND;    Sample[233]=PIND;    Sample[234]=PIND;
    Sample[235]=PIND;    Sample[236]=PIND;    Sample[237]=PIND;
    Sample[238]=PIND;    Sample[239]=PIND;    Sample[240]=PIND;    
    Sample[241]=PIND;    Sample[242]=PIND;    Sample[243]=PIND;
    Sample[244]=PIND;    Sample[245]=PIND;    Sample[246]=PIND;
    Sample[247]=PIND;    Sample[248]=PIND;    Sample[249]=PIND;
    Sample[250]=PIND;
    EndSTime = micros();
  }
  // Collect the data with a no delay
  // It will not allow a delay of 0 so this is here to do that
  if (tdelay ==0){
    StartSTime = micros();
    for (int xpos=0; xpos <250; xpos++){
      Sample[xpos]=PIND;
    }
    EndSTime = micros();
  }
  // Collect the data with a variable delay
  if (tdelay > 0){
    StartSTime = micros();
    for (int xpos=0; xpos <250; xpos++){
      Sample[xpos]=PIND;
      delayMicroseconds(tdelay);
    }
    EndSTime = micros();
  }
  stime = EndSTime - StartSTime;
  // fix a bug in mode -1 that the displayed time is not correct
  if (tdelay ==-1) stime = 49;
  // display the collected data
  for (int xpos = 0; xpos <320; xpos++){
    // erase the old line
    tft.drawLine(xpos+1, 0, xpos+1, 240, ILI9341_BLACK);
    // draw the trace line (xPos1, yPos1, xPos2, yPos2, color);
    // 256- inverts teh data so it is right side up
    if (xpos<250){
      if (gain==1){
        tft.drawLine(xpos, (256-Sample[xpos]), xpos+1, 256-Sample[xpos+1], ILI9341_WHITE);
      }
      if (gain==2){
        tft.drawLine(xpos, (384-Sample[xpos]*2), xpos+1, 384-Sample[xpos+1]*2, ILI9341_WHITE);
      }
      if (gain==3){
        tft.drawLine(xpos, (512-Sample[xpos]*3), xpos+1, 512-Sample[xpos+1]*3, ILI9341_WHITE);
      }
      if (gain==4){
        tft.drawLine(xpos, (640-Sample[xpos]*4), xpos+1, 640-Sample[xpos+1]*4, ILI9341_WHITE);
      }
      if (gain==5){
        tft.drawLine(xpos, (768-Sample[xpos]*5), xpos+1, 768-Sample[xpos+1]*5, ILI9341_WHITE);
      }
    }
        // draw the horizontal green lines as dots
    if (xpos<250){
    tft.drawPixel(xpos, 0, ILI9341_GREEN);
    tft.drawPixel(xpos, 60, ILI9341_GREEN);
    tft.drawPixel(xpos, 120, ILI9341_GREEN);
    tft.drawPixel(xpos, 180, ILI9341_GREEN);
    tft.drawPixel(xpos, 239, ILI9341_GREEN);
    }
    // draw top to bottom green lines
    if (xpos==0) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==50) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==100) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==150) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==200) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
    if (xpos==250) tft.drawLine(xpos, 0, xpos,240, ILI9341_GREEN);
  }

  //*** check the status of push button switches
  // They are now circular, so only 2 switches are needed
  if (digitalRead(17) == 0) select++;
  if (digitalRead(16) == 0) select--;
  if (select > 4) select=1;
  if (select < 1) select=4;
  // update the trigger level
  if (select==1){
    if (digitalRead(18)==0) trigger++;
    if (digitalRead(19)==0) trigger--;
    if (trigger > 240) trigger=1;
    if (trigger < 1) trigger=240;
  }
  // change the trigger phase
  if (select==2){
    if (digitalRead(18)==0) trigphase++;
    if (digitalRead(19)==0) trigphase--;
    if (trigphase < 1) trigphase=1;
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

  //*** Update the text on the right side
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 1) tft.setTextColor(ILI9341_RED);
  tft.setCursor(252, 10);
  tft.println( "Trigr");
  tft.setCursor(252, 29);
  tft.println( itoa(128-trigger, buf, 10));
  // if selected set font color to red
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 2) tft.setTextColor(ILI9341_RED);
  tft.setCursor(252, 58);
  tft.println( "Phase");
  tft.setCursor(252, 77);
  tft.println( itoa(trigphase, buf, 10));
  // if selected set color to red
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 3) tft.setTextColor(ILI9341_RED);
  tft.setCursor(252, 106);
  tft.println( "Delay");
  tft.setCursor(252, 125);
  tft.println( itoa(tdelay, buf, 10));
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 4) tft.setTextColor(ILI9341_RED);
  tft.setCursor(252, 152);
  tft.println( "Gain");
  tft.setCursor(252, 171);
  tft.println( itoa(gain, buf, 10));
  tft.setTextColor(ILI9341_BLUE);
  // if selected set font color to red
  if (select == 5) tft.setTextColor(ILI9341_RED);
  tft.setCursor(252, 196);
  tft.println( "T-Ms");
  tft.setCursor(252, 215);
  tft.println( itoa(stime, buf, 10));
}
// End of program
