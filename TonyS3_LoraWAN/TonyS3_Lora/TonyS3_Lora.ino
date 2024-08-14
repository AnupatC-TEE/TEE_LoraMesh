#include "TonyS_S3.h"
#include "TonySpace_LoRaWAN.h"
#include "HardwareSerial.h"

//---------------- Setting Parameter ----------------//
String Syncword = "10";  // Set value 0 to FF
//---------------------------------------------------//

uint16_t timeout = 0;

char response[200];

void setup() {
  Serial.begin(115200);
  
  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT); //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.setSlot(SLOT2);

  // Serial.println("Testing send command to the module...");
  // LoRaSerial.write("sip get_ver"); // Send command for asking firmware version of the chip

  /* Set Syncword  */
  timeout = 1000;
  if(TonyLORA.setSyncword(Syncword, timeout)) Serial.println("Set up syncword successfully");
  else Serial.println("Set syncword fail");
  Serial.println();


  /* Please reset the module after set Syncword  */
  TonyLORA.reset();
  delay(100);
  Serial.println("Reset the module successfully");
  // TonyLORA.begin("asdas", "asdasd", "ASdddd");
  // Serial.println("Init module successfully");
  // TonyLORA.sendAndGet("sip get_hw_model",response, 3000);
  // Serial.println(response);
  // TonyLORA.sendAndGet("sip get_hw_model",response, 3000);
  // Serial.println(response);
  // TonyLORA.getModuleInfo();


  /* Sending brodcast */
  // timeout = 2000;
  // String testdata = "5008754215"; //Please fill the data in pairs. Such as 10, 1020 or 102030  
  // /*                  testdata = data for sending (String)
  //                     Maximum data size = 255 byte      */
  // if(TonyLORA.sendBrodcast(testdata, timeout) == 1) // return 1 = successfully, 0 = fail
  // {
  //   Serial.println("Sending brodcast successfully.");
  // }
  // else Serial.println("Sending brodcast fail.");

}

void loop() {
  // put your main code here, to run repeatedly:
  Tony.digitalWrite(LED_BUILTIN, HIGH); //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(1000); 
  Tony.digitalWrite(LED_BUILTIN, LOW); //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(1000);
  // Serial.println("Test serial");

}
