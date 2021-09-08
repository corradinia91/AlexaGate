//********************************************************************************************
// Webserver Handling
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
uint8_t WEBSEWRVER_PORT =  200;
char* WEBSERVER_USERNAME  = "Admin";
char* WEBSERVER_PASSWORD  = "Admin";

//********************************************************************************************
// Variables
//********************************************************************************************
ESP8266WebServer server(WEBSEWRVER_PORT);


//********************************************************************************************
// Methods
//********************************************************************************************

void InitWebServer()
{   
  if (ConfigMode)
  {
    WEBSERVER_USERNAME ="Admin";
    WEBSERVER_PASSWORD="Admin";
  }
  Serial.printf("[InitWebserver] Configuring WebServer ");
  Serial.printf("Username = %s ",(String)WEBSERVER_USERNAME);
  Serial.printf("Password= %s ",(String)WEBSERVER_PASSWORD);
  Serial.printf("Port= %s ",(String)WEBSEWRVER_PORT);
  Serial.println("");
  
  MDNS.begin("Cancello");

   server.on("/", []()
   {
    server.send(200, "text/html", "Welcome to Cancello website");
   });

   server.on("/info", []()
   {
      String stat = "Sinric: ";
      stat.concat(SinricConnected?"Connected ":"Disconnected ");
      stat.concat("Wifi: ");
      stat.concat(WifiConnected?"Connected ":"Disconnected ");
      stat.concat("Config Mode: ");
      stat.concat(ConfigMode?"Active ":"Not Active ");

      server.send(200,"text/html",stat);
   });

    server.on("/open", []()
   {
      OpenGateRequestedByAlexa =true;
      server.send(200, "text/json", "{success:true}");
   });

    server.on("/config/set", HTTP_POST, []()
    {
      if (!server.authenticate(WEBSERVER_USERNAME,WEBSERVER_PASSWORD))
      return server.requestAuthentication();

      DynamicJsonDocument doc(MAX_EEPROM_SIZE);
      deserializeJson(doc, server.arg("plain"));

      Serial.println(server.arg("plain"));

      WIFI_FIXED_IP=doc["WIFI_FIXED_IP"];       
      WIFI_IP= (String)doc["WIFI_IP"];
      WIFI_SUBNET= (String)doc["WIFI_SUBNET"];
      WIFI_GATEWAY= (String)doc["WIFI_GATEWAY"];   
      WIFI_DNS1= (String)doc["WIFI_DNS1"];  
      WIFI_DNS2= (String)doc["WIFI_DNS2"];  
      WIFI_SSID=(String)doc["WIFI_SSID"];       
      WIFI_PASSWORD= (String)doc["WIFI_PASSWORD"];
      OUT_RF_COMM_PROTOCOL= (short)doc["OUT_RF_COMM_PROTOCOL"];
      OUT_RF_COMM_PULSELENGHT= (short)doc["OUT_RF_COMM_PULSELENGHT"];
      OUT_RF_COMM_REPEATTRANSMIT=(short)doc["OUT_RF_COMM_REPEATTRANSMIT"];
      OUT_RF_COMM_CODE = (int)doc["OUT_RF_COMM_CODE"];
      OUT_RF_COMM_CODE_LEN = (short)doc["OUT_RF_COMM_CODE_LEN"];
      APP_KEY=  (String)doc["APP_KEY"];
      APP_SECRET= (String)doc["APP_SECRET"];
      GATE_DEVICE_ID=(String)doc["GATE_DEVICE_ID"];
      WEBSERVER_USERNAME= AsCharArray((String)doc["WEBSERVER_USERNAME"]);
      WEBSERVER_PASSWORD= AsCharArray((String)doc["WEBSERVER_PASSWORD"]);
      BLINK_LAMP_TIME_DELAY =doc["BLINK_LAMP_TIME_DELAY"];
      FIXED_LAMP_TIME_DELAY = doc["FIXED_LAMP_TIME_DELAY"];    

      SaveEEPROMRequest =true;

    server.send ( 200, "text/json", "{success:true}" );
    });

  server.begin();
}

void ExecuteWebServer()
{
  server.handleClient();
  MDNS.update();
}


char* AsCharArray(String str)
{
    if(str.length()!=0)
    {
        char *p = const_cast<char*>(str.c_str());
        return p;
    }
}
