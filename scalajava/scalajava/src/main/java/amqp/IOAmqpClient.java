package amqp;

import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;

public class IOAmqpClient {
	
	private static Connection amqpClient;
	private static Channel channel;
	
	public IOAmqpClient() throws Exception {
		connect();
		return;
	}

	public void connect() throws Exception {
		AMQP.BasicProperties.Builder bob = new AMQP.BasicProperties.Builder();
		AMQP.BasicProperties minBasic = bob.build();
		AMQP.BasicProperties minPersistentBasic = bob.deliveryMode(2).build();
		AMQP.BasicProperties persistentBasic
		                    = bob.priority(0).contentType("application/octet-stream").build();
		AMQP.BasicProperties persistentTextPlain = bob.contentType("text/plain").build();
		
		ConnectionFactory factory = new ConnectionFactory();
		factory.setUsername(userName);
		factory.setPassword(password);
		factory.setVirtualHost(virtualHost);
		factory.setHost(hostName);
		factory.setPort(portNumber);
		
		amqpClient = factory.newConnection();
		channel = amqpClient.createChannel();
	}
	
	public void disconnect() throws Exception {
		channel.close();
		amqpClient.close();
	}
	
}
