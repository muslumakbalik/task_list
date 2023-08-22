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
#include "stdlib.h"

void CLI_Command(void );


void CLI_Command( void)
{

	char command[1];
	char command_name[1];
	char command_prio[1];
	char command_block_rate[1];
	char command_period[1];

	char command_status[32]={0};
	char name[8]={0};
	char prio[2]={0};
	char block_rate[2]={0};
	char period[5]={0};
	char space = 32;

	HAL_StatusTypeDef Hal_Status;
	int status1,status2,status3,status4;


	printf("\r\n>>");// command
	for(int i=0; i<32; i++)
	{
		Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *)command, 1, HAL_MAX_DELAY);
		if(HAL_OK == Hal_Status)
		{
			HAL_UART_Transmit(&huart3, (uint8_t *)command, 1, 1);
			command_status[i] = command[0];
			if(command[0] == '\b')
			{
			printf("%c\b",space);
			command_status[i]=0;
			i=i-2;
			continue;
			}
			if(command[0] == '\r' || command[0] == '\n' )
			{
			command_status[i] = '0';
			break;
			}
		}
	}
	printf("\r\n");
	if(command_status[8] == ('0'))
	{
		status1 = memcmp(command_status, "task add",8);
	}
	else
	{
		status1 = 1;
	}

	if(command_status[8] == ('0'))
	{
	status2 = memcmp(command_status, "task dell",8);
	}
	else
	{
	status2 = 1;
	}

	if(command_status[5] == ('0'))
	{
	status3 = memcmp(command_status, "print",5);
	}
	else
	{
	status3 = 1;
	}
	if(command_status[4] == ('0'))
	{
	status4 = memcmp(command_status, "help",4);
	}
	else
	{
	status4 = 1;
	}


	TaskHandle_t xHandle;
	if(status1 == 0) //Add
	{
	printf("you can press 'q' to exit\r\n");
	printf("please enter Task Name:");
		for(int i=0; i<8; i++)
		{
				Hal_Status = HAL_UART_Receive( &huart3, (uint8_t *)command_name, 1, HAL_MAX_DELAY);
				if(HAL_OK == Hal_Status)
				{
					HAL_UART_Transmit(&huart3, (uint8_t *)command_name, 1, 1);
					name[i] = command_name[0];
						if(command_name[0] == 27)
						{
						break;
						}
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
					if(command_prio[0] == 27)
					{
					break;
					}
					if(command_prio[0] == '\r' || command_prio[0] == '\n' )
					{
						printf("\r\n");
						break;
					}
				}
		}
	 prio[2]=('\0');
	 UBaseType_t prio_number=atoi(prio);

	 printf("\r\n");
	 printf("please enter Task Block Rate:");
	 		for(int i=0; i<2; i++)
	 		{
	 				Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command_block_rate,1, HAL_MAX_DELAY);
	 				if(HAL_OK == Hal_Status)
	 				{
	 					HAL_UART_Transmit(&huart3, (uint8_t *)command_block_rate,1, 1);
	 					block_rate[i] = command_block_rate[0];
	 					if(command_block_rate[0] == 27)
	 					{
	 					break;
	 					}
	 					if(command_block_rate[0] == '\r' || command_block_rate[0] == '\n' )
	 					{
	 						printf("\r\n");
	 						break;
	 					}
	 				}
	 		}
	 block_rate[2]=('\0');
	 TickType_t BlockRate=atoi(block_rate);
	 printf("\r\n");
	 printf("***%lu***\r\n",BlockRate);

	 printf("please enter Task Period:");
	 		 for(int i=0; i<4; i++)
	 		 {
	 		 		Hal_Status = HAL_UART_Receive( &huart3,(uint8_t *) command_period,1, HAL_MAX_DELAY);
	 		 		if(HAL_OK == Hal_Status)
	 		 		{
	 		 			HAL_UART_Transmit(&huart3, (uint8_t *)command_period,1, 1);
	 		 			period[i] = command_period[0];
	 		 			if(command_period[0] == 27)
	 		 			{
	 		 			break;
	 		 			}
	 		 			if(command_period[0] == '\r' || command_period[0] == '\n' )
	 		 			{
	 		 				printf("\r\n");
	 		 				break;
	 		 			}
	 		 		}
	 		 }
	 printf("\r\n");
	 period[4]=('\0');
	 TickType_t PeriodofTask=atoi(period);
	 printf("***%lu***\r\n",PeriodofTask);

		if(command_name[0] != 27 && command_prio[0] != 27)
		{
		void vTaskFunction(void *pvParameters)
			{
			for(;;)
				{
				 CPU_Load(BlockRate, PeriodofTask);
				 osDelay(1);
				}
			}
		xTaskCreate(vTaskFunction, name, 64, ( void * ) 1, tskIDLE_PRIORITY +(unsigned long)prio_number,&xHandle);
		printf("task created\r\n");
		}
		else
		{
			printf("\r\ntask could not be created\r\n");
		}
	}

	else if(status2 == 0) //Del
	{
		printf("please enter Task Name:");
		for(int i=0; i<8; i++)
		{
			Hal_Status = HAL_UART_Receive( &huart3, (uint8_t *)command_name, 1, HAL_MAX_DELAY);
			if(HAL_OK == Hal_Status)
			{
				HAL_UART_Transmit(&huart3, (uint8_t *)command_name, 1, 1);
				name[i] = command_name[0];
					if(command_name[0] == 'q')
					{
					break;
					}
					if(command_name[0] == '\r' || command_name[0] == '\n')
					{
						printf("\r\n");
						break;
					}
			}
	     }
	printf("\r\n");
	xHandle=xTaskGetHandle(name);
		if(xHandle != NULL)
		{
			vTaskDelete(xHandle);
		}
		else
		{
			printf("deletion failed\r\n");
		}
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
		printf("\r\ntask add --> you can add task by entering prio and name\r\ntask del --> you can delete task by entering  name\r\nprint --> prints CPU usage\r\nhelp --> you can see the commands\r\n");
	}

	else
	{
	printf(	"\r\nWrong command \r\nPlease try the command below\r\n help --> you can see the commands\r\n");
	}

}
