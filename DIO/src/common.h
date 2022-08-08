#define I8013_I2C_ADDR	0x20
#define REG_GPIOIR		0x09
#define REG_GPIOSOV		0x0A
#define REG_DO0_MASK	(1 << 0)
#define REG_DO1_MASK	(1 << 1)
#define REG_DO2_MASK	(1 << 2) 
#define REG_DO3_MASK	(1 << 3) 
#define REG_DI0_MASK    (1 << 4)
#define REG_DI1_MASK    (1 << 5)
#define REG_DI2_MASK    (1 << 6)
#define REG_DI3_MASK    (1 << 7)
#define REG_DO_MASK		0x0F  

typedef enum {
    DIO_SUCCESS = 0,                        /**< Expected response */    
    DIO_ERROR_UNSPECIFIED = 99 				/**< Unknown Error */
} dio_result_t;
typedef unsigned int dio_boolean_t;

dio_result_t dio_atoi(char* intStr, int* value);
int search_i2_device_num(const char *pci_device, const char* pci_id);

int i2c_smbus_access(int file, char read_write, unsigned char command,
		       int size, union i2c_smbus_data *data);
int i2c_smbus_read_byte_data(int file, unsigned char command);


int i2c_smbus_write_byte_data(int file, unsigned char command, unsigned char value);
int set_slave_addr(int file, int address, int force);

int i8013_get_i2c_register(int file, unsigned char addr, unsigned char reg, unsigned char *val);
int i8013_set_i2c_register(int file, unsigned char addr, unsigned char reg, unsigned char val);
