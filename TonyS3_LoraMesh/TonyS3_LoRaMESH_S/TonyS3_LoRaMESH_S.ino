#include "TonyS_S3.h"
// #include "TonySpace_LoRaWAN.h"
// #include "HardwareSerial.h"
// #include "RH_S7XG.h"

#include "TonySpace_LoRaMesh.h"

uint16_t timeout = 1000;
// RH_S7XG S76S;

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  // TonyLORA.setSlot(SLOT2);
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

  //set coding rate
  // Serial.println(TonyLORA.setCodingRate("4/8") ? "CR OK" : "CR Failed");

  // TonyLORA.getConfig();s
}

void loop() {
  /* Sending brodcast */
  timeout = 2000;
  String test = "Aerial";
  // String cvt = TonyLORA.stringToHex(test);
  if (TonyLORA.send((uint8_t*)test.c_str(), test.length()) == 1)  // return 1 = successfully, 0 = fail
  {
    Serial.println("Sending brodcast successfully.");
  } else Serial.println("Sending brodcast fail.");

  blink();
}

void blink() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);  //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(1000);
  Tony.digitalWrite(LED_BUILTIN, LOW);  //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(2000);
}