//****************************************
// Three color ext AtoD+FIFO Scope
// By Bob Davis
// UTFT_(C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//

#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Note that control pins are now assigned to 8-11
UTFT myGLCD(ILI9325C,8,9,10,11);  
int Input=0;
int Sample[320];
int StartSTime=0;
int EndSTime=0;
float SampleTime=0;

void DrawMarkers(){
  myGLCD.setColor(0, 200, 0);
  myGLCD.drawLine(0, 0, 0, 240);
  myGLCD.drawLine(54, 0, 54, 240);
  myGLCD.drawLine(107, 0, 107, 240);
  myGLCD.drawLine(160, 0, 160, 240);
  myGLCD.drawLine(213, 0, 213, 240);
  myGLCD.drawLine(266, 0, 266, 240);
  myGLCD.drawLine(319, 0, 319, 240);
  myGLCD.drawLine(0, 0, 319, 0);
  myGLCD.drawLine(0, 50, 319, 50);
  myGLCD.drawLine(0, 100, 319, 100);
  myGLCD.drawLine(0, 150, 319, 150);
  myGLCD.drawLine(0, 200, 319, 200);
  myGLCD.drawLine(0, 239, 319, 239);
}

void setup() {
  myGLCD.InitLCD();
  myGLCD.clrScr();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
}

void loop() {
  // set color(Red, Green, Blue) range = 0 to 255
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  char buf[12]; 
  while(1) {
    DrawMarkers(); 
// Reset the FIFO
  digitalWrite(12, LOW);
  digitalWrite(12, HIGH);

// wait for trigger of a positive input
//  while (Input == 0){
//    Input = digitalRead(A1);
//    }

// collect the analog data into an array
// Read analog port as a parallel port PINC
  StartSTime = micros();
  for(int xpos=0; xpos<319; xpos++) {
    Sample[xpos]=PINC;
    // Advance the read address
    digitalWrite(13, LOW);
    digitalWrite(13, HIGH);
    
  } 
  EndSTime = micros();
  
// display the collected analog data from array
  for(int xpos=0; xpos<319; xpos++) {
    // Erase old stuff
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawLine (xpos+1, 1, xpos+1, 180);
    // Draw new data
    if (xpos%10==0) DrawMarkers(); 
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawLine (xpos, Sample[xpos]*2, xpos+1, Sample[xpos+1]*2);  }  
  // display the sample time  
  myGLCD.setColor(0, 0, 255);
  SampleTime = EndSTime - StartSTime;
  myGLCD.print("uSeconds=          ", 10, 220);
  myGLCD.print(ltoa(SampleTime, buf, 10), 170, 220);
    } 
}


