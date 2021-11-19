# Transfering File
Both filenames and images are transferd through 203.146.252.179 server.

Server spec : <br/>
1 vCore <br/>
2GB RAM <br/>
40GB SSD <br/>
100Mbps port speed <br/>
Ubuntu 18.04 64bit <br/>
203.146.252.179 <br/>
Port 22


## MQTT
Filenames are transfered through MQTT broker from center processing to client side. In the center processing side, when a smoker is detected. The program will save that image and publish filename as a message through MQTT broker. When the client side subscribe that message, that message(filename) is used to indicate which image to get from the server.
### Necessary Links
[MQTT Python](http://www.steves-internet-guide.com/into-mqtt-python-client/) <br/>
[MQTT C](https://www.eclipse.org/paho/files/mqttdoc/MQTTClient/html/index.html) <br/>
![image](https://user-images.githubusercontent.com/87508144/142567940-ccbca5b8-4a81-4e07-ad13-fa0e1d820283.png)

## SFTP
Images are uploaded to our server using sftp protocol so that client side can get the images using curl. In the center processing side, as the message is being sent. The program also connect and upload saved image onto the server which later the client side will use curl to get that image onto their own system. The images will now be shown in the GUI of the client side.

### Necessary Links
[SFTP Python](https://pypi.org/project/pysftp/) <br/>
[Curl](https://github.com/curl/curl) <br/>
![image](https://user-images.githubusercontent.com/87508144/142567853-66e73875-ddd5-42f4-b065-ad6b587d1bee.png)
![image](https://user-images.githubusercontent.com/87508144/142567792-0ba7f718-80e4-4b75-a720-a73d73334b74.png)

