from random import randint

with open('higgs-social_network.edgelist', 'r') as f:
  with open ('higgs-social_network.edgelist_weighted', 'w') as f2:
   for line in f:
     f2.write(line[:-1] + ' ' + str(randint(1,100)) + "\n")

f2.close()
f.close()
