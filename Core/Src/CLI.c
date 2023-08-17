/*
 * CLI.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Müslüm
 */


#include "cmsis_os.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
#include "CPU_usage.h"





void CLI_Command( )
{

	char buffer[250]; // for VtaskList
	char command[1]; // for input
	char command_status[8]; // for output
	HAL_StatusTypeDef Hal_Status;
	int status1,status2,status3;
	const char c1[8] = "task_add";
	const char c2[8] = "task_del";
	const char c3 [8] = "print_cu";


	printf("please enter command:  ");// command
	for(int i=0; i<8; i++)
	{
		Hal_Status = HAL_UART_Receive( &huart3, command, sizeof(command), HAL_MAX_DELAY);
		if(HAL_OK == Hal_Status)
		{
			HAL_UART_Transmit(&huart3, command, 1, 1);
			command_status[i] = command[0];
			if(command[0] == '\r' || command[0] == '\n' )
			{
			break;
			}
		}
	}
	printf("\r\n");






	status1 = memcmp(command_status, c1,8);
	status2 = memcmp(command_status, c2,8);
	status3 = memcmp(command_status, c3,8);

	if(status1 == 0) //Add
	{
	TickType_t BlockRate,TotalRunTime
	uint16_t Prio;
	const char *name;
	TaskFunction_t startmytask;
	const uint32_t stack_size = 1024;

	prinft("please enter Task Name: ");
	Hal_Status = HAL_UART_Receive( &huart3, command, sizeof(command), HAL_MAX_DELAY);
			if(HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, command, 1, 1);
				command_status[i] = command[0];
				if(command[0] == '\r' || command[0] == '\n' )
				{
					break;
				}
			}
			*name =command_status;
			printf("\r\n");
	printf("please enter Task Prio :");
	Hal_Status = HAL_UART_Receive( &huart3, command, sizeof(command), HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, command, 1, 1);
					command_status[i] = command[0];
					if(command[0] == '\r' || command[0] == '\n' )
					{
						break;
					}
				}
				Prio =command_status;
				printf("\r\n");


	xTaskCreate(startmytask, name, stack_size, NULL,2, NULL);



	}




	else if(status2 == 0) //Del
	{



	}

	else if(status3 == 0) //Print CPU_usage
	{
	printf("************************************** \r\n");
	CPU_usage( );
	printf("************************************** \r\n");
	printf("TASK         STATE     PRIO    STACK   NUM \r\n");
	vTaskList( buffer) ;
	printf("%s", buffer);
	printf("************************************** \r\n");
	}


	else
	{
	printf(" wrong command\r\n");
	}



}
