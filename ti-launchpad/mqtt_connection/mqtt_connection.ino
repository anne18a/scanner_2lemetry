#include <WiFiMQTTClient.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

/*
 * A simple ThingFabric demo for the TI Launchpad
 */

#define       SERVER            "q.thingfabric.com"
#define       PORT              1883
#define       CLIENT_ID         "launchpad-mqtt"    // This can be left empty and a random ID will be generated.  
                                      //You can add an ID if you'd like a human-readable way to identify the device.
#define       USERNAME          "<Your ThingFabric Credentials Username>"
#define       TOKEN             "<Your (pre-MD5 hashed) ThingFabric Credentials Token>"
#define       MQTT_SUB_TOPIC    "[domain]/test-stuff/test-thing"
#define       MQTT_PUB_TOPIC    "[domain]/test-stuff/test-thing"
#define       MQTT_PUB_PAYLOAD  "{\"Hello\":\"World!\"}"
#define       WIFI_SSID         "<Your WiFi Network SSID>"
#define       WIFI_PWD          "<Your WiFi Network Password>"

WiFiMQTTClient *Clt;
long count = 0;
int pub_time = 0;
boolean high;
char msg[100];
uint32_t delay_millis = 1000;

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
    // Client not connected.
    if(Clt->connect(CLIENT_ID, USERNAME, TOKEN)) {
      Serial.println("Successfully Connected!"); 
      
      delay(2000);
      
      Serial.println("Subscribing...");
      Clt->subscribe(MQTT_SUB_TOPIC);
      
      delay(1000);
      
      Serial.println("Publishing...");
      Clt->publish(MQTT_PUB_TOPIC, MQTT_PUB_PAYLOAD);
    }else{
      Serial.println("Connection unsuccessful!");
      
      delay(delay_millis);
      
      // Increase wait time between connection attempts
      delay_millis *= 2;
    }
  }

  // Maintain connection with the broker.
  Clt->loop();
}

void Callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic ");
  Serial.println(topic);
  
  Serial.print("Payload: ");
  Serial.println((char *)payload);
}