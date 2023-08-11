/*
 * CPU_load.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Müslüm
 */
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "CPU_usage.h"
#include "usart.h"
#include "cmsis_os.h"
#include "usart.h"
#include "stdio.h"
#include "CPU_usage.h"
#include "timers.h"
void CPU_Load1(TickType_t stoptime, TickType_t tick, uint8_t x);


void CPU_Load(TickType_t BlockRate , TickType_t TotalRunTime)
{
	TickType_t start_time,start_time1;
	start_time = osKernelGetTickCount();
	start_time1 = osKernelGetTickCount();
	while(start_time  < pdMS_TO_TICKS(BlockRate)+start_time1)
	{
		start_time = osKernelGetTickCount();

	}
	osDelay(TotalRunTime);


}






TickType_t tickarray[100];
void CPU_Load1(TickType_t stoptime, TickType_t tick, uint8_t x)
{

	tickarray[x] = tick;
	if(x == 0)
	{
		int averagetick = tickarray[x];
		uint32_t CPU_Load_Percentage = (stoptime * 100) / averagetick;
		printf("-time-%lu--\r\n", stoptime);
		printf("-Percentage-%lu--\r\n", CPU_Load_Percentage);
		printf("---tick--- %u---\r\n", averagetick);
	}
	else
	{
    	uint32_t averagetick = tickarray[x]-tickarray[x-1];
    	uint32_t CPU_Load_Percentage = (stoptime * 100) / averagetick;
    	printf("-time-%lu--\r\n",stoptime);
    	printf("-Percentage-%lu--\r\n", CPU_Load_Percentage);
    	printf("---tick--- %u---\r\n", averagetick);
	}




}
