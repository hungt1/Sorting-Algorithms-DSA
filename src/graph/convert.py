import csv

out = ['random.csv', 'sorted.csv', 'reverse.csv', 'nearly.csv']

input()

methods = ["selection-sort", "insertion-sort", "bubble-sort", "shell-sort", 
    "shaker-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"]

fields = ['sort', 'time_10000', 'time_30000', 'time_50000', 'time_100000', 'time_300000', 'time_500000', 
            'comp_10000', 'comp_30000', 'comp_50000', 'comp_100000', 'comp_300000', 'comp_500000']

listTime, listComp = dict(), dict()

for file_name in out:
    rows = []
    for sort in methods:
        listTime[sort] = []
        listComp[sort] = []
    for i in range(66):
        cur = list(input().split(', '))
        listTime[cur[0]].append(cur[3]) 
        listComp[cur[0]].append(cur[4].strip())
    for sort in methods:
        row = [sort]
        row += listTime[sort]
        row += listComp[sort]
        print(row)
        rows.append(row)
    with open(file_name, 'w') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(fields)
        csvwriter.writerows(rows)