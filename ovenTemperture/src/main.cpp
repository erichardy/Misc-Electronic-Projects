#include <Arduino.h>

// From "SdFat - Adafruit Fork by Bill Greiman"
#include <SPI.h>
/*
#include "SdFat.h"
#include "sdios.h"
*/
#include <SD.h>
File myFile;
/*
// SD card chip select pin
const uint8_t chipSelect = SS;

// file system
SdFat sd;

// print stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash memory
#define error(s) sd.errorHalt(F(s))
//------------------------------------------------------------------------------

// END From "SdFat - Adafruit Fork by Bill Greiman"...
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    tft.drawFastHLine(0, y, tft.width(), WHITE);
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(GREEN);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(1000);
}

void demoTFT() {
  tft.fillScreen(BLACK);
  showmsgXY(20, 10, 1, NULL, "System x1");
  showmsgXY(20, 24, 2, NULL, "System x2");
  showmsgXY(20, 60, 1, &FreeSans9pt7b, "FreeSans9pt7b");
  showmsgXY(20, 80, 1, &FreeSans12pt7b, "FreeSans12pt7b");
  showmsgXY(20, 100, 1, &FreeSerif12pt7b, "FreeSerif12pt7b");
  showmsgXY(20, 120, 1, &FreeSmallFont, "FreeSmallFont");
  showmsgXY(5, 180, 1, &FreeSevenSegNumFont, "01234");
  showmsgXY(5, 190, 1, NULL, "System Font is drawn from topline");
  tft.setTextColor(RED, GREY);
  tft.setTextSize(2);
  tft.setCursor(0, 220);
  tft.print("7x5 can overwrite");
  delay(1000);
  tft.setCursor(0, 220);
  tft.print("if background set");
  delay(1000);
  showmsgXY(5, 260, 1, &FreeSans9pt7b, "Free Fonts from baseline");
  showmsgXY(5, 285, 1, &FreeSans9pt7b, "Free Fonts transparent");
  delay(1000);
  showmsgXY(5, 285, 1, &FreeSans9pt7b, "Free Fonts XXX");
  delay(1000);
  showmsgXY(5, 310, 1, &FreeSans9pt7b, "erase backgnd with fillRect()");
}

// SD CARD
void testSD() {
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}



void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.println("Example: Font_simple");
    Serial.print("found ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
    tft.begin(ID);
    tft.setRotation(0);
}

void loop(void)
{
    // demoTFT();
    testSD();
    delay(10000);
}


