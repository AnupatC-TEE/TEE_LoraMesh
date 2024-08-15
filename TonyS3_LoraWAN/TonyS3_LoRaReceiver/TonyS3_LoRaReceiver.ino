#include "TonyS_S3.h"
#include "TonySpace_LoRaWAN.h"
#include "HardwareSerial.h"

//---------------- Setting Parameter ----------------//
String Syncword = "10";  // Set value 0 to FF
//---------------------------------------------------//

uint16_t timeout = 0;
char charbuff[40];   // char array buffer
String stringbuff;   // string buffer

char response[200];

void setup() {
  Serial.begin(115200);
  
  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT); //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.setSlot(SLOT2);
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

  Serial.println("Testing send command to the module...");
  TonyLORA.getModuleInfo();

  //set freq
  // TonyLORA.setFrequency(915000000);

  // TonyLORA.getRespond(response, 1000);
  // Serial.println(response);

  //set tx power

  //set spreading factor

  //set bandwidth

  TonyLORA.getConfig();


}

void loop() {
  /* receiving brodcast */
  /*  Maximum data size = 255 byte  */
  timeout = 20000; 
  if(TonyLORA.receiveBrodcast(charbuff, timeout) == 1) // return 1 = successfully, 0 = fail
  {
    Serial.print("Data : ");
    stringbuff = charbuff;  // Convert char to string
    // Serial.println(stringbuff);
    TonyLORA.decodingRawMsg(stringbuff);
    Serial.println(TonyLORA.lastMSG);
  }
  else Serial.println("Receiving brodcast fail.");
  charbuff[0] = '\0';  // Clear char array buffer

  blink();
}

void blink(){
  Tony.digitalWrite(LED_BUILTIN, HIGH); //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(1000); 
  Tony.digitalWrite(LED_BUILTIN, LOW); //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(1000);
}
