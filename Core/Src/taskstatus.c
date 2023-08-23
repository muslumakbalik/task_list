/*
 * taskstatus.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Müslüm
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "taskstatus.h"
#include "taskstatus.h"


void task_status (void)
{
	char buffer[1000];

	printf("TASK         STATE     PRIO    STACK   NUM \r\n");
	vTaskList( buffer) ;
	printf("%s", buffer);
	printf("************************************** \r\n");

}
