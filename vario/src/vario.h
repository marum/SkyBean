/*
 * vario.h
 *
 *  Created on: 4.12.2013
 *      Author: horinek
 */

#ifndef VARIO_H_
#define VARIO_H_

#include "xlib/core/i2c.h"
#include "xlib/core/clock.h"
#include "xlib/core/system.h"
#include "xlib/core/timer.h"

#include "filter.h"
#include "common.h"
#include "bui.h"
#include "buzzer.h"
#include "pc.h"
#include "ms5611.h"
#include "bmp180.h"
#include "battery.h"

//#include "build_defs.h"

//version info
#define BUILD_MAJOR	"dev"
#define BUILD_VER	"%s.%02d%02d%02d-%02d%02d", BUILD_MAJOR, BUILD_YEAR, BUILD_MONTH, BUILD_DAY, BUILD_HOUR, BUILD_MIN

//always clean when changing sensor type or clock speed!!!

#ifdef SENSOR_TYPE_MS
	#define SENSOR	MS5611 sensor
#else
	#define SENSOR	BMP180 sensor
#endif

//#define FLUID_LIFT
#define FLUID_LIFT_REFRESH	20
//1 == 20ms

#define FAST_CLOCK
//#define SLOW_CLOCK

//uart debug & timing pin
//#define ENABLE_DEBUG_TIMING
#define ENABLE_DEBUG_UART


//old or new version
#define FINAL_VER

#ifdef FINAL_VER
	#define LEDR			porta1
	#define LEDG			porta0
	#define B_EN			portc3
	#define I2C_EN			portd4
	#define BUTTON_PIN		portc2
	#define DEBUG_PIN		portd6
	#define BM_PIN			porta3
#else
	#define LEDR			portc5
	#define LEDG			portc5
	#define B_EN			portd4
	#define I2C_EN			portc7
	#define BUTTON_PIN		portd2
	#define DEBUG_PIN		portd6
#endif


#define LEDR_ON			GpioWrite(LEDR, LOW);
#define LEDR_OFF		GpioWrite(LEDR, HI);
#define LEDG_ON			GpioWrite(LEDG, LOW);
#define LEDG_OFF		GpioWrite(LEDG, HI);

#define BUTTON_DOWN		(GpioRead(BUTTON_PIN) == LOW)

void mark();

#endif /* VARIO_H_ */
