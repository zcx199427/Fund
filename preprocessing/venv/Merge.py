g_NMBR = str(470058)
type = str(2)
from Extract import tot
fout = open("htmls/" + str(g_NMBR) + "/merge.txt", "a")
fout.write("NMBR" + g_NMBR)
fout.write("TYPE" + type)
fout.write("NTVL" + str(tot))
fin = open("htmls/" + g_NMBR + "/NetValue.txt",'r')
for line in fin:
    fout.write(line)
fin.close()
if (type == 4):
    



