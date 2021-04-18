#include <Wire.h>
#include <SSD1306.h>
#include <OLEDDisplayFonts.h>
#include "FS.h"

SSD1306  display(0x3c, D4, D5); 

String filename = "/video.dat";
String folderPath = "/";
File dataFile;
unsigned char upic [1024];
char pic [1024];
unsigned short count = 0;

void setup() {
    Serial.begin(115200);
    delay(10);
    initFS();
    // Initialising the UI will init the display too.
    display.init();
    display.flipScreenVertically();
}


void loop() { 
    dispalyBadapple();
}

void initFS()
{
  Serial.println("");
  // Start SPIFFS
  if(SPIFFS.begin())
  {
    //   SPIFFS.format();
      Serial.println("SPIFFS started.");
  }
  else
  { 
      SPIFFS.format();
      Serial.println("SPIFFS failed to start");
  }
  if(SPIFFS.exists(filename))
    {
        Serial.println("File founded.");
        dataFile = SPIFFS.open(filename, "r");
        int fileSize = dataFile.size();
        Serial.print("Size of file is:");Serial.println(fileSize);
        Serial.println("");
    }
    else
    {
        Serial.println("Can not found file.");
        Dir dir = SPIFFS.openDir(folderPath);
        Serial.print("Listing DIR: ");Serial.println(folderPath);
        while(dir.next()){
            Serial.println(dir.fileName()); //print file name
        }
    }
}

void charToUnsignedChar(char* c, unsigned char* uc, int length)
{
    for(int i=0;i<length;i++){
        *(uc+i) = *(c+i) >= 0 ? *(c+i) : 127-*(c+i); //Signed char to unsigned char
    }
}

void printPic(char* pic, int length)
{
    for(int i=0;i<length;i++){
        Serial.print((int)(*(pic+i))); 
    }
    Serial.println();
}

void dispalyBadapple()
{
    dataFile.readBytes(pic, 128*64/8);
    charToUnsignedChar(pic, upic, 1024);
    display.clear();
    display.drawXbm(0, 0, 128, 64, upic);
    display.display();
    delay(20);
    count++;
    if(count>1999)
    {
        dataFile.seek(0);
        count=0;
    }
    Serial.println(count);

}