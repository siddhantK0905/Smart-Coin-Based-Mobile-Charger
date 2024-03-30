#include "Countimer.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Countimer timer;
int runTimer = 1; 
int buzzerPin = 8;
int relayPin=9;
int sensor = 7;      
void setup()
{
   pinMode(buzzerPin, OUTPUT);
   pinMode(relayPin,OUTPUT);
   pinMode(sensor,INPUT);
   //digitalWrite(sensor,HIGH);
   lcd.begin();
   lcd.backlight(); // Turn on the blacklight 
   // Set up count down timer with 10s and call method onComplete() when timer is complete.
   // 00hr:10min:00sec
  timer.setCounter(0,10,00, timer.COUNT_DOWN, onComplete);
  // Print current time every 1s on serial port by calling method refreshClock().
  timer.setInterval(refreshClock, 1000);
  lcd.print(" Coin Based");  
   lcd.setCursor(0,1);
   lcd.print(" Mobile Charger"); 
   delay(2000);
   lcd.clear();
   lcd.print(" Insert Coin ");  
   delay(1000);
   lcd.clear();
   lcd.print("Count Down Timer"); 
 }
void loop() 
{
   while(digitalRead(sensor)==HIGH)
   { 
    while(runTimer == 1)
    {
      digitalWrite(relayPin,HIGH);
     //Start timer
      count_down_timer(); 
    } 
  }
}
void count_down_timer() 
{
  timer.run();
    // Now timer is running and listening for actions.
    // If you want to start the timer, you have to call start() method.
    if(!timer.isCounterCompleted()) 
    {
      timer.start();
    }
}
  void onComplete() 
{
   digitalWrite(relayPin,LOW); 
   runTimer = 0;
   lcd.clear();
   lcd.print(" Time Over !"); 
   lcd.setCursor(0,1);
   lcd.print("Reset Device");
   Serial.println("Timer Over!!!"); 
   delay(500);
   digitalWrite(buzzerPin, HIGH);
   delay(500);
   digitalWrite(buzzerPin, LOW);
   delay(500);
  }
void refreshClock() 
{
  Serial.println(timer.getCurrentTime());
  lcd.setCursor(2,1);
  lcd.print(timer.getCurrentTime());
 }

