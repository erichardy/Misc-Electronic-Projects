#include <Arduino.h>


#include <max6675.h>
/*
//câblage module spi max6675 :
                                  //GND --> Gnd masse Arduino
                                  //Vcc -->(+5V) sur pin 2 digital en Output & High
                                  //DO Data Output --> pin 5
                                  //CS Chip Select --> pin 4
                                  //CLK clock --> pin 3
*/

int thermoDO = 5;
int thermoCS = 4;
int thermoCLK = 3; 
double temperture;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);


#include <SPI.h>
#include <SD.h>
File myFile;
File fileTemps;

#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //  LCD address  0x27 pour 16 chars sur 2 lignes 

/*
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
*/
int i = 1;
String line;

// SD CARD
void testSD() {
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("3333 testing 1, 2, 3.");
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
  lcd.init();// initialize the lcd 
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Mont a ra?");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.print("Initializing SD card...");
  lcd.println("Initializing SD card...");
  if (!SD.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.println("initialization failed!");
    lcd.println("initialization failed!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.println("initialization done.");
    lcd.println("initialization done.");
    //
    SD.remove("temps.csv");
    fileTemps = SD.open("temps.csv", FILE_WRITE);
    if (fileTemps) {
      fileTemps.println("Millis|Temp|Num");
      fileTemps.close();
    }
    //
  }
    delay(3000);
    lcd.clear();
}

void loop(void)
{
  temperture = thermocouple.readCelsius();
  line = (long) millis() / 1000; // secondes
  line += "|";
  line += temperture;
  line += "|";
  line += i;
  line.replace(".", ",");
  /* */
  fileTemps = SD.open("temps.csv", FILE_WRITE);
  if (fileTemps) {
    fileTemps.println(line);
    fileTemps.close();
  } else {
    line = "Erreur ouverture fichier !!!";
  }
  /* */
  Serial.println(line);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line);
  i++;
  delay(5000);
}

