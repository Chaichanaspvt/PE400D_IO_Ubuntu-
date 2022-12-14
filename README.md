# PE400D_IO_Ubuntu-
Runtime Environment: 
BIOS: Version: 1.08.98 Release Date: 05/31/2022
OS: Linux asus-PE400D 5.4.0-110-generic #124~18.04.1-Ubuntu
OS: Linux asus-PE400D 5.13.0-44-generic #49~20.04.1-Ubuntu
OS: Linux asus-PE400D 5.15.0-41-generic #44-Ubuntu 22.04 LTS
Step 1: Installing Ubunut OS 18.04.6, 20.04.4/22.04
Make sure the Linux Kernel version is 5.4.0 (Ubuntu 18.04) or 5.13.0 (Ubuntu 20.04). 
// for Ubuntu 18.04 with Linux kernel 5.4
asus@asus-PE400D:~$ uname -a
Linux asus-PE400D 5.4.0-110-generic #124~18.04.1-Ubuntu SMP Fri Apr 22 
12:01:21 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
// for Ubuntu 20.04 with Linux kernel 5.13
asus@asus-PE400D:~$ uname -a
Linux asus-PE400D 5.13.0-44-generic #49~20.04.1-Ubuntu SMP Wed May 18 
18:44:28 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
for Ubuntu 22.04 with Linux kernel 5.15
asus@asus-PE400D:~$ uname -a
Linux asus-PE400D 5.15.0-41-generic #44-Ubuntu SMP Wed Jun 22 14:20:53 UTC 
2022 x86_64 x86_64 x86_64 GNU/Linux
Step 2: Input the following command to install driver
// for Ubuntu 18.04 with Linux kernel 5.4
$ sudo apt-get update
$ sudo apt-get install build-essential i2c-tools
$ sudo modprobe i2c-i801
Step 3: Make sure the driver is loaded
asus@asus-PE400D:~$ lsmod | grep i2c
i2c_i801 36864 0
i2c_smbus 20480 1 i2c_i801
i2c_algo_bit 16384 2 igb,i915
Step 4: Check the target device DIO is existing
asus@asus-PE400D:~$ sudo i2cdetect -l
[sudo] password for asus:
i2c-0 smbus SMBus I801 adapter at efa0 SMBus adapter
i2c-1 i2c Synopsys DesignWare I2C adapter I2C adapter
i2c-2 i2c Synopsys DesignWare I2C adapter I2C adapter
i2c-3 i2c i915 gmbus dpb I2C adapter
i2c-4 i2c i915 gmbus dpc I2C adapter
i2c-5 i2c i915 gmbus misc I2C adapter
i2c-6 i2c i915 gmbus dpd I2C adapter
i2c-7 i2c AUX B/DDI B/PHY B I2C adapter
i2c-8 i2c AUX D/DDI D/PHY D I2C adapter
asus@asus-PE400D:~$ sudo i2cdetect -y -r 0
 0 1 2 3 4 5 6 7 8 9 a b c d e f
00: -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: 30 -- -- -- -- 35 UU UU -- -- -- -- -- -- -- --
40: -- -- -- -- 44 -- -- -- -- -- -- -- -- -- -- --
50: UU -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- 62 -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
The DIO sample code is based on Linux native i2c-dev interface
Dev-interface: https://www.kernel.org/doc/Documentation/i2c/dev-interface.rst
Step 6: Get into the C sample code folder and compile the DIO sample code
asus@asus-PE400D:~/code/PE400D/DIO$ make clean
make -C src/ clean
make[1]: Entering directory '/home/asus/code/PE400D/DIO/src'
rm -f ./*.o ./DO0 ./DO1 ./DO2 ./DO3 ./DI0 ./DI1 ./DI2 ./DI3
rm -f ../bin/DO0 ../bin/DO1 ../bin/DO2 ../bin/DO3 ../bin/DI0 ../bin/DI1 ../bin/DI2 ../bin/DI3
make[1]: Leaving directory '/home/asus/code/PE400D/DIO/src'
asus@asus-PE400D:~/code/PE400D/DIO$ make
make -C src/ clean
make[1]: Entering directory '/home/asus/code/PE400D/DIO/src'
rm -f ./*.o ./DO0 ./DO1 ./DO2 ./DO3 ./DI0 ./DI1 ./DI2 ./DI3
rm -f ../bin/DO0 ../bin/DO1 ../bin/DO2 ../bin/DO3 ../bin/DI0 ../bin/DI1 ../bin/DI2 ../bin/DI3
make[1]: Leaving directory '/home/asus/code/PE400D/DIO/src'
make -C src/
make[1]: Entering directory '/home/asus/code/PE400D/DIO/src'
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DO0.c -o DO0.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c common.c -o common.o
cc -o DO0 DO0.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DO1.c -o DO1.o
cc -o DO1 DO1.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DO2.c -o DO2.o
cc -o DO2 DO2.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DO3.c -o DO3.o
cc -o DO3 DO3.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DI0.c -o DI0.o
cc -o DI0 DI0.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DI1.c -o DI1.o
cc -o DI1 DI1.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DI2.c -o DI2.o
cc -o DI2 DI2.o common.o
cc -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnestedexterns -Winline -W -Wundef -Wmissing-prototypes -Iinclude -c DI3.c -o DI3.o
cc -o DI3 DI3.o common.o
make[1]: Leaving directory '/home/asus/code/PE400D/DIO/src'
asus@asus-PE400D:~/code/PE400D/DIO$ ls bin/
DI0 DI1 DI2 DI3 DO0 DO1 DO2 DO3
Step 6: Run the sample code
// Get DIO value
asus@asus-PE400D:~/code/PE400D/DIO/bin$ sudo ./DI0
0
// Set DO1 to High
asus@asus-PE400D:~/code/PE400D/DIO/bin$ sudo ./DO1 1
// set DO1 to Low
asus@asus-PE400D:~/code/PE400D/DIO/bin$ sudo ./DO1 0