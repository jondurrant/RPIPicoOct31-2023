/*
 * Head.h
 *
 *  Created on: 6 Oct 2023
 *      Author: jondurrant
 */

#ifndef SRC_HEAD_H_
#define SRC_HEAD_H_

#include "Agent.h"
#include "Servo.h"


class Head : public Agent{
public:
	Head(uint8_t gpLat, uint8_t gpLong);
	virtual ~Head();

	void moveDeg(float lat, float lon, uint ticks);

protected:
	/***
	 * Task main run loop
	 */
	virtual void run();

	/***
	 * Get the static depth required in words
	 * @return - words
	 */
	virtual configSTACK_DEPTH_TYPE getMaxStackSize();

private:
	Servo xLat;
	Servo xLong ;

	float xCurrentLong = 90.0;
	float xTargetLong = 90.0;
	float xTotalSin = 0.0;
	float xDeltaLong = 0.0;
	float xCurrentLat = 90.0;
	float xTargetLat = 90.0;
	float xDeltaLat = 0.0;
	int xSteps = 0;
	int xStep = 0;
};

#endif /* SRC_HEAD_H_ */
