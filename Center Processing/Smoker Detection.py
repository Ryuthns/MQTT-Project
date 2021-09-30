import paho.mqtt.client as mqtt
import os
import tkinter as tk
import tkinter.font as font
from tkinter import *
import cv2
from PIL import Image, ImageTk
import numpy as np
from time import strftime

global last_frame                                      
last_frame = np.zeros((480, 640, 3), dtype=np.uint8)
global cap
cap = cv2.VideoCapture(0)
global running, counter, flag_connected
running = True
counter = 0
flag_connected = 0

face_cascade = cv2.CascadeClassifier('classifier\haarcascade_frontalcatface.xml') 
face_cascade = cv2.CascadeClassifier('classifier\haarcascade_frontalcatface_extended.xml')

def on_connect(client, userdata, flags, rc):
    if rc==0:
        client.connected_flag=True #set flag
        print("Connection OK")
    else:
        print("Bad connection Returned code=",rc)
        client.bad_connection_flag=True

def Time():
    global string, T
    string = strftime('%H:%M:%S %p')
    T = strftime('%d-%m-%Y_%H-%M-%S')
    lbl.config(text = string)
    lbl.after(1000, Time)

def to_menuframe():
    menu_frame.pack(fill='both', expand = 1)
    cam_frame.forget()
    close_vid()
    return 0

def to_camframe():
    cam_frame.pack(fill='both', expand = 1)
    menu_frame.forget()
    trigger()
    return 0

def close_vid():
    cap.release()
    global running, counter
    running = False
    counter = 0
    lmain.configure(image='')

def trigger():
    Time()
    global running, counter, cap
    running = True
    counter += 1
    if counter >= 2:
        return 0
    cap = cv2.VideoCapture(0)
    show_vid()

def show_vid():                                       #creating a function
    global frame
    if not cap.isOpened():                             #checks for the opening of camera
        return 0
    flag, frame = cap.read()
    frame = cv2.flip(frame, 1)
    
    pic = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5) 

    path = 'C:/Users/PC/Desktop/CprE. Work/Coding/Project/Smoker Detection/saved_images'

    for (x,y,w,h) in faces: 
        # To draw a rectangle in a face 
        cv2.rectangle(pic,(x,y),(x+w,y+h),(255,255,0),2)
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,255,0),2)  
        cv2.putText(pic, 'Detected', (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
        cv2.putText(frame, 'Detected', (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
        filename = T + '.jpg'
        # cv2.imwrite(os.path.join(path , filename ), frame)
        client.publish("kjpie", "cam1 = " + str(T))
    
    img = Image.fromarray(pic)
    reim = img.resize((1150,600))
    imgtk = ImageTk.PhotoImage(image=reim)
    lmain.imgtk = imgtk
    if running:
        lmain.configure(image=imgtk)
        lmain.after(10, show_vid)
    

if __name__ == '__main__':
    broker = "25.17.177.235"
    client = mqtt.Client()
    client.on_connect = on_connect
    client.loop_start()
    print("Connecting to broker :",broker)
    try:
        client.connect(broker, 1883, 60) #connect to broker
        flag_connected = 1
        print("Connected")
    except:
        print("Connection Failed")
        flag_connected = 0
        pass
    
    root=tk.Tk()
    root.title('Smoker Detection')
    root.iconbitmap('no_smoke.ico')
    root.geometry("1200x800")  

    font_large = font.Font(family='Georgia', size='72', weight='bold')
    font_small = font.Font(family='Calibri', size='18')
    font_verysmall = font.Font(family='Calibri', size='12')

#=========================================================================
    #MENU FRAME
    menu_frame = tk.Frame(root)
    menu_frame.configure(bg='#f1f1f1')

    l1=Label(menu_frame, text="Smoker Detection", font=font_large, fg='black', bg='#f1f1f1')
    l1.place(relx=0.5, rely=0.3, anchor=CENTER)
    l3=Label(menu_frame, text="V.1.0.1", font=font_small, fg='black', bg='#f1f1f1')
    l3.place(relx=0.95, rely=0.95, anchor=CENTER)
    l4=Label(menu_frame, text="Server : "+broker, font=font_verysmall, fg='black', bg='#f1f1f1')
    l4.place(relx=0.07, rely=0.92, anchor=CENTER)
    l5=Label(menu_frame, text="Topic : KJPIE", font=font_verysmall, fg='black', bg='#f1f1f1')
    l5.place(relx=0.06, rely=0.95, anchor=CENTER)
    startimg = (Image.open("start2.png"))
    resized_image = startimg.resize((300,300), Image.ANTIALIAS)
    photoimg = ImageTk.PhotoImage(resized_image)
    b1=Button(menu_frame, image=photoimg, borderwidth=0, bg="#f1f1f1",
             activebackground='#f1f1f1', command=to_camframe)
    b1.place(relx=0.5, rely=0.6, anchor=CENTER)
    
    
#==========================================================================
    #CAM FRAME
    cam_frame = tk.Frame(root)
    cam_frame.configure(bg='#f1f1f1')

    l2=Label(cam_frame, text="Camera 1", font=font_small, fg='black', bg='#f1f1f1')
    l2.place(relx=0.06, rely=0.8, anchor=CENTER)
    l6=Label(cam_frame, text="V.1.0.1", font=font_small, fg='black', bg='#f1f1f1')
    l6.place(relx=0.95, rely=0.95, anchor=CENTER)
    lbl=Label(cam_frame, font=font_verysmall, fg='black', bg='#f1f1f1')
    lbl.place(relx=0.06, rely=0.95, anchor=CENTER)

    b2=Button(cam_frame,width=9,text="Stop",fg='black', bg='#EE1005', activebackground='#EE1005',
             font=font_small, borderwidth=5, command=to_menuframe)
    b2.place(relx=0.5, rely=0.9, anchor=CENTER)

    if flag_connected == 1:
        l7=Label(cam_frame, text="• Connected", font=font_verysmall, fg='green', bg='#f1f1f1')
        l7.place(relx=0.945, rely=0.8, anchor=CENTER)
    elif flag_connected == 0:
        l7=Label(cam_frame, text="• Disconnected", font=font_verysmall, fg='red', bg='#f1f1f1')
        l7.place(relx=0.945, rely=0.8, anchor=CENTER)

    lmain = tk.Label(master=cam_frame, bg='black')
    lmain.place(relx=0.5, rely=0.4, anchor=CENTER)
#===========================================================================
    menu_frame.pack(fill='both', expand=1)
    
    root.mainloop()                                  #keeps the application in an infinite loop so it works continuosly
    cap.release()
    client.disconnect()
