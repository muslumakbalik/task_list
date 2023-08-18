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
	char command1[1];
	char command_status[8]; // for output
	char command_status1[2];
	HAL_StatusTypeDef Hal_Status;
	int status1,status2,status3,status4;
	const char c1[8] = "task_add";
	const char c2[8] = "task_del";
	const char c3 [8] = "print_cu";
	const char c4 [8] = "help_com";


	printf("\r\n>>");// command
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
	status4 = memcmp(command_status, c4,8);

	TaskHandle_t xHandle = NULL;
	if(status1 == 0) //Add
	{
	TickType_t BlockRate,TotalRunTime;
	uint16_t Prio;
	const char *name;
	const uint32_t stack_size = 128;


	printf("please enter Task Name:");
		for(int i=0; i<8; i++)
		{
				Hal_Status = HAL_UART_Receive( &huart3, command, sizeof(command), HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, command, 1, 1);
					command_status[i] = command[0];
						if(command[0] == '\r' || command[0] == '\n' || command[0] =='BS'|| command[0] =='DEL')
						{
							printf("\r\n");
							break;
						}
				}
		}
			name =command_status;
			printf("\r\n");

	printf("please enter Task Prio :");
		for(int i=0; i<2; i++)
		{
				Hal_Status = HAL_UART_Receive( &huart3, command1, sizeof(command1), HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, command1,sizeof(command1), 1);
					command_status1[i] = command1[0];
					if(command1[0] == '\r' || command1[0] == '\n' )
					{
						break;
					}
				}
				Prio =command_status1;
				printf("\r\n");

		}

		void startmytask( void * pvParameters ) //function of task
		{

			for(;;)
			{
			osDelay(1);

			}
		}
	xTaskCreate(startmytask, name, stack_size, NULL,12, xHandle);
	printf("task created\r\n");
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

	else if(status4 == 0) //Help
	{
		RESET;
		printf("\r\ntask_add --> you can add task by entering prio and name\r\ntask_del --> you can delete task by entering  name\r\nprint_cu --> prints CPU usage\r\nhelp --> you can see the commands\r\n");
	}

	else
	{
	printf(	"\r\nWrong command \r\nPlease try the command below\r\n help_com --> you can see the commands\r\n");
	}

}
