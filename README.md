CIOT Client Library
===================

This is the arduino library to easy access CIOT[http://ciot.kadu.com.br]

Just download the zip structure and import to your arduino installation.

## Example
### Simple example to sender data
```js
#include <SPI.h>
#include <Ethernet.h>
#include <SendCiot.h>

// Replace with your CIOT device key
const String APIKEY="CIOT_DEVICE_KEY";

// Replace with the id_developer of your device
const String DEVICE="CIOT_DEVICE_NAME";

// Specify the number of rows in your array, in this case 3
const int numElements=3;

byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

SendCiot sender;

void setup() {
  // Start serial port
  Serial.begin(9600);
  Serial.println(F("Starting"));

  // Start the Ethernet connection
  Ethernet.begin(mac);
}

void loop() {
  // Define the values of the array to be sent
  String array[numElements][2] =
    {
      {"Name", "James"},
      {"Age", "28"},
      {"Gender", "Male"}
    };

  // Using the instance of the library, call the method send
  Serial.println(sender.send(array, numElements, APIKEY, DEVICE));

  //Send this stream every 10 secs.
  delay(10000);
}
```
