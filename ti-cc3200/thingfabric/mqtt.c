/* mqtt.c */

#include <stdio.h>
#include "mqtt.h"
//#include <string.h>
#include "simplelink.h"
//#include "netcfg.h"
#include "uart_if.h"
#include "gpio_if.h"
#include "bma222drv.h"
#include "tmp006drv.h"

// These are the defines for the 2lemetry mqtt broker
// The default USERID and PASSWORD is for the "TI account"
// To connect to your own account, you will need to modify
// the TWOLEMETRY_USERID, TWOLEMETRY_PASSWORD with your unique
// MD5 hash for your userid and password.
// You can use http://www.md5hashgenerator.com/ as an example
// Also, you should change the TWOLEMETRY_DOMAIN_STUFF to match
// your domain for your account instead of com.ti. The "stuff"
// name is set to CC3200, but you can set this to something different.
// THING_PREFIX could also be change to your own name if you like.
// The "thing" name starts with this prefix with the MAC address
// appended to the end. You could simplify this name if you like.

#define TWOLEMETRY_SERVER "q.m2m.io"
#define TWOLEMETRY_USERID "demo@ti.com"
#define TWOLEMETRY_PASSWORD "4c7a34d25eff9121c49658dbceadf694"
#define TWOLEMETRY_DOMAIN_STUFF "com.ti/msp430/"
#define THING_PREFIX	"MyName_"
#define THING_PREFIX_SIZE	7

#define OPEN_BRACKET		"{"
#define OPEN_BRACKET_QUOTE	"{\""
#define QUOTE_CLOSE_BRACKET "\" }"
#define CLOSE_BRACKET		"}"
#define QUOTE_COLON			"\":"
#define QUOTE_COLON_QUOTE 	"\":\""
#define QUOTE				"\""
#define COMMA				","

#define SMALL_BUF           32
#define SMALL_BUF_2x        (SMALL_BUF * 2)
#define MAX_SEND_BUF_SIZE   512
#define MAX_SEND_RCV_SIZE   1024

// 2lemetry mqtt broker is at port 1883
unsigned int gPort = 1883;
char MACAddress[SL_MAC_ADDR_LEN+2];
unsigned char MACAddressLen = SL_MAC_ADDR_LEN;
char MACAddressHex[SL_MAC_ADDR_LEN*2+2];
char thingName[THING_PREFIX_SIZE+sizeof(MACAddressHex)+2];

// sensor data - used to simulate data from CC3200
float Temperature;
signed char Accel_X;
signed char Accel_Y;
signed char Accel_Z;

struct
{
	char HostName[SMALL_BUF];
	unsigned long DestinationIP;
	int SockID;
	char sendBuff[MAX_SEND_BUF_SIZE];
	char Recvbuff[MAX_SEND_RCV_SIZE];
	mqtt_broker_handle_t broker;
}appData;

int CreateConnection()
{
	SlSockAddrIn_t  Addr;

	long sd = 0;
	long AddrSize = 0;
	short ret_val = 0;

	Addr.sin_family = SL_AF_INET;
	Addr.sin_port = sl_Htons(gPort); //gPort usually 80, but mqqt broker is port 1883

	/* Change the DestinationIP endianity, to big endian */
	Addr.sin_addr.s_addr = sl_Htonl(appData.DestinationIP);

	AddrSize = sizeof(SlSockAddrIn_t);

	sd = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, 0);
	if( sd < 0 )
	{
		Report("Error creating socket\r\n\r\n");
		return sd;
	}

	ret_val = sl_Connect(sd, ( SlSockAddr_t *)&Addr, AddrSize);
	if( ret_val < 0 )
	{
		/* error */
		Report("Error connecting to socket\r\n\r\n");
		return ret_val;
	}

	return sd;
}

int GetHostIP()
{
	unsigned long status = 0;

	status = sl_NetAppDnsGetHostByName(appData.HostName,
			strlen(appData.HostName),
			&appData.DestinationIP, SL_AF_INET);
	if (status != 0)
	{
		Report("Unable to reach Host\r\n\r\n");
		return -1;
	}

	return 0;
}

void hexify(char * src, char * dst, unsigned int dstlen)
{
	static const char alphabet[] = "0123456789ABCDEF";

	unsigned int i = 0;
	while (*src && 2*i + 1 < dstlen)
	{
		dst[2*i]   = alphabet[*src / 16];
		dst[2*i+1] = alphabet[*src % 16];
		++src;
		++i;
	}
	dst[2*i] = 0;
}
void getMacAddress(void)
{
	char * p_bufLocation = NULL;

	sl_NetCfgGet(SL_MAC_ADDRESS_GET,NULL,&MACAddressLen,(unsigned char *)MACAddress);

	hexify(MACAddress, MACAddressHex, SL_MAC_ADDR_LEN*2);
	//Report("MAC Address: ");
	//Report(MACAddressHex);

	memset(thingName, 0x00, sizeof(thingName));
	p_bufLocation = thingName;
	strcpy(p_bufLocation, THING_PREFIX);
	p_bufLocation += THING_PREFIX_SIZE;
	strcpy(p_bufLocation, MACAddressHex);
}

//Return a json pair string of format "name":value
//If needed, we could create a similar function json_pair_string
//that would return the value as a string, e.g. "name":"value"
//The third argument would then be of type char *
void json_pair_int(char * pair, const char *name, int8_t value)
{
	char valueString[5];

	memset(pair, 0, sizeof(pair));
	strcpy(pair, QUOTE);
	pair += strlen(QUOTE);

	strcpy(pair, name);
	pair += strlen(name);

	strcpy(pair, QUOTE_COLON);
	pair += strlen(QUOTE_COLON);

	//need to convert integer "value" to string "valueString"
	memset(valueString, 0, sizeof(valueString));
	sprintf(valueString, "%d", value);
	strcpy(pair, valueString);
}

void publishSensorData(void)
{
	char * p_bufLocation = NULL;
	char json_pair[40];
	char payload_data[512];
	char pubTopic[50];

	// Read the Accelerometer values
	BMA222ReadNew(&Accel_X, &Accel_Y, &Accel_Z);

	// Read the temperature sensor value
	TMP006DrvGetTemp(&Temperature);

	// construct payload
	memset(payload_data, 0, sizeof(payload_data));
	p_bufLocation = payload_data;

	strcpy(p_bufLocation, OPEN_BRACKET);
	p_bufLocation += strlen(OPEN_BRACKET);

	json_pair_int(json_pair,"Temp", Temperature);
	strcpy(p_bufLocation, json_pair);
	p_bufLocation += strlen(json_pair);

	strcpy(p_bufLocation, COMMA);
	p_bufLocation += strlen(COMMA);

	json_pair_int(json_pair,"Accel_X", Accel_X);
	strcpy(p_bufLocation, json_pair);
	p_bufLocation += strlen(json_pair);

	strcpy(p_bufLocation, COMMA);
	p_bufLocation += strlen(COMMA);

	json_pair_int(json_pair,"Accel_Y", Accel_Y);
	strcpy(p_bufLocation, json_pair);
	p_bufLocation += strlen(json_pair);

	strcpy(p_bufLocation, COMMA);
	p_bufLocation += strlen(COMMA);

	json_pair_int(json_pair,"Accel_Z", Accel_Z);
	strcpy(p_bufLocation, json_pair);
	p_bufLocation += strlen(json_pair);

	strcpy(p_bufLocation, CLOSE_BRACKET);
	p_bufLocation += strlen(CLOSE_BRACKET);

	// build publish topic with MAC address for unique device topic

	memset(pubTopic, 0, sizeof(pubTopic));
	p_bufLocation = pubTopic;
	strcpy(p_bufLocation, TWOLEMETRY_DOMAIN_STUFF);
	p_bufLocation += strlen(TWOLEMETRY_DOMAIN_STUFF);
	strcpy(p_bufLocation, thingName);

	//		Report("Topic: %s", pubTopic);
	Report("Publishing to """"%s"""": %s\r\n", pubTopic, payload_data);

	// publish the data
	mqtt_publish(&appData.broker, pubTopic, payload_data);
}

void mqtt_init_auth(mqtt_broker_handle_t* broker, const char* username, const char* password) {
	if(username && username[0] != '\0')
		strncpy(broker->username, username, strlen(username));
	if(password && password[0] != '\0')
		strncpy(broker->password, password, strlen(password));
}

int mqtt_connect(mqtt_broker_handle_t* broker)
{
	uint8_t flags = 0x00;

	int16_t received;

	uint16_t clientidlen = strlen(broker->clientid);
	uint16_t usernamelen = strlen(broker->username);
	uint16_t passwordlen = strlen(broker->password);
	uint16_t payload_len = clientidlen + 2;

	// Preparing the flags
	if(usernamelen) {
		payload_len += usernamelen + 2;
		flags |= MQTT_USERNAME_FLAG;
	}
	if(passwordlen) {
		payload_len += passwordlen + 2;
		flags |= MQTT_PASSWORD_FLAG;
	}
	if(broker->clean_session) {
		flags |= MQTT_CLEAN_SESSION;
	}

	// Variable header
	uint8_t var_header[] = {
			0x00,0x06,0x4d,0x51,0x49,0x73,0x64,0x70, // Protocol name: MQIsdp
			0x03, // Protocol version
			0,//	flags, // Connect flags
			0,0//	broker->alive>>8, broker->alive&0xFF, // Keep alive
	};
	var_header[9] = flags;
	var_header[10] = broker->alive>>8;
	var_header[11] = broker->alive&0xFF;

	// Fixed header
	uint8_t remainLen = sizeof(var_header)+payload_len;
	uint8_t fixed_header[3];
	uint8_t fixedHeaderSize = 2;  // Default size = one byte Message Type + one byte Remaining Length

	if (remainLen > 127) {
		fixedHeaderSize++;          // add an additional byte for Remaining Length
	}

	// Message Type
	fixed_header[0] = MQTT_MSG_CONNECT;

	// Remaining Length
	if (remainLen <= 127) {
		fixed_header[1] = remainLen;
	} else {
		// first byte is remainder (mod) of 128, then set the MSB to indicate more bytes
		fixed_header[1] = remainLen % 128;
		fixed_header[1] = fixed_header[1] | 0x80;
		// second byte is number of 128s
		fixed_header[2] = remainLen / 128;
	}

	uint16_t offset = 0;
	uint16_t packet_size = fixedHeaderSize + sizeof(var_header) + payload_len;

	memcpy(appData.sendBuff, fixed_header, fixedHeaderSize);
	offset += fixedHeaderSize;
	memcpy(appData.sendBuff+offset, var_header, sizeof(var_header));
	offset += sizeof(var_header);

	// Client ID - UTF encoded
	appData.sendBuff[offset++] = clientidlen>>8;
	appData.sendBuff[offset++] = clientidlen&0xFF;
	memcpy(appData.sendBuff+offset, broker->clientid, clientidlen);
	offset += clientidlen;

	if(usernamelen) {
		// Username - UTF encoded
		appData.sendBuff[offset++] = usernamelen>>8;
		appData.sendBuff[offset++] = usernamelen&0xFF;
		memcpy(appData.sendBuff+offset, broker->username, usernamelen);
		offset += usernamelen;
	}

	if(passwordlen) {
		// Password - UTF encoded
		appData.sendBuff[offset++] = passwordlen>>8;
		appData.sendBuff[offset++] = passwordlen&0xFF;
		memcpy(appData.sendBuff+offset, broker->password, passwordlen);
		offset += passwordlen;
	}

	Report("MQTT connecting...");

	// Send the packet
	sl_Send(appData.SockID, appData.sendBuff, packet_size, 0);

	//Receive response
	memset(appData.Recvbuff, 0, sizeof(appData.Recvbuff));
	received = sl_Recv(appData.SockID, &appData.Recvbuff[0], MAX_SEND_RCV_SIZE, 0);

	if(received > 0)
	{
		if(MQTTParseMessageType(appData.Recvbuff) == MQTT_MSG_CONNACK && appData.Recvbuff[3] == 0x00)
		{
			Report("connected.\n\r");
			return 0;
		}
		else
		{
			Report("MQTT connection error\n\r");
			return 1;
		}
	}
	else
	{
		return 1;
	}
}

// simple publish - QoS 0, no retain
int mqtt_publish(mqtt_broker_handle_t* broker, const char* topic, const char* msg) {

	uint16_t topiclen = strlen(topic);
	uint16_t msglen = strlen(msg);

	uint8_t qos_flag = MQTT_QOS0_FLAG;

	// Variable header
	uint8_t var_header[100];      // topic size + 2 bytes (utf-encoded topic)
	uint8_t varHeaderSize = topiclen+2;
	memset(var_header, 0, varHeaderSize);
	var_header[0] = topiclen>>8;
	var_header[1] = topiclen&0xFF;
	memcpy(var_header+2, topic, topiclen);

	// Fixed header
	// the remaining length is one byte for messages up to 127 bytes, then two bytes after that
	// actually, it can be up to 4 bytes but I'm making the assumption the embedded device will only
	// need up to two bytes of length (handles up to 16,383 (almost 16k) sized message)
	uint8_t fixed_header[3];      // may or may not end up using 3 bytes
	uint8_t fixedHeaderSize = 2;  // Default size = one byte Message Type + one byte Remaining Length
	uint16_t remainLen = varHeaderSize+msglen;
	if (remainLen > 127) {
		fixedHeaderSize++;          // add an additional byte for Remaining Length
	}

	// Message Type, DUP flag, QoS level, Retain
	fixed_header[0] = MQTT_MSG_PUBLISH | qos_flag;

	// Remaining Length
	if (remainLen <= 127) {
		fixed_header[1] = remainLen;
	} else {
		// first byte is remainder (mod) of 128, then set the MSB to indicate more bytes
		fixed_header[1] = remainLen % 128;
		fixed_header[1] = fixed_header[1] | 0x80;
		// second byte is number of 128s
		fixed_header[2] = remainLen / 128;
	}

	uint16_t packet_size = fixedHeaderSize+varHeaderSize+msglen;

	memcpy(appData.sendBuff, fixed_header, fixedHeaderSize);
	memcpy(appData.sendBuff+fixedHeaderSize, var_header, varHeaderSize);
	memcpy(appData.sendBuff+fixedHeaderSize+varHeaderSize, msg, msglen);

	// Send the packet
	sl_Send(appData.SockID, appData.sendBuff, packet_size, 0);

	return 1;
}

void connect2mqqtbroker(void)
{
	// MQTT connection options
	appData.broker.alive = 300; // 300 seconds = 5 minutes
	appData.broker.seq = 1; // Sequence for message indetifiers

	// MQTT client options
	memset(appData.broker.clientid, 0, sizeof(appData.broker.clientid));
	memset(appData.broker.username, 0, sizeof(appData.broker.username));
	memset(appData.broker.password, 0, sizeof(appData.broker.password));
	strncpy(appData.broker.clientid, (const char *)MACAddressHex, sizeof(MACAddressHex));
	appData.broker.clean_session = 1;

	mqtt_init_auth(&appData.broker, TWOLEMETRY_USERID, TWOLEMETRY_PASSWORD);

	strcpy(appData.HostName, TWOLEMETRY_SERVER);

	if(GetHostIP() == 0)
	{
		// establish socket connection
		if( (appData.SockID = CreateConnection()) < 0 )
		{
			Report("Could not create connection\r\n");
			return;
		}

		// send MQTT connect
		if (mqtt_connect(&appData.broker) != 0)
		{
			return;
		}
	}
	else
	{
		Report("Could not get Host IP\r\n ");
	}
}

void mqttTask(void *pvParameters)
{
extern OsiSyncObj_t semaphore_Connected;
OsiTime_t timeout=30000;

	if (osi_SyncObjWait(&semaphore_Connected, timeout) != OSI_OK )
	{
		Report("mqttTask timed out waiting for internet access\r\n");
		return;
	}

	/* Display banner */
	Report("\r\n\r\nTexas Instruments CC3200 Application\r\n");
	Report("Powered by 2lemetry's ThingFabric Cloud\r\n\r\n");
	Report("Ready to sample and publish 64 sets of sensor data to 2lemetry server\r\n");
	Report("Move the CC3200 LaunchPad in three dimensions to change Accelerometer values\r\n");
	Report("To see your sample data in a web browser, go to http://ti-act.2lemetry.com/\r\n");

	// Initialize the GPIO ports for SW2 and SW3 push buttons - no this is done in button_if.c
	//	GPIODirModeSet(GPIOA1_BASE, GPIO_PIN5, GPIO_DIR_MODE_IN); //S3 is GPIO_13
	//	GPIODirModeSet(GPIOA2_BASE, GPIO_PIN6, GPIO_DIR_MODE_IN); // S2 is GPIO_22

	// Need to wait for OOBTask to obtain an internet connection before proceeding
	// If started in AP mode, it will never connect
	// If started in STA mode, need to wait for connection, possibly smartconfig



	getMacAddress(); //this is done for pubTopic, unique ID for the device

	connect2mqqtbroker();

	while(1)
	{

		osi_Sleep(100);
		GPIO_IF_LedOn(MCU_RED_LED_GPIO);
		publishSensorData(); //publish accellerometer and temperature values
		osi_Sleep(400);
		GPIO_IF_LedOff(MCU_RED_LED_GPIO);

	}
}
