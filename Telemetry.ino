#include <Wire.h> 
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>
 
Adafruit_BMP085 bmp;

const int chipSelect = 10;
void setup() {
  Serial.begin(9600);
  Serial.print("Initializing altimeter...");
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  Serial.print("Altimeter initialized.");
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  File dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println('Init completed! Proceeding to logging...\n\n\n\n\n\n');
  } else {
    Serial.println("error opening DATALOG.txt");
    return;
  }
}

void loop() {
  File dataFile = SD.open("log.txt", FILE_WRITE);
  if (dataFile) {
    unsigned long time = millis();
    dataFile.println(round(time/100)/10 + ": A: " + String(bmp.readAltitude()) + "m + P: " + String(bmp.readPressure()) + "T: " + String(bmp.readTemperature()) + "°");
    dataFile.close();
    delay(100); // Частота записи показаний датчика 1000=1сек
  } else {
    Serial.println("error opening DATALOG.txt");
  }
}

