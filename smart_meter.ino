
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "819e7805e573444a9dbd633a8e3478de";
char ssid[]="Raspberry15";
char pass[]="workshop";
boolean start=true;
int price=0;
float units=0;
float unitsDay=0;
int ac=D3;
int geyser=D4;
float maxAc=0;
float maxGeyser=0;
int acUnits=0;
int geyserUnits=0;
int acSwitch=D5;
int geyserSwitch=D6;
long acStart=0;
long geyserStart=0;
boolean noteAc=true;
boolean noteGeyser=true;
boolean t=true;
//char auth[] = "819e7805e573444a9dbd633a8e3478de";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,INPUT);
  pinMode(D6,INPUT);
  // Blynk.begin(auth);
 // pinMode(D3,LOW);
  Blynk.virtualWrite( V0,0);
   Blynk.virtualWrite( V1,0);
    Blynk.virtualWrite( V2,0);
     Blynk.virtualWrite( V3,0);
      Blynk.virtualWrite( V4,0);
 }

void loop() {
  // put your main code here, to run repeatedly:
   Blynk.run();
   
  
 /* if(noteAc==false)
  {
    long durationAc=millis();
    if((durationAc-acStart)>5000)
    {
      acUnits+=10;
    }
    if(acUnits>=(maxAc*.75))
    {
      Serial.println("Used 75% of power allowance for AC...Increase temperature");
    }
    else if(acUnits>=maxAc)
    {
      Serial.println("AC exceeding allowed usage ");
    }
  }*/
  if(noteGeyser==false)
  {
    long durationGeyser=millis();
  Serial.println(durationGeyser-geyserStart);
    
    if((durationGeyser-geyserStart)>60000)
    {
      geyserUnits+=10;
      geyserStart=durationGeyser;
      durationGeyser=0;
      Blynk.virtualWrite( V4,geyserUnits);
    }
    
    if(geyserUnits>=maxGeyser)
    {
      Serial.println("Geyser exceeding allowed usage ");
      pinMode(D4,LOW);
      noteGeyser=true;
      t=false;
      
    }
  }
if(start==true)
{ 
  Serial.println("Enter the maximum usage for the month:");
  while (Serial.available() == 0);
  if (Serial.available() > 0) {    // is a character available?
    
  price=Serial.parseInt();
  
  Serial.println(price);
  }
 units=price/5;
  unitsDay=units/30;
  //Blynk.run();
 //Blynk.virtualWrite(V1,units);
  Serial.print("units usable per day= ");
  Serial.println(unitsDay);
  Blynk.virtualWrite( V0,unitsDay);
  unitsDay=unitsDay-10;
  Serial.print("ac units available= ");
  maxAc=(unitsDay*2)/3;
  Serial.println(maxAc);
   Blynk.virtualWrite( V1,maxAc);
  Serial.print("geyser units available= ");
  maxGeyser=(unitsDay)/3;
  Serial.println(maxGeyser);
   Blynk.virtualWrite( V3,unitsDay);
  start=false;
 }
 /*if(digitalRead(acSwitch)==LOW && noteAc==HIGH)
 {//acStart=millis();
  pinMode(ac,HIGH);
  Serial.println("ac on");
  noteAc=false;
  
 }
 else if(digitalRead(acSwitch)==HIGH && noteAc==LOW){
  pinMode(ac,LOW);
  Serial.println("ac off");
  noteAc=true;
 }*/
 if(digitalRead(geyserSwitch)==HIGH && noteGeyser==true && t==true)
 {geyserStart=millis();
  pinMode(geyser,HIGH);
  noteGeyser=false;
 }
 else if(digitalRead(geyserSwitch)==LOW && noteGeyser==false){
  pinMode(geyser,LOW);
  //Serial.println(geyserStart);
  noteGeyser=true;
 }
 
 
}
