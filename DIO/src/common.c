
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
#include "i2c/smbus.h"

#include "common.h"

dio_result_t dio_atoi(char* intStr, int* value)
{
    char* end;
    // here 10 determines the number base in which strol is to work
    long val = strtol(intStr, &end, 10);
    if (*end != '\0' || errno == ERANGE || end == intStr || val > INT_MAX || val < INT_MIN) {
        *value = 0;
        return DIO_ERROR_UNSPECIFIED;
    }
    *value = (int) val;
    return DIO_SUCCESS;
}


int search_i2_device_num(const char *pci_device, const char* pci_id)
{
	char path[1024] = {0};
    snprintf(path, 1024 - 1, "/sys/devices/pci%s/%s/", pci_device, pci_id);
    if (access( path, F_OK ) == 0) {
        struct dirent** namelist;
        int n;
        n = scandir(path, &namelist, NULL, alphasort);
        if (n < 0) {
            fprintf(stderr, "Failed to get information on i2c\n");
            return -1;
        } else {
            while (n--) {
                char* dup = strdup(namelist[n]->d_name);
                char* orig_dup = dup;
                if (dup == NULL) {
                    fprintf(stderr, "Ran out of memory!\n");
                    break;
                }
                const char delim = '-';
                char* token;
                token = strsep(&dup, &delim);
                if (token != NULL) {
                    if (strncmp("i2c", token, 3) == 0) {
                        token = strsep(&dup, &delim);
                        if (token != NULL) {
                            int ret = -1;
                            if (dio_atoi(token, &ret) == DIO_SUCCESS) {
                                free(orig_dup);
                                free(namelist[n]);
                                free(namelist);
                                //ptrintf("Adding i2c bus found on i2c-%d on adapter %s", ret, adapter_name);
                                return ret;
                            }
                            free(orig_dup);
                            free(namelist[n]);
                            free(namelist);
                            return -1;
                        }
                    }
                }
                free(orig_dup);
                free(namelist[n]);
            }
            free(namelist);
        }
		
		
		
    }
    return -1;
}

int i2c_smbus_access(int file, char read_write, unsigned char command,
		       int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;
	int err;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;

	err = ioctl(file, I2C_SMBUS, &args);
	if (err == -1)
		err = -errno;
	return err;
}

int i2c_smbus_read_byte_data(int file, unsigned char command)
{
	union i2c_smbus_data data;
	int err;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, command,
			       I2C_SMBUS_BYTE_DATA, &data);
	if (err < 0)
		return err;

	return 0x0FF & data.byte;
}

int i2c_smbus_write_byte_data(int file, unsigned char command, unsigned char value)
{
        union i2c_smbus_data data;
        data.byte = value;
        return i2c_smbus_access(file, I2C_SMBUS_WRITE, command,
                                I2C_SMBUS_BYTE_DATA, &data);
}


int set_slave_addr(int file, int address, int force)
{
	/* With force, let the user read from/write to the registers
	   even when a driver is also running */
	if (ioctl(file, force ? I2C_SLAVE_FORCE : I2C_SLAVE, address) < 0) {
		fprintf(stderr,
			"Error: Could not set address to 0x%02x: %s\n",
			address, strerror(errno));
		return -errno;
	}

	return 0;
}

int i8013_get_i2c_register(int file, unsigned char addr, unsigned char reg, unsigned char *val) {        
    set_slave_addr(file, addr, 0);
    *val = i2c_smbus_read_byte_data(file, reg); 
    return 0;
}

int i8013_set_i2c_register(int file, unsigned char addr, unsigned char reg, unsigned char val) {        
    set_slave_addr(file, addr, 0);
    i2c_smbus_write_byte_data(file, reg, val); 
    return 0;
}