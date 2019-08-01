import multiprocessing as mp
import os
import time

from reader import SerialReader
from plotter import Plotter

lines = []
usb_port = 'COM20'
logFilePath = "log.csv"
secondsOfPlot = 10 # the plot will show the last n seconds


#Optional - delete log file if exists
if os.path.exists(logFilePath):
    os.remove(logFilePath)

def reader(queue, timeBetweenMessage):
    # It is very likely that you have to change the usb_port
    # If you're on windows, go to device manager and find the EDBG Virtual COM Port             
    ser = SerialReader(usb_port=usb_port, logFilePath=logFilePath)
    # We discard the first line, since it's usually incomplete
    ser.readline()
    lastTime = time.time()
    while True:
        line = ser.saveData()
        if line != "":
            queue.put(line)
            timeBetweenMessage = time.time() - lastTime
            lastTime = time.time()

def plotter(queue, timeBetweenMessage):
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
    timeBetweenMessage = mp.Value('d', 1.0)
    process1 = ctx.Process(target=reader, args=(messageQueue, timeBetweenMessage))
    process1.start()

    process2 = ctx.Process(target=plotter, args=(messageQueue, timeBetweenMessage))
    process2.start()