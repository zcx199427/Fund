# coding=gbk
import re
from Merge import g_NMBR
fin = open("htmls/" + g_NMBR + "/raw.txt", "r", errors='ignore')     #��test.txt�ļ�����ֻ���÷�ʽ��ע������ʽ��������
data = fin.readlines()                            #ѭ���ı��е�ÿһ�У��õ�����һ���б�ĸ�ʽ<class 'list'>
fin.close()                                       #�ر�test.txt�ļ�
tot = 0
for line in data:
    resultD = re.search(r'<td>(\d)-(\d)-(\d)</td>$', line)  # ʹ��������ʽɸѡÿһ�е�����,���в���������ʽ
    resultD = re.search(r'<td>(\d*)-(\d*)-(\d*)</td>$', line)
    if resultD:
        Year = resultD.group(1)
        Month = resultD.group(2)
        Day = resultD.group(3)
        foutD = open("htmls/" + g_NMBR + "/Date.txt", "a+", encoding='utf-8')
        foutD.write(Year + ' ' + Month + ' ' + Day + '\n')
        foutD.close()#��ÿһ�д�ӡ��test1.txt�ļ�������
    resultN = re.search(r'<td class="tor bold">(\d+(\.\d+))?(?<!</td>)$',line)     #ʹ��������ʽɸѡÿһ�е�����,���в���������ʽ
    if resultN:
        NetValue = (resultN.group(1))                        #group(1)��������ʽ��ȡ����
        foutN = open("htmls/" + g_NMBR + "/NetValue.txt", "a+", encoding='utf-8')
        foutN.write(NetValue)  # ��ÿһ�д�ӡ��test1.txt�ļ�������
        foutN.close()
        tot = tot + 1
foutD.close()
foutN.close()
