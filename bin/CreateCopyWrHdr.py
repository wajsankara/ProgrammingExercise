#!/usr/local/bin/python3

import sys
import os
import shutil

print ("Processing ", sys.argv[1])
f = open(sys.argv[1])
newf = ".", sys.argv[1]
fn = sys.argv[1].split('/')
print("HOO: fnsize:", len(fn))
d = open(".trail_name", 'w')
d.write("/*++++++++++++++++++++++++++++++++++++++++++++++++\n")
d.write(" * File:   ");
d.write(fn[len(fn)-1])
d.write("\n * Author: Bharathwaj Sankara\n")
d.write(" * wajsankara at yahoo dot com")
d.write("\n *+++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n")

for l in f:
  d.write(l);

f.close()
d.close()

shutil.move(".trail_name", sys.argv[1])

