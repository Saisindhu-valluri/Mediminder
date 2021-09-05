/*
 Mediminder:A simple reminder to take medicines on time. 
                                   - Saisindhu Valluri
 
 The project is done using the alarm on a DS3231 with the Adafruit RTClib library.
 Set an alarm on the DS3231 RTC module and monitor its status using the
 alarmFired function. 
-----------
  SDA -> Arduino  (SDA pin)
  SCL -> Arduino  (SCL pin)
  VCC -> Arduino 5V
  GND -> Arduino GND
*/

#include "RTClib.h"
RTC_DS3231 rtc;

const int switchPin = 2; // the number of the switch pin
const int motorPin = 9; // the number of the motor pin

int switchState = 0; // variable for reading the switch's status

void setup () {
  Serial.begin(9600); // Start serial port for monitoring
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();

    pinMode(5,OUTPUT); // LED
    pinMode(6,OUTPUT); // Buzzer
    pinMode(10,INPUT); // switch(push button)
  }
  // initialize the motor pin as an output:
pinMode(motorPin, OUTPUT);
 // initialize the switch pin as an input:
pinMode(switchPin, INPUT);

  // If required set time
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // To compiled time
  //rtc.adjust(DateTime(2021, 9, 5, 19, 0, 0)); // Or  e.g. September 5, 2021 at 7pm

  // Disable and clear both alarms
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
         
  DateTime now = rtc.now(); // Get current time

  // Print current time and date
  char buff[] = "Start time is hh:mm:ss DDD, DD MMM YYYY";
  Serial.println(now.toString(buff));

  // Set alarm time
  rtc.setAlarm1(now + TimeSpan(0, 0, 0, 10), DS3231_A1_Second); // In 10 seconds time
  //rtc.setAlarm1(DateTime(2020, 6, 25, 15, 0, 0), DS3231_A1_Hour); // Or can be set explicity
}

void loop () {

  // Check if alarm by polling by using alarmFired
  if (rtc.alarmFired(1) == true){

    digitalWrite(5, HIGH);
    tone(6, 1000);
 
    // Print current time and date
    DateTime now = rtc.now(); // Get the current time
    char buff[] = "Alarm triggered at hh:mm:ss DDD, DD MMM YYYY";
    Serial.println(now.toString(buff));

    // Disable and clear alarm
    //rtc.disableAlarm(1); // Not used as only disables the alarm on the SQW pin 
    rtc.clearAlarm(1); 

    // Perhaps reset to new time if required
    rtc.setAlarm1(now + TimeSpan(0, 0, 0, 10), DS3231_A1_Second); // Set for another 10 seconds
  }
 if(digitalRead(10)==HIGH)
 {  
   digitalWrite(5, LOW);
    noTone(6); 
 }
 //read the state of the switch value:
switchState = digitalRead(switchPin);

//check if the switch is pressed.
if (switchState == HIGH) {
// turn motor on: 
digitalWrite(motorPin, HIGH);
}
else
{
// turn motor off:
digitalWrite(motorPin, LOW);
}
  }
