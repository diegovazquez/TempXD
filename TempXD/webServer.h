// Require wifi.h
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(WEBSERVER_PORT);

void onRequest(AsyncWebServerRequest *request){
  //Handle Unknown Request
  request->send(404);
}


void webServerStart() {
  // Redirect to index
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/index.html");
  });

  // Status Data
  server.on("/getData.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json", "{ \"tempLiquor\": " + String(tempLiquor) + ", \"tempMash\": " + String(tempMash) + ", \"tempBoil\" : " + String(tempBoil) + ", \"lastTempUpdate\" : " + String(lastTempUpdate) + ", \"recording\" : " + String(record) + "}" );
  });

  // Start Stop Recording
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


  server.on("/getRecords.json", HTTP_GET, [](AsyncWebServerRequest *request){
      String respons = "[";
      Dir dir = SPIFFS.openDir("/req/");
      while (dir.next()) {                      // List the file system contents
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();
        respons = respons + "'" + fileName.c_str() + "',";
        //Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
      }
      respons[respons.length()-1] = ']';
      request->send(200, "application/json", respons );
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
