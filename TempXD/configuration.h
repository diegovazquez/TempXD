// WIFI
#define WIFI_MODE                   "JOIN"                // JOIN (configure in code) // MANAGER
#define WIFI_AP_MANAGER             "MashLoggerConfig"    // AP Name For mode MANAGER
#define WIFI_NAME                   "WifiName"          // AP Name For mode JOIN
#define WIFI_PASS                   "WifiPass"            // AP Password For mode JOIN


// Sensor ID
#define SENSOR_ID_LIQUOR            "28FFF47BA815046C"
#define SENSOR_ID_MASH              "28FF0268A81501D9"
#define SENSOR_ID_BOIL              "28FF2DE143160468"


// Log to thingspeak
#define THINGSPEAK_ENABLE                             true                    // Enable Show temperature in serial console
#define THINGSPEAK_UPDATE_EVERY_X_SECONDS             60
#define THINGSPEAK_SERVER                             "api.thingspeak.com"
#define THINGSPEAK_WRITE_API_KEY                      ""

// Local Logger
#define LOCAL_LOGGER_RECORD_TEMP_EVERY_X_SECONDS      60    // if 60 = 1 record x minute
#define LOCAL_LOGGER_MAX_RECORDS_X_FILE               720   // if 60 & 120 = 12 hours max

// Time Server
#define NTP_SERVER_NAME             "time.nist.gov"   // Time Server
#define TIME_ZONE                   -3                // Time Zone
#define NTP_UDP_LOCAL_PORT          8888              // Local UDP Port
#define NTP_RESPONSE_TIMEOUT        2500              // Timeout in ms
#define NTP_SYNC_INTERVAL           600               // Sync every N seconds

// Sensor Conf
#define GET_TEMP_EVERY_X_SECONDS    5                 //
#define ONE_WIRE_BUS                2                 // DS18B20 on arduino pin2 corresponds to D4 on physical board of NodeMCU
#define TEMPERATURE_PRECISION       12                // DS18B20 Temperature presition set global resolution to 9, 10, 11, or 12 bits

// LOG TEMP TO SERIAL
#define SERIAL_TEMP_LOG_ENABLE      true              // Enable Show temperature in serial console

// Display Conf
#define DISPLAY_IC2_ENABLE          true              // Enable Display
#define DISPLAY_IC2_ADDRESS         0x3F              // Display Address

// Webserver Conf
#define WEBSERVER_PORT              80                // Enable Display

