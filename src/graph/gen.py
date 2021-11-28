print("\\begin{table}[H]")
print("\t\\centering")
print("\t\\small")
print("\t\\begin{tabular}{|P{2cm}|P{2cm}|P{2cm}|P{2cm}|P{2cm}|P{2cm}|P{2cm}|}")
print("\t\t\\hline")
print("\t\t\\multicolumn{7}{|c|}{Data order: Randomized data} \\\\")
print("\t\t\\hline")
#print("\t\t\\textbf{Data size} & \\multicolumn{2}{c|}{10000} & \\multicolumn{2}{c|}{30000} & \\multicolumn{2}{c|}{50000} \\\\")
print("\t\t\\textbf{Data size} & \\multicolumn{2}{c|}{100000} & \\multicolumn{2}{c|}{300000} & \\multicolumn{2}{c|}{500000} \\\\")

print("\t\t\\hline")
print("\t\t\\textbf{Result} & Time & Comparison & Time & Comparison & Time & Comparison \\\\")
print("\t\t\\hline")

input()
for i in range(11):
    data = list(input().split(','))
    name = data[0]
    print('\t\t' + name.capitalize().replace('-sort', ''), end = '')
    for i in range(1, 4):
        #print(' & ' + data[i] + ' & ' + data[i + 6], end = '')
        print(' & ' + data[i + 3] + ' & ' + data[i + 9].strip(), end = '')
    print(' \\\\')
    print('\t\t\\hline')

print('\t\\end{tabular}')
print('\\end{table}')