#!/usr/bin/python

import sys

print ('Number of arguments:', len(sys.argv), 'arguments.')
print ('Argument List:', str(sys.argv))
arguments = len(sys.argv) - 1
position = 1
while (arguments >= position):
    print ("Parameter %i: %s" % (position, sys.argv[position]))
    position = position + 1

with open(sys.argv[1], 'r') as file :
    filedata = file.read()

# Replace the target string
filedata = filedata.replace(sys.argv[2], sys.argv[3])

# Write the file out again
with open(sys.argv[1], 'w') as file:
    file.write(filedata)    