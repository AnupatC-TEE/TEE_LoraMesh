#include "TonySpace_LoRaMesh.h"
// #include "TonyS_X1.h"
#include "TonyS_S3.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
TONY_LORA TonyLORA;
// extern HardwareSerial LoRaSerial(NULL);
#endif


TONY_LORA::TONY_LORA()
{
}

void TONY_LORA::setSlot(uint8_t slot) 
{
	// LoRaSerial = Tony.SerialBegin(slot,115200);
	Serial.begin(115200);
	switch(slot)
	{
		case  SLOT1 :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT2 :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT3 :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT4 :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
		case  SLOT5 :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
		case  SLOT6 :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
		case  SLOT1_U :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT2_U :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT3_U :
			pin_RX = RX1;
			pin_TX = TX1;
			_uart_nr = 1;
			break;
		case  SLOT4_U :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
		case  SLOT5_U :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
		case  SLOT6_U :
			pin_RX = RX2;
			pin_TX = TX2;
			_uart_nr = 2;
			break;
	}
	LoRaSerial = new HardwareSerial(_uart_nr);
	LoRaSerial->begin(115200,SERIAL_8N1,pin_RX,pin_TX);
	// LoRaSerial->begin(115200,SERIAL_8N1,pin_RX,pin_TX);

	Serial.println("Module init success");
}

bool TONY_LORA::begin(String deveui, String appeui, String appkey)
{
	//Serial.println("Setting up LoRaWAN module");
	uint16_t timeout = 2000;
	if(deveui != "") 
	{
		if(setDeveui(deveui, timeout) == 0) 
		{
			Serial.println("Set deveui : Fail");
			return 0;
		}
	}
	if(appeui != "") 
	{
		if(setAppeui(appeui, timeout) == 0) 
		{
			Serial.println("Set appeui : Fail");
			return 0;
		}
	}		
	if(appkey != "") 
	{
		if(setAppkey(appkey, timeout) == 0) 
		{
			Serial.println("Set appkey : Fail");
			return 0;
		}
	}
	//Serial.println("Setup is complete.");
	return 1;
}

bool TONY_LORA::reset()
{
	LoRaSerial->print("sip reset");
	delay(1000);
	while(LoRaSerial->available() > 0 ) LoRaSerial->read();
	return 1;
}

bool TONY_LORA::getDeveui(char * deveui, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("mac get_deveui");
	if(getRespond(deveui, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getAppeui(char * appeui, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("mac get_appeui");
	if(getRespond(appeui, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getAppkey(char * appkey, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("mac get_appkey");
	if(getRespond(appkey, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getBandFrequency(char* band_freq, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_freq");
	if(getRespond(band_freq, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getTxPower(char* txPower, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_pwr");
	if(getRespond(txPower, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getSpredingFactor(char* sf, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_sf");
	if(getRespond(sf, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getBandWidth(char* bw, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_bw");
	if(getRespond(bw, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getDataRate(char* dataRate, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_bw");
	if(getRespond(dataRate, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getPreambleLength(char* lenght, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_prlen");
	if(getRespond(lenght, timeout)) return 1;
	else return 0;
}

bool TONY_LORA::getSyncWord(char* syncword, uint16_t timeout)
{
	String buff = "";
	LoRaSerial->print("rf get_sync");
	if(getRespond(syncword, timeout)) return 1;
	else return 0;
}


bool TONY_LORA::sendAndGet(String cmd, char* res, uint16_t timeout) {
	LoRaSerial->print(cmd);
	if(getRespond(res, timeout)) return 1;
	// else
	return 0;
}

void TONY_LORA::getModuleInfo() {
	char response[50];
	// char appeui[50]
	sendAndGet("sip get_hw_model", response, 1000);
	Serial.print("HW model: ");
	Serial.println(response);
	sendAndGet("sip get_ver", response, 1000);
	Serial.print("HW version: ");
	Serial.println(response);
	getDeveui(response, 1000);
	Serial.print("EUI: ");
	Serial.println(response);
}

void TONY_LORA::getConfig(){
	char response[50];

	getBandFrequency(response, 1000);
	Serial.print("Freq: ");
	Serial.println(response);

	getTxPower(response, 1000);
	Serial.print("Tx Power: ");
	Serial.println(response);

	getBandWidth(response, 1000);
	Serial.print("Bandwidth: ");
	Serial.println(response);

	getSpredingFactor(response, 1000);
	Serial.print("Spreading Factor: ");
	Serial.println(response);

	getDataRate(response, 1000);
	Serial.print("Data rate: ");
	Serial.println(response);

	getPreambleLength(response, 1000);
	Serial.print("Preamble length: ");
	Serial.println(response);
}

bool TONY_LORA::joinOTAA(uint16_t timeout)
{
	char buff[7];
	LoRaSerial->print("mac join otaa");
	if(getRespond(buff, timeout)) 
	{
		if(buff == "Ok") return 1;
	}
	else return 0;
}

bool TONY_LORA::joinStatus(uint16_t timeout)
{
	unsigned long startTime = millis(); 
	unsigned long currentTime = 0; 
	String buff;
	while(1)
	{
		buff[0] = '\0';
		LoRaSerial->print("mac get_join_status");
		if(LoRaSerial->available()) buff = LoRaSerial->readString();
		if(buff == ">> joined" || buff.indexOf(">> joined")>0) return 1;	
		currentTime = millis(); 
		if((currentTime-startTime)>=timeout) return 0;	
		delay(100);
	}	
}

bool TONY_LORA::setDeveui(String deveui, uint16_t timeout)
{
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("mac set_deveui "+deveui);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setAppeui(String appeui, uint16_t timeout)
{
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("mac set_appeui "+appeui);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setAppkey(String appkey, uint16_t timeout)
{ 
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("mac set_appkey "+appkey);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setFrequency(long freq, uint16_t timeout) 
{
	if(freq < 862000000 && freq > 932000000) return 0;

	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_freq "+String(freq));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setTxPower(uint8_t level, uint16_t timeout) 
{
	if(level < 2 && level > 20) return 0;

	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_pwr "+String(level));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setSpreadingFactor(uint8_t sf, uint16_t timeout)
{
	if(sf < 6 && sf > 12) return 0;

	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_pwr "+String(sf));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setSignalBandwidth(uint16_t bw, uint16_t timeout)
{
	if(bw != 125 && bw != 250 && bw != 500 ) return 0;

	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_bw "+String(bw));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setCodingRate(String codingRate, uint16_t timeout)
{
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_cr "+codingRate);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::setPremLenght(uint16_t lenght, uint16_t timeout)
{
	// if(sf < 0 && sf > 65535) return 0;

	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_prlen "+String(lenght));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

// bool TONY_LORA::setCADTimeout()

bool TONY_LORA::stringWrite(uint8_t port, String stringdata, uint16_t timeout)
{
	if(stringdata.length()<=512) // 64 Byte
    {
		char buff[200];
		String buffstring = "";
		port = constrain(port, 0, 223);
		
		if(joinStatus() == 1) LoRaSerial->print("mac tx ucnf "+String(port)+" "+stringdata);
		else
		{
			if(TonyLORA.joinOTAA())
			{			
				if(TonyLORA.joinStatus(timeout))
				{
					LoRaSerial->print("mac tx ucnf "+String(port)+" "+stringdata);
				}
				else return 0;
			}
			else return 0;
		}

		if(getRespond(buff, timeout)) 
		{
			buffstring = buff;
			buffstring.trim();
			if(buffstring == "Ok")
			{
				buff[0] = '\0';
				if(getRespond(buff, timeout)) 
				{
					buffstring = buff;
					buffstring.trim();
					if(buffstring == "tx_ok" || buffstring.indexOf("tx_ok")>0) return 1;    
					else if(buffstring != 0) return 0;
				}
				else return 0;		
			}
			else if(buffstring != 0) return 0;
		}
		else return 0;		
	}
}

bool TONY_LORA::setSyncword(String sync, uint16_t timeout)
{
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_sync "+sync);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		Serial.println(buff);
		if(buffstring == "Ok") return 1;
		else if(buffstring != 0) return 0;
	}
	else return 0;	
}

bool TONY_LORA::receiveBrodcast(char * receivedata, uint16_t timeout)
{
	char buff[40];
	String buffstring = "";
	LoRaSerial->print("rf rx "+String(timeout-200));
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		// Serial.print("buffer : ");
		// Serial.println(buffstring);
		if(buffstring == "Ok")
		{
			if(getRespond(receivedata, timeout)) return 1;
			else return 0;
		}
		else if(buffstring != 0) return 0;
	}
	else return 0;		
}

bool TONY_LORA::sendBrodcast(String stringdata, uint16_t timeout)
{
	if(stringdata.length()<=2040) // 255 Byte
    {
		char buff[20];
		String buffstring = "";
		LoRaSerial->print("rf tx "+stringdata);
		if(getRespond(buff, timeout)) 
		{
			buffstring = buff;
			if(buffstring == "radio_tx_ok" || buffstring.indexOf("radio_tx_ok")>0) return 1;
			else if(buffstring != 0) return 0;
		}
		else return 0;		
	}
}

bool TONY_LORA::getRespond(char * respond, uint16_t timeout)
{
	unsigned long startTime = millis(); 
	unsigned long currentTime = 0; 
	String buff = "";
	while(1)
	{
		buff = "";
		if(LoRaSerial->available()) buff = LoRaSerial->readString();
		if(buff != "")
		{
			buff = buff.substring(5);
			buff.trim();
			strcpy(respond,&buff[0]);
			// Serial.println(buff);
			// Serial.print("Length : ");
			// Serial.println(buff.length()); 
			return 1;
		}
		
		currentTime = millis(); 
		if((currentTime-startTime)>=timeout) return 0;
	}	
}

bool TONY_LORA::msgAvailable() {
	if(LoRaSerial->available()) return 1;
	else return 0;
}

String TONY_LORA::readIncomingMsg() {
	String buff = "";
	buff = LoRaSerial->readString();
	if(buff != "")
	{
		buff = buff.substring(5);
		buff.trim();
	}
	return buff;
}

String TONY_LORA::decodingRawMsg(String msg) {
	char str[200];
	strcpy(str, msg.c_str());
    char *token;
    char *buff[4];  // Array to hold the split tokens
    int i = 0;

    // Get the first token
    token = strtok(str, " ");

    // Walk through other tokens
    while (token != NULL) {
        buff[i++] = token;  // Store the token in the array
        token = strtok(NULL, " ");
    }

	// Serial.println(array[0]); //cmd
	// Serial.println(array[1]); //data
	// Serial.println(array[2]); //rssi
	// Serial.println(array[3]);

	lastMSG = buff[1];
	lastRSSI = buff[2];
	lastSNR = buff[3];

	return lastMSG;
}

/* MESH function */

bool TONY_LORA::available() {
    return msgAvailable();
}

bool TONY_LORA::init(String deveui, String appeui, String appkey) {
    return begin(deveui,appeui,appkey);
}

bool TONY_LORA::send(const uint8_t* data, uint8_t len) {
    if(len > RH_S7GX_MAX_LEN) return false;

    return sendBrodcast(String(*data), 2000);
}

bool TONY_LORA::recv(uint8_t* buf, uint8_t* len) {
    return receiveBrodcast(buf, 2000);
}