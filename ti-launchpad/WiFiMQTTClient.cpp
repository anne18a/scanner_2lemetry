#include "WiFiMQTTClient.h"

char * clientID = NULL;
char * user = NULL;
char * pass = NULL;
char * willTopic = 0;
uint8_t willQos = 0; 
uint8_t willRetain = 0; 
char * willMessage = 0;

char * wifi_ssid = NULL;
char * wifi_pass = NULL;


WiFiMQTTClient::WiFiMQTTClient(char* ssid, char* pass, char* domain, uint16_t port, void (*callback)(char*,uint8_t*,unsigned int)) {	
	wifi_ssid = ssid;
	wifi_pass = pass;
	checkTime = 0;
	psClient = PubSubClient(domain, port, callback, wifiClient);
	wifi_init(wifi_ssid, wifi_pass);
}

WiFiMQTTClient::WiFiMQTTClient(char* ssid, char* pass, uint8_t *ip, uint16_t port, void (*callback)(char*,uint8_t*,unsigned int)) {	
	wifi_ssid = ssid;
	wifi_pass = pass;
	checkTime = 0;
	psClient = PubSubClient(ip, port, callback, wifiClient);
	wifi_init(wifi_ssid, wifi_pass);
}

boolean WiFiMQTTClient::connect(char *_clientID) {
	clientID = _clientID;
	user = NULL;
	pass = NULL;
	willTopic = 0;
	willQos = 0;
	willRetain = 0;
	willMessage = 0;	
	bool res = psClient.connect(clientID, user, pass, willTopic, willQos, willRetain, willMessage);
	currTimeLoop = 0;
	oldTimeLoop = millis();
	currTimePub = 0;
	oldTimePub = millis();
	return res; 
}

boolean WiFiMQTTClient::connect(char *_clientID, char *_user, char *_pass) { 
	clientID = _clientID;
	user = _user;
	pass = _pass;
	willTopic = 0;
	willQos = 0;
	willRetain = 0;
	willMessage = 0;	
	bool res = psClient.connect(clientID, user, pass, willTopic, willQos, willRetain, willMessage);
	currTimeLoop = 0;
	oldTimeLoop = millis();
	currTimePub = 0;
	oldTimePub = millis();
	return res; 
}

boolean WiFiMQTTClient::connect(char *_clientID, char* _willTopic, uint8_t _willQos, uint8_t _willRetain, char* _willMessage) {
	clientID = _clientID;
	user = NULL;
	pass = NULL;
	willTopic = _willTopic;
	willQos = _willQos;
	willRetain = _willRetain;
	willMessage = _willMessage;	
	bool res = psClient.connect(clientID, user, pass, willTopic, willQos, willRetain, willMessage);
	currTimeLoop = 0;
	oldTimeLoop = millis();
	return res;
}
boolean WiFiMQTTClient::connect(char *_clientID, char *_user, char *_pass, char* _willTopic, uint8_t _willQos, uint8_t _willRetain, char* _willMessage) {
	clientID = _clientID;
	user = _user;
	pass = _pass;
	willTopic = _willTopic;
	willQos = _willQos;
	willRetain = _willRetain;
	willMessage = _willMessage;
	bool res = psClient.connect(clientID, user, pass, willTopic, willQos, willRetain, willMessage);
	currTimeLoop = 0;
	oldTimeLoop = millis();
	return res;
}

void WiFiMQTTClient::disconnect() {
	psClient.disconnect();
	WiFi.disconnect();
	checkTime = 0;
}

boolean WiFiMQTTClient::loop() {
	currTimeLoop = millis(); 
	if(checkTime > 0 && (currTimeLoop - oldTimeLoop > checkTime*1000 || oldTimeLoop > currTimeLoop)){ //check status every checkTime seconds (if checkTime<=0 then not check)
		oldTimeLoop = currTimeLoop;
		if(WiFi.status() == WL_CONNECTED){
			if (psClient.connected()) {
				Serial.println("C");
    		} else {
				Serial.println("NC");
				Serial.println("Client Connecting...");
				psClient.connect(clientID, user, pass, willTopic, willQos, willRetain, willMessage);
				return false;
			}
		} else {
			Serial.print("WiFi status: ");
			Serial.println(WiFi.status());
			wifi_init(wifi_ssid, wifi_pass);
			return false;
		}		
	}
	return psClient.loop();
}

boolean WiFiMQTTClient::publish(char* topic, char* payload) {
	currTimePub = millis(); 
	if((currTimePub - oldTimePub > 200 || oldTimePub > currTimePub)){
		oldTimePub = currTimePub;
		return psClient.publish(topic,(uint8_t*)payload,strlen(payload),false);
	}
	return false;
}

boolean WiFiMQTTClient::publish(char* topic, uint8_t* payload, unsigned int plength) {
	currTimePub = millis(); 
	if((currTimePub - oldTimePub > 200 || oldTimePub > currTimePub)){
		oldTimePub = currTimePub;
		return psClient.publish(topic, payload, plength, false);
	}
	return false;
}

boolean WiFiMQTTClient::publish(char* topic, uint8_t* payload, unsigned int plength, boolean retained) {
	currTimePub = millis(); 
	if((currTimePub - oldTimePub > 200 || oldTimePub > currTimePub)){
		oldTimePub = currTimePub;
		return psClient.publish(topic, payload, plength, retained);
	}
	return false;
}

boolean WiFiMQTTClient::subscribe(char* topic) {
	return psClient.subscribe(topic);
}

boolean WiFiMQTTClient::unsubscribe(char* topic) {
	return psClient.unsubscribe(topic);
}

boolean WiFiMQTTClient::connected() {
	return psClient.connected()&&(WiFi.status() == WL_CONNECTED);
}

// time in seconds
void WiFiMQTTClient::setCheckTime(unsigned int time){
	if(time > 0){
		checkTime = time;
	} else {
		checkTime = 0;
	}
}

void WiFiMQTTClient::printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void WiFiMQTTClient::wifi_init(char* _ssid, char* _pass){
	Serial.println("CC3000");	
	WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
	WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
	WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C
	Serial.print("Attempting to connect to SSID: ");
	Serial.println(_ssid);    
	WiFi.begin(_ssid, _pass);
	Serial.println("Connected to wifi");
	Serial.println("Waiting for DHCP address....");
	int count = 0;
	while(IPAddress(0, 0, 0, 0) == WiFi.localIP() && count < 60){		// wait 1 minute
		delay(1000);
		count ++;
	}  
	printWifiStatus(); 
}