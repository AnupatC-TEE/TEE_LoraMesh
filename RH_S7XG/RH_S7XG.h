#include "RHGenericDriver.h"
#include "TonySpace_LoRaWAN.h"

class RH_S7XG : public RHGenericDriver, public TONY_LORA {
    public:
        RH_S7XG();
        RH_S7XG(uint8_t n_slot, String syncword);
        virtual bool init(String deveui="", String appeui="", String appkey="");
        // virtual bool available();
        virtual bool send(const uint8_t* data, uint8_t len);
        virtual bool recv(uint8_t* buf, uint8_t* len);
        bool available();
        // virtual void waitAvailable();
    private:

};

