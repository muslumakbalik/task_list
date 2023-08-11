/*
 * CPU_usage.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Müslüm
 */

#include "cmsis_os.h"
#include "usart.h"
#include "stdio.h"

#ifdef __GNUC__

    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
 #else

    #define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
 #endif

void CPU_usage(void);

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFF);
	return ch;
}


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
	volatile UBaseType_t ArraySize,x,TaskCount;
	unsigned long TotalRunTime;//total working time

	ArraySize=uxTaskGetNumberOfTasks(); //number of task
	TaskStatusArray=pvPortMalloc(ArraySize * sizeof(TaskStatus_t)); //Memory allocated for storing statistics

	if(TaskStatusArray != NULL)
	{
	ArraySize=uxTaskGetSystemState(TaskStatusArray, ArraySize, &TotalRunTime); //Get all stats and get uptime


		for(x=0;x< ArraySize;x++)
		{
			printf("Task: %s\t\t CPU Usage: %% %.4f \r \n",
			       TaskStatusArray[x].pcTaskName,
			      ((float)TaskStatusArray[x].ulRunTimeCounter * 100) / TotalRunTime);

		}

	}
	vPortFree(TaskStatusArray);
}


