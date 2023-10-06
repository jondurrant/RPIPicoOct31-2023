/***
 * main.cpp - HTTP Get over socket
 * Jon Durrant
 * 4-Oct-2022
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "Eyes.h"
#include "Servo.h"
#include "Head.h"





#define TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )


void runTimeStats(){
  TaskStatus_t         * pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  unsigned long        ulTotalRunTime;


  /* Take a snapshot of the number of tasks in case it changes while this
  function is executing. */
  uxArraySize = uxTaskGetNumberOfTasks();
  printf("Number of tasks %d\n", uxArraySize);

  /* Allocate a TaskStatus_t structure for each task.  An array could be
  allocated statically at compile time. */
  pxTaskStatusArray = (TaskStatus_t*) pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

  if (pxTaskStatusArray != NULL){
    /* Generate raw status information about each task. */
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray,
                                       uxArraySize,
                                       &ulTotalRunTime);



    /* For each populated position in the pxTaskStatusArray array,
    format the raw data as human readable ASCII data. */
    for (x = 0; x < uxArraySize; x++){
      printf("Task: %d \t cPri:%d \t bPri:%d \t hw:%d \t%s\n",
             pxTaskStatusArray[x].xTaskNumber,
             pxTaskStatusArray[x].uxCurrentPriority,
             pxTaskStatusArray[x].uxBasePriority,
             pxTaskStatusArray[x].usStackHighWaterMark,
             pxTaskStatusArray[x].pcTaskName
      );
    }


    /* The array is no longer needed, free the memory it consumes. */
    vPortFree(pxTaskStatusArray);
  } else{
    printf("Failed to allocate space for stats\n");
  }

  HeapStats_t heapStats;
  vPortGetHeapStats(&heapStats);
  printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
         heapStats.xAvailableHeapSpaceInBytes,
         heapStats.xNumberOfFreeBlocks,
         heapStats.xNumberOfSuccessfulAllocations,
         heapStats.xNumberOfSuccessfulFrees
  );

}


void main_task(void* params){
	Eyes eyes( 4, 3, 2);
	Head head(14,15);
	//Servo servoLong(15);

	float d=45.0;
	float lat= 70.0;


  printf("Main task started\n");

  head.start("Head", TASK_PRIORITY);

  for(;;){



	for (int c = 0; c < 6; c++){
		for (uint8_t i=0; i < 0xFF; i++){
			switch(c){
			case 0:
				eyes.setColour(i, 0, 0);
				break;
			case 1:
				eyes.setColour(0xFF-i, 0, 0);
				break;
			case 2:
				eyes.setColour(0, i, 0);
				break;
			case 3:
				eyes.setColour(0, 0xFF - i, 0);
				break;
			case 4:
				eyes.setColour(0, 0, i);
				break;
			case 5:
				eyes.setColour(0, 0, 0xFF - i);
				break;
			}

			vTaskDelay(5);
		}
	}



	/*
	for (int d=45; d < 135; d++){
		servoLong.goDegree(d);
		vTaskDelay(100);
	}
	for (int d=135; d > 45; d--){
		servoLong.goDegree(d);
		vTaskDelay(100);
	}
	 vTaskDelay(100);

	servoLong.goDegree(0);//90.0 - 34.0);
	vTaskDelay(1000);
	servoLong.off();
	vTaskDelay(3000);
	servoLong.goDegree(90.0 );
	vTaskDelay(1000);
	servoLong.off();
	vTaskDelay(3000);
	servoLong.goDegree(180.0);//90.0 + 34.0);
	vTaskDelay(1000);
	servoLong.off();
	vTaskDelay(3000);
	servoLong.goDegree(90.0 );
	vTaskDelay(500);
	servoLong.off();
	vTaskDelay(1000);
	*/

	head.moveDeg(lat, d, 200);
	d = d +45.0;
	if (d > 140.0){
		d = 45.0;
	}
	lat = lat + 20;
	if (lat > 120){
		lat = 70;
	}

    runTimeStats();

    vTaskDelay(5000);

    }

}


void vLaunch(void) {
  TaskHandle_t task;

  xTaskCreate(main_task, "MainThread", 2048, NULL, TASK_PRIORITY, &task);

  /* Start the tasks and timer running. */
  vTaskStartScheduler();
}


int main(void) {
  stdio_init_all();
  sleep_ms(2000);
  printf("GO\n");

  /* Configure the hardware ready to run the demo. */
  const char* rtos_name;
  rtos_name = "FreeRTOS";
  printf("Starting %s on core 0:\n", rtos_name);
  vLaunch();

  return 0;
}
