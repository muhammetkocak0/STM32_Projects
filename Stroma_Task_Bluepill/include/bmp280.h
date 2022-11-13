/*
 * bmp280.h
 *
 *  Created on: 7 Kas 2022
 *      Author: muhammetkocak
 */
#ifndef BMP280_H_
#define BMP280_H_


//#define BMP280_dev_address 0xEE

extern signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

 extern void calibrate(void);
 extern void bmp280_Init(void);
 extern int bmp280_get_temperature();
 extern int bmp280_get_pressure();
#endif /* BMP280_H_ */




