import pysftp
from ftplib import FTP 
import time
import paho.mqtt.client as mqtt
import os
import tkinter as tk
import tkinter.font as font
from tkinter import messagebox
from tkinter import *
import cv2
from PIL import Image, ImageTk
from time import strftime
import threading
from subprocess import call
import configparser

global cap
global running, flag_connected, signal_running
running = True
flag_connected = 0
signal_running = False
detecting = False

#TODO : Read config file
parser = configparser.ConfigParser()
parser.read("config.txt")

face_cascade = cv2.CascadeClassifier('classifier/face_detect.xml')
cigar_cascade = cv2.CascadeClassifier('classifier/cascade25.xml')

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.connected_flag = True  # set flag
        print("Connection OK")
    else:
        print("Bad connection Returned code=", rc)
        client.bad_connection_flag = True


def Time():
    global string, T
    string = strftime('%H:%M:%S %p')
    T = strftime('%d-%m-%Y_%H-%M-%S')
    lbl.config(text=string)
    lbl.after(1000, Time)


def close_vid():
    menu_frame.pack(fill='both', expand=1)
    cam_frame.forget()
    cap.release()
    global running, signal_running
    running = False
    signal_running = False
    lmain.configure(image='')


def trigger():
    global running, cap, camid, signal_running, thread1
    camid = cam_var.get()
    if camid.isnumeric():
        if int(camid) > 9 or int(camid) == 0:
            messagebox.showerror("Error", "Camera ID must be between 1-9")
            return
        else:
            l2.config(text=('Camera', camid))
            cam_frame.pack(fill='both', expand=1)
            menu_frame.forget()
    else:
        if camid.isalpha():
            messagebox.showerror("Error", "Camera ID must be an integer")
            return
        messagebox.showerror("Error", "Enter Camera ID First")
        return

    Time()
    running = True
    signal_running = True
    cap = cv2.VideoCapture(0)
    show_vid()
    thread1 = threading.Thread(target=uploadpic)
    thread1.daemon = True
    thread1.start()

def show_vid():  # creating a function
    global frame, filename, path, resize, cap, detecting, folder

    if not cap.isOpened():  # checks for the opening of camera
        return 0
    flag, frame = cap.read()
    frame = cv2.flip(frame, 1)

    pic = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    
    path = parser.get("config","path")
    filename = "cam" + camid + "_" + T + ".jpg"

    for (x,y,w,h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (255,0,0), 2)
        cv2.rectangle(pic, (x,y), (x+w, y+h), (255,0,0), 2)
        roi_gray = gray[y:y+h+20, x:x+w+20]
        roi_color = frame[y:y+h+70, x:x+w+70]
        roi_pic = pic[y:y+h+70, x:x+w+70]
        cv2.putText(frame, 'faces', (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2) 
        cv2.putText(pic, 'faces', (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
        cigs = cigar_cascade.detectMultiScale(roi_gray,1.3,1)
        if len(cigs) != 0:
            detecting = True 
        else: 
            detecting = False
        for (ex,ey,ew,eh) in cigs:
            cv2.rectangle(roi_color, (ex,ey), (ex+ew, ey+eh), (0,0,255), 2)
            cv2.rectangle(roi_pic, (ex,ey), (ex+ew, ey+eh), (0,0,255), 2)
            cv2.putText(roi_color, 'Cigarette', (ex, ey-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
            cv2.putText(roi_pic, 'Cigarette', (ex, ey-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
            resize = cv2.resize(frame, (576, 432))

    img = Image.fromarray(pic)
    reim = img.resize((1150, 600))
    imgtk = ImageTk.PhotoImage(image=reim)
    lmain.imgtk = imgtk
    if running:
        lmain.configure(image=imgtk)
        lmain.after(10, show_vid)
        
def uploadpic():
    f = open("data.txt","a")
    while signal_running :
        if detecting:
            cv2.imwrite(os.path.join(path+"/current_images", filename), resize)
            f.write(filename+"\n")
            client.publish(topic, "cam" + camid + "_" + T)
            localfile = path+"/current_images"+"/"+filename
            username = "admin"
            # password = "U%%FSM74Y$GZ"
            hostname = "203.146.252.179"
            cnopts = pysftp.CnOpts()
            cnopts.hostkeys = None
            with pysftp.Connection(hostname, username, password = "U%%FSM74Y$GZ", cnopts=cnopts) as sftp:
                with sftp.cd('/home/admin/web/sv1.kjpie/public_html/uploads'):
                    sftp.put(localfile)
            time.sleep(5)
        time.sleep(1)
    f.close()
      
if __name__ == '__main__':
    broker = parser.get("config", "server")
    topic = parser.get("config", "topic")
    client = mqtt.Client()
    client.on_connect = on_connect
    client.loop_start()
    print("Connecting to broker :", broker)

    try:
        client.connect(broker, 1883, 60)  # connect to broker
        flag_connected = 1
        print("Connected")
    except:
        print("Connection Failed")
        flag_connected = 0
        pass

    root = tk.Tk()
    root.title('Smoker Detection')
    root.iconphoto(True, PhotoImage(file="no_smoke.png"))
    root.geometry("1200x800")
    font_large = font.Font(family='Georgia', size='72', weight='bold')
    font_small = font.Font(family='Calibri', size='18')
    font_verysmall = font.Font(family='Calibri', size='12')

    # =========================================================================
    # MENU FRAME
    menu_frame = tk.Frame(root)
    menu_frame.configure(bg='#f1f1f1')

    l1 = Label(menu_frame, text="Smoker Detection", font=font_large, fg='black', bg='#f1f1f1')
    l1.place(relx=0.5, rely=0.2, anchor=CENTER)
    l3 = Label(menu_frame, text="V.1.0.3", font=font_small, fg='black', bg='#f1f1f1')
    l3.place(relx=0.95, rely=0.95, anchor=CENTER)
    l4 = Label(menu_frame, text="Server : " + broker, font=font_verysmall, fg='black', bg='#f1f1f1')
    l4.place(relx=0.07, rely=0.92, anchor=CENTER)
    l5 = Label(menu_frame, text="Topic : " + topic, font=font_verysmall, fg='black', bg='#f1f1f1')
    l5.place(relx=0.06, rely=0.95, anchor=CENTER)
    startimg = (Image.open("start2.png"))
    resized_image = startimg.resize((300, 300), Image.ANTIALIAS)
    photoimg = ImageTk.PhotoImage(resized_image)
    b1 = Button(menu_frame, image=photoimg, borderwidth=0, bg="#f1f1f1",
                activebackground='#f1f1f1', command=trigger)
    b1.place(relx=0.5, rely=0.7, anchor=CENTER)

    le = Label(menu_frame, text="Please Input Your Camera ID", font=font.Font(family='Georgia', size='30'), fg='black',
               bg='#f1f1f1')
    le.place(relx=0.5, rely=0.4, anchor=CENTER)

    cam_var = StringVar()
    e1 = Entry(menu_frame, font=font.Font(family='Times New Roman', size='24'), textvariable=cam_var)
    e1.place(relx=0.5, rely=0.5, anchor=CENTER)

    # ==========================================================================
    # CAM FRAME
    cam_frame = tk.Frame(root)
    cam_frame.configure(bg='#f1f1f1')

    l2 = Label(cam_frame, font=font_small, fg='black', bg='#f1f1f1')
    l2.place(relx=0.06, rely=0.8, anchor=CENTER)
    l6 = Label(cam_frame, text="V.1.0.3", font=font_small, fg='black', bg='#f1f1f1')
    l6.place(relx=0.95, rely=0.95, anchor=CENTER)
    lbl = Label(cam_frame, font=font_verysmall, fg='black', bg='#f1f1f1')
    lbl.place(relx=0.06, rely=0.95, anchor=CENTER)

    b2 = Button(cam_frame, width=9, text="Stop", fg='black', bg='#EE1005', activebackground='#EE1005',
                font=font_small, borderwidth=5, command=close_vid)
    b2.place(relx=0.5, rely=0.9, anchor=CENTER)

    if flag_connected == 1:
        l7 = Label(cam_frame, text="• Connected", font=font_verysmall, fg='green', bg='#f1f1f1')
        l7.place(relx=0.945, rely=0.8, anchor=CENTER)
    elif flag_connected == 0:
        l7 = Label(cam_frame, text="• Disconnected", font=font_verysmall, fg='red', bg='#f1f1f1')
        l7.place(relx=0.945, rely=0.8, anchor=CENTER)

    lmain = tk.Label(master=cam_frame, bg='black')
    lmain.place(relx=0.5, rely=0.4, anchor=CENTER)
    # ===========================================================================
    menu_frame.pack(fill='both', expand=1)

    root.resizable(False, False)
    root.mainloop()  # keeps the application in an infinite loop so it works continuosly
    client.disconnect()
    signal_running = False
    try:
        cap.release()
        thread1.join()
    except:
        print("")

    f = open("data.txt","r")
    line = f.read().splitlines()
    for i in line:
        try:
            os.rename(path+"/"+"current_images"+"/"+i, path+"/"+"Cache"+"/"+i)      # (old dir, new dir)
        except:
            print("")
    f.close()
    f = open("data.txt","w")
    f.truncate(0)
    f.close()
