// Require webServer.h
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER
#include <WiFiManager.h>          //https://github.com/btomer/WiFiManager WiFi Configuration Magic

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void startWifiManager(){
  // Start Wifi
  Serial.println("Starting Wifi connection"); 
  WiFiManager wifiManager;
  wifiManager.autoConnect(WIFI_AP_MANAGER);
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }   
  //if you get here you have connected to the WiFi
  Serial.println("Wifi connected"); 
} 


void startWifi(){
  int status;
  Serial.println("Starting Wifi connection"); 
  // attempt to connect to Wifi network:
  status = WiFi.begin(WIFI_NAME, WIFI_PASS);
  status = WiFi.waitForConnectResult();
  
  if (status != WL_CONNECTED) {
    Serial.println("Connection Failed");
    while (true) {}
  }

  Serial.println("Connected.");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
  Serial.print("Channel: ");
  Serial.println(WiFi.channel());
  Serial.print("Status: ");
  Serial.println(WiFi.status());
} 
