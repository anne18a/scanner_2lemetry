<?php
// PHP MQTT Connection Example

// Define some constants.
// Change username and password to values in Your Credentials.
$_USERNAME = '';
$_TOKEN = '';
$_TOKEN_HASH = md5($_TOKEN);
$_HOST = 'q.thingfabric.com';
$_PORT = 1883;		// Use port 8883 for SSL
$_TOPIC = '[domain]/test-stuff/test-thing';
$_PAYLOAD = '{"Hello":"World!"}';
$_QOS = 0;

// Using the PHP Mosquitto extension (https://github.com/mgdm/Mosquitto-PHP).
$client = new Mosquitto\Client();

// Bind callbacks
$client->onConnect('on_connect');
$client->onDisconnect('on_disconnect');
$client->onSubscribe('on_subscribe');
$client->onMessage('on_message');

// Set client credentials.
$client->setCredentials($_USERNAME, $_TOKEN_HASH);

$client->connect($_HOST, $_PORT);

// Subscribe to a topic.
$client->subscribe($_TOPIC, $_QOS);



// Loop forever to maintain a connection with the host.
for(;;){
	$client->loop();
}

// Define callback functions.
function on_connect($rc, $message) {
	global $_TOPIC, $_PAYLOAD;

	// Display the connection's result code and explanation message.
	echo 'Code: ' . $rc . ' (' . $message . ')' . PHP_EOL;

	// Publish to a topic.
	$client->publish($_TOPIC, $_PAYLOAD);
}
function on_disconnect() {
	global $_HOST, $_PORT, $_USERNAME;

	// Display notice/confirmation of being disconnected.
	echo 'Client disconnected.' . PHP_EOL;
	echo 'Will attempt to reconnect in 5s.' . PHP_EOL;

	sleep(5);

	// Create a new $client object.
	echo 'Trying to reconnect...' . PHP_EOL;

	$client = new Mosquitto\Client();

	$client->connect($_HOST, $_PORT);

	// Bind callbacks
	$client->onConnect('on_connect');
	$client->onDisconnect('on_disconnect');
	$client->onSubscribe('on_subscribe');
	$client->onMessage('on_message');

	for(;;){
		$client->loop();
	}
}
function on_subscribe() {
	// Confirm that the subscription has been made.
	echo 'Subscription confirmed.' . PHP_EOL;
}
function on_message($message) {
	// Display the received message's topic and payload.
	echo 'Message received on ' . $message->topic . ': ' . $message->payload . PHP_EOL;
}

?>