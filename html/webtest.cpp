#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

const char* ssid = "xxx";
const char* password = "xxx";

const char index_html[] PROGMEM = "<form action='action' method='post'><input type='submit' name='B1' value='B1'><input type='submit' name='B2' value='B2'></form>";

void action(AsyncWebServerRequest *request) {
  Serial.println("ACTION!");

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
  request->send_P(200, "text/html", index_html);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi issue");
    while (true) yield();
  }

  Serial.print("Connect to: http://"); Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/action", HTTP_POST, action);
  
  server.begin();
}

void loop() {}