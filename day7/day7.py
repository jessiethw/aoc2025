import numpy as np

# read file
#with open("testin.txt", "r") as f:
with open("input.txt", "r") as f:
    contents= f.readlines()

def splitters(c):
    if c=='.':
        return False
    elif c=='^':
        return True
    elif c=="S":
        return True
    else:
        print("How did I get here?")
        return None

def new_beams(beam, idxs):
    # split the beam at each location
    for idx in idxs:
        if idx > 0:
            beam[idx-1]= True
        if idx < (len(beam)-1):
            beam[idx+1]=True
        beam[idx]=False
    return beam

beams = contents[0].replace('\n','')
beams = np.array(list(map(splitters,beams)))
nsplit=0

for line in contents[1:]: #skip start line
    line = line.replace('\n','')
    splitter_loc = np.array(list(map(splitters, line)))
    split_pts = splitter_loc*beams

    beams = new_beams(beams, np.where(split_pts)[0])
    nsplit+=np.count_nonzero(split_pts)

print("Part 1: ", nsplit)
