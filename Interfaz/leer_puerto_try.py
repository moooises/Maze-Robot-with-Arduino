import serial
import time

try:
    arduino=serial.Serial(28,9600,timeout=1) #Windows--> Serial(PortNumber-1)
    time.sleep(2)  #Wait initialization
    print arduino.name
    print "Hola Arduino"
    
    print arduino.read()    #Read one byte
    print arduino.read(5)   #Read five bytes
    print arduino.readline()#Read a line
    for i in range (5):
        print arduino.readline()#Read a line
   
    arduino.close()
    exit()
       
except:
    print"Fallo"
    exit()



