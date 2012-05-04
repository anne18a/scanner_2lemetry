package mqtt;

public interface IOMqttClientInterface {

	public void onConnected();

	public void onMessageReceived();

	public void onMessagePublished();

	public void onConnectionLost();

}
