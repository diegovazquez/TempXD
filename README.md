# TempXD
TempXD es un logger (registrador de datos) de temperatura para la realización de cerveza, pensado para el sistema de 3 ollas, también esta pensado para poder remplazar los termómetros de la misma

## Estado
TempXD se encuentra en su desarrollo inicial y no se recomienda su uso.

## El nombre
El nombre del dispositivo IOT hace honor a 2 cosas: Al Monkey Island con su bebida GrogXD y el echo de usar una referencia a una aventura grafica de lucas art es en honor al excelente software brew-o-matic http://brew-o-matic.com.ar

## Librerias

* [WiFiManager](https://github.com/vitotai/WiFiManager)
* [OneWire](https://github.com/PaulStoffregen/OneWire)
* [TimeLib](https://github.com/PaulStoffregen/Time)
* [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

# Hardware

* NodeMCU - ESP8266EX ESP12F-4MB
* Display Lcd 2004 Backlight 20x4 
* Serie I2c (para el display)
* DS18B20 Sumergible (3 en total)
* 4.7k Resistor
* 1 swich

# Funcionalidad

## Configuracion

Ver configuration.h

## Logging Remoto

Se puede almacenar la informacion en Thingspeak

## Logging Local

El almacenamiento de datos locales se realiza en formato CSV.


