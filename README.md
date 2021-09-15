# **What we've done**
[Test Mosquitto Website](https://test.mosquitto.org/) <br/>
[Download MQTT](https://mosquitto.org/download/) <br/>
[Download MQTT-Paho-python](https://github.com/eclipse/paho.mqtt.python) <br/>
[MQTT-Paho-python-client Guide](http://www.steves-internet-guide.com/into-mqtt-python-client/) <br/>
[Download MQTT-Paho-c](https://github.com/eclipse/paho.mqtt.c) <br/>
[MQTT-Paho-C-client Guide](https://docs.emqx.io/en/broker/v4.3/development/c.html#paho-c-usage-example)

## Text (Publishing and Subscribing)
We published 1000 messages using test.mosquitto.org as host and subscribed the messages in another terminal. We also created a counter to count messages received to make sure that no message is lost along the way.
![image](https://user-images.githubusercontent.com/87508144/132022442-01ccf664-9392-455c-b449-cbac216c5072.png)

## Pictures (Publishing and Subscribing) 
We did similiar thing, but this time we published 100 pictures instead. We observed that the counter stop counting after sometimes, so we calculated the overall size of images transfered. We found out that the broker won't allow any more images if the combined size of images are over 400kb.
![image](https://user-images.githubusercontent.com/87508144/133457337-0595e407-e394-4c31-bfaa-6612f3afa088.png)


## Cross-platform pub&sub
We tried publishing and subscribing on various operating systems. The result is that it can be cross-platformed. <br/>
• Windows to Linux and Linux to Window ✅<br/>
• Raspbian to Linux and Linux to Raspbian ✅<br/>
• Linux to Linux  ✅<br/>
 
# Conclusion
We were unable to publish 100 images to another device because MQTT broker allows the overall size of images transfered to approximately 400kb which is not enough for our car plate recognition project. So we decided to make a smoker recognition instead. We tested publishing and subscribing (as you can see from above sections) in python, but we will change to C programming language later. We will also use test.mosquitto.org as our broker since we can't afford one. 

