//********************************************************************************************
// MAIN ARDUINO CYCLE
//********************************************************************************************
void setup() 
{
  delay(TAKEOFF_TIME);
  Serial.begin(SERIAL_BAUDRATE);
  Serial.print("**** [Startup] Board is starting up. Firmware version "); Serial.print(FIRMWARE_VERSION); Serial.print(" ****\n");
  InitIO();
  InitEEPROM();
  InitWifi();
  InitRF();
  InitSinric();
  InitWebServer();
  Serial.println("**** [Startup] Completed ****");
}

void loop() 
{
  ExecuteSinric();
  ReceiveRF();
  ExecuteRF();
  ExecuteIO();
  ExecuteWebServer();
  ExecuteEEPROM();
}
