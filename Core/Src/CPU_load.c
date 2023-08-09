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


void CPU_Load(void)
{

//		 	 uint32_t totalRunTime = 0;
//
//		    for (int i = 0; i < 5; i++) {
//		            startTime = xTaskGetTickCount();
//
//		            vTaskDelay(pdMS_TO_TICKS(1000));
//
//		           endTime = xTaskGetTickCount() - startTime;
//
//		            totalRunTime += endTime;
//		         }
//		    uint32_t averageRunTime = totalRunTime / 5;
//		    uint32_t cpuLoadPercentage = (averageRunTime * 100) / (5 * configTICK_RATE_HZ);
//		    printf("RunTime:%lu\r\n",averageRunTime);
//		    printf("cpuLoadPercentage:%% %lu\r\n",cpuLoadPercentage);

}

void CPU_Load1(TickType_t stoptime,TickType_t tick,int x)
{

    int averagetick=tick/x;
	uint32_t CPU_Load_Percentage=(stoptime * 100)/averagetick;
	printf("-time-%lu--\r\n",stoptime);
	printf("-Percentage-%lu--\r\n",CPU_Load_Percentage);
	printf("---tick--- %u---\r\n",tick);




}
