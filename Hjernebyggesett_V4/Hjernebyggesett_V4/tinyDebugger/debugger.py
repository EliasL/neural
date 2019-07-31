import multiprocessing as mp
import os

from reader import SerialReader
from plotter import Plotter

lines = []
usb_port = 'COM20'
logFilePath = "log.csv"
maxNumberOfLinesToPlot = 150


#Optional - delete log file if exists
if os.path.exists(logFilePath):
    os.remove(logFilePath)



def reader(queue):
    # It is very likely that you have to change the usb_port
    # If you're on windows, go to device manager and find the EDBG Virtual COM Port             
    ser = SerialReader(usb_port=usb_port, logFilePath=logFilePath)
    # We discard the first line, since it's usually incomplete
    ser.readline()

    while True:
        line = ser.saveData()
        if line != "":
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

        if len(lines) > maxNumberOfLinesToPlot:
            lines = lines[-150:]
        



if __name__ == '__main__':
    ctx = mp.get_context('spawn')
    queue = ctx.Queue()
    process1 = ctx.Process(target=reader, args=(queue,))
    process1.start()

    process2 = ctx.Process(target=plotter, args=(queue,))
    process2.start()