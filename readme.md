# TonySpace LoRaMesh 
This library is originally from LoRaWAN and has beed retro fitted for RadioHead library for Mesh topology.

## Prerequisite
https://github.com/epsilonrt
Noted: RHAsk.cpp and RHAsk.h need to be remove to be able to compile

## Technical debt
* ~~some time on receiver side if message is reponse error other than 'radio_err' the program will still run and the cause memory conflict by rawMsgDecoder on can't get hold enough information to split message to smaller chunk~~
* chip do not have message incoming without calling command, creator of this make work around by enable continuous rx mode and detect incoming serial.
* continuous rx mode do not have buffer(FIFO) due to work around only store the last message, there is still a way to fix by adding callback function after each message has been decode, or inceasing loop frequency to not miss a single message.
* In decodingRawMsg() and decodingRawCon() still working with data in from of char array while Radiohead library work with uint8_t data as standard data type every character than can't be type will result in error such as 0 value of uint8_t and NULL pointer of char array.