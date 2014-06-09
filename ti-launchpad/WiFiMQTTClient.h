#ifndef WiFiMQTTClient_h
#define WiFiMQTTClient_h

#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

class WiFiMQTTClient {
	private:
		PubSubClient psClient;
		WiFiClient wifiClient;
		unsigned long oldTimeLoop;
		unsigned long currTimeLoop;
		unsigned long oldTimePub;
		unsigned long currTimePub;
		unsigned int checkTime;	
		void printWifiStatus();
		void wifi_init(char*, char*);
	public:
		WiFiMQTTClient(char*, char*, char*, uint16_t, void(*)(char*,uint8_t*,unsigned int));
		WiFiMQTTClient(char*, char*, uint8_t*, uint16_t, void (*)(char*,uint8_t*,unsigned int));
		boolean connect(char *); 
		boolean connect(char *, char*, char*);
		boolean connect(char *, char*, uint8_t, uint8_t, char*);
		boolean connect(char *, char*, char*, char*, uint8_t, uint8_t, char*);
		void disconnect();
		boolean loop();
		boolean publish(char *, char *);
		boolean publish(char *, uint8_t*, unsigned int);
		boolean publish(char *, uint8_t*, unsigned int, boolean);
		boolean subscribe(char *);
		boolean unsubscribe(char *);
		boolean connected();
		void setCheckTime(unsigned int);
};

#endif