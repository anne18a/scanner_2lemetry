#include <WiFiMQTTClient.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

/*
 * A simple ThingFabric demo for the TI Launchpad
 */

#define       SERVER       "q.thingfabric.com"
#define       PORT         1883
#define       CLIENT_ID       "TIlaunchpad"
#define       USERNAME         "[your username]"
#define       TOKEN        "[your MD5-hashed token]"
#define       MQTT_SUB_TOPIC    "[domain]/test-stuff/test-thing"
#define       MQTT_PUB_TOPIC    "[domain]/test-stuff/test-thing"
#define       MQTT_PUB_PAYLOAD  "{\"Hello\":\"World!\"}"
#define       WIFI_SSID         "[wifi network name]"
#define       WIFI_PWD          "[wifi network password]"

WiFiMQTTClient *Clt;

long count = 0;
int pub_time = 0;
boolean high;
char msg[100];

void setup()
{
  Serial.begin(9600);
  delay(500);

  Clt = new WiFiMQTTClient(WIFI_SSID, WIFI_PWD, SERVER, PORT, Callback);
  Clt->setCheckTime(0.1);

  delay(2000);
  Serial.println("End setup.");
}

void loop()
{
  if(!Clt->connected())
  {
    if(Clt->connect(CLIENT_ID, USERNAME, TOKEN)) {
      Serial.println("Successfully Connected...");
      Clt->publish(MQTT_PUB_TOPIC, MQTT_PUB_PAYLOAD);
      Serial.println("Message published!");
      Clt->subscribe(MQTT_SUB_TOPIC);
      Serial.println("Subscribed!");
    } 
    else {
      Serial.println("Failed to connect!");
    }
  }

  Clt->loop();
}

void Callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(payload);
}
