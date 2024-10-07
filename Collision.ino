
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
float lattitude,longitude; 
SoftwareSerial gpsSerial(2,3);
SoftwareSerial gsmm(4,5);
TinyGPSPlus gps;
int imp=9;
void setup(){
Serial.begin(9600);
pinMode(imp,INPUT);
  lcd.init();
  lcd.backlight();
//lcd.begin(16, 2);
gpsSerial.begin(9600);

gsmm.begin(9600);

}
void loop()
{
  int collision=digitalRead(imp);
  delay(1000);
if(collision==0)
{  
  gpsSerial.listen();
  textgps();
  Serial.print("LATTITUDE="); Serial.println(lattitude,6);
 Serial.print("LONGITUDE="); Serial.println(longitude,6);
 lcd.print("LAT ");lcd.print(lattitude,6);
 lcd.setCursor(0, 1);
 lcd.print("LONG ");lcd.print(longitude,6);
 delay(2000);
 lcd.clear();
  gsmm.print("\r");
  delay(1000);                  
  gsmm.print("AT+CMGF=1\r");    
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  gsmm.print("AT+CMGS=\"+917200053487\"\r");    
  delay(1000);
//gsmm.print(lattitude,longitude);
//gsmm.print(lattitude); 
//gsmm.print(longitude); 
  gsmm.print("https://www.google.com/maps/place/");
      gsmm.print(lattitude, 6);
      gsmm.print(",");
      gsmm.print(longitude, 6);
  
  delay(1000);
  gsmm.write(0x1A);
  delay(1000); 
  
}
else if(collision==1)
{
  Serial.print("NO COLLISION");
  Serial.println();
}
delay(2000);



}


void textgps()
{

    while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       //Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       //Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
      break;
      }
  
}
 
}
