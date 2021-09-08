//********************************************************************************************
// EEPROM HANDLING - TO BE IMPLEMENTED
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************

//********************************************************************************************
// Variables
//********************************************************************************************

//********************************************************************************************
// Methods
//********************************************************************************************
void InitEEPROM()
{
   Serial.println("[InitEEPROM] Getting Data");
   EEPROM.begin(MAX_EEPROM_SIZE);
   
   DynamicJsonDocument doc(MAX_EEPROM_SIZE);
   EepromStream eepromStream(0, MAX_EEPROM_SIZE);
   
   deserializeJson(doc, eepromStream);
   serializeJson(doc, Serial);
   Serial.println("");

    WIFI_FIXED_IP=doc["WIFI_FIXED_IP"];       
    WIFI_IP= (String)doc["WIFI_IP"];
    WIFI_SUBNET= (String)doc["WIFI_SUBNET"];
    WIFI_DNS1= (String)doc["WIFI_DNS1"];
    WIFI_DNS2= (String)doc["WIFI_DNS2"];
    WIFI_GATEWAY= (String)doc["WIFI_GATEWAY"];     
    WIFI_SSID=(String)doc["WIFI_SSID"];       
    WIFI_PASSWORD= (String)doc["WIFI_PASSWORD"];
    OUT_RF_COMM_PROTOCOL= (short)doc["OUT_RF_COMM_PROTOCOL"];
    OUT_RF_COMM_PULSELENGHT= (short)doc["OUT_RF_COMM_PULSELENGHT"];
    OUT_RF_COMM_REPEATTRANSMIT=(short)doc["OUT_RF_COMM_REPEATTRANSMIT"];
    OUT_RF_COMM_CODE = (int)doc["OUT_RF_COMM_CODE"];
    OUT_RF_COMM_CODE_LEN = (short)doc["OUT_RF_COMM_CODE_LEN"];
    APP_KEY=  (String)doc["APP_KEY"];
    APP_SECRET= (String)doc["APP_SECRET"];
    WEBSERVER_USERNAME = AsCharArray((String)doc["WEBSERVER_USERNAME"]);
    WEBSERVER_PASSWORD = AsCharArray((String)doc["WEBSERVER_PASSWORD"]);
    GATE_DEVICE_ID=(String)doc["GATE_DEVICE_ID"];
    FIXED_LAMP_TIME_DELAY =doc["FIXED_LAMP_TIME_DELAY"];
    BLINK_LAMP_TIME_DELAY =doc["BLINK_LAMP_TIME_DELAY"];
}

void ExecuteEEPROM()
{
  if (SaveEEPROMRequest)
  {
    Serial.println("[ExecuteEEPROM] Save Requested");
    SaveEEPROMRequest=false;

    DynamicJsonDocument doc(MAX_EEPROM_SIZE);

    doc["WIFI_FIXED_IP"] = (WIFI_FIXED_IP);
    doc["WIFI_IP"] = String(WIFI_IP);
    doc["WIFI_SUBNET"] = String(WIFI_SUBNET);
    doc["WIFI_GATEWAY"] = String(WIFI_GATEWAY);
    doc["WIFI_DNS1"] = String(WIFI_DNS1);     
    doc["WIFI_DNS2"] = String(WIFI_DNS2);     
    doc["WIFI_SSID"] = String(WIFI_SSID);
    doc["WIFI_PASSWORD"]= String(WIFI_PASSWORD);
    doc["OUT_RF_COMM_PROTOCOL"]=OUT_RF_COMM_PROTOCOL;
    doc["OUT_RF_COMM_PULSELENGHT"]=OUT_RF_COMM_PULSELENGHT;
    doc["OUT_RF_COMM_REPEATTRANSMIT"]=OUT_RF_COMM_REPEATTRANSMIT;
    doc["OUT_RF_COMM_CODE"]=OUT_RF_COMM_CODE;
    doc["OUT_RF_COMM_CODE_LEN"]=OUT_RF_COMM_CODE_LEN;
    doc["APP_KEY"]=String(APP_KEY);
    doc["APP_SECRET"]=String(APP_SECRET);
    doc["GATE_DEVICE_ID"]=String(GATE_DEVICE_ID);
    doc["WEBSERVER_USERNAME"]=String(WEBSERVER_USERNAME);
    doc["WEBSERVER_PASSWORD"]=String(WEBSERVER_PASSWORD);
    doc["FIXED_LAMP_TIME_DELAY"]=FIXED_LAMP_TIME_DELAY;
    doc["BLINK_LAMP_TIME_DELAY"]=BLINK_LAMP_TIME_DELAY;

   EepromStream eepromStream(0, MAX_EEPROM_SIZE);
   serializeJson(doc, eepromStream);
   
   EEPROM.commit();

  deserializeJson(doc, eepromStream);
  serializeJson(doc, Serial);
  Serial.println("");
    
  }
}
