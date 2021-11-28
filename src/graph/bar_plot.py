from pandas.io.parsers import read_csv
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib import rcParams

sns.set_style("whitegrid")

name = ["Selection Sort", "Insertion Sort", "Bubble Sort", "Shell Sort", 
    "Shaker Sort", "Heap Sort", "Merge Sort", "Quick Sort", "Counting Sort", "Radix Sort", "Flash Sort"]

methods = ["selection-sort", "insertion-sort", "bubble-sort", "shell-sort", 
    "shaker-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"]

comp = ['comp_100000', 'comp_300000', 'comp_500000']

df = read_csv('./random.csv')

new_name = name * 3
comp_list = []
size = [100000] * 11 + [300000] * 11 + [500000] * 11

for c in comp:
    for i in range(11):
        comp_list.append(df[c][i])

my_data = {'x' : new_name, 'y' : comp_list, 'Size' : size}
my_data = pd.DataFrame(my_data)

def bar():
    rcParams['figure.figsize'] = 20, 10
    fig, ax = plt.subplots()
    sns.barplot(x='x', y='y', hue='Size', data=my_data, palette='hot')
    ax.set_yscale("log")
    ax.set_title("Randomized Input")
    ax.set_ylabel('Number of comparisons')
    ax.set_xlabel('Sorting Algorithms')
    ax.legend(bbox_to_anchor=(1.02, 1), loc=2, borderaxespad=0.)
    plt.savefig(f'randomized.png')
    plt.show()

bar()