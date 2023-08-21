/*
 * taskstatus.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Müslüm
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "stdio.h"


void task_status(void);


void task_status(void)
{
	char buffer[250];

	printf("TASK         STATE     PRIO    STACK   NUM \r\n");
	vTaskList( buffer) ;
	printf("%s", buffer);
	printf("************************************** \r\n");

}
