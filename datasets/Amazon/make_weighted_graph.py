from random import randint

with open('amazon0601.txt', 'r') as f:
  with open ('amazon0601.txt_weighted', 'w') as f2:
   for line in f:
     f2.write(line[:-1] + ' ' + str(randint(1,100)) + "\n")

f2.close()
f.close()
