/* 
 * Arduino GPS clock with local time using NEO-6M module and 20x4 LCD.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/



#include <TinyGPSPlus.h>        // include TinyGPS++ library
#include <TimeLib.h>          // include Arduino time library
#include <SoftwareSerial.h>   // include software serial library

TinyGPSPlus gps;

#define S_RX    9   // define software serial RX pin
#define S_TX    8   // define software serial TX pin

SoftwareSerial SoftSerial(S_RX, S_TX);   // configure SoftSerial library

// LCD module connections (RS, E, D4, D5, D6, D7)

#define time_offset   3600  // define a clock offset of 3600 seconds (1 hour) ==> UTC + 1

// variable definitions
char Time[]  = "TIME: 00:00:00";
char Date[]  = "DATE: 00-00-2000";
byte last_second, Second, Minute, Hour, Day, Month;
int Year;

void setup(void)
{
  SoftSerial.begin(9600);  // initialize software serial at 9600 baud
}

void loop()
{
  while (SoftSerial.available() > 0)
  {
    if (gps.encode(SoftSerial.read()))
    {
      // get time from GPS module
      if (gps.time.isValid())
      {
        Minute = gps.time.minute();
        Second = gps.time.second();
        Hour   = gps.time.hour();
      }

      // get date drom GPS module
      if (gps.date.isValid())
      {
        Day   = gps.date.day();
        Month = gps.date.month();
        Year  = gps.date.year();
      }

      if(last_second != gps.time.second())  // if time has changed
      {
        last_second = gps.time.second();

        // set current UTC time
        setTime(Hour, Minute, Second, Day, Month, Year);
        // add the offset to get local time
        adjustTime(time_offset);

        // update time array
        Time[12] = second() / 10 + '0';
        Time[13] = second() % 10 + '0';
        Time[9]  = minute() / 10 + '0';
        Time[10] = minute() % 10 + '0';
        Time[6]  = hour()   / 10 + '0';
        Time[7]  = hour()   % 10 + '0';

        Serial.println(Time);
      }

    }

  }

}
// end of code.
*/