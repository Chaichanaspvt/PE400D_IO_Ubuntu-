
from PE400_DIO import *
from subprocess import call
import subprocess
DIO = PE400_DIO(passwords='a')
A = DIO._DO1()
print("A = ",A)
status = 0
B  = subprocess.call(["bin/DO0 {0}".format(status)],shell=True)
print(B)
