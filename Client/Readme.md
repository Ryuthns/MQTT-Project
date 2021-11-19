# Monitor GUI Application
On this side, we created a GUI application using GTK in C language. Our app will act as a monitor to receive images sent from the program on center processing side.

## Necessary Links
[Curl](https://curl.se/) <br/>
[GTK 3.0](https://docs.gtk.org/gtk3/index.html) <br/>
[Paho MQTT](https://www.eclipse.org/paho/index.php?page=clients/c/index.php)

## How it works
In home page, Camera ID of three cameras is required. On the bottom right of the page, "Connected" is shown to let us know that the program connected to our server without any problem.
![image](https://user-images.githubusercontent.com/87508144/142411825-1717cf25-ca6d-4ad6-a15a-fb10ab40ae76.png)
Once we clicked start, we will be moved to another page that shows images from Cameras that we chose. In this page, Images of detected smokers will be uploaded to our server with the help of sftp and we will use curl.h to get the images on our server and show them in the GUI. Filenames will also be sent from center processing side through MQTT to let us know which file to get from the server. If no images have been sent, "No image available" will be shown instead.
![image](https://user-images.githubusercontent.com/87508144/142411886-094a575a-db05-4414-804a-83973e945399.png)
We also put a setting button to let user change things. The button consists of login, server, and topic.
![image](https://user-images.githubusercontent.com/87508144/142411916-05d3590a-7ed2-41fe-a5bf-ba19cfb761b6.png)
We also created a function to delete images stored in the system, but login through setting button is required. Once login, we will be able to click the file in case we want to view it in full size. We can also click the file to select and delete it or delete all files in the diretory.
![image](https://user-images.githubusercontent.com/87508144/142411939-9dfca7f3-5509-4516-940f-f73c04bc3499.png)
The image below shows the result of sending images from three cameras at the same time.
![image](https://user-images.githubusercontent.com/87508144/142594741-1d50dfda-155b-4c85-a980-ca367b3f2d51.png)



