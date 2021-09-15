# What we've done
## Text (Publishing and Subscribing)
We published 1000 messages using test.mosquitto.org as host and subscribed the messages in another terminal. We also created a counter to count messages received to make sure that no message is lost along the way.
![image](https://user-images.githubusercontent.com/87508144/132022442-01ccf664-9392-455c-b449-cbac216c5072.png)

## Pictures (Publishing and Subscribing) 
We did similiar thing, but this time we published 100 pictures instead. We observed that any picture with the size above 400kb won't reach the subscribing terminal.
**"more updates soon"**

## Cross-platform pub&sub
We tried publishing in Linux and subscribing in Windows. The result is that it can be cross-platformed. <br/>
Windows to Linux and Linux to Window ✅<br/>
Raspbian to Linux and Linux to Raspbian ✅<br/>
Linux to Linux  ✅<br/>
 
##Conclusion
We were unable to publish 100 images to another device because MQTT broker allows the overall size of images transfered to approximately 130kb which is not enough for our project.
