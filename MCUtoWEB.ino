/* https://create.arduino.cc/projecthub/Rjuarez7/arduino-yun-iot-for-home-monitoring-using-dweet-io-b95009 */
/* Use of the httpclient library to create a "thing" in dweet.io using an Arduino YUN. */

#include <Bridge.h>
#include <HttpClient.h>

int analogIn = A0;
int analogVal = 0;
int analogIn1 = A1;
int analogVal1 = 0;
int light = 0;
float temp;

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
}

void loop() {
String dataString;

/* Lee las entradas analógicas */
analogVal = analogRead(analogIn);
analogVal1 = analogRead(analogIn1);


/* Mapea de un rango a otro
map(value, fromLow, fromHigh, toLow, toHigh)
  value: the number to map.
  fromLow: the lower bound of the value’s current range.
  fromHigh: the upper bound of the value’s current range.
  toLow: the lower bound of the value’s target range.
  toHigh: the upper bound of the value’s target range.*/

light=map(analogVal,0,1023,0,100); // To convert Analog values to % of luminosity

temp=analogVal1*0.4689455791989076; //Sensor Calibration

HttpClient client;

dataString += getTimeStamp(); // CAll routine to obtain current timestamp from the linino side of the YUN
  // Make a HTTP request:To send analog input values of A0 and A1
  
client.get("http://www.dweet.io/dweet/for/YUN_ANALOG_IN_DWEETING?A0_Home_Light="+String(light)+"&A1_Home_Temp="+String(temp)+"&TimeStamp="+String(dataString));

delay(1000); // To give time to the server for answering
}

String getTimeStamp() {
   String result;
   Process time;
   time.begin("date");
   time.addParameter("+%D-%T");  
   time.run(); 
   while(time.available()>0) {
     char c = time.read();
     if(c != '\n')
       result += c;
   }
   return result;
}
