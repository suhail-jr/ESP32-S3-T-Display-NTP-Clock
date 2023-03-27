#include <TFT_eSPI.h>  
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "DHT.h"

#define DHTPIN 21

#include "fonts.h"
#include "icon.h"
#include "make.h"
const char* ssid     = "Staff";
const char* password = "st@ff2019@@";


#define TimeFont ag_stencil
#define PMFont ag_stencil33
#define Weather arial25
#define DHTTYPE DHT11
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
TFT_eSPI tft = TFT_eSPI();

String Hour;
int Hr12,Hr24;
String Hr;
String H;

String M;
String Hum;
String Temp;;
String PM;
int flag=0;
DHT dht(DHTPIN, DHTTYPE);

  void setup(void) 
  {

      Serial.begin(115200);
      tft.begin(); 
      dht.begin();    
      tft.setSwapBytes(true); 
      tft.fillScreen(TFT_BLACK);
      tft.setRotation(1);
      tft.setCursor(95,75);
      tft.print("Connecting to ");
      tft.print(ssid);
      WiFi.begin(ssid, password);
      
            while (WiFi.status() != WL_CONNECTED)
                    {
                       tft.pushImage(56.5, 25,207,120, make[0]);
                        delay(2000);
                    }

      timeClient.begin();
      timeClient.setTimeOffset(14400);
      tft.fillScreen(TFT_BLACK);
      flag =1;
 delay(1000);

}
 
   void loop() { 
    
  while(!timeClient.update())
     {
     timeClient.forceUpdate();
      }


int h = dht.readHumidity();
int t = dht.readTemperature();
Hum = String(h)+"%";
Temp = String(t)+"C";
      
 Hour = timeClient.getFormattedTime();
 H = Hour.substring(0,2);
 M = Hour.substring(3,5);

 
 Hr12 = H.toInt();
 Hr24 = H.toInt();
 Hr12 = Hr12 % 12;
  
  if(Hr12<10||Hr24>11)
  {
     Hr = String(Hr12);
     PM = "PM";
     
     Hr = "0"+Hr;
    
  }
else
{
  Hr = Hr;
  PM = "AM";
  
}
  



Serial.println(Hr);
  






  tft.setCursor(45,70);
  tft.loadFont(TimeFont);
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.println(Hr+":"+M);
  tft.unloadFont();
  
  tft.loadFont(PMFont);
  tft.setCursor(240,85);
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.println(PM);
  tft.unloadFont();


  tft.loadFont(Weather);



  tft.pushImage(48, 1,32  ,32, icon[0]);
  tft.setCursor(80,8);
  
  tft.println(Temp);
  
  tft.pushImage(152, 1,32  ,32, icon[1]);
  tft.setCursor(186,10);
  tft.println(Hum);

}
