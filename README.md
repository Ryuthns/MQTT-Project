# Smoker Detection
[Explanation Video (in Thai)](https://youtu.be/fULGcC-HwrQ)
![image](https://user-images.githubusercontent.com/87508144/142571608-c2beee8f-f1e5-4a1b-9b9c-5b62111f0c31.png)

## Overview
In this project, we will use our program to detect smoker in public areas with the help of haar cascade which is a feature in [Viola–Jones](https://en.wikipedia.org/wiki/Viola%E2%80%93Jones_object_detection_framework). Once detected, the program will publish an image of smoker along with location(camara ID) and time as filename to client side using MQTT broker and SFTP protocol. The client side will now use that image to show in the GUI application. <br/>

✅ This program also supports all OS. ✅

> Each directory is included with an explanation for each part of the project.

## Efficiency
The more image we keep on detecting the less time we get.
![image](https://user-images.githubusercontent.com/87508144/142568115-aa6e6da2-993b-4371-bc99-7a724c983744.png)
The images below show that it takes two times the CPU when detecting.
![image](https://user-images.githubusercontent.com/87508144/142594925-4d1433d6-068e-410b-a2aa-904e16494441.png)
![image](https://user-images.githubusercontent.com/87508144/142594935-3aff0e6c-bbf6-4ecc-8b93-577b20febd68.png)


## Result
The program work as intended, but sometimes there is a problem with multithreading on center processing side. The program sometimes still save an image even with a delay and that saved image may or may not be moved to "Cache". This could be due to some problems with sftp because we put a code to connect to server in a while loop. Our XML files still can't detect some images. It needs more training to be more precise, but other than that it's working fine.

## Benefits
- Help prevent smoking in public areas




