import matplotlib.pyplot as plt
import time
import reader
plt.ion()

class Plotter:

    def __init__(self, names):
        # We want to have a separate graph for dendrites
        plot1Names = []
        dendriteNames = []
        # We need to keep track of what index each of the names came from, since the data given in draw() doesn't contain names
        self. isInPlot1 = []
        for name in names:
            if 'dendrite' in name.lower():
                dendriteNames.append(name)
                self.isInPlot1.append(False)
            else:
                plot1Names.append(name)
                self.isInPlot1.append(True)

        #Set up plot
        self.timeInterval = 120
        self.figure1, (self.ax1, self.ax2) = plt.subplots(2,1)
        self.lines1 = [self.ax1.plot([],[])[0] for _ in range(len(plot1Names))]
        self.lines2 = [self.ax2.plot([],[])[0] for _ in range(len(dendriteNames))]

        #Autoscale on unknown axis and known lims on the other
        self.ax1.set_autoscaley_on(True)
        self.ax1.set_xlim(0, self.timeInterval)
        self.ax2.set_autoscaley_on(True)
        self.ax2.set_xlim(0, self.timeInterval)
        #Other stuff
        self.ax1.grid()
        self.ax1.legend(plot1Names,loc='upper left')
        self.ax2.grid()
        self.ax2.legend(dendriteNames,loc='upper left')

    def draw(self, dataList):
        now = dataList[0][0][-1]
        self.ax1.set_xlim(now-self.timeInterval, now)
        self.ax2.set_xlim(now-self.timeInterval, now)

        lines1Index = 0
        lines2Index = 0
        
        for addToPlot1, data in zip(self.isInPlot1, dataList):

            if addToPlot1:
                line = self.lines1[lines1Index]
                lines1Index += 1
            else:
                line = self.lines2[lines2Index]
                lines2Index += 1

            #Update data (with the new _and_ the old points)
            line.set_xdata(data[0])
            line.set_ydata(data[1])

        #Need both of these in order to rescale
        self.ax1.relim()
        self.ax1.autoscale_view()
        self.ax2.relim()
        self.ax2.autoscale_view()
        #We need to draw *and* flush
        self.figure1.canvas.draw()
        self.figure1.canvas.flush_events()

def parseData(lines, names):
    if 'time' not in names:
        print(names)
        raise ValueError("You need to provide a time variable if you want to plot.")
        
    #                x, y
    dataStorage = [([],[]) for _ in names]
    for line in lines:
        data = reader.parse_data(line)

        # Find time
        for name, value in data:
            if name == 'time':
                x = value
        values = reader.get_values(data)
        # Now we enter the values in the storage
        # We also remove the last one, because that one is time (the x axis)
        for variable, value in list(zip(dataStorage, values))[:-1]:
            variable[0].append(x)
            variable[1].append(value)
    return dataStorage


    

logFilePath = "log/log.csv"

with open(logFilePath, 'r', newline='') as logFile: 
    topLine = logFile.readline()
    secondLine = logFile.readline() # The top line is often corrupted from the reader starting to read in the middle of a line.
names, values = reader.get_names_values(reader.parse_data(secondLine))

# If the file becomes too big, reading from the end of the file becomes expensive, so just delete the log
# when it's very large

# :-1 to remove time
plotter = Plotter(names[:-1])
while True:
    with open(logFilePath, 'r') as f:
        lines = f.read().splitlines()
        last_lines = lines[-150:]
    plotter.draw(parseData(last_lines, names))
    