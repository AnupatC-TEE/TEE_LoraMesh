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

bool TONY_LORA::setRxContinuous(bool state, uint16_t timeout)
{
	String buf = state ? "on" : "off";
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf rx_con "+buf);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
		// Serial.println(buff);
		if(buffstring == "Ok") {
			_rx_con = "enable";
			return 1; 
		}
		else if(buffstring != 0) {
			_rx_con = "failed";
			return 0;
		}
	}
	else {
		_rx_con = "disable";
		return 0;
	}
}

bool TONY_LORA::setCAD(bool state, uint16_t timeout) 
{
	String buf = state ? "on" : "off";
	char buff[7];
	String buffstring = "";
	LoRaSerial->print("rf set_cad "+buf);
	if(getRespond(buff, timeout)) 
	{
		buffstring = buff;
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
	char str[300];
	strcpy(str, msg.c_str());
    char *token;
    char *buff[5];  // Array to hold the split tokens
    int i = 0;

    // Get the first token
    token = strtok(str, " ");

    // Walk through other tokens
    while (token != NULL) {
        buff[i++] = token;  // Store the token in the array
        token = strtok(NULL, " ");
    }

	if(_rx_con == "enable") {
		lastMSG = buff[2];
		_lastRssi = String(buff[3]).toInt();
		_lastSNR = String(buff[4]).toInt();
	} else {
		lastMSG = buff[1];
		_lastRssi = String(buff[2]).toInt();
		_lastSNR = String(buff[3]).toInt();
	}
	// Serial.println(lastMSG);
	return lastMSG;
}

void TONY_LORA::decodingRawCon(String msg) {
	char str[1000];
	strcpy(str, msg.c_str());
	char *token;
	char *buff[20];  // Array to hold the split tokens
	int i = 0;
	String data_temp = "";

	// Get the first token
	token = strtok(str, "\n");

	// Walk through other tokens
	while (token != NULL) {
		buff[i++] = token;  // Store the token in the array
		token = strtok(NULL, "\n");
	}

	for(int k=0; k<i;){
		data_temp = buff[k];
		decodingRawMsg(data_temp);
		k = k+2;
	}
}

/* MESH function */

bool TONY_LORA::available() {
	handleRxMsg();
    return _rxBufValid;
}

void TONY_LORA::waitAvailable() {
    while (!available())
		YIELD;
}

bool TONY_LORA::waitAvailableTimeout(uint16_t timeout) {
    unsigned long starttime = millis();
	while ( (millis() - starttime) < timeout)
	{
		if (available())
		{
			return true;
		}
		YIELD;
	}
	return false;
}

uint8_t TONY_LORA::maxMessageLength() {
    return MAX_RX_BUF_LEN;
}

bool TONY_LORA::init(uint8_t slot, int bandwidth, String codingRate, int frequency, int tx_power) {
	bool bw, cr, freq, pow;

    setSlot(slot);
	setRxContinuous(0);
	reset();
    getModuleInfo();

	bw = setSignalBandwidth(bandwidth);
	cr = setCodingRate(codingRate);
	freq = setFrequency(frequency);
	pow = setTxPower(tx_power);

    return bw && cr && freq && pow;
}

bool TONY_LORA::send(const uint8_t* dataT, uint8_t len) {
    if(len > MAX_RX_BUF_LEN) return false;

	// uint8_t real_len = String((char*)dataT).length();
	holdRx();

	String data_out = "";
	// Serial.println((char*)dataT);

	//set msg header
	data_out += (char)_txHeaderTo;
	// Serial.println((int)_txHeaderTo);
	data_out += (char)_txHeaderFrom;
	// Serial.println((int)_txHeaderFrom);
	data_out += (char)_txHeaderId;
	// Serial.println((int)_txHeaderId);
	data_out += (char)_txHeaderFlags;
	// Serial.println("Header only");
	data_out = stringToHex(data_out);

	for (int i = 0; i < len; i++) {
		if (dataT[i] < 0x10) data_out += "0";  // Add leading zero for single hex digits
		data_out += String(dataT[i], HEX);
	}
	// Serial.println(data_out.length());
	int lastNonZeroIndex = data_out.length() - 1;
  
	// Iterate backwards through the string to find the last non-zero character
	for (int i = lastNonZeroIndex; i >= 0; i--) {
		if (data_out[i] != '0') {
		lastNonZeroIndex = i;
		break;
		}
	}
	
	// Extract the substring from the beginning up to the last non-zero index
	data_out = data_out.substring(0, lastNonZeroIndex + 1);

	Serial.println(data_out);
	bool res = sendBrodcast(data_out, 4000);

	delay(200); //Mysterious delay???? if not include this line will cause early heap overflow // don't touch it magic number
	unholdRx();

    return res;
}

void TONY_LORA::handleRxMsg() {

	String decode_data = "";
	String buf = "";

	if(_rx_con == "enable") {
		if(msgAvailable()){
			buf = TonyLORA.LoRaSerial->readString();
			Serial.println(buf);
			decodingRawCon(buf);
		} else {
			return;
		}
	} 
	else 
	{
		receiveBrodcast(_rx_buf, (int)_rx_timeout);
		if(String(_rx_buf) == "radio_err") return;
		if(String(_rx_buf) == "") return;
		TonyLORA.decodingRawMsg(String(_rx_buf));
	}
	// Serial.print("raw: ");
	// Serial.println(lastMSG);
	// Serial.println(decode_data);
	

	hexToUint8(lastMSG,_rx_data_buf);
	// data = hexToString(lastMSG).substring(4);
	// data = hexToString(lastMSG);
	// Serial.println(header);
	// Serial.println(data);


	validateRxBuf();
}

bool TONY_LORA::recv(uint8_t* respond, uint8_t* len) {

	if (!available())
		return false;

	if (respond && len) memcpy(respond, _rx_data_buf+4, sizeof(_rx_data_buf));

	// Serial.println("Byte Array:");
  	// for (int i = 0; i < sizeof(data); i++) {
	// 	Serial.print("0x");
	// 	if (respond[i] < 0x10) Serial.print("0");
	// 	Serial.print(respond[i], HEX);
	// 	Serial.print(" ");
	// }

	clearRxBuf();
    return true;
}

void TONY_LORA::validateRxBuf() {
	header = hexToString(lastMSG).substring(0,4);
	_rxHeaderTo    = (uint8_t)header[0];
	_rxHeaderFrom  = (uint8_t)header[1];
	_rxHeaderId    = (uint8_t)header[2];
	_rxHeaderFlags = (uint8_t)header[3];
	// Serial.print("Header to:");
	// Serial.println((int)_rxHeaderTo);
	// Serial.print("This:");
	// Serial.println((int)_thisAddress);
	// Serial.println((int)RH_BROADCAST_ADDRESS);
	if (_promiscuous ||
			_rxHeaderTo == _thisAddress ||
			_rxHeaderTo == RH_BROADCAST_ADDRESS)
	{
		// setRxLedState(true);
		_rxGood++;
		_rxBufValid = true;
		// Serial.println("Rx good");
		return;
	}
}

void TONY_LORA::clearRxBuf()
{
	_rxBufValid = false;
	// for(size_t i = 0; i < sizeof(_rx_data_buf); ++i) _rx_data_buf[i] = 0;
	memset(_rx_data_buf, 0, sizeof(_rx_data_buf));
	Serial.print("Clear buffer:");
	Serial.println((char*)_rx_data_buf);
	data = "";

}

String TONY_LORA::stringToHex(String input) {
    String hexString = "";
    for (int i = 0; i < input.length(); i++) {
        char c = input.charAt(i);
        if (c < 16) hexString += "0";  // Add leading zero for single-digit hex values
        hexString += String(c, HEX);
    }
    return hexString;
}

String TONY_LORA::hexToString(String hexInput) {
    String decodedString = "";
    for (int i = 0; i < hexInput.length(); i += 2) {
        String hexByte = hexInput.substring(i, i + 2);
        char c = (char) strtol(hexByte.c_str(), NULL, 16);
        decodedString += c;
    }
    return decodedString;
}

void TONY_LORA::hexToUint8(const String &hexInput, uint8_t *outputArray) {
    int length = hexInput.length();
    for (int i = 0; i < length; i += 2) {
        String hexByte = hexInput.substring(i, i + 2);
        outputArray[i / 2] = (uint8_t) strtol(hexByte.c_str(), NULL, 16);
    }
}

void TONY_LORA::holdRx() {
	if(_rx_con == "enable") {
		setRxContinuous(0);
		_tx_over_con = true;
	}
	delay(1);
}

void TONY_LORA::unholdRx() {
	if(_tx_over_con) {
		setRxContinuous(1);
	}
	delay(10);
}