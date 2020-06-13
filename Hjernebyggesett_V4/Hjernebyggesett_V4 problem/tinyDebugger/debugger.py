import multiprocessing as mp
import os
import time

from reader import SerialReader
from plotter import Plotter

lines = []
usb_port = 'COM3'
logFilePath = "log.csv"
secondsOfPlot = 10 # the plot will show the last n seconds


#Optional - delete log file if exists
if os.path.exists(logFilePath):
    os.remove(logFilePath)

def reader(queue, printData=False):
    # It is very likely that you have to change the usb_port
    # If you're on windows, go to device manager and find the EDBG Virtual COM Port             
    ser = SerialReader(usb_port=usb_port, logFilePath=logFilePath)
    # We discard the first line, since it's usually incomplete
    ser.readLine()
    while True:
        # Use ser.saveData() here if you want to save the data to log.csv
        line = ser.readLine()
        if line != "":
            if printData:
                print(line, end="")
            queue.put(line)

def plotter(queue):
    lines = []
    plotter = Plotter()
    while True:
        while not queue.empty():
            line = queue.get()
            if line != None:
                lines.append(line)

        if len(lines) > 1:
            debugMessages = SerialReader.parseData(lines)
            plotter.draw(debugMessages)

        numberOfLinesToDraw = 150
        if len(lines) > numberOfLinesToDraw:
            lines = lines[-numberOfLinesToDraw:]      



if __name__ == '__main__':
    ctx = mp.get_context('spawn')
    messageQueue = ctx.Queue()
    process1 = ctx.Process(target=reader, args=(messageQueue, True))
    process1.start()

    process2 = ctx.Process(target=plotter, args=(messageQueue,))
    process2.start()