'''
Created on 2011-10-12

@author: weizili
'''

import os

g_securecrt_templete_file = 'build7.kill.corp.qihoo.net.ini'
g_xshell_templete_file = 'build7.kill.corp.qihoo.net.xsh'
g_templete_hostname = 'build7.kill.corp.qihoo.net'
g_xshell_dir = 'E:/dropbox/misc/sharesoft/xshell/a/'
g_securecrt_dir = 'E:/dropbox/misc/sharesoft/config_secureCRT_zieckey/Sessions/online/a/'

#modify there three parameters
g_leading = 'mse1'
g_host = '.safe.zzbc.qihoo.net'
g_start_end_number = [0, 9] # [1,4] include 1,2,3,4

def readfile(path):
    #fh = open(path, encoding='utf-8')
    fh = open(path)
    content = fh.read()
    fh.close()
    return content

def writefile(path, data):
    #fh = open(path, mode='w', encoding='utf-8')
    fh = open(path, mode='w')
    fh.write(data)
    fh.close()

if __name__ == '__main__':
    
    
    num = range( g_start_end_number[0], g_start_end_number[1] + 1 )
    print num 
    content = readfile(g_securecrt_templete_file)    
    for n in num:
        name = g_leading + str(n) + g_host
        newcontent = content.replace(g_templete_hostname, name)
        writefile(g_securecrt_dir+name + '.ini', newcontent)

    content = readfile(g_xshell_templete_file)    
    for n in num:
        name = g_leading + str(n) + g_host
        newcontent = content.replace(g_templete_hostname, name)
        writefile(g_xshell_dir+name + '.xsh', newcontent)
    
    print('OK')
    os.system('pause')
    