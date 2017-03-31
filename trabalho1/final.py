import csv

f = open('benchmarks.csv', 'r')
reader = csv.reader(f)


dic = {}

for row in reader:
    row[0] = row[0].replace(',','.')
    if row[1] in dic:
        dic[row[1]][0] = float(dic[row[1]][0]) + float(row[0])
        dic[row[1]][1] = dic[row[1]][1] + 1
    else:
        dic[row[1]] = [float(row[0]), 1]

for key, value in dic.items():
    dic[key] = float(value[0])/float(value[1])


for key, value in dic.items():
    print(str(key)+"="+str(value))


