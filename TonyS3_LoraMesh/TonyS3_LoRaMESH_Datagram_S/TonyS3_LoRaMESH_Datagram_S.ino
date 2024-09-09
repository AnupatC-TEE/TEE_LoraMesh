#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"
// #include <RHRouter.h>
// #include <RHMesh.h>;
#include <RHReliableDatagram.h>

#define BRIDGE_ADDRESS 1 
#define NODE_ADDRESS 3 

RHReliableDatagram *handler;

char buf[MAX_RX_BUF_LEN];
uint8_t data[] = "Hello from node";
uint8_t res;
int counter = 0;


void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  handler = new RHReliableDatagram(TonyLORA, NODE_ADDRESS);
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

  // //set cad_mode
  Serial.println(TonyLORA.setCAD(1) ? "CAD OK" : "CAD Failed");

  //set rx_continue
  Serial.println(TonyLORA.setRxContinuous(1) ? "RX_CON OK" : "RX_CON Failed");

  // TonyLORA.getConfig();

  Serial.println("TonyS76S Send : ready");

}
String test_data;
void loop() {
  // put your main code here, to run repeatedly:
  test_data = "Alecchino "+ String(counter++);
  Serial.println(test_data.length());
  // res = handler->sendtoWait(data, sizeof(data), BRIDGE_ADDRESS);
  res = handler->sendtoWait((uint8_t*)test_data.c_str(), (uint8_t)test_data.length(), BRIDGE_ADDRESS);
  Serial.println(res ? "Res ok" : "Failed res");
  // delay(1000);
  // Serial.println(ESP.getFreeHeap());
}
