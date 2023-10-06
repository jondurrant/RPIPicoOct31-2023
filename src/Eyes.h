/*
 * Eyes.h
 *
 *  Created on: 6 Oct 2023
 *      Author: jondurrant
 */

#ifndef SRC_EYES_H_
#define SRC_EYES_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"

class Eyes {
public:
	Eyes(uint8_t gpRed, uint8_t gpGrn, uint8_t gpBlu);
	virtual ~Eyes();

	void setColour(uint8_t red, uint8_t grn, uint8_t blu);

private:
	uint8_t xGPRed;
	uint8_t xGPGrn;
	uint8_t xGPBlu;
};

#endif /* SRC_EYES_H_ */
