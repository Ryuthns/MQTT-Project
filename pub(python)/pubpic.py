# PUB_PIC
import paho.mqtt.client as mqtt

# This is the Publisher

'''f= open("pic_pub/A.jpg","rb")
filecontent = f.read()'''

client = mqtt.Client()
client.connect("broker.hivemq.com",1883,60)
#client.publish("thk0092", filecontent);
for i in range(100):
    name = "pic_pub/"+str(1)+".jpg"
    #name = "pic_pub/10MB.png"
    print(name)
    f= open(name,"rb")
    filecontent = f.read()
    client.publish("kjpie1", filecontent);

client.disconnect();

# L -> L pic localhost 7.70 s
