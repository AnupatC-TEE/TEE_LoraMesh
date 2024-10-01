# TonySpace LoRaMesh 
This library is originally from LoRaWAN and has beed retro fitted for RadioHead library for Mesh topology.

## Table of Contents
- [TonySpace LoRaMesh](#tonyspace-loramesh)
  - [Table of Contents](#table-of-contents)
  - [Prerequisite](#prerequisite)
  - [Installation](#installation)
  - [Usage](#usage)
    - [no mesh protocol](#no-mesh-protocol)
    - [mesh protocol](#mesh-protocol)
  - [Technical debt](#technical-debt)

## Prerequisite
https://github.com/epsilonrt
Noted: RHAsk.cpp and RHAsk.h need to be remove to be able to compile

## Installation
1. Clone this project
2. Open folder Library
3. Copy Radiohead, LoRaWAN and LoRaMesh to arduino libraries folder

## Usage
This repo have 2 lora library. LoRaWAN and LoRaMESH, LoRaMESH is improved version of LoRaWAN with added configuration function and mesh functionality folk from RadioHead library.
### no mesh protocol
Header
```
#include "TonyS_S3.h"
\\ #include "TonySpace_LoRaWAN.h"
#include "TonySpace_LoRaMesh.h"
```
init(setup)
```
Tony.begin();
TonyLORA.setSlot(SLOT2);
```
Sending data
```
String testdata = "5008754215"; //Please fill the data in pairs. Such as 10, 1020 or 102030  
  /*                  testdata = data for sending (String)
                      Maximum data size = 255 byte      */
if(TonyLORA.sendBrodcast(testdata, timeout) == 1) // return 1 = successfully, 0 = fail
{
  Serial.println("Sending brodcast successfully.");
} else Serial.println("Sending brodcast fail.");
```
Receive data
```
if(TonyLORA.receiveBrodcast(charbuff, timeout) == 1) // return 1 = successfully, 0 = fail
{
  Serial.print("Data : ");
  stringbuff = charbuff;  // Convert char to string
  // Serial.println(stringbuff);
  TonyLORA.decodingRawMsg(stringbuff);
  Serial.println(TonyLORA.lastMSG);
} else Serial.println("Receiving brodcast fail.")
```
### mesh protocol
Header
```
#include "TonyS_S3.h"
#include "TonySpace_LoRaMesh.h"
#include <RHRouter.h>
#include <RHMesh.h>
```
init(setup)
```
#define TXINTERVAL 40000
unsigned long nextTxTime;
int rt_interval = TXINTERVAL;

#define BRIDGE_ADDRESS 3 
#define NODE_ADDRESS 1 



RHMesh *manager;
```
sending
```
if (millis() > nextTxTime) {
  uint8_t data[] = "Node 1! Acheron";
  uint8_t res;

  nextTxTime += rt_interval;
  Serial.print("Sending to bridge n .");
  Serial.print(BRIDGE_ADDRESS);
  Serial.print(" res=");

  // A route to the destination will be automatically discovered.
  res = manager->sendtoWait(data, sizeof(data), BRIDGE_ADDRESS);
  Serial.println(res);
  if (res == RH_ROUTER_ERROR_NONE) {
    // Data has been reliably delivered to the next node.
    // now we do...
    Serial.println("Success route");
    rt_interval = TXINTERVAL;
  } else {
    // Data not delivered to the next node.
    Serial.println("sendtoWait failed. Are the bridge/intermediate mesh nodes running?");
    rt_interval = rt_interval/2;
    nextTxTime -= rt_interval;
  }
}
```
receive
```
uint8_t* len;
uint8_t from;
char buf[255];
if (manager->recvfromAck((uint8_t *)buf, len, &from)) {
  Serial.print("message from node n.");
  Serial.print(from);
  Serial.print(": ");
  Serial.print((char *)buf);
  Serial.print(" rssi: ");
  Serial.println(TonyLORA.lastRssi());
}
```



## Technical debt
* ~~some time on receiver side if message is reponse error other than 'radio_err' the program will still run and the cause memory conflict by rawMsgDecoder on can't get hold enough information to split message to smaller chunk~~
* chip do not have message incoming store without calling command, creator of this library do work around by enable continuous rx mode and detect incoming serial then store latest message in .
* continuous rx mode do not have buffer(FIFO) due to work around only store the last message, there is still a way to fix by adding callback function after each message has been decode, or inceasing loop frequency to not miss a single message.
* In decodingRawMsg() and decodingRawCon() still working with data in from of char array while Radiohead library work with uint8_t data as standard data type every character than can't be type will result in error such as 0 value of uint8_t and NULL pointer of char array.