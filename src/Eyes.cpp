/*
 * Eyes.cpp
 *
 *  Created on: 6 Oct 2023
 *      Author: jondurrant
 */

#include "Eyes.h"

Eyes::Eyes(uint8_t gpRed, uint8_t gpGrn, uint8_t gpBlu){
	uint slice_num;
	xGPRed = gpRed;
	xGPGrn = gpGrn;
	xGPBlu = gpBlu;

	gpio_init(xGPRed);
	gpio_set_function(xGPRed, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGPRed, 0xFFFF);
	slice_num = pwm_gpio_to_slice_num(xGPRed);
	pwm_set_enabled(slice_num, true);

	gpio_init(xGPGrn);
	gpio_set_function(xGPGrn, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGPGrn, 0xFFFF);
	slice_num = pwm_gpio_to_slice_num(xGPGrn);
	pwm_set_enabled(slice_num, true);

	gpio_init(xGPBlu);
	gpio_set_function(xGPBlu, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGPBlu, 0xFFFF);
	slice_num = pwm_gpio_to_slice_num(xGPBlu);
	pwm_set_enabled(slice_num, true);

}

Eyes::~Eyes() {
	// TODO Auto-generated destructor stub
}

void Eyes::setColour(uint8_t red, uint8_t grn, uint8_t blu){
	uint16_t r = red * red;
	uint16_t g = grn * grn;
	uint16_t b = blu * blu;
	pwm_set_gpio_level(xGPRed, 0xFFFF - r);
	pwm_set_gpio_level(xGPGrn, 0xFFFF - g);
	pwm_set_gpio_level(xGPBlu, 0xFFFF - b);
}

