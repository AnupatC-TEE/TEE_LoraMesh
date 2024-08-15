#include "TonyS_S3.h"
#include "TonySpace_LoRaWAN.h"
#include "HardwareSerial.h"

//---------------- Setting Parameter ----------------//
String Syncword = "10";  // Set value 0 to FF
//---------------------------------------------------//

uint16_t timeout = 1000;

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


  /* Please reset the module after set Syncword  */
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
  /* Sending brodcast */
  timeout = 2000;
  String testdata = "5008754215"; //Please fill the data in pairs. Such as 10, 1020 or 102030  
  /*                  testdata = data for sending (String)
                      Maximum data size = 255 byte      */
  if(TonyLORA.sendBrodcast(testdata, timeout) == 1) // return 1 = successfully, 0 = fail
  {
    Serial.println("Sending brodcast successfully.");
  }
  else Serial.println("Sending brodcast fail.");

  blink();
}

void blink(){
  Tony.digitalWrite(LED_BUILTIN, HIGH); //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(3000); 
  Tony.digitalWrite(LED_BUILTIN, LOW); //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(1000);
}
