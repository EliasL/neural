import serial
import matplotlib.pyplot as plt
import time
import csv
import os
plt.ion()

class SerialReader:
    def __init__(self, logFilePath="log/log.csv", usb_port='COM18', baudrate=9600):
        self.logFilePath = logFilePath
        self.ser = serial.Serial(usb_port, baudrate)
        self.ser.flushInput()
        self.ser.flushOutput()

    def readline(self):
        raw_data = self.ser.readline()
        try:
            return raw_data.decode('utf-8')
        except:
            return ""
    

    def get_data(self):
        string = self.readline()
        if string == "":
            return ""
        else:
            return parse_data(self.readline())
    
    def saveData(self):
        data = self.readline()
        # Check if there was an error reading the data
        if data == "":
            return
        with open(self.logFilePath, 'a+', newline='') as logFile:
            logFile.write(data)


def get_names_values(data):
    if data == "":
        return [[],[]]
    else:
        return list(zip(*data))
def get_names(data):
    return get_names_values(data)[0]
def get_values(data):
    return get_names_values(data)[1]

def parse_data(string):
    # Example string:
    # Potential:0.0;Dendrite1:0;Dendrite2:0;Dendrite3:0;Dendrite4:0;Dendrite5:0;Axon output:0;Pulses in queue:0;

    # This line is too long, but it's kinda fun
    key_values = [[key_value for key_value in key_value_string.split(":")] for key_value_string in string.split(";")[:-1]]
    
    key_values = [[key_value[0], eval(key_value[1])] for key_value in key_values]
    # key_values is in the format [['key', value], ... ]
    return key_values

                
if __name__ == '__main__':               
    ser = SerialReader()
    while True:
        ser.saveData()

    
