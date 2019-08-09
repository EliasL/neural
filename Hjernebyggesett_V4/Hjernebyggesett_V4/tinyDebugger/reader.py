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
    
    def __eq__(self, obj):
        if self.key_list != obj.key_list:
            return False

        for key in self.key_list:
            if getattr(self, key) != getattr(obj, key):
                return False
        
        return True



class DebugMessages:
    def __init__(self, debugMessages):
        # We assume that the keys of the first debugMessage are the same
        # as the keys in all of the debugMessages
        self.debugMessages = debugMessages
        
    def get_values_of(self, key):
        # NB! -1 is used as an error when there is no attribute to get. Don't be confused if a lot of values suddenly go to -1.
        # If a value you expected should change, is constantly -1, you should check if the names are the same everywhere. 
        return [getattr(debugMessage, key) if hasattr(debugMessage, key) else -1 for debugMessage in self.debugMessages]
    
    def remove_values_where_key_larger_than(self, key, value):
        newMessages = []
        for debugMessage in self.debugMessages:
            if hasattr(debugMessage, key):
                if getattr(debugMessage, key) <= value:
                    newMessages.append(debugMessage)
        self.debugMessages = newMessages


class SerialReader:
    def __init__(self, usb_port, logFilePath="log.csv", baudrate=115200):
        self.logFilePath = logFilePath
        self.ser = serial.Serial(usb_port, baudrate)
        self.ser.flushInput()
        self.ser.flushOutput()

    def readLine(self):
        raw_data = self.ser.readline()
        try:
            return raw_data.decode('utf-8')
        except:
            return ""
    
    def saveData(self, printData=False):
        data = self.readLine()
        # Check if there was an error reading the data
        if data == "":
            return
        with open(self.logFilePath, 'a+', newline='') as logFile:
            logFile.write(data)
        
        if printData:
            print(data, end='')

        return data
    
    @staticmethod
    def parseData(lines):
        messages = [DebugMessage(line) for line in lines]
        return DebugMessages(messages)  
                
if __name__ == '__main__':  
    
    # It is very likely that you have to change the usb_port
    # If you're on windows, go to device manager and find the EDBG Virtual COM Port             
    ser = SerialReader(usb_port='COM20')

    #Optional - delete log file if exists
    if os.path.exists(ser.logFilePath):
        os.remove(ser.logFilePath)

    while True:
        ser.saveData()

    
