import os

lists = os.listdir()

for fname in lists:
    if(fname.split('.')[1] != 'mdl'):
        continue
    fin = open(fname, 'r')
    fout = open(fname.split('.')[0]+'.h', 'w')
    print(fname.split('.')[0]+'.h')
    i=0
    for line in fin:
        fout.write(line.strip()+',\r\n')
        i+=1
    print(i)
    fin.close()
    fout.close()
