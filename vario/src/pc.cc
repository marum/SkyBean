/*
 * pc.cc
 *
 *  Created on: 7.11.2013
 *      Author: horinek
 */

#include "pc.h"

extern float temperature;
extern float altitude0;
extern int16_t altitude1;
extern int16_t altitude2;
extern int16_t ram_alt1_offset;
extern int16_t ram_alt2_offset;
extern float ram_sea_level_Pa;
extern float ram_kalman_q;
extern float ram_kalman_r;
extern float ram_kalman_p;
extern float raw_pressure;
extern float pressure;
extern float climb;
extern uint16_t adc_raw;

extern bool meas_new_sample;

Usart usart;
Usart gps_usart;

CreateStdIn(usart_in, usart.Read);
CreateStdOut(usart_out, usart.Write);

char gps_buff[256];
uint8_t gps_buff_index = 0;

void pc_init()
{
	GpioSetDirection(portd7, OUTPUT);

	usart.Init(usartD0, 115200, 0, 32);
	usart.SetInterruptPriority(MEDIUM);

	gps_usart.Init(usartC0, 115200, 250, 0);
	gps_usart.SetInterruptPriority(MEDIUM);

	SetStdIO(usart_in, usart_out);
}


int checksum(char *s)
{
    int c = 0;

    while(*s)
        c ^= *s++;

    return c;
}

char buff[512];

void pc_step()
{
	while (!gps_usart.isRxBufferEmpty())
	{
		uint8_t c = gps_usart.Read();
		gps_buff[gps_buff_index++] = c;
		if (c == '\n')
		{
			gps_buff[gps_buff_index] = 0;
			printf("%s", gps_buff);
			gps_buff_index = 0;
		}

	}

//	printf ("%0.1f\n", altitude0);

//	float temp = adc_raw;

	sprintf(buff, "$D,%0.2f,%0.3f,,,%0.1f,,,,,,,", climb * 10, pressure, temperature);
	printf("%s*%02X\n", buff, checksum(buff));
}

