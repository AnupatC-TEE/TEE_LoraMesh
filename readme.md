# TonySpace LoRaMesh 
This library is originally from LoRaWAN and has beed retro fitted for RadioHead library for Mesh topology.

## Prerequisite
https://github.com/epsilonrt

## Technical debt
* ~~some time on receiver side if message is reponse error other than 'radio_err' the program will still run and the cause memory conflict by rawMsgDecoder on can't get hold enough information to split message to smaller chunk~~
* chip do not have message incoming without calling command, creator of this make work around by enable continuous rx mode and detect incoming serial.
* continuous rx mode do not have buffer(FIFO) due to work around only store the last message, there is still a way to fix by adding callback function after each message has been decode, or inceasing loop frequency to not miss a single message.
