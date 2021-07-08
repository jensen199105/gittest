/*
 *  \file driver_bus.c
 *
 * 
 * 
 * 
 * 
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define ADAPTER_NAME        "MY_I2C_ADAPTER"

static u32 my_func(struct i2c_adapter *adap)
{
    return 0;
}

static s32 my_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg * msgs, int num)
{
    int i;

    for (i = 0; i < num; ++i) {
        int j;
        struct i2c_msg *msg_temp = &msgs[i];

        pr_info("[Count: %d] [%s]: [Addr = 0x%x] [Len = %d] [Data] = ", i, __func__, msg_temp->addr, msg_temp->len);

        for (j = 0; j < msg_temp->len; ++j) {
            pr_cont("[0x%02x] ", msg_temp->buf[i]);
        }

        return 0;
    }
}


static s32 my_smbus_xfer(struct i2c_adapter *adap, u16, unsigned short flags,
                        char read_write, u8 command, int size, union i2c_smbus_data)
{
    pr_info("In %s\n", __func__);
    return 0;
}                        

static struct i2c_algorithm my_i2c_algorithm = {
    .smbus_xfer = my_smbus_xfer,
    .master_xfer = my_i2c_xfer,
    .functionality = my_func,
};

static struct i2c_adapter my_i2c_adapter = {
    .owner = THIS_MODULE,
    .class = I2C_CLASS_HWMON,
    .algo = &my_i2c_algorithm,
    .name = ADAPTER_NAME,
};

static int __init my_driver_init(void)
{
    int ret = -1;
    ret = i2c_add_adapter(&my_i2c_adapter);

    pr_info("Bus Driver Added!\n");

    return ret;
}


static void __exit my_driver_exit(void)
{
    i2c_del_adapter(&my_i2c_adapter);
    pr_info("Bus Driver Removed!\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jensen199105@gmail.com");
MODULE_DESCRIPTION("Simple I2C Bus driver");
MODULE_VERSION("1.0");