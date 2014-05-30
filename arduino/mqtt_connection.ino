#include <SPI.h>
#include "PubSubClient.h"
#include <Ethernet.h>
 
#define MQTT_SERVER "q.m2m.io"
#define TOPIC "maaakihz/test-stuff/test-thing"
#define CLIENT_ID "g3z559a6c1"
#define TOKEN_HASH "fe61771c6a61d59a3e6ea432521c3bf8"
#define PAYLOAD "{\"Hello\":\"World!\"}"
 
// MAC Address of Arduino Ethernet Shield (on sticker on shield)
byte MAC_ADDRESS[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
PubSubClient client;

char message_buff[100];

void setup()
{
  // init serial link for debugging
  Serial.begin(9600);

  if (Ethernet.begin(MAC_ADDRESS) == 0)
  {
      Serial.println("Failed to configure Ethernet using DHCP");
      return;
  }

  client = PubSubClient(MQTT_SERVER, 1883, callback);
}

void loop()
{
  if (!client.connected())
  {
      // clientID, username, MD5-hashed token
      client.connect(CLIENT_ID, CLIENT_ID, PASSWORD);
      client.subscribe(TOPIC);
      client.publish(TOPIC, PAYLOAD);
  }

  // MQTT client loop processing
  client.loop();
}

// handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length));

  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '';

  String msgString = String(message_buff);

  Serial.println("Payload: " + msgString);
}