#include "twi.h"
#include "imu.h"

void imu_init(void) {
    //accelerommetr config
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL1_XL);
    twi_write(0x58);
    twi_stop();
    
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL9_XL);
    twi_write(0x38);
    twi_stop();
    
    //gyroscope config
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL2_G);
    twi_write(0x58);
    twi_stop();
    
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL10_C);
    twi_write(0x38);
    twi_stop();
}

int16_t imu_receive(uint8_t reg) {
    uint8_t high_byte, low_byte;
    int16_t data;
    
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(reg);
    twi_start();
    twi_write(LSM6DS33_ADDRESS_R);
    low_byte = twi_read_ack();
    high_byte = twi_read_nack();
    twi_stop();
    
    data = (high_byte << 8) | low_byte;
    
    return data;
}

