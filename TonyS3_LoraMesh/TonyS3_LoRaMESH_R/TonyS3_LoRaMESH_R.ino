#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"

//---------------- Setting Parameter ----------------//
String Syncword = "10";  // Set value 0 to FF
//---------------------------------------------------//

uint16_t timeout = 0;
char charbuff[40];   // char array buffer
String stringbuff;   // string buffer

uint8_t response[200];

uint8_t len = MAX_RX_BUF_LEN;

void setup() {
  Serial.begin(115200);
  
  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT); //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  Serial.println();

  /* Set Syncword  */
  // timeout = 1000;
  // if(TonyLORA.setSyncword(Syncword, timeout)) Serial.println("Set up syncword successfully");
  // else Serial.println("Set syncword fail");
  // Serial.println();


  // /* Please reset the module after set Syncword  */
  // TonyLORA.reset();
  // Serial.println("Reset the module successfully");
  // Serial.println();

  // Serial.println("Testing send command to the module...");
  // TonyLORA.getModuleInfo();

  //set freq
  Serial.println(TonyLORA.setFrequency(915000000) ? "Freq OK" : "Freq Failed");

  //set tx power
  Serial.println(TonyLORA.setTxPower(10) ? "TX OK" : "TX Failed");

  //set spreading factor
  Serial.println(TonyLORA.setSpreadingFactor(8) ? "SF OK" : "SF Failed");

  //set bandwidth
  Serial.println(TonyLORA.setSignalBandwidth(250) ? "BW OK" : "BW Failed");

  TonyLORA.getConfig();
}

void loop() {
  /* receiving brodcast */
  /*  Maximum data size = 255 byte  */
  timeout = 20000; 
  if(TonyLORA.recv(response, &len) == 1){
    Serial.println("Successfully receiving message.");
    Serial.print("Data : ");
    delay(10);
    Serial.println((char*)response);
  } else Serial.println("Receiving message fail.");

  blink();
}

void blink(){
  Tony.digitalWrite(LED_BUILTIN, HIGH); //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(1000); 
  Tony.digitalWrite(LED_BUILTIN, LOW); //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(1000);
}
