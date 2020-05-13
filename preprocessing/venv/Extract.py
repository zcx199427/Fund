# coding=gbk
import re
from Merge import g_NMBR
fin = open("htmls/" + g_NMBR + "/raw.txt", "r", errors='ignore')     #打开test.txt文件，以只读得方式，注意编码格式，含中文
data = fin.readlines()                            #循环文本中得每一行，得到得是一个列表的格式<class 'list'>
fin.close()                                       #关闭test.txt文件
tot = 0
for line in data:
    resultD = re.search(r'<td>(\d)-(\d)-(\d)</td>$', line)  # 使用正则表达式筛选每一行的数据,自行查找正则表达式
    resultD = re.search(r'<td>(\d*)-(\d*)-(\d*)</td>$', line)
    if resultD:
        Year = resultD.group(1)
        Month = resultD.group(2)
        Day = resultD.group(3)
        foutD = open("htmls/" + g_NMBR + "/Date.txt", "a+", encoding='utf-8')
        foutD.write(Year + ' ' + Month + ' ' + Day + '\n')
        foutD.close()#将每一行打印进test1.txt文件并换行
    resultN = re.search(r'<td class="tor bold">(\d+(\.\d+))?(?<!</td>)$',line)     #使用正则表达式筛选每一行的数据,自行查找正则表达式
    if resultN:
        NetValue = (resultN.group(1))                        #group(1)将正则表达式提取出来
        foutN = open("htmls/" + g_NMBR + "/NetValue.txt", "a+", encoding='utf-8')
        foutN.write(NetValue)  # 将每一行打印进test1.txt文件并换行
        foutN.close()
        tot = tot + 1
foutD.close()
foutN.close()
