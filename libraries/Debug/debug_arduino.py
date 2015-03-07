from time import sleep
import sys
import serial
import connectfour
ser = serial.Serial("COM3", 9600) # establish connection to port
counter = 32
command = ""
VALID = ["START", "EXIT", "DIRECTION?", "STOP","LEFT", "RIGHT","FORWARD", "BACK"]
connectfour.start()

while command != "EXIT":
    command = input("$$ ")
    if command not in VALID and not "BOARD":
        sys.stdout.write("Invalid command\n")
        continue

    if command in VALID:
        ser.write(command)
        sys.stdout.write(ser.readline()) # read output from Arduino
        sleep(.1) # delay for 1/10th of second
