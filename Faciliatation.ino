#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
 
TinyGPSPlus gps;
 
SoftwareSerial ss(RXPin, TXPin);
 
void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
 
  Serial.print(F("Testing TinyGPS++ library v. "));
  Serial.println();
}
 
void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
 
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
 
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" ");
    Serial.print(F("Speed:"));
    Serial.print(gps.speed.kmph());
  }
  else
  {
    Serial.print(F("0.0,0.0"));
  }
 
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 
  Serial.println();
}
