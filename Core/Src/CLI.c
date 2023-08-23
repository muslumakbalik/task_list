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

#include "CPU_load.h"
#include "CPU_usage.h"
#include "stdlib.h"
#include "CLI.h"

#define ESC 27
#define BACKSPACE 32

typedef struct {
	uint32_t BlockRate;
	uint32_t PeriodofTask;
} CPU_Load_args_t;

void vTaskFunction (void *pvParameters)
{
	CPU_Load_args_t *args = (CPU_Load_args_t *)pvParameters;

	if (NULL == args)
	{
		printf("CPU Load parameters are NULL!\r\n");
		return;
	}

	for (;;)
	{
		CPU_Load(args->BlockRate, args->PeriodofTask);
		osDelay(1);
	}
}

void CLI_Command (void)
{
	static CPU_Load_args_t CPU_Load_args;

	char command[1];

	char command_status[32]={0};
	char name[9]={0};
	char prio[3]={0};
	char block_rate[3]={0};
	char period[5]={0};

	HAL_StatusTypeDef Hal_Status;
	int status_add;
	int status_del;
	int	status_print;
	int	status_help;
	TaskHandle_t xHandle;
	name[8]=('\0');
	prio[2]=('\0');
	block_rate[2]=('\0');
	period[4]=('\0');

	printf("\r\n>>");// command
	for (int i=0; i<32; i++)
	{
		Hal_Status = HAL_UART_Receive(&huart3, (uint8_t *)command, 1, HAL_MAX_DELAY);
		if(HAL_OK == Hal_Status)
		{
			HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
			command_status[i] = command[0];
			if (command[0] == '\b')
			{
				if (0 < i)
				{
				printf("%c\b",BACKSPACE);
				command_status[i]=0;
				i=i-2;
				continue;
				}
				else
				{
				break;
				i++;
				}
			}
			if(command[0] == '\r' || command[0] == '\n' )
			{
			command_status[i] = '0';
			break;
			}
		}
	}

	printf("\r\n");
	if (command_status[8] == ('0'))
	{
		status_add = memcmp(command_status, "task add",8);
	}
	else
	{
		status_add = 1;
	}

	if (command_status[8] == ('0'))
	{
		status_del = memcmp(command_status, "task del",8);
	}
	else
	{
		status_del = 1;
	}

	if (command_status[5] == ('0'))
	{
		status_print = memcmp(command_status, "print",5);
	}
	else
	{
		status_print = 1;
	}
	if (command_status[4] == ('0'))
	{
		status_help = memcmp(command_status, "help",4);
	}
	else
	{
		status_help = 1;
	}


	if (status_add == 0) //Add
	{
		printf("you can press 'esc' to exit\r\n");
		printf("please enter Task Name:");
		for (int i=0; i<8; i++)
		{
			Hal_Status = HAL_UART_Receive(&huart3, (uint8_t *)command, 1, HAL_MAX_DELAY);
			if (HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
				name[i] = command[0];
				if (command[0] == ESC)
				{
					break;
				}
				if (command[0] == '\r' || command[0] == '\n')
				{
					printf("\r\n");
					break;
				}
			}
		}

		printf("\r\n");
		printf("please enter Task Prio:");
		for (int i=0; i<2; i++)
		{
			Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command,1, HAL_MAX_DELAY);
			if (HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, (uint8_t *)command,1, 1);
				prio[i] = command[0];
				if (command[0] == ESC)
				{
					break;
				}
				if (command[0] == '\r' || command[0] == '\n' )
				{
					printf("\r\n");
					break;
				}
			}
		}
		TickType_t prio_number = atoi(prio);

		printf("\r\n");
		printf("please enter Task Block Rate:");
		for (int i=0; i<2; i++)
		{
			Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command, 1, HAL_MAX_DELAY);
			if(HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
				block_rate[i] = command[0];
				if(command[0] == ESC)
				{
					break;
				}
				if((command[0] == '\r') || (command[0] == '\n'))
				{
					printf("\r\n");
					break;
				}
			}
		}
		CPU_Load_args.BlockRate = atoi(block_rate);
		printf("\r\n");


		printf("please enter Task Period:");
		for (int i=0; i<4; i++)
		{
			Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command,1, HAL_MAX_DELAY);
			if (HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, (uint8_t *)command,1, 1);
				period[i] = command[0];
				if (command[0] == ESC)
				{
					break;
				}
				if (command[0] == '\r' || command[0] == '\n' )
				{
					printf("\r\n");
					break;
				}
			}
		}
		printf("\r\n");
		CPU_Load_args.PeriodofTask=atoi(period);

		if (ESC != command[0])
		{
			xTaskCreate(vTaskFunction, name, 1024, (void *)&CPU_Load_args, tskIDLE_PRIORITY + (unsigned long)prio_number, &xHandle);
			printf("task created\r\n");
		}
		else
		{
			printf("\r\ntask could not be created\r\n");
		}
	}

	else if (0 == status_del) //Del
	{
	printf("you can press 'esc' to exit\r\n");
	printf("please enter Task Name:");
	for (int i=0; i<8; i++)
	{
	Hal_Status = HAL_UART_Receive( &huart3, (uint8_t *)command, 1, HAL_MAX_DELAY);
		if(HAL_OK == Hal_Status)
		{
		HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
		name[i] = command[0];
			if(command[0] == ESC)
			{
				break;
			}
			if(command[0] == '\r' || command[0] == '\n')
			{
			printf("\r\n");
				break;
			}
		}
	     }
	printf("**%s**",name);
	printf("\r\n");
	xHandle=xTaskGetHandle(name);
		if (xHandle != NULL)
		{
		vTaskDelete(xHandle);
		}
		else
		{
		printf("deletion failed\r\n");
		}
	}

	else if (status_print == 0) //Print CPU_usage
	{
	printf("************************************** \r\n");
	CPU_usage( );
	printf("************************************** \r\n");
	}

	else if (status_help == 0) //Help
	{
		printf("\r\ntask add --> you can add task by entering prio and name\r\ntask del --> you can delete task by entering  name\r\nprint --> prints CPU usage\r\nhelp --> you can see the commands\r\n");
	}

	else
	{
	printf(	"\r\nWrong command \r\nPlease try the command below\r\n help --> you can see the commands\r\n");
	}

}
