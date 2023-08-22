/*
 * CPU_load.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Müslüm
 */
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "stdio.h"


void CPU_Load(TickType_t BlockRate , TickType_t TotalRunTime)
{
	TickType_t start_time,start_time1,block_time = (TotalRunTime * BlockRate) / 100;
	start_time = osKernelGetTickCount();
	start_time1 = osKernelGetTickCount();
	while(start_time  < pdMS_TO_TICKS(block_time)+start_time1)
	{
		start_time = osKernelGetTickCount();

	}
	osDelay(TotalRunTime-block_time);

}



//#if 0
//TickType_t tickarray[100];
//void CPU_Usage1(TickType_t stop_time, TickType_t Total_Tick, uint8_t x)
//{
//	uint64_t averagetick;
//	uint8_t CPU_Load_Percentage;
//
//	tickarray[x] = Total_Tick;
//	if(x == 0)
//	{
//		averagetick = tickarray[x];
//		CPU_Load_Percentage = (stop_time * 100) / averagetick;
//		printf("-time-%lu--\r\n", stop_time);
//		printf("-Percentage-%u--\r\n", CPU_Load_Percentage);
//		printf("---tick--- %u---\r\n", averagetick);
//	}
//	else
//	{
//		averagetick = tickarray[x]-tickarray[x-1];
//    	CPU_Load_Percentage = (stop_time * 100) / averagetick;
//    	printf("-time-%lu--\r\n",stop_time);
//    	printf("-Percentage-%u--\r\n", CPU_Load_Percentage);
//    	printf("---tick--- %u---\r\n", averagetick);
//	}
//
//
//
//
//}
//#endif
