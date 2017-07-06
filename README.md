# TempXD
TempXD es un logger (registrador de datos) de temperatura para la realización de cerveza, pensado para el sistema de 3 ollas, también esta pensado para poder remplazar los termómetros de la misma

## Estado
TempXD se encuentra en su desarrollo inicial y no se recomienda su uso.

## El nombre
El nombre del dispositivo IOT hace honor a 2 cosas: Al Monkey Island con su bebida GrogXD y el echo de usar una referencia a una aventura grafica de lucas art es en honor al excelente software brew-o-matic http://brew-o-matic.com.ar

## Librerias

* [WiFiManager w/ESPAsyncWebServer support](https://github.com/btomer/WiFiManager)
* [OneWire](https://github.com/PaulStoffregen/OneWire)
* [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
* [ESPAsyncWebServer] (https://github.com/me-no-dev/ESPAsyncWebServer)
* [ESPAsyncTCP] (https://github.com/me-no-dev/ESPAsyncTCP)
* [Time] (https://github.com/PaulStoffregen/Time) Rename Time.h to _Time.h
* [Dallas Temperature Control Library] (https://github.com/milesburton/Arduino-Temperature-Control-Library)

Podes encontrarlas en los extras/libraries.zip

# Hardware

* NodeMCU - ESP8266EX ESP12F-4MB
* Display Lcd 2004 Backlight 20x4 
* Serie I2c (para el display)
* DS18B20 Sumergible (3 en total)
* 4.7k Resistor

![Planos](https://github.com/diegovazquez/TempXD/raw/develop/extras/sketch.png)

# Funcionalidad

## Configuracion

Ver configuration.h

## Logging Remoto

Se puede almacenar la informacion en Thingspeak

## Logging Local

El almacenamiento de datos locales se realiza en formato CSV.

# Instalar

* [Arduino IDE - Support for ESP8266] (https://github.com/esp8266/Arduino)
* [Arduino ESP8266 filesystem uploader] (https://github.com/esp8266/arduino-esp8266fs-plugin)
