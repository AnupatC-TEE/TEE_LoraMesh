#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"

uint16_t timeout = 0;

uint8_t response[MAX_RX_BUF_LEN];

uint8_t len = sizeof(response);

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  Serial.println();

  // /* Please reset the module after set Syncword  */
  // TonyLORA.reset();
  // Serial.println("Reset the module successfully");
  // Serial.println();

  // Serial.println("Testing send command to the module...");
  // TonyLORA.getModuleInfo();

  //set freq
  Serial.println(TonyLORA.setFrequency(924000000) ? "Freq OK" : "Freq Failed");

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

  //set rx_continue
  Serial.println(TonyLORA.setRxContinuous(1) ? "RX_CON OK" : "RX_CON Failed");

  // TonyLORA.getConfig();
}

void loop() {
  /* receiving brodcast */
  if (TonyLORA.available()) Serial.println("message available");
  /*  Maximum data size = 255 byte  */
  if (TonyLORA.recv(response, &len)) {
    Serial.println("Successfully receiving message.");
    Serial.print("Data : ");
    delay(10);
    Serial.println((char*)response);
    blink();
    response[0] = '\0';
  } else {
    // Serial.println("Receiving message fail.");
    // Serial.println("No signal");
    delay(1000);
  }
}

void blink() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);  //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(500);
  Tony.digitalWrite(LED_BUILTIN, LOW);  //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(100);
}
