# PUB_MES
import paho.mqtt.client as mqtt

# This is the Publisher

client = mqtt.Client()
client.connect("test.mosquitto.org",1883,60)
for i in range(1000):
    client.publish("KJPIE", "Hello {}".format(i+1));

client.disconnect();
