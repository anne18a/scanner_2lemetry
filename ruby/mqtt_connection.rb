# Ruby MQTT Connection Example

require 'rubygems'
require 'mqtt' 		# Using the mqtt gem
require 'digest'

# Define some constants.
# Change username and password to values found in Your Credentials.
CLIENT_ID = 'g3z559a6c1'
TOKEN = 'ex2vcx0vfznu'
TOKEN_HASH = Digest::MD5.hexdigest(TOKEN)
HOST = 'q.m2m.io'
PORT = 1883
TOPIC = 'maaakihz/test-stuff/test-thing'
PAYLOAD = '{"Hello":"World!"}'

# Connect to q.m2m.io using the following parameters.
MQTT::Client.connect(
	:remote_host => HOST,
	:remote_port => PORT,
	:username => CLIENT_ID,
	:password => TOKEN_HASH
	) do |client|
	# Confirm that the connection has been made.
	puts 'Connected to host.'

	# The publishing has to be done in a separate thread, as 
	# the subscription service locks up the current thread.
	Thread.new do
		# Publish a payload to a topic.
		client.publish(TOPIC, PAYLOAD)

		# Display a notice that the message was published.
		puts 'Published message.'
	end

	# This both subscribes to a topic and defines the callback function.
	client.get(TOPIC) do |topic, message|
		# Display the received message's topic and payload.
		puts "Received message on #{topic}: #{message}"
	end
end
