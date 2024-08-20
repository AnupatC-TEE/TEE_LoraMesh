#include "tee_router.h"

TEE_Router::TEE_Router() {

}


String msgDecoder(char input) {
    JsonDocument doc;
    JsonDocument output;
    deserializeJson(doc, input);
    int key = 1;
    //key checking
    if (doc["key"] == key) {

    }

    //check nearby relay 
        //if not the same msg
            //store msg and continue
        //if repeat message return
    

    //shakehand
    if (doc["dest"] == -1) {
        //store rssi of this message to route table

        //set msg destination to source node

        //return our route table
        return shareRouteTable();
    }

    if (doc["dest"] != nodeID) return "";




}

String createShakeHandMsg(char* id) {
    JsonDocument msg;
    String output;

    msg["id"] = id;
    msg["key"] = 1;
    msg["dest"] = -1;

    serializeJson(msg, output);
    return output;
}

bool joinNetwork(char* id, char* network_id, char* password) {
    //boardcast this device id
    String msg = createShakeHandMsg(id,);
    send(msg);

    //listen nearby
    //loop: read and update route table
    int startTime = millis();
    while(millis() - startTime < 10000){
        //read message

        //decode message
    }

}

bool updateRoute() {
    //send update route

    //loop: repeat and update route table

}

//decode message if it suppose to do next
bool isMyNode() {
    //if this mesage is my node

        //update route

        //send back route

        //ack send back

    //if not flush message
}

bool updateRouteTable() {
    //store all direct route

    //compare with signal
        //self can reach = direct

        //compare signal from diffrent node
        //greater than self = hop

}

bool createRoute(uint8_t dest) {
    //look into route table
    //pick highest signal strength

    //create router message
}


String shareRouteTable() {
    //send back your route table
    return "";
}

bool bestRouteSend() {
    //re-arrage the sending path to source
}