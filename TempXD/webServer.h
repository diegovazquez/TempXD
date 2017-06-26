// Require wifi.h
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal

ESP8266WebServer server(WEBSERVER_PORT);


void handleRoot() {
  server.send(200, "text/plain", "Hola Humanoides!");
}

void handleStartStopRecord() {
  // update Clock
  time_t t = now();
  if ( record == false) {
    record = true;
  } else {
    record = false;
  }
  server.send(200, "application/json", "{ \"recording\" : " + String(record) + "}" );
}


void handleBasicData() {
  // update Clock
  time_t t = now();
  server.send(200, "application/json", "{ \"tempLiquor\": " + String(tempLiquor) + ", \"tempMash\": " + String(tempMash) + ", \"tempBoil\" : " + String(tempBoil) + ", \"time\" : " + String(t) + ", \"lastTempUpdate\" : " + String(lastTempUpdate) + ", \"recording\" : " + String(record) + "}" );
}


String getContentType(String filename) { // determine the filetype of a given filename, based on the extension
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  //else if (filename.endsWith(".csv")) return "text/csv";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  //Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
    if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
      path += ".gz";                                         // Use the compressed verion
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    //Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
  return false;
}

void handleNotFound() { // if the requested file or page doesn't exist, return a 404 not found error
  if (!handleFileRead(server.uri())) {        // check if the file exists in the flash memory (SPIFFS), if so, send it
    /*String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET)?"GET":"POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i=0; i<server.args(); i++){
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);*/
    server.send(404, "text/plain", "404: File Not Found");
  }
}

void webServerStart() {
  server.on("/", handleRoot);

  server.on("/getData.json", handleBasicData);
  server.on("/startStopRecord.json", handleStartStopRecord);

  /*server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });*/

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
