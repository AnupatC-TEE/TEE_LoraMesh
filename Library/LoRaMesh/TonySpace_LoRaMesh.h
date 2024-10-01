#ifndef TonySpace_LoRaMesh_h
#define TonySpace_LoRaMesh_h

#include "Arduino.h"
#include <stdlib.h>
#include <inttypes.h>
#include "Stream.h"
#include "esp32-hal.h"

#include "RHGenericDriver.h"

#define MAX_RX_BUF_LEN 255

#define RH_S76S_HEADER_LEN 4

class TONY_LORA : public RHGenericDriver
{
	public:
		TONY_LORA();
		~TONY_LORA() {
		};
		void setSlot(uint8_t slot);

		/* low power */
		// bool sleep();
		// bool wakeUp();
		bool reset(void);

		/* WAN MODE */
		bool begin(String deveui="", String appeui="", String appkey="");
		bool setDeveui(String deveui, uint16_t timeout = 2000);
		bool setAppeui(String appeui, uint16_t timeout = 2000);
		bool setAppkey(String appkey, uint16_t timeout = 2000);
		bool setSyncword(String sync, uint16_t timeout = 1000);

		bool getDeveui(char * deveui, uint16_t timeout = 1000);
		bool getAppeui(char * appeui, uint16_t timeout = 1000);
		bool getAppkey(char * appkey, uint16_t timeout = 1000);
		bool getSyncWord(char* syncword, uint16_t timeout=1000);

		bool joinOTAA(uint16_t timeout = 1000);
		bool joinStatus(uint16_t timeout = 15000);
		bool stringWrite(uint8_t port, String stringdata, uint16_t timeout = 15000);

		/* Config */
		bool setFrequency(long freq, uint16_t timeout = 2000);
		bool setTxPower(uint8_t level, uint16_t timeout = 2000);
		bool setSpreadingFactor(uint8_t sf, uint16_t timeout = 2000);
		bool setSignalBandwidth(uint16_t bw, uint16_t timeout = 2000);
		bool setCodingRate(String codingRate, uint16_t timeout = 2000);
		bool setPremLenght(uint16_t lenght, uint16_t timeout = 2000);
		bool setRxContinuous(bool state = 0, uint16_t timeout = 1000);
		// bool setCRC(bool state=0, timeout = 1000);
		// bool setChannelFreq();
		bool setCAD(bool state = 0, uint16_t timeout = 1000);

		bool getBandFrequency(char* band_freq, uint16_t timeout=1000);
		bool getTxPower(char* txPower, uint16_t timeout=1000);
		bool getSpredingFactor(char* sf, uint16_t timeout=1000);
		bool getBandWidth(char* bw, uint16_t timeout=1000);
		bool getDataRate(char* dataRate, uint16_t timeout=1000);
		bool getPreambleLength(char* lenght, uint16_t timeout=1000);

		/* Utility function*/
		bool sendAndGet(String cmd, char* res, uint16_t timeout = 1000);
		void getModuleInfo();
		void getConfig();
		bool getRespond(char * respond, uint16_t timeout);
		void holdRx();
		void unholdRx();

		bool receiveBrodcast(char * receivedata, uint16_t timeout = 20000);
		bool sendBrodcast(String stringdata, uint16_t timeout = 2000);	

		bool msgAvailable();
		String readIncomingMsg();
		String decodingRawMsg(String msg);
		void decodingRawCon(String msg);

		String lastMSG;
		int16_t _lastSNR;

		/* MESH function*/
        bool available();
        void waitAvailable();
        bool waitAvailableTimeout(uint16_t timeout);
        uint8_t maxMessageLength();
		bool init(uint8_t slot, int bandwidth=125, String codingRate="4/5", int frequency=920000000, int tx_power=13);
        bool send(const uint8_t* data, uint8_t len);
        bool recv(uint8_t* buf, uint8_t* len);
		void handleRxMsg();
		void validateRxBuf();
		void clearRxBuf();
		bool _rxBufValid;

		/* Serial */
		HardwareSerial *LoRaSerial;
		uint16_t _tx_timeout = 4000;
		uint16_t _rx_timeout = 4000;

		/* Utils */
		String hexToString(String hexInput);
		String stringToHex(String input);
		void hexToUint8(const String &hexInput, uint8_t *outputArray);

		bool debug_mode = false;

	private:
		char _rx_buf[100] = "";
		uint8_t _rx_data_buf[MAX_RX_BUF_LEN] = "";
		String _rx_con = "";
		String header = "";
		String data = "";

		/* Serial variable */
		uint8_t pin_RX, 
				pin_TX,
				_uart_nr;

		bool _rx_sta = 0;
		bool _tx_over_con = 0;
		uint8_t _bufLen;
		
	protected:

};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
extern TONY_LORA TonyLORA;
// extern HardwareSerial LoRaSerial;
#endif

#endif















