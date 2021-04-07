import cv2
import numpy as np
import serial

ser = serial.Serial('/dev/ttyACM0', 115200)
ser.timeout=0.3
print(ser.portstr)

cap = cv2.VideoCapture('videoplayback.mp4')
flag = False
p_flag = False
flag1 = False
p_flag1 = False
while(1):

    # Take each frame
    _, frame = cap.read()

    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # define range of green color in HSV
    lower_green = np.array([110,50,50])
    upper_green = np.array([130,255,255])

    lower_red = np.array([110,0,0])
    upper_red = np.array([230,70,70])

    # Threshold the HSV image to get only green colors
    mask = cv2.inRange(frame, lower_red, upper_red)
    x,y = mask.shape
    left = mask[0:int(x), 0:int(y/2)-1]
    per =  ((np.sum(left)/255)/(x*y))*100
    
    mask = cv2.inRange(frame, lower_green, upper_green)
    x,y = mask.shape
    left = mask[0:int(x), 0:int(y/2)-1]
    per1 =  ((np.sum(left)/255)/(x*y))*100
    print("Red percentage",per)
    print("Green percentage",per1)

    p_flag = flag
    p_flag1 = flag1

    if per > 0.001:
        flag = True
    else:
        flag = False
    
    if per1 > 0.001:
        flag1 = True
    else:
        flag1 = False

    ser.write("LD_"+str(int(flag)+int(flag1)))
    print("LD_"+str(int(flag)+int(flag1)))
    # if p_flag < flag and p_flag1 < flag1:
    #     ser.write("LD_3")
    #     print("LD_3")
    # if p_flag < flag and p_flag1 > flag1:
    #     ser.write("LD_2")
    #     print("LD_2")
    # if p_flag > flag and p_flag1 < flag1:
    #     ser.write("LD_1")
    #     print("LD_1")
    # if p_flag > flag and p_flag1 > flag1:
    #     ser.write("LD_0")
    #     print("LD_0")
    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)

    cv2.imshow('frame',frame)
    #cv2.imshow('mask',mask)
    #cv2.imshow('res',res)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
ser.close()
cv2.destroyAllWindows()
