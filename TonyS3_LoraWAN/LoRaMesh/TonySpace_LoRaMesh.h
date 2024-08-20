#ifndef TonySpace_LoRaMesh_h
#define TonySpace_LoRaMesh_h

#include "Arduino.h"
#include <stdlib.h>
#include <inttypes.h>
#include "Stream.h"
#include "esp32-hal.h"

#include "RHGenericDriver.h"

#define MAX_RX_BUF_LEN 500

class TONY_LORA : public RHGenericDriver
{
	public:
		TONY_LORA();
		~TONY_LORA() {
		};
		void setSlot(uint8_t slot);
		bool reset(void);
		bool begin(String deveui="", String appeui="", String appkey="");
		bool setDeveui(String deveui, uint16_t timeout = 2000);
		bool setAppeui(String appeui, uint16_t timeout = 2000);
		bool setAppkey(String appkey, uint16_t timeout = 2000);
		bool setFrequency(long freq, uint16_t timeout = 2000);
		bool setTxPower(uint8_t level, uint16_t timeout = 2000);
		bool setSpreadingFactor(uint8_t sf, uint16_t timeout = 2000);
		bool setSignalBandwidth(uint16_t bw, uint16_t timeout = 2000);
		bool setCodingRate(String codingRate, uint16_t timeout = 2000);
		bool setPremLenght(uint16_t lenght, uint16_t timeout = 2000);
		bool setSyncword(String sync, uint16_t timeout = 1000);
		// bool setChannelFreq();
		// bool setCADTimeout();
		// bool setModemRegistor();
		// bool setModelConfig();


		bool getDeveui(char * deveui, uint16_t timeout = 1000);
		bool getAppeui(char * appeui, uint16_t timeout = 1000);
		bool getAppkey(char * appkey, uint16_t timeout = 1000);
		// bool getLastRssi();
		bool getBandFrequency(char* band_freq, uint16_t timeout=1000);
		bool getTxPower(char* txPower, uint16_t timeout=1000);
		bool getSpredingFactor(char* sf, uint16_t timeout=1000);
		bool getBandWidth(char* bw, uint16_t timeout=1000);
		bool getDataRate(char* dataRate, uint16_t timeout=1000);
		bool getPreambleLength(char* lenght, uint16_t timeout=1000);
		bool getSyncWord(char* syncword, uint16_t timeout=1000);

		bool sendAndGet(String cmd, char* res, uint16_t timeout = 1000);
		void getModuleInfo();
		void getConfig();


		bool joinOTAA(uint16_t timeout = 1000);
		bool joinStatus(uint16_t timeout = 15000);
		bool stringWrite(uint8_t port, String stringdata, uint16_t timeout = 15000);
		bool receiveBrodcast(char * receivedata, uint16_t timeout = 20000);
		bool sendBrodcast(String stringdata, uint16_t timeout = 2000);	
		bool getRespond(char * respond, uint16_t timeout);
		bool msgAvailable();
		String readIncomingMsg();
		String decodingRawMsg(String msg);

		//low power plan
		// bool sleep();
		// bool wakeUp();

		String lastMSG;
		String lastRSSI;
		String lastSNR;

		HardwareSerial *LoRaSerial;
	
		/* MESH function*/

        bool available();
        void waitAvailable();
        bool waitAvailableTimeout(uint16_t timeout);
        uint8_t maxMessageLength();
		bool init(uint8_t slot);
        bool send(const uint8_t* data, uint8_t len);
        bool recv(uint8_t* buf, uint8_t* len);
		char _rx_buf[MAX_RX_BUF_LEN] = "";


	private:
		uint8_t pin_RX, 
				pin_TX,
				_uart_nr;
		
	protected:

};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
extern TONY_LORA TonyLORA;
// extern HardwareSerial LoRaSerial;
#endif

#endif















