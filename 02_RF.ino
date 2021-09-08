//********************************************************************************************
// RF TRANSMISSION HANDLING
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
short OUT_RF_COMM_PROTOCOL =  0;
short OUT_RF_COMM_PULSELENGHT = 0;
short OUT_RF_COMM_REPEATTRANSMIT =  0;

uint8_t IN_RF_COMM_PIN    = D3;
uint8_t OUT_RF_COMM_PIN   = D4;
int  OUT_RF_COMM_CODE =  0;
short  OUT_RF_COMM_CODE_LEN =  0;

//********************************************************************************************
// Variables
//********************************************************************************************
RCSwitch txs = RCSwitch();
RCSwitch rxs = RCSwitch();

//********************************************************************************************
// Methods
//********************************************************************************************
void InitRF()
{
  Serial.printf("[RFInit] Setting up RF Port ");
  Serial.printf("Transmission Pin = %s ",(String)OUT_RF_COMM_PIN);
  Serial.printf("Receive Pin = %s ",(String)IN_RF_COMM_PIN);
  Serial.printf("Protocol = %s ",(String)OUT_RF_COMM_PROTOCOL);
  Serial.printf("Pulse Lenght = %s ",(String)OUT_RF_COMM_PULSELENGHT);
  Serial.printf("Repeat times = %s ",(String)OUT_RF_COMM_REPEATTRANSMIT);
  Serial.printf("Code = %s ",(String)OUT_RF_COMM_CODE);
  Serial.printf("Code Lenght = %s ",(String)OUT_RF_COMM_CODE_LEN);
  Serial.println("");
  
  rxs.enableReceive(digitalPinToInterrupt(IN_RF_COMM_PIN));
  
  txs.enableTransmit(OUT_RF_COMM_PIN);
  txs.setProtocol(OUT_RF_COMM_PROTOCOL);
  txs.setPulseLength(OUT_RF_COMM_PULSELENGHT);
  txs.setRepeatTransmit(OUT_RF_COMM_REPEATTRANSMIT);
}

void ReceiveRF()
{
  if (rxs.available()) 
  {
    Serial.println("[ReceiveRF] Something is arrived");
    printFormattedData(rxs.getReceivedValue(), rxs.getReceivedBitlength(), rxs.getReceivedDelay(), rxs.getReceivedRawdata(),rxs.getReceivedProtocol());
    rxs.resetAvailable();
  }
}

void ExecuteRF()
{
  if (OpenGateRequestedByAlexa || OpenGateRequestedByButton)
  {
    txs.send(OUT_RF_COMM_CODE,OUT_RF_COMM_CODE_LEN);
    Serial.println("[ExecuteRF] Code Sent");

    OpenGateRequestedByAlexa =false;
    OpenGateRequestedByButton = false;

    LastCommandMillis = millis();
    PowerOnLedFixed =true;
  }
}




static const char* bin2tristate(const char* bin);
static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength);

void printFormattedData(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) 
{
  const char* b = dec2binWzerofill(decimal, length);
  Serial.print("[ReceiveRF]");
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" (");
  Serial.print( length );
  Serial.print("Bit) Binary: ");
  Serial.print( b );
  Serial.print(" Tri-State: ");
  Serial.print( bin2tristate( b) );
  Serial.print(" PulseLength: ");
  Serial.print(delay);
  Serial.print(" microseconds");
  Serial.print(" Protocol: ");
  Serial.println(protocol);
  
  Serial.print("Raw data: ");
  for (unsigned int i=0; i<= length*2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.println();
}

static const char* bin2tristate(const char* bin) 
{
  static char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') 
  {
    if (bin[pos]=='0' && bin[pos+1]=='0') 
    {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') 
    {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') 
    {
      returnValue[pos2] = 'F';
    } else 
    {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength) 
{
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) 
  {
    bin[32+i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) 
  {
    if (j >= bitLength - i) 
    {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    } else 
    {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}
