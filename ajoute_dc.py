#! /usr/bin/python
import sys
prun=open(sys.argv[1],"r")
prun.readline()
n = int(prun.readline())
prun.readline()
df={}
for i in range(n-1) :
    s=prun.readline().split()
    # print s
    df[s[0]]=s[1]
prun.close()
nom=open(sys.argv[2],"r")
dn={}
for l in nom.readlines() :
    s=l.split()
    # print s
    dn[s[0]]=s[0]+"@"+s[1]
nom.close()
for k in df.keys() :
    print k,dn[df[k]]
