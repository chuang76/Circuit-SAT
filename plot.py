import matplotlib.pyplot as plt

arr = []
with open('./result.txt', 'r') as f:
    for line in f.readlines():
#         ans = int(line.split(' ')[0])
        arr.append(float(line.split(' ')[1]))

time = []
for i in reversed(arr):
    time.append(i)
    
proc = ['1', '2', '4', '8', '16']

plt.plot(proc, time, '-o')
plt.ylabel('time (sec)')
plt.xlabel('number of processes')

plt.savefig('result.png')