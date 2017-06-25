
WiFiClient client;

void thingspeakUpdate() {
  if (client.connect(THINGSPEAK_SERVER, 80)) {
    // Construct API request body
    String body = "field1=";
    body += String(tempLiquor);
    body += "&field2=";
    body += String(tempMash);
    body += "&field3=";
    body += String(tempBoil);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + String(THINGSPEAK_WRITE_API_KEY) + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();
}
