# Detection
We will be using openCV and viola-jones algorithm for detection. <br/>
**- Why OpenCV and Viola-Jones ?** <br/>
- **OpenCV** : It's open source library for computer vision, machine learning, and image processing. It also has real-time operation which is very important. <br/>
- **Viola-Jones** : It's well known for its reputation and reliability. It's exceptionally notable in real-time face detection. <br/>

There are two stages of Viola-Jones which is training and detection.
![image](https://user-images.githubusercontent.com/87508144/134677353-bb8dfd05-b1f4-4d63-9201-a64c031230b4.png)
Once we finished training, we got the xml file and tested it.

![image](https://user-images.githubusercontent.com/87508144/142204770-aa6d6819-142c-403b-a1df-7a9c11f93828.png)



# GUI Application
For our GUI application, we will use tkinter which is a package in python for creating GUI. It's easy to use which will make coding much faster when compared to using other programming languages.
## How it works
Once executed, the program will read and get data like server, topic, and path from config.txt file in the same directory. Then it will try to connect to MQTT broker with topic from your config file. If the connection is OK, "connected" will be shown in the GUI.

![image](https://user-images.githubusercontent.com/87508144/142207803-e6462cbe-e629-4db3-bf64-267c44945e14.png)





