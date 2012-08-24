package mqtt;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.UUID;

import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;

/**
 * TODO:
 * 
 * 1) Default last will/testament should come from information passed back from
 * broker.
 * 
 * 2) Make sure broker passes us anything at all.
 * 
 * 3) Add implementation for default subscriptions, e.g. ctrl.
 * 
 */
public class IOMqttClient implements MqttCallback {
	
	private IOMqttClientInterface ioMqttClientInterface;

	/** Allow static access to ioMqttClient **/
	public static MqttClient mqttClient;

	/** Default broker settings **/
	private String url = "q.m2m.io";
	private int port = 1883;

	/** Default to starting with a clean session **/
	private boolean cleanSession = true;

	/** Default to 30 second ping **/
	private int keepAlive = 30;

	/** Default to public channel **/
	private String username = null;
	private String password = null;

	/** Default to random client ID **/
	private String clientId = UUID.randomUUID().toString();

	/** Default subscribed topics (ctrl) should be passed back from broker **/
	private Map<String, Integer> subscribeOnTopics = new HashMap<String, Integer>();

	/** Domain gets set on initial message recevied from broker **/
	private String domain;

	public IOMqttClient() throws Exception {
		connect();
		return;
	}

	public void connect() throws Exception {

		System.out.println("Connect!");

		MqttConnectOptions options = new MqttConnectOptions();
		options.setCleanSession(this.isCleanSession());
		options.setKeepAliveInterval(this.getKeepAlive());

		if (this.getPassword() != null)
			options.setPassword(this.getPassword().toCharArray());
		if (this.getUsername() != null)
			options.setUserName(this.getUsername());

		// options.setConnectionTimeout();
		// options.setWill(topic, payload, qos, retained);

		mqttClient = new MqttClient(this.getBrokerEndpoint(),
				this.getClientId());
		mqttClient.connect(options);
		mqttClient.setCallback(this);
	}

	public void subscribe() throws Exception {
		for (Entry<String, Integer> entry : this.getSubscribeOnTopics()
				.entrySet()) {
			mqttClient.subscribe(entry.getKey(), entry.getValue());
		}
	}

	public boolean publish(String stuff, String payload, int qOs,
			boolean retained) {
		return publish(this.getDomain() + "/" + stuff, payload.getBytes(), qOs,
				retained);
	}

	public boolean publish(String stuff, String thing, String payload, int qOs,
			boolean retained) {
		return publish(this.getDomain() + "/" + stuff + "/" + thing,
				payload.getBytes(), qOs, retained);
	}

	private boolean publish(String topic, byte[] payload, int qOs,
			boolean retained) {

		MqttTopic mqttTopic = mqttClient.getTopic(topic);

		MqttMessage mqttMessage = new MqttMessage(payload);
		mqttMessage.setQos(0);
		mqttMessage.setRetained(retained);

		MqttDeliveryToken token;
		try {
			token = mqttTopic.publish(mqttMessage);
			token.waitForCompletion();
			return true;
		} catch (MqttPersistenceException e) {
			e.printStackTrace();
			return false;
		} catch (MqttException e) {
			e.printStackTrace();
			return false;
		}
	}

	public void disconnect() throws Exception {
		mqttClient.disconnect();
	}

	public void connectionLost(Throwable arg0) {

		System.out.println("Connection lost!");

		try {
			Thread.sleep(20);

			System.out.println("Retring connection!");

			mqttClient.connect();
		} catch (MqttSecurityException e) {
			e.printStackTrace();
		} catch (MqttException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public void deliveryComplete(MqttDeliveryToken arg0) {
		// TODO Auto-generated method stub
	}

	public void messageArrived(MqttTopic arg0, MqttMessage arg1)
			throws Exception {
		System.out.println("Message arrived: " + arg0.getName() + ", "
				+ arg1.getPayload());

		/* First message tells us domain/stuff/thing */
	}

	public static MqttClient getMqttClient() {
		return mqttClient;
	}

	public static void setMqttClient(MqttClient mqttClient) {
		IOMqttClient.mqttClient = mqttClient;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public int getPort() {
		return port;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public String getBrokerEndpoint() {
		return this.getUrl() + ":" + String.valueOf(this.getPort());
	}

	public boolean isCleanSession() {
		return cleanSession;
	}

	public void setCleanSession(boolean cleanSession) {
		this.cleanSession = cleanSession;
	}

	public IOMqttClient withCleanSession(boolean cleanSession) {
		this.cleanSession = cleanSession;
		return this;
	}

	public int getKeepAlive() {
		return keepAlive;
	}

	public void setKeepAlive(int keepAlive) {
		this.keepAlive = keepAlive;
	}

	public IOMqttClient withKeepAlive(int keepAlive) {
		this.keepAlive = keepAlive;
		return this;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public IOMqttClient withUsername(String username) {
		this.username = username;
		return this;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public IOMqttClient withPassword(String password) {
		this.password = password;
		return this;
	}

	public String getClientId() {
		return clientId;
	}

	public void setClientId(String clientId) {
		this.clientId = clientId;
	}

	public IOMqttClient withClientId(String clientId) {
		this.clientId = clientId;
		return this;
	}

	public Map<String, Integer> getSubscribeOnTopics() {
		return subscribeOnTopics;
	}

	public void setSubscribeOnTopics(Map<String, Integer> subscribeOnTopics) {
		this.subscribeOnTopics = subscribeOnTopics;
	}

	public IOMqttClient withSubscribeOnTopics(
			Map<String, Integer> subscribeOnTopics) {
		this.subscribeOnTopics = subscribeOnTopics;
		return this;
	}

	public String getDomain() {
		return domain;
	}

	public void setDomain(String domain) {
		this.domain = domain;
	}

}