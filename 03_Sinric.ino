

//********************************************************************************************
// SINRIC CLOUD HANDLING
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
String APP_KEY ;     // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
String APP_SECRET;   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
String GATE_DEVICE_ID; // Should look like "5dc1564130xxxxxxxxxxxxxx"

//********************************************************************************************
// Variables
//********************************************************************************************

//********************************************************************************************
// Methods
//********************************************************************************************
void InitSinric()
{
  Serial.printf("[InitSinric] Configuring Sinric ");
  Serial.printf("App Key = %s ",APP_KEY);
  Serial.printf("App Secret = %s ",APP_SECRET);
  Serial.printf("Device ID = %s ",GATE_DEVICE_ID);
  Serial.println("");
  
  SinricProSwitch& mySwitch = SinricPro[GATE_DEVICE_ID];

  // set callback function to device
  mySwitch.onPowerState(onPowerState);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.println("[InitSinric] Connected"); SinricConnected=true; }); 
  SinricPro.onDisconnected([](){ Serial.println("[InitSinric] Disconnected"); SinricConnected =false; });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

bool onPowerState(const String &deviceId, bool &state)
{
  Serial.printf("[Sinric onPowerState] Device %s turned %s \r\n", deviceId.c_str(), state?"on":"off");
  OpenGateRequestedByAlexa = true;
  return true; 
}

void ExecuteSinric()
{
  SinricPro.handle();
}
