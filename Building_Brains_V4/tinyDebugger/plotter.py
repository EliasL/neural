import serial

class SerialReader:
    def __init__(self, usb_port='COM18', baudrate=9600):
        self.ser = serial.Serial(usb_port, baudrate)
        self.ser.flushInput()
        self.ser.flushOutput()

    def readline(self):
        raw_data = self.ser.readline()
        try:
            return raw_data.decode('utf-8')
        except:
            return ""
    
    def parse_data(self, string):
        # Example string:
        # Potential:0.0;Dendrite1:0;Dendrite2:0;Dendrite3:0;Dendrite4:0;Dendrite5:0;Axon output:0;Pulses in queue:0;

        # This line is too long, but it's kinda fun
        key_values = [[key_value for key_value in key_value_string.split(":")] for key_value_string in string.split(";")[:-1]]
        
        key_values = [[key_value[0], eval(key_value[1])] for key_value in key_values]
        return key_values

    def get_data(self):
        return self.parse_data(self.readline())

class Plotter:
    pass


sr = SerialReader()
while True:
    print(sr.get_data())
    