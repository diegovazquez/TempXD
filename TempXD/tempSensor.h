#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices; //Number of temperature devices found
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

float tempLiquor;
float tempMash;
float tempBoil;


// function to print a device address
void tempSensorPrintAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void tempSensorStart() {
  // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++)
  {
      // Search the wire for address
      if(sensors.getAddress(tempDeviceAddress, i))
      {
          Serial.print("Found device ");
          Serial.print(i, DEC);
          Serial.print(" with address: ");
          tempSensorPrintAddress(tempDeviceAddress);
          Serial.println();
    
          Serial.print("Setting resolution to ");
          Serial.println(TEMPERATURE_PRECISION, DEC);
    
          // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
          sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
    
          Serial.print("Resolution actually set to: ");
          Serial.print(sensors.getResolution(tempDeviceAddress), DEC); 
          Serial.println();
      } else  {
          Serial.print("Found ghost device at ");
          Serial.print(i, DEC);
          Serial.print(" but could not detect address. Check power and cabling");
      } 
  } 
}


void getTempFromSensors() {
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  if (SERIAL_TEMP_LOG_ENABLE == true) { Serial.print("Requesting temperatures..."); }
  sensors.requestTemperatures(); // Send the command to get temperatures
  if (SERIAL_TEMP_LOG_ENABLE == true) { Serial.println("DONE"); }  

  float temperatures[numberOfDevices];
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
    {
      float temp = sensors.getTempC(tempDeviceAddress);
      // Output the device ID
      if (SERIAL_TEMP_LOG_ENABLE == true) { 
        Serial.print("Temperature for device ");
        Serial.print(i,DEC);     
        Serial.print(": ");
        Serial.println(temp);
      }
      if ( i == 0 ) { tempLiquor = temp ;}   
      if ( i == 1 ) { tempMash = temp ;}   
      if ( i == 2 ) { tempBoil = temp ;} 
    }   
  }  
}


