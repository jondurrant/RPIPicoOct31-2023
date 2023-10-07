/*
 * RangeArray.h
 *
 *  Created on: 7 Oct 2023
 *      Author: jondurrant
 */

#ifndef SRC_RANGEARRAY_H_
#define SRC_RANGEARRAY_H_

#include "Agent.h"
#include "HCSR04Range.h"
#include "Head.h"
#include "Eyes.h"

class RangeArray : public Agent{
public:
	RangeArray(
			uint8_t leftTrigger,
			uint8_t leftEcho,
			uint8_t centreTrigger,
			uint8_t centreEcho,
			uint8_t rightTrigger,
			uint8_t rightEcho
			);
	virtual ~RangeArray();

	void setHead(Head *p);

	void setEyes(Eyes *p);

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
	HCSR04Range xLeftSensor;
	HCSR04Range xCentreSensor;
	HCSR04Range xRightSensor;

	Head * pHead = NULL;
	Eyes *pEyes = NULL;

};

#endif /* SRC_RANGEARRAY_H_ */
