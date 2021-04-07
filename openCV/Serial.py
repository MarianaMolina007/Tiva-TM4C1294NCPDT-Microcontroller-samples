import serial

#init serial port and bound
# bound rate on two ports must be the same
ser = serial.Serial('/dev/ttyACM0', 115200)
ser.timeout=0.3
print(ser.portstr)

while 1:
   print(ser.readline())
#send data via serial port
#ser.write("012345688902341")
ser.close()
