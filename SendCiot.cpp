#include <SPI.h>
#include <Ethernet.h>
#include "SendCiot.h"


String dataString = "";
EthernetClient client;
char server[] = "ciot.kadu.com.br";

/**
    Sends an HTTP request to the CIOT system after constructing a JSON
    @param array contains the key-value pairs that will be sent in the JSON
    @param elements contains the number of columns in the array
    @param apikey contains the apikey of the CIOT user
    @param device contains the device id of the CIOT user
    @return gives the message sent from the CIOT server

    99.9% Based on Carriots library
*/

String SendCiot::send(String array[][2], int elements, String apikey, String device){
  String key;
  String value;
  String msg;
  if (client.connect(server, 80)) {
    Serial.println(F("connected"));
    dataString = "{\"device\":\"";
    dataString += device;
    dataString += "\",\"data\":{";
    for (int i=0; i<elements;i++){
      key=array[i][0];
      value=array[i][1];
      dataString += "\""+key+"\":";
      dataString += "\""+value+"\"";
      if (elements>1 && i!=elements-1){
         dataString += ",";
      }
    }
    dataString += "}}";
    Serial.print("\n\nDataString:\n");
    Serial.println(dataString);

    client.println("POST /v1/streams/new HTTP/1.1");
    client.println("Host: ciot.kadu.com.br");
    client.println("Accept: application/json");
    client.println("User-Agent: Arduino-CIOT");
    client.println("Content-Type: application/json");
    client.print("key: ");
    client.println(apikey);
    client.print("Content-Length: ");
    int thisLength = dataString.length();
    client.println(thisLength);
    client.println("Connection: close");
    client.println();
    client.println(dataString);

   }
   delay(5);
  while (client.available()) {
      char c = client.read();
      msg += c;
  }
  if (!client.connected()) {
      client.stop();
  }
  return msg;
}