f = open("../mirabel/mir06.txt")
while True :
    l = f.readline()
    if l == "" :
        break
    l = l.strip().split('\t')
    if l[0][0] in ('0','1','2','3','4','5','6','7','8','9') and \
     l[1][0] in ('0','1','2','3','4','5','6','7','8','9') :
        print "\t".join(l)

