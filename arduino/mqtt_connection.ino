/*
 Basic MQTT example with Authentication
 
  - connects to an MQTT server, providing username
    and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Change username and password to values found in Your Credentials.
char CLIENT_ID[] = /* Client ID */;
char TOKEN_HASH[] = /* MD5-hashed token */;
char HOST[] = "q.m2m.io";
int PORT = 1883;
char TOPIC[] = /* domain/topic */
char PAYLOAD[] = "{\"Hello\":\"World\"}";


// Update these with values suitable for your network.
byte mac[]    = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  // MAC address
byte server[] = { 0, 0, 0, 0 }; // IP
byte ip[]     = { 0, 0, 0, 0 }; // IP

void on_message(char* topic, byte* payload, unsigned int length) {
  // Accept and handle the newly arrived message
}

EthernetClient ethClient;
PubSubClient client(server, 1883, on_message, ethClient);

void setup()
{
  Ethernet.begin(mac, ip);
  if (client.connect(CLIENT_ID, CLIENT_ID, TOKEN_HASH)) {
    client.subscribe(TOPIC);
    client.publish(TOPIC, PAYLOAD);
  }
}

void loop()
{
  client.loop();
}