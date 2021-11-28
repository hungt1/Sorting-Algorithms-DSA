# source: https://github.com/huynhtuan17ti/Sorting-Overview/blob/main/src/graph/data.py

from pandas.io.parsers import read_csv
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib import rcParams

sns.set_style("whitegrid")

methods = ["selection-sort", "insertion-sort", "bubble-sort", "shell-sort", 
    "shaker-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"]
time = ['time_10000', 'time_30000', 'time_50000', 'time_100000', 'time_300000', 'time_500000']
comp = ['comp_10000', 'comp_30000', 'comp_50000', 'comp_100000', 'comp_300000', 'comp_500000']

df = read_csv('./reverse.csv')
my_data = {}

for i in range(11):
    curTime, curComp = [], []
    for t in time:
        curTime.append(df[t][i])
    print(curTime)
    for c in comp:
        curComp.append(df[c][i])
    my_data[methods[i] + '-time'] = curTime
    my_data[methods[i] + '-comp'] = curComp
    my_data[methods[i]] = methods[i]

x = [10000, 30000, 50000, 100000, 300000, 500000]
my_data['x'] = x
my_data = pd.DataFrame(my_data)

def line():        
    rcParams['figure.figsize'] = 16, 10
    fig, ax = plt.subplots()
    colors = ['red', 'blue', 'yellow', 'orange', 'green', 'violet', 'purple', 'limegreen', 'cyan', 'palegreen', 'darkred']
    rm = []
    for idx, sort in enumerate(methods):
        sns.pointplot(data = my_data, y = sort+'-time', x = 'x', markers = '2', ax = ax, color = colors[idx])
    rm.reverse()
    for idx in rm:
        colors.pop(idx)
        methods.pop(idx)
    ax.legend(handles = ax.lines[::len(my_data)+1], labels = methods, loc = 2, bbox_to_anchor = (1,1))
    ax.set_title('Reverse Sorted Input')
    ax.set_ylabel('Run time in milliseconds')
    ax.set_xlabel('Input size')
    #plt.savefig(f'reverse_sorted_1.png')
    plt.show()
