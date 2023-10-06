/*
 * Head.cpp
 *
 *  Created on: 6 Oct 2023
 *      Author: jondurrant
 */

#include "Head.h"
#include "math.h"
#include <cstdio>

Head::Head(uint8_t gpLat, uint8_t gpLong){
	xLat.setGP(gpLat);
	xLong.setGP(gpLong);
	xLat.goDegree(90.0);
	xLong.goDegree(90.0);
}

Head::~Head() {
	// TODO Auto-generated destructor stub
}

void Head::moveDeg(float lat, float lon, uint ticks){

	int t = ticks/10;
	float f = 0;

	//Long Setup
	for (int i=0; i < t; i++){
		f += sin( M_PI / (float) t * (float) i);
	}

	xTotalSin= f;
	xTargetLong = lon;
	xDeltaLong =( xTargetLong - xCurrentLong);
	xSteps = t;
	xStep = xSteps;
	//printf("SETUP MOVE to %f delta %f Sin Total %f\n", lon, xDeltaLong, xTotalSinLong);

	//Lat Setup
	xTargetLat = lat;
	xDeltaLat =( xTargetLat - xCurrentLat);
}

void Head::run(){

	for (;;){

		if (xStep > 0){
			float s =  sin( (M_PI / (float) xSteps) * (float) (xStep -1)) / xTotalSin;
			float d = s  * xDeltaLong ;
			xCurrentLong += d;
			//printf("%f Move by %f to %f of %f\n",s, d, xCurrentLong, xTargetLong);
			xLong.goDegree(xCurrentLong);

			d = s * xDeltaLat;
			xCurrentLat += d;
			xLat.goDegree(xCurrentLat);

			xStep --;
			if (xStep == 0){
				xLong.off();
				xLat.off();
			}
		}

		vTaskDelay(100);
	}
}

/***
* Get the static depth required in words
* @return - words
*/
configSTACK_DEPTH_TYPE Head::getMaxStackSize(){
	return 1024;
}
