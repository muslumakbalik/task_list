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
#include "taskstatus.h"

void CLI_Command(void );


void CLI_Command( void)
{
	setbuf(stdout, NULL);
	char command[1];
	char command_name[1];
	char command_prio[1];

	char command_status[8]={0};
	char prio[2]={0};
	char name[8]={0};

	HAL_StatusTypeDef Hal_Status;
	int status1,status2,status3,status4;
	const char c1[8] = "task_add";
	const char c2[8] = "task_del";
	const char c3 [8] = "print_cu";
	const char c4 [8] = "help_com";



	printf("\r\n>>");// command
	for(int i=0; i<8; i++)
	{
		Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *)command, sizeof(command), HAL_MAX_DELAY);
		if(HAL_OK == Hal_Status)
		{
			HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
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

	if(status1 == 0) //Add
	{

	printf("please enter Task Name:");
		for(int i=0; i<8; i++)
		{
				Hal_Status = HAL_UART_Receive( &huart3, (uint8_t *)command_name, 1, HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, (uint8_t *)command_name, 1, 1);
					name[i] = command_name[0];
						if(command_name[0] == '\r' || command_name[0] == '\n')
						{
							printf("\r\n");
							break;
						}
				}
		}
		printf("\r\n");
	printf("please enter Task Prio:");
		for(int i=0; i<2; i++)
		{
				Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command_prio,1, HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, (uint8_t *)command_prio,1, 1);
					prio[i] = command_prio[0];
					if(command_prio[0] == '\r' || command_prio[0] == '\n' )
					{
						printf("\r\n");
						break;
					}
				}
		}
		UBaseType_t prio_number=atoi(prio);
		printf("***%u***",prio_number);
	void vTaskFunction(void *pvParameters)
		{

		for(;;)
			{
			CPU_Load(30, 500);
			osDelay(1);
			}
		}
	xTaskCreate(vTaskFunction, name, 64, ( void * ) 1, tskIDLE_PRIORITY +(unsigned long)prio_number, NULL);
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
	task_status();
	}

	else if(status4 == 0) //Help
	{
		printf("\r\ntask_add --> you can add task by entering prio and name\r\ntask_del --> you can delete task by entering  name\r\nprint_cu --> prints CPU usage\r\nhelp --> you can see the commands\r\n");
	}

	else
	{
	printf(	"\r\nWrong command \r\nPlease try the command below\r\n help_com --> you can see the commands\r\n");
	}

}
