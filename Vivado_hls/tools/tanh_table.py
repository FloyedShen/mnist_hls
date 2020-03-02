import sys
import math

if(len(sys.argv) == 1):
    bits = 8
    integer = 3
elif(len(sys.argv) == 3):
    bits = int(argv[1])
    integer = int(argv[2])
else:
    print('Using in wrong way. Please refer to source file.')
    exit()

index = []
value = []
_min = 1/(2**(bits-integer))
_begin = -(2**(integer-1))

for i in range(2**bits):
    index.append(_begin + _min*i)
    value.append(math.tanh(index[-1]))

findex = open('../include/tanh_index.h', 'w')
fvalue = open('../include/tanh_value.h', 'w')

for item in index:
    findex.write(str(item) + ',\r\n')

for item in value:
    fvalue.write(str(item) + ',\r\n')

findex.close()
fvalue.close()