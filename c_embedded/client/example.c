/***
Example MQTT Client for Embedded Applications

Includes provisioning message and sensor loop.
***/

#include "../include/libemqtt.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/* Choose one of these .h files depeding on your platform */

/* #include <linux/tcp.h> */	/* For Linux applications */
#include <netinet/tcp.h>		/* For OSX applications */

#include <netdb.h>

// values below can be found by logging into the thingfabric.com portal (http://app.thingfabric.com)
// Username:  your email address you used to create the account
// Password:  MD5 hash of your password (32 character string)
// Domain:  Randomly generated.  Can be found on Accounts tab in portal.
// Device Type:  Can remain "things".  If this device is a commonly supported
//               device on the thingfabric.com portal there may be a type to choose.
//               For example, Arduino.
// Device ID: A string uniquely identifying this device from your other
//            devices.  Only needs to be unique to you, not across all users.
//            Common examples include device's MAC address or serial number.
//            Device-1, Device-2 are fine too.

#define  THINGFABRIC_USERNAME   	"g3z559a6c1"
#define  THINGFABRIC_PASSWORD   	"fe61771c6a61d59a3e6ea432521c3bf8"	/* pre-hashed (MD5) token */
#define  THINGFABRIC_DOMAIN     	"maaakihz"			/* domain */
#define  THINGFABRIC_DEVICE_TYPE	"test-stuff"		/* topic */
#define  THINGFABRIC_DEVICE_ID  	"test-thing"		/* device */
#define  THINGFABRIC_BROKER_HOSTNAME "q.thingfabric.com"
#define	 THINGFABRIC_BROKER_PORT	1883	/* Use port 8883 for SSL */

#define RCVBUFSIZE 1024
uint8_t packet_buffer[RCVBUFSIZE];

int socket_id;
char broker_ip[100];  // holds return ip address from DNS lookup

// scratch space to build message payloads
char pubMsgStr[250];

// variables, function to make a "fake" sensor
int sensorCount = 0;
int tempReading[20] = { 45, 46, 49, 51, 45, 32, 35, 66, 43, 48,
							   43, 41, 39, 31, 35, 34, 35, 56, 63, 38 };

int hostname_to_ip(char * hostname , char* ip);

int readTemperatureSensor(void) {
   int temp = tempReading[sensorCount];
	sensorCount = sensorCount >= 19 ? 0 : sensorCount+1;
	return temp;
}

// json helper routines
void initJsonMsg(char *buffer) {
   sprintf(buffer, "%s", "{");
}

void finishJsonMsg(char *buffer) {
   sprintf(buffer+strlen(buffer), "%s", "}");
}

void addStringValToMsg(const char *n, const char *v, char *buffer) {
   if (strlen(buffer) > 1) {
      sprintf(buffer+strlen(buffer), ",");
   }
   sprintf(buffer+strlen(buffer), "\"%s\":", n);
   sprintf(buffer+strlen(buffer), "\"%s\"", v);
}

void addIntValToMsg(const char *n, const long l, char *buffer) {
   if (strlen(buffer) > 1) {
      sprintf(buffer+strlen(buffer), ",");
   }
   sprintf(buffer+strlen(buffer), "\"%s\":", n);
   sprintf(buffer+strlen(buffer), "%ld", l);
}

void addDoubleValToMsg(const char *n, const double d, char *buffer) {
   if (strlen(buffer) > 1) {
      sprintf(buffer+strlen(buffer), ",");
   }
   sprintf(buffer+strlen(buffer), "\"%s\":", n);
   sprintf(buffer+strlen(buffer), "%g", d);
}

int send_packet(void* socket_info, const void* buf, unsigned int count) {
	int fd = *((int*)socket_info);
	return send(fd, buf, count, 0);
}

int init_socket(mqtt_broker_handle_t* broker, const char* hostname, short port) {
	int flag = 1;
	int keepalive = 3; // Seconds

	// Create the socket
	if((socket_id = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	// Disable Nagle Algorithm
	if (setsockopt(socket_id, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag)) < 0)
		return -2;

	struct sockaddr_in socket_address;
	// Create the stuff we need to connect
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);
	socket_address.sin_addr.s_addr = inet_addr(hostname);

	// Connect the socket
	if((connect(socket_id, (struct sockaddr*)&socket_address, sizeof(socket_address))) < 0)
		return -1;

	// MQTT stuffs
	mqtt_set_alive(broker, keepalive);
	broker->socket_info = (void*)&socket_id;
	broker->send = send_packet;

	return 0;
}

int close_socket(mqtt_broker_handle_t* broker) {
	int fd = *((int*)broker->socket_info);
	return close(fd);
}

int read_packet(int timeout) {
	if(timeout > 0) {
		fd_set readfds;
		struct timeval tmv;

		// Initialize the file descriptor set
		FD_ZERO (&readfds);
		FD_SET (socket_id, &readfds);

		// Initialize the timeout data structure
		tmv.tv_sec = timeout;
		tmv.tv_usec = 0;

		// select returns 0 if timeout, 1 if input available, -1 if error
		if(select(1, &readfds, NULL, NULL, &tmv))
			return -2;
	}

	int total_bytes = 0, bytes_rcvd, packet_length;
	memset(packet_buffer, 0, sizeof(packet_buffer));

	// Reading fixed header
	while(total_bytes < 2) {
		if((bytes_rcvd = recv(socket_id, (packet_buffer+total_bytes), RCVBUFSIZE - total_bytes, 0)) <= 0)
			return -1;
		total_bytes += bytes_rcvd; // Keep tally of total bytes
	}

	packet_length = packet_buffer[1] + 2; // Remaining length + fixed header length

	// Reading the packet
	while(total_bytes < packet_length) {
		if((bytes_rcvd = recv(socket_id, (packet_buffer+total_bytes), RCVBUFSIZE - total_bytes, 0)) <= 0)
			return -1;
		total_bytes += bytes_rcvd; // Keep tally of total bytes
	}

	return packet_length;
}

int main(int argc, char* argv[]) {
	int16_t packet_length;
	//uint16_t msg_id, msg_id_rcv;
	mqtt_broker_handle_t broker;

	char host[30];  // temp space for hostname string
	sprintf(host, THINGFABRIC_BROKER_HOSTNAME);
  char *hostname = host;
  hostname_to_ip(hostname , broker_ip);
  printf("\n%s resolved to %s\n" , hostname , broker_ip);

	// if user specified provisioning flag then first
	// provision device to user, then start sending sensor values
	if ((argc > 1) && (strcmp(argv[1], "-p") == 0)) {
		printf("Sending provisioning message...\n");
		char clientIDStr[100];
		sprintf(clientIDStr, "%s-%s", THINGFABRIC_DOMAIN, THINGFABRIC_DEVICE_ID);
		mqtt_init(&broker, clientIDStr);
		mqtt_init_auth(&broker, "", "");
	
		init_socket(&broker, broker_ip, THINGFABRIC_BROKER_PORT);
		mqtt_connect(&broker);

		// look for CONNACK	
		packet_length = read_packet(1);
		if(packet_length < 0) {
			fprintf(stderr, "Error(%d) on read packet!\n", packet_length);
			return -1;
		}

		if(MQTTParseMessageType(packet_buffer) != MQTT_MSG_CONNACK) {
			fprintf(stderr, "CONNACK expected!\n");
			return -2;
		}

		if(packet_buffer[3] != 0x00) {
			fprintf(stderr, "CONNACK failed!\n");
			return -2;
		}

		// build provisioning message payload string
		initJsonMsg(pubMsgStr);
		addStringValToMsg("type", THINGFABRIC_DEVICE_TYPE, pubMsgStr);
		addStringValToMsg("mac", THINGFABRIC_DEVICE_ID, pubMsgStr);
		finishJsonMsg(pubMsgStr);
		
		// publish message
		printf("Publish: %s\n", pubMsgStr);
		char enrollTopic[100];
		sprintf(enrollTopic, "public/enroll/%s", THINGFABRIC_USERNAME);
		mqtt_publish(&broker, enrollTopic, pubMsgStr, 0);

		mqtt_disconnect(&broker);
		close_socket(&broker);
	}

	sleep(5);

	// now connect using user/password, publish sensor values on
	// appropriate topic (<domain>/<device type>/<device id>
	char clientIDStr[100];
	sprintf(clientIDStr, "%s/%s", THINGFABRIC_DEVICE_TYPE, THINGFABRIC_DEVICE_ID);
	mqtt_init(&broker, clientIDStr);
	mqtt_init_auth(&broker, THINGFABRIC_USERNAME, THINGFABRIC_PASSWORD);
	init_socket(&broker, broker_ip, THINGFABRIC_BROKER_PORT);

	mqtt_connect(&broker);
	// wait for CONNACK	
	packet_length = read_packet(1);
	if(packet_length < 0) {
		fprintf(stderr, "Error(%d) on read packet!\n", packet_length);
		return -1;
	}

	if(MQTTParseMessageType(packet_buffer) != MQTT_MSG_CONNACK) {
		fprintf(stderr, "CONNACK expected!\n");
		return -2;
	}

	if(packet_buffer[3] != 0x00) {
		fprintf(stderr, "CONNACK failed!\n");
		return -2;
	}


	char pubTopic[100];
	sprintf(pubTopic, "%s/%s/%s", THINGFABRIC_DOMAIN, THINGFABRIC_DEVICE_TYPE, THINGFABRIC_DEVICE_ID);

	printf("%s\n", pubTopic);
	
	while (1) {
		// build publish message payload string
		initJsonMsg(pubMsgStr);
		addIntValToMsg("t", readTemperatureSensor(), pubMsgStr);
		finishJsonMsg(pubMsgStr);
		
		// publish message
		printf("Publish: %s\n", pubMsgStr);
		mqtt_publish(&broker, pubTopic, pubMsgStr, 0);

		sleep(3);
	}

	mqtt_disconnect(&broker);
	close_socket(&broker);
	return 0;
}

int hostname_to_ip(char* hostname , char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
		
	if ( (he = gethostbyname( hostname ) ) == NULL) 
	{
		// get the host info
		herror("gethostbyname");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}
	
	return 1;
}
