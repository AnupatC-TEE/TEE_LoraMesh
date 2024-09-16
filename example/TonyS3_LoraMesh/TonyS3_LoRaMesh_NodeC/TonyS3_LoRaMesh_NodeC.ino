#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"
#include <RHRouter.h>
#include <RHMesh.h>

// #define RH_TEST_NETWORK 1

#define BRIDGE_ADDRESS 3  // address of the bridge ( we send our data to, hopefully the bridge knows what to do with our data )
#define RXTIMEOUT 3000    // it is roughly the delay between successive transmissions

// Class to manage message delivery and receipt, using the driver declared above
RHMesh *manager;

char buf[MAX_RX_BUF_LEN];
uint8_t data[] = "Hello back from bridge";
uint8_t res;

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  TonyLORA.reset();

  manager = new RHMesh(TonyLORA, BRIDGE_ADDRESS); 

  if (!manager->init()) {
    Serial.println(F("init failed"));
  } else {
    Serial.println("init done");
  }

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

  Serial.println("TonyS76S Recv : ready");
}

void loop() {
  uint8_t len = sizeof(buf);
  uint8_t from;
  uint8_t dest;
  uint8_t id;
  uint8_t flag;
  if (manager->recvfromAck((uint8_t *)buf, &len, &from, &dest, &id, &flag)) {
    Serial.print("request from node n.");
    Serial.print(from);
    Serial.print(": ");
    Serial.print((char *)buf);
    Serial.print(" dest: ");
    Serial.print(dest);
    Serial.print(" id: ");
    Serial.print(id);
    Serial.print(" flag: ");
    Serial.print(flag);
    Serial.print(" rssi: ");
    Serial.println(TonyLORA.lastRssi());
    blink();
    memset(buf, 0 ,sizeof(buf));
  }
  delay(25);
}



void blink() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);  //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(500);
  Tony.digitalWrite(LED_BUILTIN, LOW);  //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(100);
}
