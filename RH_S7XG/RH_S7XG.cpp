#include "RH_S7XG.h"

#define RH_S7GX_MAX_LEN 200

RH_S7XG::RH_S7XG() {}

RH_S7XG::RH_S7XG(uint8_t n_slot){
    setSlot(n_slot);
}

bool RH_S7XG::available() {
    return msgAvailable();
}

bool RH_S7XG::init(String deveui, String appeui, String appkey) {
    return begin(deveui,appeui,appkey);
}

bool RH_S7XG::send(const uint8_t* data, uint8_t len) {
    if(len > RH_S7GX_MAX_LEN) return false;

    return sendBrodcast(String(*data), 2000);
}

bool RH_S7XG::recv(uint8_t* buf, uint8_t* len) {
    return receiveBrodcast(buf, 2000);
}