/*
Beer Liquor/Mash/Boil Temperature Logger
See exelent tutorial: https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html
*/

/* vars */
time_t lastTempUpdate = 0;                    // Last time to get temp 
time_t lastLocalLoggerUpdate = 0;             // Last time to white temp in local logger
time_t lastLocalLoggerLastRecordNumber = 0;   // Last time to white temp in local logger
time_t lastThingspeakUpdate = 0;              // Last time to white temp in local logger
boolean record = false;                       // Write in local logger
boolean recordWasEnabled = false;             // In the last loop record was enabled?
String  recordFileName;

/* Modules */
#include "configuration.h"
#include "tempSensor.h"
#include "wifi.h"
#include "SPIFFS.h"
#include "ntp.h"
#include "webServer.h"
#include "display.h"
#include "thingspeak.h"


void setup() {
  // start serial port
  Serial.begin(115200);
  Serial.println("Starting");
  Serial.println("Serial set to 115200");

  // Display a ap for configure wifi connection
  if (WIFI_MODE == "MANAGER") {
    startWifiManager();
  }
  // Join a preconfigured wifi
  if (WIFI_MODE == "JOIN") {
    startWifi();
  }

  // Start ntp sync
  ntpStart();

  // Start Filesystem
  startSPIFFS();

  // Configure Web Server
  webServerStart();
  
  // Start & configure sensors
  tempSensorStart();         
  // Start & configure display                              
  if (DISPLAY_IC2_ENABLE == true) { displayStart(); }     
}

void loop() {
  // update Clock
  time_t t = now();

  // Get sensor temp & show in display
  if ( now() > (lastTempUpdate + GET_TEMP_EVERY_X_SECONDS )) {
      Serial.print(t);
      Serial.print(" ");
      // Get temperature from sensors
      getTempFromSensors();
      // Show Sensors temps in IC2 Display
      if (DISPLAY_IC2_ENABLE == true) { displayTemperatures();}  
      lastTempUpdate = t;
  }


  
  if (record == true) {
    t = now();
    
    if ( recordWasEnabled == false ) {
        recordFileName = "/req/" + String(year(t)) + "-" + String(month(t)) + "-" + String(day(t)) + "_" + String(hour(t)) + "-" + String(minute(t)) + "-" + String(second(t)) + ".csv";
    }    
    
    // Check File Size      
    if (lastLocalLoggerLastRecordNumber < LOCAL_LOGGER_MAX_RECORDS_X_FILE) {
      // Record temp In file
      if ( t > (lastLocalLoggerUpdate + LOCAL_LOGGER_RECORD_TEMP_EVERY_X_SECONDS )) {
          Serial.print( recordFileName + " Write Local LOG...");
          File tempLog = SPIFFS.open(recordFileName, "a"); // Write the time and the temperature to the csv file
          if (!tempLog) {
            Serial.println("file open failed");
          }
          tempLog.print(year(t));
          tempLog.print("-");
          tempLog.print(month(t));
          tempLog.print("-");
          tempLog.print(day(t));
          tempLog.print(',');
          tempLog.print(hour(t));
          tempLog.print(":");
          tempLog.print(minute(t));
          tempLog.print(":");
          tempLog.print(second(t));
          tempLog.print(',');
          tempLog.print(String(tempLiquor));
          tempLog.print(',');
          tempLog.print(String(tempMash));        
          tempLog.print(',');
          tempLog.println(String(tempBoil));        
          tempLog.close();
          Serial.println("done");
          lastLocalLoggerUpdate = t;
          lastLocalLoggerLastRecordNumber = lastLocalLoggerLastRecordNumber + 1;
      }
    } else {
      Serial.println("File limit reached");
      record = false;
    }
    
    // Record on thingspeak
    if (THINGSPEAK_ENABLE == true) {
        if ( t > (lastThingspeakUpdate + THINGSPEAK_UPDATE_EVERY_X_SECONDS)) {
              thingspeakUpdate();
              lastThingspeakUpdate = t;
        }
    }
    //
    if ( recordWasEnabled != record) {
      if (DISPLAY_IC2_ENABLE == true) { 
        lcd.backlight(); // Turn on the backlight.   
      }
    }
      
  } else {
    // Record is disabled
    lastLocalLoggerLastRecordNumber = 0;
    if ( recordWasEnabled != record) {
      if (DISPLAY_IC2_ENABLE == true) { lcd.noBacklight(); };  // Turn off the backlight.  
    }
  }
  recordWasEnabled = record;
}

