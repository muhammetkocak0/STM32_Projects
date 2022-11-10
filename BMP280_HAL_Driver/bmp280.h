/*
 * bmp280.h
 *
 *  Created on: 7 Kas 2022
 *      Author: muhammetkocak
 */
#ifndef BMP280_H_
#define BMP280_H_






extern void calibrate(void);
extern void bmp280_Init(void);
extern int bmp280_get_temperature();
extern int bmp280_get_pressure();
extern int bmp280_get_altitude();



#endif /* BMP280_H_ */




