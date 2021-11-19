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
Filenames are transfered through MQTT broker from center processing to client side.

## SFTP
Images are uploaded to our server using [sftp](https://pypi.org/project/pysftp/) protocol so that client side can get the images.
