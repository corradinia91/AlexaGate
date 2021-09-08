//*******************************************************************************************
//                            GATE OPEN WITH ALEXA - SINRIC
//   
// Rev List:
// R1.0: Code refactoring
// R1.1: Bugfix
//
//
//*******************************************************************************************



//********************************************************************************************
// Global Variables
//********************************************************************************************
#define FIRMWARE_VERSION   "R1.1"
#define SERIAL_BAUDRATE 9600
#define TAKEOFF_TIME  6000
#define MAX_EEPROM_SIZE  2048

//********************************************************************************************
// Libraries
//********************************************************************************************
#include <RCSwitch.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <StreamUtils.h>

//********************************************************************************************
// Globally shared variables
//********************************************************************************************
long LastCommandMillis = millis();
bool OpenGateRequestedByAlexa =false;
bool OpenGateRequestedByButton =false;
bool PowerOnLedFixed=false;
bool PowerOnLedBlink=false;
bool PowerOnLedHeartBeat=false;
bool SaveEEPROMRequest =false;
bool ConfigMode =false;
bool WifiConnected = false;
bool SinricConnected= false;
