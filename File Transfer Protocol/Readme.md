# Transfering File
Both filenames and images are transferd through 203.146.252.179 server.
## MQTT
Filenames are transfered through MQTT broker from center processing to client side.

## SFTP
Images are uploaded to our server using [sftp](https://pypi.org/project/pysftp/) protocol so that client side can get the images.
