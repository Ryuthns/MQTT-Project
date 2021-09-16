#TODO : sub messages from linux
import paho.mqtt.client as mqtt
#** 1st : 25s, 2nd : 13s, 3rd : 3.53s

cou = 0    #ข้อมูลไม่หาย count ครบทุกตัว
print("cou = ",cou)

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
  print("Connected with result code "+str(rc))
  # Subscribing in on_connect() means that if we lose the connection and
  # reconnect then subscriptions will be renewed.
  client.subscribe("KJPIE")
  
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
  print(msg.payload.decode())
  global cou 
  cou +=1 
  print('cou = {}'.format(cou))
  
  

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("test.mosquitto.org", 1883, 60)


# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
