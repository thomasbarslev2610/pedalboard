
// Import required libraries
#include "webserver.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "configurationhandler.h"
#include "settingshandler.h"
#include "settings.h"
#include "switches.h"

// Create AsyncWebServer object on port 
const IPAddress local_IP(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);
//const char index_html[] PROGMEM = "<!DOCTYPE html> <html> <body> <h2>Pedal Board</h2> <form action='' method='post'> <label for='switch1'>Switch 1:</label><br> <body>Command: </body> <input type='number' id='switch1cc' name='switch1cc' value=%switch1cc_value%><br> <br></br> <label for='switch2'>Switch 2:</label><br> <body>Command: </body> <input type='number' id='switch2cc' name='switch2cc' value=%switch2cc_value%><br> <br></br> <label for='switch3'>Switch 3:</label><br> <body>Command: </body> <input type='number' id='switch3cc' name='switch3cc' value=%switch3cc_value%><br> <br></br> <label for='switch4'>Switch 4:</label><br> <body>Command: </body> <input type='number' id='switch4cc' name='switch4cc' value=%switch4cc_value%><br> <br></br> <label for='switch5'>Switch 5:</label><br> <body>Command: </body> <input type='number' id='switch5cc' name='switch5cc' value=%switch5cc_value%><br> <br></br> <input type='submit' value='Store'> </form></body> </html>";
const char index_html[] PROGMEM = "<!DOCTYPE html> <html> <head> <title>Pedal Board</title> <style> #switch1cc, #switch2cc, #switch3cc, #switch4cc, #switch5cc { width: 3em; } .switch { width: 10; } h1 { font-family: Arial, Helvetica, sans-serif; font-weight: bold; } body { font-family: Arial, Helvetica, sans-serif; } input { background-color: white; } label { color: rgb(27, 0, 94); font-family: Arial, Helvetica, sans-serif; font-weight: bold; } .buttonstyled { border: 0; line-height: 2.5; padding: 0 20px; font-size: 1rem; text-align: center; text-shadow: 1px 1px 1px #000; border-radius: 10px; background-color: rgb(212, 210, 223); background-image: linear-gradient( to top left, rgba(0, 0, 0, 0.2), rgba(0, 0, 0, 0.2), rgba(0, 0, 0, 0) ); box-shadow: inset 2px 2px 3px rgba(255, 255, 255, 0.6), inset -2px -2px 3px rgba(0, 0, 0, 0.6); } .buttonstyled:hover { background-color: rgba(255, 0, 0, 1); } .buttonstyled:active { box-shadow: inset -2px -2px 3px rgba(255, 255, 255, 0.6), inset 2px 2px 3px rgba(0, 0, 0, 0.6); } .switchvalue { background-color: rgb(122, 122, 122); width: 10em; padding-bottom: 1em; padding-top: 1em; } .breaker { background-color: white; width: 10em; padding-top: 1em; } </style> </head> <body> <h1>Pedal Board</h1> <form action='' method='post' , id='switches'> <div class='switchvalue'> <label for='switch1'>Switch 1:</label><br /> <body> Command: </body> <input type='number' id='switch1cc' name='switch1cc' value='%switch1cc_value%' /> </div> <div class='breaker'></div> <div class='switchvalue'> <label for='switch2'>Switch 2:</label><br /> <body> Command: </body> <input type='number' id='switch2cc' name='switch2cc' value='%switch2cc_value%' /> </div> <div class='breaker'></div> <div class='switchvalue'> <label for='switch3'>Switch 3:</label><br /> <body> Command: </body> <input type='number' id='switch3cc' name='switch3cc' value='%switch3cc_value%' /> </div> <div class='breaker'></div> <div class='switchvalue'> <label for='switch4'>Switch 4:</label><br /> <body> Command: </body> <input type='number' id='switch4cc' name='switch4cc' value='%switch4cc_value%' /><br /> </div> <div class='breaker'></div> <div class='switchvalue'> <label for='switch5'>Switch 5:</label><br /> <body> Command: </body> <input type='number' id='switch5cc' name='switch5cc' value='%switch5cc_value%' /> </div> </form> <div class='breaker'></div> <button form='switches' formaction='' class='buttonstyled'>Save</button> </body> </html>";




void setParameters(AsyncWebServerRequest *request) {
  Serial.println("setParameter!");

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    
  }
  
  AsyncWebParameter * p1 = request->getParam(0);
  SWITCH1CC_VALUE = p1->value().toInt();
  configuration["switches"][0]["switch1cc"]=SWITCH1CC_VALUE;
  
  
  AsyncWebParameter * p2 = request->getParam(1);
  SWITCH2CC_VALUE = p2->value().toInt();
  configuration["switches"][1]["switch2cc"]=SWITCH2CC_VALUE;

  AsyncWebParameter * p3 = request->getParam(2);
  SWITCH3CC_VALUE = p3->value().toInt();
  configuration["switches"][2]["switch3cc"]=SWITCH3CC_VALUE;

  AsyncWebParameter * p4 = request->getParam(3);
  SWITCH4CC_VALUE = p4->value().toInt();
  configuration["switches"][3]["switch4cc"]=SWITCH4CC_VALUE;
  
  AsyncWebParameter * p5 = request->getParam(4);
  SWITCH5CC_VALUE = p5->value().toInt();
  configuration["switches"][4]["switch5cc"]=SWITCH5CC_VALUE;

  saveConfigurationJSON(configuration, CONFIGURATION_JSON_FILE);
  setupSwitches();

  //request->send_P(200, "text/html", index_html);
  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
  response->addHeader("Server","ESP Async Web Server");
  request->send(response);
}

String processor(const String& var)
{
  if(var == "switch1cc_value")

    return (String) SWITCH1CC_VALUE;
  
  if(var == "switch2cc_value")
    return (String) SWITCH2CC_VALUE;
   
  if(var == "switch3cc_value")
    return (String) SWITCH3CC_VALUE;
   
  
  if(var == "switch4cc_value")
    return (String) SWITCH4CC_VALUE;
  
  if(var == "switch5cc_value")
    return (String) SWITCH5CC_VALUE;
  
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
  
  
  server.on("/", HTTP_POST, setParameters);
  
 
  // Start server
  server.begin();
}
