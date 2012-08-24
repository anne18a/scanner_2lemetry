mqtt = require('mqttjs/lib/mqtt')
crypto = require('crypto')
client_id = 'mqtt_node_' + process.pid

user = ''
pass = ''
subTopic = ''

mqtt.createClient 1883, 'q.m2m.io', (error, client) ->
  client.connect
    versionNum: 3.1
    keepalive: 3000
    client: client_id
    username: user
    password: crypto.createHash('md5').update(pass).digest('hex')

  client.on 'connack', (packet) ->
    if packet.returnCode is 0
      client.subscribe
        topic: subTopic
        qos: 2
      console.log 'hello'
    else
      console.log 'connack error ' + packet.returnCode
      console.log JSON.stringify(packet)
      process.exit -1

  client.on 'publish', (packet) ->
    console.log 'Someone said ' + packet.payload + ' on ' + packet.topic

  client.on 'close', ->
    process.exit 0

  client.on 'puback', (packet) ->
    console.log '     [MQTT-COMMS] ' + client_id + ' puback received.'

  client.on 'pubrec', (packet) ->
    console.log '\t [MQTT-COMMS] ' + client_id + ' pubrec received, replying with pubcomp.'
    client.pubcomp messageId: packet.messageId

  client.on 'suback', (packet) ->

  client.on 'error', (e) ->
    console.log e
    process.exit -1