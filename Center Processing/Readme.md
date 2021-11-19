# Detection
We will be using openCV and viola-jones algorithm for detection. <br/>
**- Why OpenCV and Viola-Jones ?** <br/>
- **OpenCV** : It's open source library for computer vision, machine learning, and image processing. It also has real-time operation which is very important. <br/>
- **Viola-Jones** : It's well known for its reputation and reliability. It's exceptionally notable in real-time face detection. <br/>

There are two stages of Viola-Jones which is training and detection.
[Haar cascade](https://www.pyimagesearch.com/2021/04/12/opencv-haar-cascades/) <br/>
We trained it by feeding positive(gray images with ciga) and negative images(gray images without ciga).
![image](https://user-images.githubusercontent.com/87508144/134677353-bb8dfd05-b1f4-4d63-9201-a64c031230b4.png)
![image](https://user-images.githubusercontent.com/87508144/142566082-3a430c9a-dcaf-4f79-a2c1-e420f32492e8.png)

We used haar cascade which is a feature in viola-jones. Once we finished training, we got the xml file and tested it.
![image](https://user-images.githubusercontent.com/87508144/142566123-b4c86453-5c0d-4021-b797-318bca64ffd0.png)
![image](https://user-images.githubusercontent.com/87508144/142204770-aa6d6819-142c-403b-a1df-7a9c11f93828.png)

## PC spec
**The system used for training has these features :** <br/>
FX505DT-AL043T <br/>
CPU : AMD Ryzen 7 3750H 2.3 - 4 GHz <br/>
GPU : NVIDIA GeForce GTX 1650 (4GB GDDR5) <br/>
RAM : 16GB DDR4 <br/>
Storage : SSD PCIe 512GB <br/>
Display : 15.6″ Full HD IPS 120Hz <br/>
OS : Windows 10



# GUI Application
For our GUI application, we will use tkinter which is a package in python for creating GUI. It's easy to use which will make coding much faster when compared to using other programming languages. Python3 is used to write this program.
## Necessary Links
[Paho MQTT Client](https://www.eclipse.org/paho/index.php?page=clients/python/index.php) <br/>
[OpenCV](https://pypi.org/project/opencv-python/) <br/>
[Python Pillow](https://pillow.readthedocs.io/en/stable/installation.html) <br/>
[pysftp](https://pypi.org/project/pysftp/) <br/>
[Tkinter Documents](https://docs.python.org/3/library/tkinter.html) <br/>
[Configparser Documents](https://docs.python.org/3/library/configparser.html)

## How it works
Once executed, the program will read and get data like server, topic, and path from config.txt file in the same directory. Then it will try to connect to MQTT broker with topic from your config file with the help of Configparser library. If the connection is OK, "Connected" will be shown in the GUI. The program comes with config file to let user change server, topic, and path(needed).

![image](https://user-images.githubusercontent.com/87508144/142207803-e6462cbe-e629-4db3-bf64-267c44945e14.png) <br/>
Camera ID is required in the entry box. The camaera ID must be between 1-9, others will be rejected and an error message will pop up. Clicking start button will move to another page unless the entry box is blank. OpenCV library is required to capture video from recording device. Then Python PIL is used to help with images like icon, custom button, and showing videos in GUI.<br/>
![image](https://user-images.githubusercontent.com/87508144/142209374-f6175fa2-c441-4583-b448-fd952e76c8c2.png) <br/>
As you can see from the image above, "Connected" is shown in the GUI to let us know that the connection to our MQTT broker server has no problem. Camera ID and timestamp are also there. In this page, your recording device is displayed in the GUI and you're ready to detect. We used 2 XML files to help detect. One is for face detection and another is for cigarette detection. <br/>
![image](https://user-images.githubusercontent.com/87508144/142212056-447d1c52-8dd5-4a12-b3ec-4b77c9525d33.png)
![image](https://user-images.githubusercontent.com/87508144/142213518-88b9aa29-7a98-4a14-a0b1-7603456449f7.png) <br/>
We put a delay(around 5sec) between saving images so that our folder won't be flooded with images being saved every seconds during detection. Once detected, that image is then saved with timestamp being file name in the directory "current_images" and the file name will be stored in "data.txt" temporary. During this process, the saved images are uploaded to our server using sftp protocol and filenames are sent through MQTT.
![image](https://user-images.githubusercontent.com/87508144/142213977-01f3f25a-76c2-4f9c-bdc1-70a39433c951.png) <br/>
After you close the program, all the images in "current_images" will be moved to "Cache" using names in "data.txt". Then we clear all the texts in "data.txt". <br/>
## Webcam used : <br/>
![image](https://user-images.githubusercontent.com/87508144/142566217-98e6a778-124d-43c8-b728-0c24a9b9b5cd.png)












