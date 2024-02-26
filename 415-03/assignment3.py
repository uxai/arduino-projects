# Speed monitor with accelerometer
# Feb 24, 2024
# Matthew Talebi

import warnings
import serial
import time
from gpiozero import LED, PinNonPhysical
from subprocess import call

# This disables the PinNonPhysical warning for the rest of the script
warnings.simplefilter('ignore', category=PinNonPhysical)


ser=serial.Serial("/dev/ttyUSB1",115200)  #change ACM number as found from ls /dev/tty/ACM*
ser.baudrate=115200
actled = LED(29)


while True:
   try:
      # read the message from Serial
      message=ser.readline()[0:-2]
      #Clean up the message, convert to a string to split
      messages = str(message).split(',')
      # Remove redundancies
      messages[0] = float(messages[0][1:].strip('\''))
      messages[1] = float(messages[1].strip('\''))
      # Logic to print if going too fast, moving too slow, etc.
      if(messages[1] > 4 or messages[1] < -4):
         if((messages[0] > 4 or messages[0] < -4) and (messages[1] > 7 or messages[1] < -7)):
            print('Woh! Slow down around corners!')
            ser.write(b'Woh! Slow down around corners!')
         elif((messages[0] < 4 or messages[0] > -4)):
            if(messages[1] > 4):
               print('Moving forward')
               ser.write(b'Moving forward')
            elif(messages[1] < -4):
               print('Moving backward')
               ser.write(b'Moving backward')
            else:
               print('Moving like a snail')
               ser.write(b'Moving like a snail')
      time.sleep(.2)
   except KeyboardInterrupt:
      ser.close()
      break
