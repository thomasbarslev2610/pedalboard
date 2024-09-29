
// Import required libraries
#include "webserver.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
// Create AsyncWebServer object on port 
const IPAddress local_IP(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);
const char index_html[] PROGMEM = "<!DOCTYPE html> <html> <body> <h2>Pedal Board</h2> <form action='' method='post'> <label for='switch1'>Switch 1:</label><br> <body>Command: </body> <input type='number' id='switch1cc' name='switch1cc' value=%switch1cc_value%><br> <br></br> <label for='switch2'>Switch 2:</label><br> <body>Command: </body> <input type='number' id='switch2cc' name='switch2cc' value=%switch2cc_value%><br> <br></br> <label for='switch3'>Switch 3:</label><br> <body>Command: </body> <input type='number' id='switch3cc' name='switch3cc' value=%switch3cc_value%><br> <br></br> <label for='switch4'>Switch 4:</label><br> <body>Command: </body> <input type='number' id='switch4cc' name='switch4cc' value=%switch4cc_value%><br> <br></br> <label for='switch5'>Switch 5:</label><br> <body>Command: </body> <input type='number' id='switch5cc' name='switch5cc' value=%switch5cc_value%><br> <br></br> <input type='submit' value='Store'> </form></body> </html>";

int switch1cc_value = 101;
int switch2cc_value = 202;
int switch3cc_value = 303;
int switch4cc_value = 404;
int switch5cc_value = 505;

//const char index_html[] PROGMEM =  "<!DOCTYPE html> <html> <body> %HELLO_FROM_TEMPLATE%</body> </html>";


void action(AsyncWebServerRequest *request) {
  Serial.println("ACTION!");

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    
  }
  
  AsyncWebParameter * p1 = request->getParam(0);
  switch1cc_value = p1->value().toInt();
  
  AsyncWebParameter * p2 = request->getParam(1);
  switch2cc_value = p2->value().toInt();
  
  AsyncWebParameter * p3 = request->getParam(2);
  switch3cc_value = p3->value().toInt();
  
  AsyncWebParameter * p4 = request->getParam(3);
  switch4cc_value = p4->value().toInt();
  
  AsyncWebParameter * p5 = request->getParam(4);
  switch5cc_value = p5->value().toInt();

  //request->send_P(200, "text/html", index_html);
  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
  response->addHeader("Server","ESP Async Web Server");
  request->send(response);
}

String processor(const String& var)
{
  if(var == "switch1cc_value")
    return (String) switch1cc_value;
  
  if(var == "switch2cc_value")
    return (String) switch2cc_value;
   
  if(var == "switch3cc_value")
    return (String) switch3cc_value;
   
  
  if(var == "switch4cc_value")
    return (String) switch4cc_value;
  
  if(var == "switch5cc_value")
    return (String) switch5cc_value;
  
  return String();

}

void setupwebServer()
{
  // Serial port for debugging purposes
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "POST");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  Serial.println("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAPsetHostname("pedalboard.local");
  WiFi.softAP("pedalboard", "12345678");

  IPAddress IP = WiFi.softAPIP();

  // Print ESP Local IP Address
  Serial.print("AP IP address: ");
  Serial.println(IP);
  

  
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
    response->addHeader("Server","ESP Async Web Server");
    request->send(response);
  
  });
  
  
  server.on("/", HTTP_POST, action);
  
 
  // Start server
  server.begin();
}
