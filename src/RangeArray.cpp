/*
 * RangeArray.cpp
 *
 *  Created on: 7 Oct 2023
 *      Author: jondurrant
 */

#include "RangeArray.h"
#include <cstdio>

RangeArray::RangeArray(
		uint8_t leftTrigger,
		uint8_t leftEcho,
		uint8_t centreTrigger,
		uint8_t centreEcho,
		uint8_t rightTrigger,
		uint8_t rightEcho
		){

	xLeftSensor.setGP(leftTrigger, leftEcho);
	xCentreSensor.setGP(centreTrigger, centreEcho);
	xRightSensor.setGP(rightTrigger, rightEcho);

}

RangeArray::~RangeArray() {
	// TODO Auto-generated destructor stub
}

void RangeArray::run(){
	uint32_t now, last = 0;
	uint delay=50;
	int direction = 0;
	int preDirection = 0;
	int left, right, centre, min =0;
	int moveCount = 0;
	bool sleep = false;

	last =  to_ms_since_boot(get_absolute_time ());
	for (;;){

		xLeftSensor.trigger();
		vTaskDelay(delay);
		left = (left / 10 * 7) + (xLeftSensor.getDistanceMM() / 10 * 3);

		xCentreSensor.trigger();
		vTaskDelay(delay);
		centre = (centre / 10 * 7) + (xCentreSensor.getDistanceMM() / 10 * 3);

		xRightSensor.trigger();
		vTaskDelay(delay);
		right = (right / 10 * 7) + (xRightSensor.getDistanceMM() / 10 * 3);

		if (
				(left < centre) &&
				(left <  right)){
			direction = -1;
		} else if (
				(right < centre) &&
				(right <  left)){
			direction = 1;
		} else {
			direction = 0;
		}

		min = left;
		if (centre < min){
			min = centre;
		}
		if (right < min){
			min = right;
		}

		now = to_ms_since_boot(get_absolute_time ());

		if (min > 1000){
			if (pEyes != NULL){
				pEyes->setColour(0, 0xFF, 0);
			}
		} else if (min > 500){
			if (pEyes != NULL){
				pEyes->setColour(min/10 + 70, 0x50, 0x50);
			}
			last = now;
		} else {
			if (pEyes != NULL){
				pEyes->setColour(0xFF, 0, 0);
			}
			last = now;
		}

		printf("Ranges %d, %d, %d Dir %d\n",
				left,
				centre,
				right,
				direction);




		if (direction != preDirection){
			moveCount++;
			if (moveCount > 3){
				sleep = false;
				last = now;
				moveCount = 0;
				preDirection = direction;
				if (pHead != NULL){
					float lat = 90.0 + (34.0 * direction);
					pHead->moveDeg(70.0,  lat, 100);
					vTaskDelay(300);
				}
			}
		} else {

			if((now - last) > 10000){
				if (!sleep){
					sleep = true;
					if (pHead != NULL){
						pHead->moveDeg(10.0,  90.0, 300);
					}
					if (pEyes != NULL){
						pEyes->setColour(0,0,0xFF);
						vTaskDelay(1000);
						pEyes->setColour(0,0,0);
					}
					vTaskDelay(5000);

					last = now;
					preDirection = direction = 2;
				}
			}

		}

	}
}

/***
 * Get the static depth required in words
 * @return - words
 */
 configSTACK_DEPTH_TYPE RangeArray::getMaxStackSize(){
	 return 1024;
 }


 void RangeArray::setHead(Head *p){
	 pHead = p;
 }

void RangeArray::setEyes(Eyes *p){
	pEyes = p;
}
