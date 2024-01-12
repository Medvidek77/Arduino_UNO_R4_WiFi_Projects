#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "bear_a.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "math.h"


#define ONE_WIRE_BUS 2


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ArduinoLEDMatrix matrix;

int num3 = 0;

void setup(void)
{

  Serial.begin(9600);

  sensors.begin(); 
  matrix.loadSequence(bear_a);
  matrix.begin();
  matrix.play(false);
  delay(2000);
  
  num3 = 0;
}
void loop(void)
{ 
 matrix.beginDraw();
 matrix.textFont(Font_5x7);
 matrix.beginText(2, 1, 0xFFFFFF);

 float num2 = 0;
 float avTemp;

 if(num3 == 1){
   int num1 = 1;

   while(num1 <= 4 && num1 > 0){
     delay(5000);
     sensors.begin();
     sensors.requestTemperatures(); // Send the command to get temperatures
     Serial.println("DONE");
     float temp = sensors.getTempCByIndex(0);
     num2 += temp;
     Serial.println(num2);
     Serial.println(temp);
     Serial.println(num1);

     num1 += 1;
     if (num1 == 4){
       avTemp = num2 / 3;
       num1 = 0;
     }
     
   }

 }
 else
 {
   sensors.begin();
   sensors.requestTemperatures(); // Send the command to get temperatures
   Serial.println("DONE");
   avTemp = sensors.getTempCByIndex(0);
   delay(100);
   num3 = 1;
 }

 int roundedTemp = round(avTemp);
 String tempStr = String((int)roundedTemp);

 tempStr.replace("0", "O");
 if (num2 == -127.00 || num2 < -25.00){
   matrix.textFont(Font_4x6);
   matrix.beginText(1, 1, 0xFFFFFF);
   matrix.println("Err");
 }
 else
 {
   matrix.clear();
   matrix.println(tempStr);
 }
 
 matrix.endText();

 matrix.endDraw();

 delay(1000);
}
