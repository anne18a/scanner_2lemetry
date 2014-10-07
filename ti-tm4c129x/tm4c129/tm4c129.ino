/**
 ********************************************************************************************************
 * @file    tm4c129.ino
 * @author  Mark Mulrooney <mark@2lemetry.com>
 * @brief   Simple example to conenct the TM4C129
 * @details In this example an IP is acquired via DHCP and then a connection is made to the MQTT server.
 *          Once the connection is made a message is sent every 5 seconds.
 ********************************************************************************************************
 */

/*
 ********************************************************************************************************
 *                                             INCLUDE FILES                                            *
 ********************************************************************************************************
 */

#include <Ethernet.h>
#include <PubSubClient.h>

/*
 ********************************************************************************************************
 *                                                DEFINES                                               *
 ********************************************************************************************************
 */

#define DELAY_MS2S                              (1000)              /*!< Used to convert ms to s */
#define SERIAL_BAUD_RATE                        (115200)            /*!< Serial port baud rate */
#define DEFAULT_TIMEOUT_S                       (5)                 /*!< Default to sending every 5 seconds */

/*
 ********************************************************************************************************
 *                                               CONSTANTS                                              *
 ********************************************************************************************************
 */

// MAC address from the board
byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};                  /*!< Board's MAC address */

// Thingfabric parameters
const int mqtt_port         = 1883;
const char domain[]         = "";                                   /*!< ThingFabric Project Name */
const char user[]           = "";                                   /*!< ThingFabric User Key */
const char pass[]           = "";                                   /*!< ThingFabric Password MD5 */
const char mqtt_server[]    = "q.thingfabric.com";

/*
 ********************************************************************************************************
 *                                               DATA TYPES                                             *
 ********************************************************************************************************
 */

/*
 ********************************************************************************************************
 *                                          FUNCTION PROTOTYPES                                         *
 ********************************************************************************************************
 */

/*
 ********************************************************************************************************
 *                                            GLOBAL VARIABLES                                          *
 ********************************************************************************************************
 */

PubSubClient ps_client;
EthernetClient e_client;

/*
 ********************************************************************************************************
 *                                           GLOBAL FUNCTIONS                                           *
 ********************************************************************************************************
 */

/*
 ********************************************************************************************************
 *                                            LOCAL FUNCTIONS                                           *
 ********************************************************************************************************
 */

/**
 *******************************************************************************
 * @fn      setup(void)
 * @brief   Set-up calls
 * @param   None
 * @return  None
 *******************************************************************************
 */
void setup()
{
    // Initialize the serial port
    Serial.begin(SERIAL_BAUD_RATE);

    // Attempt to create the ethernet connection
    if(Ethernet.begin(mac) == 0)
    {
        // Print the error message and halt
        Serial.println("Error: Unable to configure Ethernet using DHCP");
        while(1);
    }

    // Print the Ethernet connection info
    else
    {
        Serial.print("My IP address: ");
        for(byte i = 0; i < 4; i++)
        {
            Serial.print(Ethernet.localIP()[i], DEC);
            Serial.print(".");
        }
        Serial.println("");
    }

    // Create the PubSub client
    ps_client = PubSubClient((char*) mqtt_server, mqtt_port, callback, e_client);

    // Connect to the server
    Serial.println("Attempting to connect to the server");
    if(ps_client.connect((char*) "tm4c129", (char*) user, (char*) pass))
    {
      Serial.println("Connected to the server!");
    }

    // First connect attempt didn't work
    else
    {
      Serial.println("First connect attempt failed");
    }
}

/**
 *******************************************************************************
 * @fn      loop(void)
 * @brief   Main system loop
 * @param   None
 * @return  Does not return
 *******************************************************************************
 */
void loop()
{
    static int msg_num = 0;
    static int timeout_s = DEFAULT_TIMEOUT_S;

    // Check if we're already connected
    if(!(ps_client.connected()))
    {
        Serial.println("Attempting to connect to the server");

        // Attempt to conenct to the server
        if(ps_client.connect((char*) "tm4c129", (char*) user, (char*) pass))
        {
            Serial.println("Connected to the server!");

            // Attempt to publish a hello world
            ps_client.publish((char*) domain, "Hello world!");
            timeout_s = DEFAULT_TIMEOUT_S;
        }

        // Can't connect to the server. Double the connect time
        else
        {

            Serial.println("Unable to connect");
            timeout_s *= 2;
        }
    }

    // We're connected, send a message on the timeout interval
    else
    {
      char msg[16];

      // Create the publish string and publish it
      sprintf((char*) &msg, "Update #%d", msg_num);
      ps_client.publish((char*) domain, (char*) &msg);
    }

    // PubSub processing looop
    ps_client.loop();

    // Sleep for the set timeout
    Serial.print("Sleeping for ");
    Serial.print(timeout_s);
    Serial.println(" seconds");
    delay(timeout_s * DELAY_MS2S);

    // Increment the message number
    msg_num++;
}

/**
 *******************************************************************************
 * @fn      callback(char* in_topic, byte* payload, unsigned int length)
 * @brief   Called when data is recieved from PubSub
 * @param   in_topic:   Topic of the MQTT message
 * @param   payload:    The received data
 * @param   length:     The length of the payload data
 * @return  None
 *******************************************************************************
 */
void callback(char* in_topic, byte* payload, unsigned int length)
{
    // Not used in this demo
}
