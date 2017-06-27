// Require wifi.h
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(WEBSERVER_PORT);

void onRequest(AsyncWebServerRequest *request){
  //Handle Unknown Request
  request->send(404);
}


void webServerStart() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/index.html");
  });

  server.on("/getData.json", HTTP_GET, [](AsyncWebServerRequest *request){
    time_t t = now();
    request->send(200, "application/json", "{ \"tempLiquor\": " + String(tempLiquor) + ", \"tempMash\": " + String(tempMash) + ", \"tempBoil\" : " + String(tempBoil) + ", \"time\" : " + String(t) + ", \"lastTempUpdate\" : " + String(lastTempUpdate) + ", \"recording\" : " + String(record) + "}" );
  });

  server.on("/startStopRecord.json", HTTP_GET, [](AsyncWebServerRequest *request){
    // update Clock
    time_t t = now();
    if ( record == false) {
      record = true;
    } else {
      record = false;
    }
    request->send(200, "application/json", "{ \"recording\" : " + String(record) + "}" );
  });

  // attach filesystem root at URL /fs
  server.serveStatic("/", SPIFFS, "/");

  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound(onRequest);

  server.begin();
  Serial.println("HTTP server started");
}
