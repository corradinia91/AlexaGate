//********************************************************************************************
// WIFI HANDLING
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
String WIFI_SSID =  "";
String WIFI_PASSWORD =  "";
int WIFI_FIXED_IP;
String WIFI_IP =  "";
String WIFI_SUBNET =  "";
String WIFI_GATEWAY =  "";
String WIFI_DNS1 =  "";
String WIFI_DNS2 =  "";

//********************************************************************************************
// Variables
//********************************************************************************************
WiFiEventHandler disconnectedEventHandler;
WiFiEventHandler gotIpEventHandler;

//********************************************************************************************
// Methods
//********************************************************************************************
void InitWifi()
{
  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
  {
      Serial.printf("[InitWifi] Connected to SSID: %s with IP address: %s Subnet %s Gateway %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str(),WiFi.subnetMask().toString().c_str(),WiFi.gatewayIP().toString().c_str());
      WifiConnected =true;
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
  {
    Serial.println("[InitWifi] Disconnected");
  });
  
 if(ConfigMode)
 {
    IPAddress local_IP(192,168,1,2);
    IPAddress gateway(192,168,1,1);
    IPAddress subnet(255,255,255,0);

    Serial.print("[InitWifi] Setting AP Configuration configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("[InitWifi] Setting AP ... ");
    Serial.println(WiFi.softAP("CancelloTemp") ? "Ready" : "Failed!");

    Serial.print("AP IP address = %s ");
    Serial.print(WiFi.softAPIP());
    Serial.println();
 }  
else
{
      Serial.printf("[InitWifi] Trying to connect to %s with password %s", WIFI_SSID, WIFI_PASSWORD);
      Serial.println("");
       if (WIFI_FIXED_IP)
       {
          IPAddress ip(getByteFromString(WIFI_IP,'.',0),getByteFromString(WIFI_IP,'.',1),getByteFromString(WIFI_IP,'.',2),getByteFromString(WIFI_IP,'.',3));
          IPAddress subnet(getByteFromString(WIFI_SUBNET,'.',0),getByteFromString(WIFI_SUBNET,'.',1),getByteFromString(WIFI_SUBNET,'.',2),getByteFromString(WIFI_SUBNET,'.',3));
          IPAddress gateway(getByteFromString(WIFI_GATEWAY,'.',0),getByteFromString(WIFI_GATEWAY,'.',1),getByteFromString(WIFI_GATEWAY,'.',2),getByteFromString(WIFI_GATEWAY,'.',3));
          IPAddress dns1(getByteFromString(WIFI_DNS1,'.',0),getByteFromString(WIFI_DNS1,'.',1),getByteFromString(WIFI_DNS1,'.',2),getByteFromString(WIFI_DNS1,'.',3));
          IPAddress dns2(getByteFromString(WIFI_DNS2,'.',0),getByteFromString(WIFI_DNS2,'.',1),getByteFromString(WIFI_DNS2,'.',2),getByteFromString(WIFI_DNS2,'.',3));

          if(WIFI_IP.length()>0 and WIFI_DNS1.length()>0 and WIFI_DNS2.length()>0 and WIFI_GATEWAY.length()>0 and WIFI_SUBNET.length()>0)
           WiFi.config(ip,gateway,subnet,dns1,dns2);
           else if(WIFI_IP.length()>0  and WIFI_GATEWAY.length()>0 and WIFI_SUBNET.length()>0)
           WiFi.config(ip,gateway,subnet);
           else
           WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
           
       }

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

}

byte getByteFromString(String str, char sep, int index)
{
 int found = 0;
 int strIdx[] = { 0, -1 };
 int maxIdx = str.length() - 1;

 for (int i = 0; i <= maxIdx && found <= index; i++)
 {
    if (str.charAt(i) == sep || i == maxIdx)
    {
      found++;
      strIdx[0] = strIdx[1] + 1;
      strIdx[1] = (i == maxIdx) ? i+1 : i;
    }
 }
 return found > index ? (byte)str.substring(strIdx[0], strIdx[1]).toInt() : 0;
}
