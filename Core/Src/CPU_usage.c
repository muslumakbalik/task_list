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
	TaskStatus_t *TaskStatusArray; //istatistikleri depolamak için gereken dizi
	volatile UBaseType_t ArraySize,x,TaskCount;
	unsigned long TotalRunTime;//toplam çalışma süresi

	ArraySize=uxTaskGetNumberOfTasks(); //görev sayısı
	TaskStatusArray=pvPortMalloc(ArraySize * sizeof(TaskStatus_t)); //İstatistikleri depolamak için ayrılan bellek

	if(TaskStatusArray != NULL)
	{
	ArraySize=uxTaskGetSystemState(TaskStatusArray, ArraySize, &TotalRunTime); //Tüm istatistikleri al ve çalışma süresini elde et


		for(x=0;x< ArraySize;x++)
		{
			printf("Task: %s\t\t CPU Usage: %% %u \r \n",
			       TaskStatusArray[x].pcTaskName,
			      (TaskStatusArray[x].ulRunTimeCounter * 100) / TotalRunTime);

		}

	}
	vPortFree(TaskStatusArray);
}




