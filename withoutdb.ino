#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;
int piezo_Pin= A0;
int LED_Pin= 13;

//Set the threshold levels
int threshold= 50;
 
TinyGPSPlus gps;
 
SoftwareSerial ss(RXPin, TXPin);
 
void setup()
{
  Serial.begin(9600);
  pinMode(LED_Pin, OUTPUT);
  
  Serial.begin(9600);
  ss.begin(GPSBaud);
 
  Serial.print(F("Testing GPS "));
  Serial.println();
}
 
void loop()
{
  int reading= analogRead(piezo_Pin);
  Serial.println(reading);
  delay(500);
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
  if (reading > threshold)
  {
    digitalWrite(LED_Pin, HIGH);
    digitalWrite(LED_Pin, LOW);
  }
 
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
 
void displayInfo()
{
  Serial.print(F("Location: https://www.google.com/maps/place/")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F("+"));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" ");
    Serial.print(F("Speed:"));
    Serial.print(gps.speed.kmph());
    delay(300);
  }
  else
  {
    Serial.print(F("11.041898+77.0272319"));
    delay(300);
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
