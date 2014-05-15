#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "./paho/src/MQTTAsync.h"

#define HOST			"q.m2m.io:1883"
#define CLIENT_ID		"g3z559a6c1"
#define TOPIC			"maaakhiz/test-topic"
#define PAYLOAD			"{'encoding':'json', 'language':'c'}"
#define QOS				0

int main(int argc, char* argv[]){
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	int rc;
	int ch;

	printf("Made it here.\n");
	return 0;
}