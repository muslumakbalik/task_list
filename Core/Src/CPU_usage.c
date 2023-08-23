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
#include "CPU_usage.h"
#include "task.h"

#define tskRUNNING_CHAR		( 'X' )
#define tskBLOCKED_CHAR		( 'B' )
#define tskREADY_CHAR		( 'R' )
#define tskDELETED_CHAR		( 'D' )
#define tskSUSPENDED_CHAR	( 'S' )


void configureTimerForRunTimeStats(void)
{


}
unsigned long getRunTimeCounterValue(void)
{
	return osKernelGetTickCount();
}

void CPU_usage(void)
{

	TaskStatus_t *TaskStatusArray; //needed to store statistics
	volatile UBaseType_t ArraySize,x;
	unsigned long TotalRunTime;//total working time
	char cStatus;

	ArraySize=uxTaskGetNumberOfTasks(); //number of task
	TaskStatusArray=pvPortMalloc(ArraySize * sizeof(TaskStatus_t)); //Memory allocated for storing statistics

	if (TaskStatusArray != NULL)
	{
	ArraySize=uxTaskGetSystemState(TaskStatusArray, ArraySize, &TotalRunTime); //Get all stats and get uptime

		for (x = 0; x< ArraySize; x++)
		{

			switch( TaskStatusArray[ x ].eCurrentState )
				{
					case eRunning:		cStatus = tskRUNNING_CHAR;
										break;

					case eReady:		cStatus = tskREADY_CHAR;
										break;

					case eBlocked:		cStatus = tskBLOCKED_CHAR;
										break;

					case eSuspended:	cStatus = tskSUSPENDED_CHAR;
										break;

					case eDeleted:		cStatus = tskDELETED_CHAR;
										break;

					case eInvalid:
					default:

										cStatus = ( char ) 0x00;
										break;
				}

		printf("Task:%s\t\tCPUUsage:%%%lu\tTaskState:%c\tTaskPrio:%lu\r\n",
				TaskStatusArray[x].pcTaskName,
			    (TaskStatusArray[x].ulRunTimeCounter * 100) / TotalRunTime,
				cStatus,
				TaskStatusArray[x].uxCurrentPriority);
		}

	}
	vPortFree(TaskStatusArray); //memory is freed

}


