import matplotlib.pyplot as plt
import time
from reader import DebugMessage, DebugMessages
plt.ion()

class Plotter:

    def __init__(self):
        # We want to have a separate graph for some variabels
        # Select the x axis by labeling the variable with -1
        # Choose what graph to draw the various variables to with 0, 1, 2 or 3
        # NB You have to use either ONLY -1, 0 and 1 OR 2 and 3 as well (all of them)
        self.variable_graph_number = {
            "time":-1,
            "DendP":0,
            "AxonP":0,
            "D1":1,
            "D2":1,
            "D3":1,
            "D4":1,
            "D5":1,
            "Axon":2,
            "Pulses":3
        }

        number_of_graphs = max(self.variable_graph_number.values())+1
        
        if(number_of_graphs == 2):
            #Set up plot
            self.figure, self.axises = plt.subplots(2,1)
        elif(number_of_graphs == 4):
            #Set up plot
            self.figure, self.axises = plt.subplots(2,2)
        
        self.axises = self.axises.flatten()

        # Each graph has a dict. Each key is a variable that should be plot,
        # and the keys value is a list containing the data that should be plotted
        self.lines = [{},{},{},{}]

        for name, graph_number in self.variable_graph_number.items():
            if graph_number != -1:
                self.lines[graph_number][name] = self.axises[graph_number].plot([],[])[0]

        # Set y limits on the graphs
        self.axises[0].set_ylim(-26, 50)
        self.axises[1].set_ylim(0, 255)
        self.axises[2].set_ylim(0, 255)
        self.axises[3].set_ylim(0, 10)

        #Other stuff
        for axis, line in zip(self.axises, self.lines):
            axis.grid()
            axis.legend(list(line.keys()), loc='upper left')

    def draw(self, debugMessages):
        
        #dataList structure
        #  [(name, (x-values, y-values)), ... ]

        # First we find the key of the x axis
        x_axis_key = ""
        for key, value in self.variable_graph_number.items():
            if value == -1:
                x_axis_key = key
        
        if x_axis_key == "":
            raise ValueError("You have not set a variable to be the x-axis!")
        
        # Now we want to find the highest and the lowest x value
        x_values = debugMessages.get_values_of(x_axis_key)
        oldest = x_values[0]
        latest = x_values[-1]
        for axis in self.axises:
            axis.set_xlim(oldest, latest)
        
        for key, graph_number in self.variable_graph_number.items():
            if graph_number != -1:
                self.lines[graph_number][key].set_xdata(x_values)
                self.lines[graph_number][key].set_ydata(debugMessages.get_values_of(key))

        #We need to draw and flush
        self.figure.canvas.draw()
        self.figure.canvas.flush_events()

def parseData(lines):
    messages = [DebugMessage(line) for line in lines]
    return DebugMessages(messages)  

logFilePath = "log.csv"

plotter = Plotter()

max_lines_to_plot = 150
while True:
    with open(logFilePath, 'r') as f:
        lines = f.read().splitlines()
        if len(lines)>max_lines_to_plot:
            last_lines = lines[-max_lines_to_plot:]
        else:
            last_lines = lines

    plotter.draw(parseData(last_lines))
    updateCheck = last_lines[-1]
    