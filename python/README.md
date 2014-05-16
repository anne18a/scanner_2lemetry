Connecting to q.m2m.io in Python
================================

What this script requires:

- Python
- The [Eclipse Paho MQTT Client](http://www.eclipse.org/paho) (for Python)
- A [ThingFabric](https://app.thingfabric.com/) account
- [Git](http://git-scm.com/) (optional)

To install the MQTT Client, open a terminal and run the following command:

`pip install paho-mqtt`

Once the client has been installed, clone the quickstart-examples Git repository to your machine by navigating to the directory you'd like to store the code in and executing the following command in your terminal:

`git clone [PUBLIC REPO URL]`

Alternatively, open a text editor and copy the code from mqtt_connection.py into it.  

#### Before running the code, we'll need to edit the credentials to match our account information.

On the [ThingFabric dashboard](https://app.thingfabric.com/dashboard_domain), click "Access" on the menu to the left of the screen.  Click "Default" to view the default credentials.  Copy the Username string and set it as the value of `CLIENT_ID` in mqtt_connection.py.  Next, copy then Token string and set it as the value of the `TOKEN` variable.

Return to your project's dashboard by clicking the project name at the top of the web page.  Click "Stream" in the menu to the left of the page.  The next page allows you to configure a connection to q.m2m.io, but the defaults will work fine for our purposes.  Click "Connect" at the bottom of the page.  Create a subscription of the form [domain]/[topic] in the Subscribe menu.  The name of the topic is up to you, but the domain must be set to the string marked "Your Domain" at the top of the page.  Leave QoS (Quality of Service) set to 0.  Click "Subscribe" and note that you are now able to see a list of current subscriptions, and can pause or delete them as you wish.

Back in mqtt_connection.py, edit the variable `TOPIC` to match the topic you've just subscribed to as a string, in the format `"[domain]/[topic]"`.

Now, your script should be ready to go.  Head back to the terminal and enter the following:

`cd path/to/quickstart-examples/python`
`python mqtt_connection.py`

If all goes well, you'll see that the script has successfully connected to the host, published a message, and subscribed to the topic.  To confirm a working connection, head back to your [ThingFabric](https://app.thingfabric.com/) Stream menu.  Let's publish a message and see if it goes through to the script.

In the "Topic" field inside the "Publish" menu, enter the same topic you've subscribed to above, and you can leave QoS at 0.  In the "Payload Message" field, enter `Hello, Python!` and press "Publish."  Look back at your console -- if everything has worked correctly, you'll see that your message was received.

This is just a simple example of what can be done with MQTT and [ThingFabric](https://app.thingfabric.com/).  Build off this code and see how you can integrate [ThingFabric](https://app.thingfabric.com/) into your project!