#include "twi.h"
#include "imu.h"

const uint8_t IMU_UPDATE_TIME_MS = 10;

void imu_init(void) {
    //accelerommetr config
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL1_XL);
    twi_write(0x58);
    twi_stop();
    
    //gyroscope config
    twi_start();
    twi_write(LSM6DS33_ADDRESS_W);
    twi_write(LSM6DS33_CTRL2_G);
    twi_write(0x58);
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
    
    data = (int16_t)(high_byte << 8 | low_byte);
    
    return data;
}

void imu_read(void) {
    //g_x = imu_receive(LSM6DS33_OUTX_L_G);
    g_y = imu_receive(LSM6DS33_OUTY_L_G);
    //g_z = imu_receive(LSM6DS33_OUTZ_L_G);
    //a_x = imu_receive(LSM6DS33_OUTX_L_XL);
    //a_y = imu_receive(LSM6DS33_OUTY_L_XL);
    //a_z = imu_receive(LSM6DS33_OUTZ_L_XL);
}

void imu_calibrate(void) {
    // wait for IMU readings to stabilize
    _delay_ms(1000);
 
    // calibrate the gyro
    int32_t total = 0;
    for (int i = 0; i < 100; i++) {
        imu_read();
        total += g_y;
        _delay_ms(1);
    }
 
    g_y_zero = total / 100;
}

void imu_integrate_gyro(void) {
    // Convert from full-scale 1000 deg/s to deg/s.
    angle_rate = (g_y - g_y_zero) / 29;
 
    angle += angle_rate * IMU_UPDATE_TIME_MS;
}

