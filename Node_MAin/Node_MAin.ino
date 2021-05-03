/*
Project : Nova
language : c++
Created On : 10-02-2021
2nd Year iot Project
*Run On nodemcu
*/

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//firebase
#define FIREBASE_HOST "nova-a85c6-default-rtdb.firebaseio.com"  
#define FIREBASE_AUTH "pjhq0lfZoyGetq3BI8058icTIgrp4RVPgZ8u0kRw"  
FirebaseData fbdo;
//wifi
#define WIFI_SSID "Malware_011010"  
#define WIFI_PASSWORD "fuckpassword"  

//to led display
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigP = D5;  //D5 for trig ultrasonic
const int echoP = D6;  //D6 for echo ultrasonic
const int sensor_pin = A0; //soil_moisture
int relay = D0; // the input to the relay pin

#define RLED D7 //D5 for Red Led
#define BLED D8  //D6 for Blue led
#define GLED D4  //D0 for Green led

#include "DHT.h"
DHT dht = DHT(D3, DHT11, 6); // DHT(uint8_t pin, uint8_t type, uint8_t count=6);

//variables
long duration;
int distance;
//tank full
int full = 12;
//soil 
float moisture_percentage;

void setup() {
  pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoP, INPUT);   // Sets the echoPin as an Input
  pinMode(RLED, OUTPUT);    // LED pin as output.
  pinMode(BLED, OUTPUT);    // LED pin as output.
  pinMode(GLED, OUTPUT);    // LED pin as output.
  pinMode(relay, OUTPUT); // initialize pin as OUTPUT
  pinMode(relay, LOW);
  Serial.begin(9600);      // Open serial channel at 9600 baud rate
  dht.begin();

  //display
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.home();

  //welcome screen
  lcd.setCursor(0,0);
  lcd.print("STARTING");
  lcd.setCursor(0,1);
  lcd.print("NOVA.");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.clear();
  wificon(); //connect to wifi
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //firebase connection
}

void loop() {  

  Firebase.reconnectWiFi(true); //autoreconnect

  
  digitalWrite(trigP, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay 
  digitalWrite(trigP, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigP, LOW);   // trigPin low
  
  duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
  distance= duration*0.034/2;        //Calculating actual/real distance

  //tank lvl
  int water_height = full-distance;
   int pre = water_height*100/full;
    if(pre<15){
    Serial.print("LOW WATER LVL = ");
      digitalWrite (BLED, LOW) ;
      digitalWrite (GLED, LOW) ;
      digitalWrite (RLED, HIGH) ;
      Serial.print(pre);
      Serial.print("%");
      lcd.setCursor(0,0);
      lcd.print("Water Lvl: ");
      lcd.print(pre);
      lcd.print("%");
      if(Firebase.setFloat(fbdo, "/water", pre))
      {
        //Success
         Serial.println(" : Set water lvl success");
    
      }else{
        //Failed?, get the error reason from fbdo
    
        Serial.print(" : Error in set water lvl ");
        Serial.println(fbdo.errorReason());
      }
  }else if(pre>65){
    Serial.print("Tank Full = ");
      digitalWrite (RLED, LOW) ;
      digitalWrite (GLED, LOW) ;
      digitalWrite (BLED, HIGH) ;
      Serial.print(pre);
      Serial.print("%");
      lcd.setCursor(0,0);
      lcd.print("Water Lvl: ");
      lcd.print(pre);
      lcd.print("%");
      if(Firebase.setFloat(fbdo, "/water", pre))
      {
        //Success
         Serial.println(" : Set water lvl success");
    
      }else{
        //Failed, get the error reason from fbdo
    
        Serial.print(" : Error in set water lvl ");
        Serial.println(fbdo.errorReason());
      }
  }else{
    Serial.print("Water Lvl = ");
    digitalWrite (BLED, LOW) ;
    digitalWrite (RLED, LOW) ;
    digitalWrite (GLED, LOW) ;
    Serial.print(pre);
    Serial.print("%");
    lcd.setCursor(0,0);
    lcd.print("Water Lvl : ");
    lcd.print(pre);
    lcd.print("%");
    if(Firebase.setFloat(fbdo, "/water", pre))
      {
        //Success
         Serial.println(" : Set water lvl success");
    
      }else{
        //Failed?, get the error reason from fbdo
    
        Serial.print(" : Error in set water lvl ");
        Serial.println(fbdo.errorReason());
      }
  }
  float humidity = dht.readHumidity(); // Get humidity value 
  float temperature = dht.readTemperature(); // Get temperature value 
  Serial.print("Humidity : ");
  Serial.print(humidity, 2);
  lcd.setCursor(0,1);
  lcd.print("Humidity : ");
  lcd.print(humidity, 2);
  delay(1000);
  lcd.clear();
  if(Firebase.setFloat(fbdo, "/humi", humidity))
      {
        //Success
         Serial.println(" : Set humidity success");
    
      }else{
        //Failed?, get the error reason from fbdo
    
        Serial.print(" : Error in set humidity ");
        Serial.println(fbdo.errorReason());
      }


      
  Serial.print("Temperature : ");
  Serial.print(temperature, 2);
  lcd.setCursor(0,0);
  lcd.print("Temp. : ");
  lcd.print(temperature, 2);
  lcd.print("C'");
  if(Firebase.setFloat(fbdo, "/temp", temperature))
      {
        //Success
         Serial.println(" : Set temperature success");
    
      }else{
        //Failed?, get the error reason from fbdo
    
        Serial.print(" : Error in temperature ");
        Serial.println(fbdo.errorReason());
      }

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) ); //calculate moisture
  Serial.print("Soil Moisture = ");
  Serial.print(moisture_percentage);
  Serial.print("%");
  lcd.setCursor(0,1);
  lcd.print("Soil M.: ");
  lcd.print(moisture_percentage);
  lcd.print("%");
  if(Firebase.setFloat(fbdo, "/soil", moisture_percentage))
  {
    //Success
     Serial.println(" : Set soil moisture success");

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print(" : Error in soil moisture ");
    Serial.println(fbdo.errorReason());
  }

      
  if(moisture_percentage<1.3){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Watering ");
    lcd.setCursor(0,1);
    lcd.print("Plant.... ");
    pinMode(relay, HIGH);
    digitalWrite (GLED, HIGH) ;
    delay(1000);
    pinMode(relay, LOW);
   }

   if(Firebase.getInt(fbdo, "/pump"))
  {
    if(fbdo.intData()==1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Watering ");
      lcd.setCursor(0,1);
      lcd.print("Plant.... ");
      pinMode(relay, HIGH);
      digitalWrite (GLED, HIGH) ;
      delay(1000);
      pinMode(relay, LOW);
      if(Firebase.setInt(fbdo, "/pump", 0))
      {
        //Success
         Serial.println(" : Set pump of success");
    
      }else{
        //Failed?, get the error reason from fbdo
    
        Serial.print(" : Error in pump data ");
        Serial.println(fbdo.errorReason());
      }
    }

  }else{
    //Failed?, get the error reason from fbdo

    Serial.print("Error in getting pump data, ");
    Serial.println(fbdo.errorReason());
  }
  
  delay(2000);                  //Pause for 2 seconds and start measuring distance again
  lcd.clear();
}

void wificon()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("WIFI");
  delay(300);
  lcd.clear();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();  
  lcd.setCursor(0,0);
  lcd.print("Connected with ");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(300);
  lcd.clear();
}
