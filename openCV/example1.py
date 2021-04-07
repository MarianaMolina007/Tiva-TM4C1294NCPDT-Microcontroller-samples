## Serial
import serial

#init serial port and bound
# bound rate on two ports must be the same
ser = serial.Serial('/dev/ttyACM0', 115200)
ser.timeout=0.3

## cv2
import cv2
import numpy as np

cap = cv2.VideoCapture(0)

flagg = False
flagr = False
p_flagg = False
p_flagr = False

while(1):

    # Take each frame
    _, frame = cap.read()

    # Convert BGR to RGB
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # define range of green color in RGB
    lower_green = np.array([69,158,111])
    upper_green = np.array([54,121,85])

    # lower_red = np.array([0,0,80])
    # upper_red = np.array([70,70,255])
    lower_red = np.array([220,138,143])
    upper_red = np.array([137,65,67])
    # Threshold the RGB image to get only green colors
    maskg = cv2.inRange(rgb, upper_green, lower_green)
    maskr = cv2.inRange(rgb, upper_red, lower_red)
    x1,y1 = maskg.shape
    x2,y2 = maskr.shape

    leftg = maskg[0:int(x1), 0:int(y1/2)-1]
    leftr = maskr[0:int(x2), 0:int(y2/2)-1]
    
    perg = ((np.sum(leftg)/255)/(x1*y1))*100
    perr = ((np.sum(leftr)/255)/(x2*y2))*100
    # print("Percentage", per)

    p_flagg = flagg
    p_flagr = flagr

    if perg > 0.001:
        flagg = True
    else:
        flagg = False
    
    if perr > 0.001:
        flagr = True
    else:
        flagr = False

    if p_flagg < flagg and p_flagr < flagr: #send 3
        ser.write("LD_OFF")
        print("LD_OFF")
    if p_flagg < flagg and p_flagr > flagr: #send 2
        ser.write("LD_OFF")
        print("LD_OFF")
    if p_flagg > flagg and p_flagr < flagr: #send 2
        ser.write("LD_ON")
        print("LD_ON")
    if p_flagg > flagg and p_flagr > flagr: #send 2
        ser.write("LD_OFF")
        print("LD_OFF")

    # Bitwise-AND mask and original image
    resg = cv2.bitwise_and(frame,frame, mask= maskg)
    resr = cv2.bitwise_and(frame,frame, mask= maskr)

    cv2.imshow('frame',frame)
    cv2.imshow('mask green',maskg)
    cv2.imshow('mask red',maskr)
    cv2.imshow('res green',resg)
    cv2.imshow('res red',resr)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()