#! /usr/bin/python
import re
import sys

def sortie(t,n,l,num) :
    print n[:5],n[6:], num, l 
    if t.has_key(n) :
        filsg,filsd,l,num = t[n] ;
        sortie(t,filsg,l,num)
        sortie(t,filsd,l,num)

p=re.compile(r'^(\S{5}_\S+)\s+(\S{5}_\S+)\s+(\S{5}_\S+)\s+(\S+)$') 

sys.setrecursionlimit(40000) 
t={}
num=1
for l in sys.stdin.readlines():
    m = p.match(l)
    if m:
        t[m.group(1)]=(m.group(2),m.group(3),m.group(4),num)
        num += 1
sortie(t,m.group(1),0,0)
