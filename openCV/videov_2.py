import cv2
import numpy as np
import serial

ser = serial.Serial('/dev/ttyACM0', 115200)
ser.timeout=0.3
print(ser.portstr)

cap = cv2.VideoCapture('videoplayback.mp4')
flag = '0'
p_flag = '0'
flag1 = '0'
p_flag1 = '0'
while(1):

    # Take each frame
    _, frame = cap.read()

    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # define range of green color in HSV
    #TODO: Mejorar limites de las capas
    lower_green = np.array([110,50,50])
    upper_green = np.array([130,255,255])

    lower_red = np.array([110,0,0])
    upper_red = np.array([230,70,70])

    # Mascara roja
    mask = cv2.inRange(frame, lower_red, upper_red)
    x,y = mask.shape
    left = mask[0:int(x), 0:int(y/2)-1]
    per =  ((np.sum(left)/255)/(x*y))*100
    
    # Mascara verde
    mask = cv2.inRange(frame, lower_green, upper_green)
    x,y = mask.shape
    left = mask[0:int(x), 0:int(y/2)-1]
    per1 =  ((np.sum(left)/255)/(x*y))*100
    print("Red percentage",per)
    print("Green percentage",per1)

    # Logica que simula un falling edge y raising edge
    p_flag = flag
    p_flag1 = flag1

    #TODO: Mejorar el porcentaje de deteccion
    if per > 0.001: 
        flag = '01' # Para encender el pin N0
    else:
        flag = '0' # Para apagar el pin N0
    
    if per1 > 0.001:
        flag1 = '10' # Para encender el pin N1
    else:
        flag1 = '0' # Para apagar el pin N1

    # Suma binaria
    sum = bin(int(flag,2) + int(flag1,2))
    # sum = '0b0'

    # Envio de datos
    ser.write("LD_"+str(int(sum,2)))
    print("LD_"+str(int(sum,2)))

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
