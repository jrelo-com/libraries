/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.0.0
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

#define DEBUG
#define SELF_CONTROL_AND_CHECK_NETWORK_DELAY 5000
#define MCE_CHECK_NETWORK 15
#define MCE_INIT_HTTP 15
#define MCE_RESPONSE_60x 1
#define MCE_PREPARE_GPRS 15
#define MCE_OTHER 5


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
	SEND_GET_REQUEST,		//14	
	HTTP_TERM,				//15
	HTTP_PARA,				//16
	SEND_POST_REQUEST,		//17
	HTTP_DATA_DOWNLOAD_P1, 	//18
	HTTP_DATA_DOWNLOAD_P2, 	//19
	RESPONSE_60x			//20
};

class SIMX {

    private :

		StringBox *stringBox = NULL;
        ATCommandExecutor *atEx = NULL;
        char *PIN = NULL;
        char *APN = NULL;
        char *url = NULL;
        char *headers = NULL;
        uint8_t powerPin = 0;
        uint8_t resetPin = 0;
        uint8_t errorCounter = 0;
        uint8_t rebootCounter = 0;
        uint8_t signalQuality = 0;
        bool prepareFlag = false;			// check PIN and set APN
        bool networkFlag = false; 			// network redy to use
        bool SIMAvailableFlag = false;  	// SIM awailable (power on and responsed)
        bool GPRSConnectionFlag = false;    // Internet ready
        bool useHTTPSFlag = false;
        Action lastFailureAction = EMPTY;
        Action lastSuccessfulAction  = EMPTY;
        SimpleTimer controlTimer = SimpleTimer(SELF_CONTROL_AND_CHECK_NETWORK_DELAY);

		bool power();
		bool checkSIMBoard();
		void powerOn();
		void powerOff();
		void restart();
		void errorProcessing(Action lastFailureAction, char *message = NULL);
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
		
    public:

        SIMX(HardwareSerial *hs, uint8_t powerPin);
        ~SIMX();

        bool getAction (StringBuffer *responseBody,	uint16_t *responseCode);
        bool postAction(StringBuffer *requestBody, 	uint16_t *responseCode);
        
        void update();

		void setStringBox(StringBox *stringBox);
		void useHTTPS(bool flag);
		bool isHTTPSUsed();
        void setPIN(char *PIN);
        void setResetPin(uint8_t resetPin);
        void setAPN(char *APN);
        void setUrl(char *url);
        void setHeaders(char *headers);
        ATCommandExecutor* getAtCmdEx();

        bool isReady();

};
