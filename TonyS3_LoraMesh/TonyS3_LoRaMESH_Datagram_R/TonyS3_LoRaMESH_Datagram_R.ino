#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"
// #include <RHRouter.h>
// #include <RHMesh.h>
// #include <RHDatagram.h>
#include <RHReliableDatagram.h>

#define BRIDGE_ADDRESS 1

char buf[MAX_RX_BUF_LEN];
uint8_t data[] = "Hello back from bridge";
uint8_t res;

RHReliableDatagram *handler;

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  handler = new RHReliableDatagram(TonyLORA, BRIDGE_ADDRESS);
  handler->init();
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

  //set cad_mode
  Serial.println(TonyLORA.setCAD(1) ? "CAD OK" : "CAD Failed");

  //set rx_continue
  Serial.println(TonyLORA.setRxContinuous(1) ? "RX_CON OK" : "RX_CON Failed");

  // TonyLORA.getConfig();

  Serial.println("TonyS76S Recv : ready");
}

uint8_t from, to, id, flag;
uint8_t len = sizeof(buf);

void loop() {
  // Serial.println("(1)");
  res = handler->recvfromAck((uint8_t *)buf, &len, &from, &to, &id, &flag);
  if (res) {
    Serial.println("Receive message");
    Serial.print("Buffer: ");
    Serial.println(buf);
  }
  delay(100);
  // Serial.println("(2)");
}
