## Necessary Links <br/>
[Test Mosquitto Website](https://test.mosquitto.org/) <br/>
[Download MQTT](https://mosquitto.org/download/) <br/>
[Download MQTT-Paho-python](https://github.com/eclipse/paho.mqtt.python) <br/>
[MQTT-Paho-python-client Guide](http://www.steves-internet-guide.com/into-mqtt-python-client/) <br/>
[Download MQTT-Paho-C](https://github.com/eclipse/paho.mqtt.c) <br/>
[MQTT-Paho-C-client Guide](https://docs.emqx.io/en/broker/v4.3/development/c.html#paho-c-usage-example) <br/>
[Paho MQTT C Client Library](https://www.eclipse.org/paho/files/mqttdoc/MQTTClient/html/index.html) </br>
[jpeglib.h Library](https://github.com/winlibs/libjpeg)

# **Python**
## Text (Publishing and Subscribing)
We published 1000 messages using test.mosquitto.org as host and subscribed the messages in another terminal. We also created a counter to count messages received to make sure that no message is lost along the way.
![image](https://user-images.githubusercontent.com/87508144/133459762-a8877785-9e4b-48b3-bd6e-f5957ea428d8.png)

## Pictures (Publishing and Subscribing) 
We did similiar thing, but this time we published 100 pictures instead. We observed that the counter stop counting after sometimes, so we calculated the overall size of images transfered. We found out that the broker won't allow any more images if the combined size of images are over 128kb.
![image](https://user-images.githubusercontent.com/87508144/133457337-0595e407-e394-4c31-bfaa-6612f3afa088.png)


## Cross-platform pub&sub
We tried publishing and subscribing on various operating systems. The result is that it can be cross-platformed. <br/>
• Windows to Linux and Linux to Window ✅<br/>
• Raspbian to Linux and Linux to Raspbian ✅<br/>
• Linux to Linux  ✅<br/>
 
## Conclusion
We were unable to publish 100 images to another device because MQTT broker allows the overall size of images transfered not more than approximately 128kb which is not enough for our car plate recognition project. So we decided to make a smoker detection instead. We tested publishing and subscribing (as you can see from above sections) in python, but we will change to C programming language later. We will be using test.mosquitto.org as our broker since we can't afford one.
  
# **C**
We can't use stdio.h to open images in C, so we need the help of jpeglib.h and paho libraries. <br/>
We used asynchronous publishing and subscribing because most things in C programming language work in sequence which we don't want in our case. Using asynchronous allows the program to work without having to wait for another program to finish.
## Text (Publishing and Subscribing)


## Pictures (Publishing and Subscribing) 


