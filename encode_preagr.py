f = open("mir06c.prun")
f.readline()
nb = int(f.readline())
p={}
for i in xrange(nb) :
    l = f.readline().strip().split('\t')
    p[l[1]]=l[0]
f.close()

f=open("preagreg")
for l in f :
    l = l.strip().split('\t')
    print "\t".join((p[l[0]],p[l[1]]))
