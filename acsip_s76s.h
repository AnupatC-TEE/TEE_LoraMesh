#pragma once
#include <Arduino.h>

// ----------------------------------------------------------------------------
// Commands
// ----------------------------------------------------------------------------

const char SIP_FACTORY_RESET[] PROGMEM =          "sip factory_reset";              // 3.1.1
const char SIP_GET_VER[] PROGMEM =                "sip get_ver";                    // 3.1.2
const char SIP_RESET[] PROGMEM =                  "sip reset";                      // 3.1.3
const char SIP_GET_HW_MODEL[] PROGMEM =           "sip get_hw_model";               // 3.1.4
const char SIP_SET_ECHO[] PROGMEM =               "sip set_echo %s";                // 3.1.5
const char SIP_SET_LOG[] PROGMEM =                "sip set_log %s";                 // 3.1.6
const char SIP_SLEEP[] PROGMEM =                  "sip sleep %d uart_on";           // 3.1.7
const char SIP_SET_BAUDRATE[] PROGMEM =           "sip set_baudrate %d %s";         // 3.1.8
const char SIP_GET_HW_MODEL_VER[] PROGMEM =       "sip get_hw_model_ver";           // 3.1.9
const char SIP_SET_GPIO_MODE[] PROGMEM =          "sip set_gpio_mode %c %d %d";     // 3.1.10
const char SIP_SET_GPIO[] PROGMEM =               "sip set_gpio %c %d %d";          // 3.1.11
const char SIP_GET_GPIO[] PROGMEM =               "sip get_gpio %c %d";             // 3.1.12
const char SIP_GET_UUID[] PROGMEM =               "sip get_uuid";                   // 3.1.13
const char SIP_SET_STORAGE[] PROGMEM =            "sip set_storage %s";             // 3.1.14
const char SIP_GET_STORAGE[] PROGMEM =            "sip get_storage";                // 3.1.15
const char SIP_SET_BATT_RESISTOR[] PROGMEM =      "sip set_batt_resistor %lu %lu";  // 3.1.16
const char SIP_GET_BATT_RESISTOR[] PROGMEM =      "sip get_batt_resistor";          // 3.1.17
const char SIP_GET_BATT_VOLT[] PROGMEM =          "sip get_batt_volt";              // 3.1.18

const char MAC_TX[] PROGMEM =                     "mac tx %s %d %s";                // 3.2.1
const char MAC_JOIN_ABP[] PROGMEM =               "mac join abp";                   // 3.2.2
const char MAC_JOIN_OTAA[] PROGMEM =              "mac join otaa";                  // 3.2.2
const char MAC_SAVE[] PROGMEM =                   "mac save";                       // 3.2.3
const char MAC_GET_JOIN_STATUS[] PROGMEM =        "mac get_join_status";            // 3.2.4
const char MAC_SET_LINKCHK[] PROGMEM =            "mac set_linkchk";                // 3.2.5
const char MAC_SET_DEVEUI[] PROGMEM =             "mac set_deveui %s";              // 3.2.6
const char MAC_SET_APPEUI[] PROGMEM =             "mac set_appeui %s";              // 3.2.7
const char MAC_SET_APPKEY[] PROGMEM =             "mac set_appkey %s";              // 3.2.8
const char MAC_SET_DEVADDR[] PROGMEM =            "mac set_devaddr %s";             // 3.2.9
const char MAC_SET_NWKSKEY[] PROGMEM =            "mac set_nwkskey %s";             // 3.2.10
const char MAC_SET_APPSKEY[] PROGMEM =            "mac set_appskey %s";             // 3.2.11
const char MAC_SET_POWER[] PROGMEM =              "mac set_power %d";               // 3.2.12
const char MAC_SET_DR[] PROGMEM =                 "mac set_dr %d";                  // 3.2.13
const char MAC_SET_ADR[] PROGMEM =                "mac set_adr %s";                 // 3.2.14
const char MAC_SET_TXRETRY[] PROGMEM =            "mac set_txretry %d";             // 3.2.15
const char MAC_SET_RXDELAY1[] PROGMEM =           "mac set_rxdelay1 %d";            // 3.2.16
const char MAC_SET_RX2[] PROGMEM =                "mac set_rx2 %d %d";              // 3.2.17
const char MAC_SET_SYNC[] PROGMEM =               "mac set_sync %02X";              // 3.2.18
const char MAC_SET_CH_FREQ[] PROGMEM =            "mac set_ch_freq %d %d";          // 3.2.19
const char MAC_SET_CH_DR_RANGE[] PROGMEM =        "mac set_ch_dr_range %d %d %d";   // 3.2.20
const char MAC_SET_CH_STATUS[] PROGMEM =          "mac set_ch_status %d %s";        // 3.2.21
const char MAC_SET_DC_CTL[] PROGMEM =             "mac set_dc_ctl %s";              // 3.2.22
const char MAC_SET_DC_BAND[] PROGMEM =            "mac set_dc_band %d %d";          // 3.2.23
const char MAC_SET_JOIN_CH[] PROGMEM =            "mac set_join_ch %d %s";          // 3.2.24
const char MAC_SET_UPCNT[] PROGMEM =              "mac set_upcnt %lu";              // 3.2.25
const char MAC_SET_DOWNCNT[] PROGMEM =            "mac set_downcnt %lu";            // 3.2.26
const char MAC_SET_CLASS[] PROGMEM =              "mac set_class %c";               // 3.2.27
const char MAC_GET_DEVADDR[] PROGMEM =            "mac get_devaddr";                // 3.2.28
const char MAC_GET_DEVEUI[] PROGMEM =             "mac get_deveui";                 // 3.2.29
const char MAC_GET_APPEUI[] PROGMEM =             "mac get_appeui";                 // 3.2.30
const char MAC_GET_NWKSKEY[] PROGMEM =            "mac get_nwkskey";                // 3.2.31
const char MAC_GET_APPSKEY[] PROGMEM =            "mac get_appskey";                // 3.2.32
const char MAC_GET_APPKEY[] PROGMEM =             "mac get_appkey";                 // 3.2.33
const char MAC_GET_DR[] PROGMEM =                 "mac get_dr";                     // 3.2.34
const char MAC_GET_BAND[] PROGMEM =               "mac get_band";                   // 3.2.35
const char MAC_GET_POWER[] PROGMEM =              "mac get_power";                  // 3.2.36
const char MAC_GET_ADR[] PROGMEM =                "mac get_adr";                    // 3.2.37
const char MAC_GET_TXRETRY[] PROGMEM =            "mac get_txretry";                // 3.2.38
const char MAC_GET_RXDELAY[] PROGMEM =            "mac get_rxdelay";                // 3.2.39
const char MAC_GET_RX2[] PROGMEM =                "mac get_rx2";                    // 3.2.40
const char MAC_GET_SYNC[] PROGMEM =               "mac get_sync";                   // 3.2.41
const char MAC_GET_CH_PARA[] PROGMEM =            "mac get_ch_para %d";             // 3.2.42
const char MAC_GET_CH_STATUS[] PROGMEM =          "mac get_ch_status %d";           // 3.2.43
const char MAC_GET_DC_CTL[] PROGMEM =             "mac get_dc_ctl";                 // 3.2.44
const char MAC_GET_DC_BAND[] PROGMEM =            "mac get_dc_band %d";             // 3.2.45
const char MAC_GET_JOIN_CH[] PROGMEM =            "mac get_join_ch";                // 3.2.46
const char MAC_GET_UPCNT[] PROGMEM =              "mac get_upcnt";                  // 3.2.47
const char MAC_GET_DOWNCNT[] PROGMEM =            "mac get_downcnt";                // 3.2.48
const char MAC_GET_CLASS[] PROGMEM =              "mac get_class";                  // 3.2.49
const char MAC_SET_TX_MODE[] PROGMEM =            "mac set_tx_mode %s";             // 3.2.50
const char MAC_GET_TX_MODE[] PROGMEM =            "mac get_tx_mode";                // 3.2.51
const char MAC_SET_BATT[] PROGMEM =               "mac set_batt %d";                // 3.2.52
const char MAC_GET_BATT[] PROGMEM =               "mac get_batt";                   // 3.2.53
const char MAC_SET_TX_CONFIRM[] PROGMEM =         "mac set_tx_confirm %s";          // 3.2.54
const char MAC_GET_TX_CONFIRM[] PROGMEM =         "mac get_tx_confirm";             // 3.2.55
const char MAC_SET_LBT[] PROGMEM =                "mac set_lbt %s";                 // 3.2.56
const char MAC_GET_LBT[] PROGMEM =                "mac get_lbt";                    // 3.2.57
const char MAC_SET_UPLINK_DWELL[] PROGMEM =       "mac set_uplink_dwell %s";        // 3.2.58
const char MAC_GET_UPLINK_DWELL[] PROGMEM =       "mac get_uplink_dwell";           // 3.2.59
const char MAC_SET_DOWNLINK_DWELL[] PROGMEM =     "mac set_downlink_dwell %s";      // 3.2.60
const char MAC_GET_DOWNLINK_DWELL[] PROGMEM =     "mac get_downlink_dwell";         // 3.2.61
const char MAC_SET_MAX_EIRP[] PROGMEM =           "mac set_max_eirp %d";            // 3.2.62
const char MAC_GET_MAX_EIRP[] PROGMEM =           "mac get_max_eirp";               // 3.2.63
const char MAC_SET_CH_COUNT[] PROGMEM =           "mac set_ch_count %d %d";         // 3.2.64
const char MAC_GET_CH_COUNT[] PROGMEM =           "mac get_ch_count";               // 3.2.65
const char MAC_SET_KEYS[] PROGMEM =               "mac set_keys %s %s %s %s %s %s"; // 3.2.66
const char MAC_SET_TX_INTERVAL[] PROGMEM =        "mac set_tx_interval %lu";        // 3.2.67
const char MAC_GET_TX_INTERVAL[] PROGMEM =        "mac get_tx_interval";            // 3.2.68
const char MAC_SET_RX1_FREQ[] PROGMEM =           "mac set_rx1_freq %lu %lu %d";    // 3.2.69
const char MAC_GET_RX1_FREQ[] PROGMEM =           "mac get_rx1_freq";               // 3.2.70
const char MAC_SET_AUTO_JOIN[] PROGMEM =          "mac set_auto_join %s %s %d";     // 3.2.71
const char MAC_GET_AUTO_JOIN[] PROGMEM =          "mac get_auto_join";              // 3.2.72
const char MAC_SET_POWER_INDEX[] PROGMEM =        "mac set_power_index %d";         // 3.2.73
const char MAC_GET_POWER_INDEX[] PROGMEM =        "mac get_power_index";            // 3.2.74


class S76SDriver {
    public:
        S76SDriver();
        bool reset(void);
        bool begin(String deveui="", String appeui="", String appkey="");

        char getVersion();
        char getHardware();
        // char getEUI();

		bool setDeveui(String deveui, uint16_t timeout = 2000);
		bool setAppeui(String appeui, uint16_t timeout = 2000);
		bool setAppkey(String appkey, uint16_t timeout = 2000);
		bool getDeveui(char * deveui, uint16_t timeout = 1000);
		bool getAppeui(char * appeui, uint16_t timeout = 1000);
		bool getAppkey(char * appkey, uint16_t timeout = 1000);

		bool joinOTAA(uint16_t timeout = 1000);
		bool joinStatus(uint16_t timeout = 15000);

		bool stringWrite(uint8_t port, String stringdata, uint16_t timeout = 15000);
		bool setSyncword(String sync, uint16_t timeout = 1000);

		bool receiveBrodcast(char * receivedata, uint16_t timeout = 20000);
		bool sendBrodcast(String stringdata, uint16_t timeout = 2000);

		bool getRespond(char * respond, uint16_t timeout);

        bool sleep(uint32_t seconds);
        bool wake();

        bool setTxPower(uint8_t power);
        bool setDatarate(uint8_t dr);
        bool enableADR(bool adr);
        bool setRetry(uint8_t times);

        bool setChannelFrequency(uint8_t channel, uint32_t frequency);


    private:

};