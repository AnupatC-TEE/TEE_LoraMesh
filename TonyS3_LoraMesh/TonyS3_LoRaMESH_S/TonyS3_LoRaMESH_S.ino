#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"

uint16_t timeout = 1000;

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  // TonyLORA.setSlot(SLOT2);
  Serial.println();

  /* Please reset the module after set Syncword  */
  // TonyLORA.reset();
  // Serial.println("Reset the module successfully");
  // Serial.println();

  // Serial.println("Testing send command to the module...");
  // TonyLORA.getModuleInfo();

  //set freq
  Serial.println(TonyLORA.setFrequency(915000000) ? "Freq OK" : "Freq Failed");

  //set tx power
  Serial.println(TonyLORA.setTxPower(12) ? "TX OK" : "TX Failed");

  //set spreading factor
  Serial.println(TonyLORA.setSpreadingFactor(8) ? "SF OK" : "SF Failed");

  //set bandwidth
  Serial.println(TonyLORA.setSignalBandwidth(125) ? "BW OK" : "BW Failed");

  //set coding rate
  // Serial.println(TonyLORA.setCodingRate("4/8") ? "CR OK" : "CR Failed");

  //set preamble
  Serial.println(TonyLORA.setPremLenght(10) ? "PL OK" : "PL Failed");

  // TonyLORA.getConfig();
}

void loop() {
  /* Sending brodcast */
  String test = "Aerial";
  if (TonyLORA.send((uint8_t*)test.c_str(), test.length()) == 1)  // return 1 = successfully, 0 = fail
  {
    Serial.println("Sending brodcast successfully.");
    blink();
  } else Serial.println("Sending brodcast fail.");
}

void blink() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);  //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(1000);
  Tony.digitalWrite(LED_BUILTIN, LOW);  //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(5000);
}