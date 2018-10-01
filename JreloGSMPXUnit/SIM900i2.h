#pragma once
#include <Arduino.h>
#include <SIM.h>
#include <AT.h>
#include <SimpleTimer.h>
#include <StringBuffer.h>

#define DEBUG true

#define MAX_NETWORK_CHECKS 16
#define MAX_PREP_GPRS 3
#define RESTART_DELAY 60000
#define CHECK_NETWORK_DELAY 10000
#define SELF_CONTROL_DELAY 5000
#define MAX_OTHER_PROBLEMS 5


enum RequestMethod {
    GET  = 0,
    POST = 1
};

enum SignalQuality {
	NO,					// 0
	MARGINAL,			// 1
	OK,					// 2
	GOOD,				// 3
	EXCELLENT			// 4
};

enum Action {
    EMPTY, 									// 0
    POWER_UP, 								// 1
    CHECK_PIN, 								// 2
    CHECK_NETWORK, 							// 3
    PREPARE_GPRS, 							// 4
    SET_SSL, 								// 5
    RESERVE, 								// 6
    SELECT_PROFILE, 						// 7
    SET_URL, 								// 8
    SET_HEADER, 							// 9
    CONFIG_APN, 							// 10
    INIT_HTTP, 								// 11
    SEND_GET_REQUEST, 						// 12
    GET_HTTP_STATUS_CODE, 					// 13
    HTTP_READ, 								// 14
    HTTP_PARA, 								// 15
    HTTP_DATA_DOWNLOAD_P1, 					// 16
    HTTP_DATA_DOWNLOAD_P2, 					// 17
    SEND_POST_REQUEST, 						// 18
    GET_HTTP_STATUS_CODE_AND_DATA_LENGTH, 	// 19
    HTTP_TERM 								// 20
};

class SIM900i2 : public SIM {

    private:
		
		StringBox *stringBox = NULL;
        AT *at = NULL;
        int powerPin = 0;
        int httpStatusCode = 0;
        bool https = false;
        char *pin = NULL;
        char *apn = NULL;
        StringBuffer *responseBody = NULL;
        
        int errorCounter = 0;
        int rebootCounter = 0;
        SimpleTimer selfControlTimer = SimpleTimer(SELF_CONTROL_DELAY);
        SimpleTimer restartTimer = SimpleTimer(RESTART_DELAY, true, false);
        SimpleTimer networkTimer = SimpleTimer(CHECK_NETWORK_DELAY);
        bool workFlag = false;
        bool readyFlag = false;
        bool prepareFlag = false;
        Action lastError = EMPTY;
        Action lastSuccess = EMPTY;
        SignalQuality signalQuality = NO;

        void errorProcessing(Action lastFail, char *message);
        void successProcessing(Action lastSuccess);
        bool powerOn();
        bool powerOff();
        bool checkPin();
        bool checkNetwork();
        void reset();
        void checkErrors();
        bool prepare();
        bool isWorking();
        bool isNetworkReady();
        bool checkPower();
        bool prepareGPRS();
        bool openGPRSConnection();
        bool enableSSL();
        bool checkSignal();
        bool configAPN();
        bool sendRequest(RequestMethod method, char *url, char *header, char *requestBody);
        bool initHttp();
        bool httpTerm();
        bool selectProfile();
        bool setUrl(char *url);
        bool setHeader(char *header);
        bool getHttpStatusCodeAndDataLength(StringBuffer *sb, RequestMethod method, int *httpStatusCode, int *dataLength);
		bool sendGetRequest(StringBuffer *sb);
		bool sendPostRequest(StringBuffer *sb);
		bool setHttpData(char *requestBody);
		int getSignalQuality();
	
    public :
    
        SIM900i2(HardwareSerial *hs, int powerPin); 
        ~SIM900i2(); 
        void setPIN(char *pin); 
        void setAPN(char *apn); 
        void useHTTPS(bool https); 
        bool getData(char *url, char *header);
        bool postData(char *requestBody, char *url, char *header);
        int getHttpStatusCode();
        StringBuffer* getResponseBody();
        void clearResponse();       
        void update() override;
        bool isReady() override; 
        bool isHTTPSUsed();
        void setStringBox(StringBox *stringBox);
        StringBox* getStringBox();
        void setAT(AT *at);
        AT* getAT();
        
        
};
