import serial
import matplotlib.pyplot as plt
import time
import csv
import os
plt.ion()

class DebugMessage:
    def __init__(self, string):
        key_value_list = self.parse_data(string)
        self.key_list = []
        for key, value in key_value_list:
            setattr(self, key, value)
            self.key_list.append(key)

    @staticmethod
    def parse_data(string):
        
        splitChar1 = "\t"
        splitChar2 = ":"
        # Example string:
        # Potential:0.0;Dendrite1:0;Dendrite2:0;Dendrite3:0;Dendrite4:0;Dendrite5:0;Axon output:0;Pulses in queue:0;

        # This line is too long to be readable, but it works, it makes a list that looks like this [[key, value], ...]
        key_value_list = [[key_value for key_value in key_value_string.split(splitChar2)] for key_value_string in string.split(splitChar1)[:-1]]
        
        key_value_list = [[key_value[0], eval(key_value[1])] for key_value in key_value_list]
        # key_values is in the format [['key', value], ... ]
        return key_value_list

class DebugMessages:
    def __init__(self, debugMessages):
        # We assume that the keys of the first debugMessage are the same
        # as the keys in all of the debugMessages
        self.debugMessages = debugMessages

        # This variable stores data so we don't have to get the data every time we call get_values_of()
        self.storage = {}
        
    def get_values_of(self, key):
        if key not in self.storage:
            # NB! -1 is used as an error when there is no attribute to get. Don't be confused if a lot of values suddenly go to -1
            # or if a value you expected should change, is constantly -1. Check your spelling. 
            self.storage[key] = [getattr(debugMessage, key) if hasattr(debugMessage, key) else -1 for debugMessage in self.debugMessages]
        return self.storage[key]



class SerialReader:
    def __init__(self, logFilePath="log.csv", usb_port='COM18', baudrate=9600):
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
    
    def saveData(self):
        data = self.readline()
        # Check if there was an error reading the data
        if data == "":
            return
        with open(self.logFilePath, 'a+', newline='') as logFile:
            logFile.write(data)
        
        #Optional
        print(data, end='')
                
if __name__ == '__main__':               
    ser = SerialReader()

    #Optional - delete log file if exists
    if os.path.exists(ser.logFilePath):
        os.remove(ser.logFilePath)

    while True:
        ser.saveData()

    
