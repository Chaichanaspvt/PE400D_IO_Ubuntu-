#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include "common.h"

int main(int argc, char* argv[]) 
{
	char filename[20] = {0};
	int i2c_file;	
	unsigned char reg = 0;
	int level = -1;
	int adapter_num;
	
	//printf("argc=%d\n", argc);	
	if (argc < 2 || 
	    dio_atoi(argv[1], &level) != DIO_SUCCESS || 
		(level != 0 && level != 1)) {
		fprintf(stderr, "Usage: DOx [1|0]\n");
		return -1;
	}
	
	adapter_num = search_i2_device_num("0000:00", "0000:00:1f.4");
	if (adapter_num < 0) {
		fprintf(stderr, "Can't get adapter\n");
		return -1; 
	}
	snprintf(filename, 20, "/dev/i2c-%d", adapter_num);	
	
	i2c_file = open(filename, O_RDWR);
	if(i2c_file < 0){
        	fprintf(stderr, "open error with i2c dev file\n");
		if (errno == EACCES)
                	fprintf(stderr, "Run as root?\n");
		return -1;
	}

	i8013_get_i2c_register(i2c_file, I8013_I2C_ADDR, REG_GPIOSOV, &reg);
	//printf("reg=0x%02X\n", reg);
	if (level > 0)
		reg |= REG_DO0_MASK;
	else 
		reg &= (REG_DO_MASK ^ REG_DO0_MASK);
	i8013_set_i2c_register(i2c_file, I8013_I2C_ADDR, REG_GPIOSOV, reg);
	close(i2c_file);	
	return 0;
}	
