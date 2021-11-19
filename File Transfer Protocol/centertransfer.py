#MQTT
def on_connect(client, userdata, flags, rc):            # A function to connect to MQTT broker
    if rc == 0:
        client.connected_flag = True  # set flag
        print("Connection OK")
    else:
        print("Bad connection Returned code=", rc)
        client.bad_connection_flag = True
        
client.publish(topic, "cam" + camid + "_" + T)             # Publish filenames as messages through MQTT broker

if __name__ == '__main__':
    broker = parser.get("config", "server")            # Broker from config file
    topic = parser.get("config", "topic")              # Topic from config file
    client = mqtt.Client()
    client.on_connect = on_connect
    client.loop_start()                                # Start connection loop
    
    client.disconnect()                                # Disconnect from MQTT broker (execute when the program is closed)



#SFTP
username = "admin"
hostname = "203.146.252.179"
cnopts = pysftp.CnOpts()
cnopts.hostkeys = None
with pysftp.Connection(hostname, username, password = "U%%FSM74Y$GZ", cnopts=cnopts) as sftp:     # Connect to server 203.146.252.179 using pysftp
  with sftp.cd('/home/admin/web/sv1.kjpie/public_html/uploads'):                                  # Access "uploads" directory
     sftp.put(localfile)                                                                          # Put saved images on the server
