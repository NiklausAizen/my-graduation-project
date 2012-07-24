import random
import os
import string
f=open('random.txt','w')
for i in range(1000000):
    j=random.random()
    f.write(str(j))
    f.write('\n')
f.close()

