# node.js

This is a node.js client library and API wrapper. Currently, the functionality is limited, but we support these protocols:

1. MQTT
1. 0

## Setup

1. Via the command-line:

```
npm install m2mIO
```

1. In your application:

```
require 'm2mIO'
```

## Usage

You _need_ to supply credentials in the constructor:

```
m2m = new m2mIO(':username',':password')
````

## Creating an Account

Params:

1. username
1. password

**username**: E-mail address, where the suffix provided will constitute your _domain_, e.g. supplying a _username_ of `frank@2lemetry.com` would make my _domain_ `com.2lemetry`.

**password**: This must be a minimum of 6 characters.

```
m2m.signup ':username', ':password'
```

## Pub/Sub clients

Protocols supported:

1. MQTT
1. ZMQ

### MQTT

1. Creating a client.

```
m2m.mqtt.connect()
```

1. Subscribing.

You can subscribe on all the traffic in your domain:

1. topics

**topics** An array of namespaces.

```
m2m.mqtt.subscribe [':domain/#']
```

Or, you can subsribe on more detailed topics:

m2m.mqtt.subscribe [':domain/:stuff/#',':domain/:stuff/:thing/#']

1. Publishing data.

### ZMQ



### Dev Notes

1. `@trace` function doesn't work. [StackOveflow](http://stackoverflow.com/questions/11973181/log-every-method)
