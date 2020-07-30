/*
 * joystick.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

//todo Lukas : calibrate joystick better
#ifndef ADC_JOYSTICK_H_
#define ADC_JOYSTICK_H_
#include <stdbool.h>
#include "adc.h"
#define X_AXIS_INDEX   2
#define Y_AXIS_INDEX   1
#define AXIS_NUMBER    2


// configurable defines al in V:
#define V_NEUTRAL_X_AXIS 1.2f
#define V_NEUTRAL_Y_AXIS 1.2f
#define V_MAX_X_AXIS     3.0f
#define V_MIN_X_AXIS     0.1f
#define V_MAX_Y_AXIS     3.0f
#define V_MIN_Y_AXIS     0.1f
#define MEASUREMENT_ERROR 0.06f


typedef enum{
	negative = 0,
	positive
}adc_direction;

typedef struct{
	uint32_t raw_data;
	float v_neutral;
	float v_max_normalized;
	float v_min_normalized;
	float converted_data;
	float percentage_value;
	uint8_t  sign;
}adc_data;

typedef struct{
	adc_data measurements[NUMBER_OF_CHANNELS];
	uint8_t bit_resolution;
	float reference_voltage;
}joystick;

typedef struct{
	uint8_t index;
	float v_max;
	float v_min;
	float v_neutral;
}ax_params;

typedef struct{
	ax_params* params;
	uint8_t size;
}joy_axis;

static ax_params joy_axis_params[] = {
		{.index = X_AXIS_INDEX, .v_max = V_MAX_X_AXIS,.v_min = V_MIN_X_AXIS,.v_neutral = V_NEUTRAL_X_AXIS},
		{.index = Y_AXIS_INDEX, .v_max = V_MAX_Y_AXIS,.v_min = V_MIN_Y_AXIS,.v_neutral = V_NEUTRAL_Y_AXIS}
};
void joy_params_init(void);
joystick* get_joy_pointer(void);
void convert_adc_values(void);
void calculate_joy_data(void);

#endif /* ADC_JOYSTICK_H_ */
