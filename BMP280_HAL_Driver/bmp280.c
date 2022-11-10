/*
 * bmp280.c
 *
 *  Created on: 7 Kas 2022
 *      Author: muhammetkocak
 */
#include <math.h>
#include "stm32f1xx_hal.h"
#include "bmp280.h"
I2C_HandleTypeDef hi2c1;
uint8_t BMP280_READ_ADDRESS = 0xEF;
uint8_t BMP280_WRITE_ADDRESS = 0xEE;
uint8_t BMP280_STATUS_ADDRESS = 0xF3;
uint8_t BMP280_CALIBRATION_START_ADDRESS = 0x88;
uint8_t BMP280_TEMP_START_ADDRESS = 0xFA;
uint8_t BMP280_PRESSURE_START_ADDRESS = 0xF7;
uint8_t BMP280_CONFIG_ADDRESS = 0xF5;
uint8_t BMP280_CTRL_MEAS_ADDRESS = 0xF4;
signed long temperature_raw, pressure_raw;
unsigned short dig_T1, dig_P1;
signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
volatile double var1, var2,t_fine;

extern float temperature, pressure, altitude, init_height;
uint8_t i2c_memory_read(uint8_t write_address, uint8_t memory_address)
{
	uint8_t rx_buffer;
	HAL_I2C_Master_Transmit(&hi2c1, write_address, &memory_address, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, write_address + 1, &rx_buffer, 1, HAL_MAX_DELAY);
	return rx_buffer;
}
void i2c_memory_write(uint8_t write_address, uint8_t memory_address, uint8_t data)
{	uint8_t tx_buffer[2];
	tx_buffer[0] = memory_address;
	tx_buffer[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, write_address, tx_buffer, 2, HAL_MAX_DELAY);
}


void bmp280_Init(void)
{
	i2c_memory_write(BMP280_WRITE_ADDRESS, BMP280_CONFIG_ADDRESS, 0b00110000);
	i2c_memory_write(BMP280_WRITE_ADDRESS, BMP280_CTRL_MEAS_ADDRESS, 0b01010111);
	calibrate();
}
void calibrate()
{
	uint8_t rx_buffer[24];
	//while(((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00000001)==1)||((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00001000)==8));
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_WRITE_ADDRESS, &BMP280_CALIBRATION_START_ADDRESS, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_READ_ADDRESS, &rx_buffer[0], 24, HAL_MAX_DELAY);
	dig_T1=(rx_buffer[0])|(rx_buffer[1]<<8);
	dig_T2=(rx_buffer[2])|(rx_buffer[3]<<8);
	dig_T3=(rx_buffer[4])|(rx_buffer[5]<<8);
	dig_P1=(rx_buffer[6])|(rx_buffer[7]<<8);
	dig_P2=(rx_buffer[8])|(rx_buffer[9]<<8);
	dig_P3=(rx_buffer[10])|(rx_buffer[11]<<8);
	dig_P4=(rx_buffer[12])|(rx_buffer[13]<<8);
	dig_P5=(rx_buffer[14])|(rx_buffer[15]<<8);
	dig_P6=(rx_buffer[16])|(rx_buffer[17]<<8);
	dig_P7=(rx_buffer[18])|(rx_buffer[19]<<8);
	dig_P8=(rx_buffer[20])|(rx_buffer[21]<<8);
	dig_P9=(rx_buffer[22])|(rx_buffer[23]<<8);
}



int bmp280_get_temperature()
{
	bmp280_Init();
	HAL_Delay(100);
	uint8_t rx_buffer[3];
	//while(((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00000001)==1)||((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00001000)==8));

	HAL_I2C_Master_Transmit(&hi2c1, BMP280_WRITE_ADDRESS, &BMP280_TEMP_START_ADDRESS, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_READ_ADDRESS, &rx_buffer[0], 3, HAL_MAX_DELAY	);

	temperature_raw=(rx_buffer[0]<<12)|(rx_buffer[1]<<4)|(rx_buffer[2]>>4);
	var1=(((double)temperature_raw)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
	var2=((((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0)*(((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);
	t_fine = (int32_t)(var1+var2);
	volatile float T = (var1+var2)/5120.0;

	return (int)T;
}

int bmp280_get_pressure()
{
	HAL_Delay(80);
	bmp280_get_temperature();
	uint8_t rx_buff[3];
	//while(((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00000001)==1)||((i2c_memory_read(BMP280_WRITE_ADDRESS, BMP280_STATUS_ADDRESS)&0b00001000)==8));
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_WRITE_ADDRESS, &BMP280_PRESSURE_START_ADDRESS, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_READ_ADDRESS, &rx_buff[0], 3, HAL_MAX_DELAY	);
	pressure_raw=(rx_buff[0]<<12)|(rx_buff[1]<<4)|(rx_buff[2]>>4);
	var1=(((double)temperature_raw)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
	var2=((((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0)*(((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);
	t_fine = (int32_t)(var1+var2);
	var1=((double)t_fine/2.0)-64000.0;
	var2=var1*var1*((double)dig_P6)/32768.0;
	var2=var2+var1*((double)dig_P5)*2.0;
	var2=(var2/4.0)+(((double)dig_P4)*65536.0);
	var1=(((double)dig_P3)*var1*var1/524288.0+((double)dig_P2)*var1)/524288.0;
	var1=(1.0+var1/32768.0)*((double)dig_P1);
	volatile	double p=1048576.0-(double)pressure_raw;
	p=(p-(var2/4096.0))*6250.0/var1;
	var1=((double)dig_P9)*p*p/2147483648.0;
	var2=p*((double)dig_P8)/32768.0;
	p=p+(var1+var2+((double)dig_P7))/16.0;
	return (int)p;

}
int bmp280_get_altitude()
{
	return (int)44330.0f*(1-powf(((float)bmp280_get_pressure())/101325.0f,1.0f/5.255f));
}

