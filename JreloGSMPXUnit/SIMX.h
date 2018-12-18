/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.2.1
 * */
 
#pragma once
#include <Arduino.h>
#include <Module.h>
#include <ATCommandExecutor.h>
#include <ATCommands.h>
#include <SimpleTimer.h>
#include <StringBuffer.h>
#include <TypeConverter.h>
#include <StringBufferUtils.h>
#include <LocationProvider.h>

#define DEBUG
#define SELF_CONTROL_DELAY 10000
#define GET_LOCATION_DELAY 30000
#define MCE_CHECK_NETWORK 10
#define MCE_INIT_HTTP 15
#define MCE_RESPONSE_60x 1
#define MCE_PREPARE_GPRS 10
#define MCE_OTHER 5
#define MAX_FAILED_ACTIONS 30

const char EMPTY_STRING	[] = "";
const char COMMA		[] = ",";

enum RequestMethod {
    GET,
    POST
};

enum Action {
    EMPTY, 					//0							
    POWER_ON,				//1						
	CHECK_PIN,				//2
	CONFIG_APN,				//3
	CHECK_SIGNAL,			//4
	CHECK_NETWORK,			//5
	PREPARE_GPRS,			//6
	SET_SSL,				//7
	INIT_HTTP,				//8
	SET_HEADER,				//9
	SET_URL,				//10
	SELECT_PROFILE,			//11
	GET_HTTP_STATUS_CODE, 	//12
	HTTP_READ,				//13
	SEND_REQUEST,			//14	
	HTTP_TERM,				//15
	HTTP_PARA,				//16
	HTTP_DATA_DOWNLOAD_P1, 	//17
	HTTP_DATA_DOWNLOAD_P2, 	//18
	RESPONSE_60x,			//19
	CHECK_VOLTAGE,			//20
	GET_LOCATION			//21
};

class SIMX : public LocationProvider {

    private :

		StringBox *stringBox = NULL;
        ATCommandExecutor *atEx = NULL;
        const char *PIN = NULL;
        const char *APN = NULL;
        const char *url = NULL;
        const char *headers = NULL;
        uint8_t powerPin = 0;
        uint8_t resetPin = 0;
        uint8_t errorCounter = 0;
        uint8_t signalQuality = 0;
        uint16_t resetCounter = 0;
        uint16_t voltage = 0;
        uint16_t failedActionCounter = 0;
        float location[2] = {1000};			// 0 - lon, 1 - lat
        bool prepareFlag = false;			// check PIN and set APN
        bool networkFlag = false; 			// network redy to use
        bool SIMAvailableFlag = false;  	// SIM awailable (responds to requests)
        bool GPRSConnectionFlag = false;    // Internet ready
        bool useHTTPSFlag = false;
        Action lastFailureAction = EMPTY;
        Action lastSuccessfulAction  = EMPTY;
        SimpleTimer controlTimer0 = SimpleTimer(SELF_CONTROL_DELAY);
        SimpleTimer controlTimer1 = SimpleTimer(GET_LOCATION_DELAY);

		bool power();
		bool checkSIMBoard();
		void powerOn();
		void powerOff();
		void restart();
		void errorProcessing(Action lastFailureAction, const char *message = NULL);
        void successProcessing(Action lastSuccessfulAction);
		void checkErrors();
		bool checkSignal();
		bool checkPIN();
		bool configAPN();
		bool prepareGPRS();
		bool enableSSL();
		bool disableSSL();
		bool openGPRSConnection();
		bool checkNetwork();
		bool isNetworkReady();
		bool sendRequest(RequestMethod method, StringBuffer *body, uint16_t *httpStatusCode);
		bool initHttp();
		bool selectProfile();
		bool configUrl();
		bool setHeader();
		bool httpTerm();
		bool sendPostRequest(StringBuffer *buffer);
		bool sendGetRequest(StringBuffer *buffer);
		bool getHttpStatusCodeAndDataLength(StringBuffer *buffer, uint16_t *httpStatusCode, uint16_t *dataLength);
		bool setHttpData(StringBuffer *body);
		bool checkVoltage();
		bool checkLocation();
		
		
    public:

        SIMX(HardwareSerial *hs, uint8_t powerPin);
        ~SIMX();

        bool getAction (StringBuffer *responseBody,	uint16_t *responseCode);
        bool postAction(StringBuffer *requestBody, 	uint16_t *responseCode);
        
        void update();

		void setStringBox(StringBox *stringBox);
		void useHTTPS(bool flag);
		bool isHTTPSUsed();
        void setPIN(const char *PIN);
        void setResetPin(uint8_t resetPin);
        void setAPN(const char *APN);
        void setUrl(const char *url);
        void setHeaders(const char *headers);
        ATCommandExecutor* getAtCmdEx();
        uint8_t getSignalQuality();
        uint16_t getVoltage();
        uint16_t getResetCounter();
        float* getLocation();
        
        bool isReady();
};
