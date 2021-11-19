# Smoker Detection
![image](https://user-images.githubusercontent.com/87508144/135110405-d9e602e9-3a44-4ce2-963c-51e6d87f57e4.png)




## Overview
In this project, we will use our program to detect smoker in public areas with the help of haar cascade which is a feature in [Viola–Jones](https://en.wikipedia.org/wiki/Viola%E2%80%93Jones_object_detection_framework). Once detected, the program will publish an image of smoker along with location(camara ID) and time as filename to client side using MQTT broker and SFTP protocol. The client side will now use that image to show in the GUI application. <br/>

This program also supports all OS.

> Each directory is included with an explanation for each part of the project.

## Efficiency
The more image we keep on detecting the less time we get.
![image](https://user-images.githubusercontent.com/87508144/142568115-aa6e6da2-993b-4371-bc99-7a724c983744.png)

## Result
The program work as intended, but sometimes there is a problem with multithreading on center processing side. The program sometimes still save an image even with a delay and that saved image will not be moved to "Cache". This could be due to bad writing for multithreading or some problems with sftp when connecting to the server many times in a row with the same user.

## Benefits
- Help prevent smoking in public areas




