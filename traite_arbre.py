#! /usr/bin/python
import re
import sys

def sortie(t,n,l,r,num) :
    print n, num, l,r 
    if t.has_key(n) :
        filsg,filsd,l,r,num = t[n] ;
        sortie(t,filsg,l,r,num)
        sortie(t,filsd,l,r,num)

p=re.compile(r'^(\S+_\S+)\s+(\S+_\S+)\s+(\S+_\S+)\s+(\S+)\s+(\S+)$') 

sys.setrecursionlimit(40000) 
t={}
num=1
for l in sys.stdin.readlines():
    m = p.match(l)
    if m:
        t[m.group(1)]=(m.group(2),m.group(3),m.group(4),m.group(5),num)
        num += 1
sortie(t,m.group(1),0,0,0)
