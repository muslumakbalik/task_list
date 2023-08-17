/*
 * CPU_usage.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Müslüm
 */

#include "cmsis_os.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "CLI.h"

void CPU_usage();


void configureTimerForRunTimeStats(void)
{


}
unsigned long getRunTimeCounterValue(void)
{
	return osKernelGetTickCount();
}

void CPU_usage()
{

	TaskStatus_t *TaskStatusArray; //needed to store statistics
	volatile UBaseType_t ArraySize,x,TaskCount;
	unsigned long TotalRunTime;//total working time
	ArraySize=uxTaskGetNumberOfTasks(); //number of task
	TaskStatusArray=pvPortMalloc(ArraySize * sizeof(TaskStatus_t)); //Memory allocated for storing statistics

	if(TaskStatusArray != NULL)
	{
	ArraySize=uxTaskGetSystemState(TaskStatusArray, ArraySize, &TotalRunTime); //Get all stats and get uptime


		for(x=0;x< ArraySize;x++)
		{

			printf("Task: %s\t\t CPU Usage: %% %u \r \n",
					TaskStatusArray[x].pcTaskName,
			      (TaskStatusArray[x].ulRunTimeCounter * 100) / TotalRunTime);

		}

	}
	vPortFree(TaskStatusArray); //memory is freed

}


