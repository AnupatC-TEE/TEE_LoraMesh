#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"
#include <RHRouter.h>
#include <RHMesh.h>

#define TXINTERVAL 15000  // delay between successive transmissions
unsigned long nextTxTime;

// In this small artifical network of 4 nodes,
#define BRIDGE_ADDRESS 4  // address of the bridge ( we send our data to, hopefully the bridge knows what to do with our data )
#define NODE_ADDRESS 3    // address of this node

// Class to manage message delivery and receipt, using the driver declared above
RHMesh *manager;

// message buffer
char buf[255];
uint8_t data[] = "Aello World!";
// String test_data = "Hello World!";
uint8_t res;

uint16_t timeout = 1000;
int counter = 0;

void setup() {
  Serial.begin(115200);

  Tony.begin();  //----  begin Library
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);  //----  Set Pin IO12 (LED_BUILTIN) to OUTPUT

  TonyLORA.init(SLOT2);
  TonyLORA.reset();
  // TonyLORA.setSlot(SLOT2);
  manager = new RHMesh(TonyLORA, NODE_ADDRESS);

  if (!manager->init()) {
    Serial.println(F("init failed"));
  } else {
    Serial.println("init done");
  }

  Serial.println();

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
  nextTxTime = millis();
}

void loop() {

  mesh();
}

void mesh() {
  if (millis() > nextTxTime) {
    String test = "Acheron";

    nextTxTime += TXINTERVAL;
    Serial.print("Sending to bridge n .");
    Serial.print(BRIDGE_ADDRESS);
    Serial.print(" res=");

    // A route to the destination will be automatically discovered.
    res = manager->sendtoWait(data, sizeof(data), BRIDGE_ADDRESS);
    Serial.println(res);
    if (res == RH_ROUTER_ERROR_NONE) {
      // Data has been reliably delivered to the next node.
      // now we do...
      // Serial.println("Success route");
    } else {
      // Data not delivered to the next node.
      Serial.println("sendtoWait failed. Are the bridge/intermediate mesh nodes running?");
    }
  }

  // radio needs to stay always in receive mode ( to process/forward messages )
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager->recvfromAck((uint8_t *)buf, &len, &from)) {
    Serial.print("message from node n.");
    Serial.print(from);
    Serial.print(": ");
    Serial.print((char *)buf);
    Serial.print(" rssi: ");
    Serial.println(TonyLORA.lastRssi());
  }
}

void blink() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);  //---- Write HIGH to pin IO12 (LED_BUILTIN)
  delay(500);
  Tony.digitalWrite(LED_BUILTIN, LOW);  //---- Write LOW to pin IO12 (LED_BUILTIN)
  delay(100);
}