# Day 1 AOC

# today is python because I forgot it's dec 1
import numpy as np

#fin = 'testin.txt'
fin = 'input.txt'

with open(fin, 'r') as f:
    ins = f.readlines()

def bounded_cumsum(arr):
    # get a cumulative sum, but on 0-100
    # that loops over if gt 100
    new_arr = np.zeros(len(arr), dtype=int)
    new_arr[0] = arr[0]
    tmp = arr[0]

    for i in range(1, len(arr)):
        tmp +=arr[i]
        if tmp<0: 
            tmp = 100+tmp%100
            tmp = tmp%100
        elif tmp>=100: 
            tmp = tmp%100
        new_arr[i] = tmp
    
    return new_arr

ins.insert(0, '50')

arr = np.array([int(n.rstrip('\n').replace('L','-').replace('R','')) \
        for n in ins], dtype=int)
p1 = bounded_cumsum(arr)

# check for zeroes
print('Part 1: ', np.count_nonzero(p1==0))

# part 2: matters how many times it passes 0
def bounded_cumsum_w0(arr):
    # same as above but only
    # keeps the number of zeroes it passes

    tmp = arr[0]
    nzeroes = 0 #number of times we pass 0

    for i in range(1, len(arr)):
        tmp +=arr[i]
        if tmp ==0: 
            nzeroes+=1
        elif tmp<0:  
            nzeroes += int(abs(tmp/100))
            if (tmp - arr[i]) !=0:
                nzeroes += 1
            tmp = (100+tmp%100)%100
        elif tmp>=100: 
            nzeroes += int(tmp/100)
            tmp = tmp%100

    return nzeroes

print('Part 2: ', bounded_cumsum_w0(arr))

