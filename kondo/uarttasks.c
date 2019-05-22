
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include "adc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/***************
 * queues...
 */
extern osMessageQId J1vectorqueueHandle;
extern osMessageQId J2vectorqueueHandle;
extern osMessageQId J3vectorqueueHandle;
extern osMessageQId J4vectorqueueHandle;
extern osMessageQId J5vectorqueueHandle;
extern osMessageQId J6vectorqueueHandle;

//Delay function
uint32_t getUs(void) {
	uint32_t usTicks = HAL_RCC_GetSysClockFreq() / 1000000;
	register uint32_t ms, cycle_cnt;
	do {
		ms = HAL_GetTick();
		cycle_cnt = SysTick->VAL;
	} while (ms != HAL_GetTick());
	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void delayUs(uint16_t micros) {
	uint32_t start = getUs();
	while (getUs()-start < (uint32_t) micros) {
		asm("nop");
	}
}

uint8_t rx_servo[6];

/* StartJ1uartport function */
//uart2
void StartJ1uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	//the val center is 7500, but when send command..
	//should divide them to two 7 bits byte
	//that is lowbyte = val&0x007f, highbyte = val&0x3f80 >> 7
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J1vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			//HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			uint8_t datatosend[3];
			//while(motornum < 1)
			//{
				//if(motornum>=anglevector.servonum)
				//{
				//	motornum = 0;
				//	break;
				//}
				//every 1 mini second control one motor...
				//datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
			    datatosend[0] = 0x80 + 10;
				//datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
				//datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				int test_angle = 1000;
				//for(uint8_t i = 0 ; i < 1; i++){
					datatosend[1] = (uint8_t)(((test_angle + 0 * 200)&0x3f80) >> 7);//high byte
					datatosend[2] = (uint8_t)((test_angle + 0 * 200)&0x007f);//low byte
					//motornum++;
				//now send to data
					HAL_UART_Transmit(&huart2,datatosend,3,1);
				//HAL_UART_Receive_IT(&huart2,rx_servo,6);
				//delayUs(100);
					osDelay(100);
				//}

			//}
		//}
		//else osDelay(100);
	}

}

/* StartJ2uartport function */
//uart7
void StartJ2uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J2vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			uint8_t datatosend[3];
			while(motornum < 1)
			{
				if(motornum>=anglevector.servonum)
				{
					motornum = 0;
					break;
				}
				//every 1 mini second control one motor...
				datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
//				datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
//				datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				uint8_t test_angle = 7500;
				datatosend[1] = (uint8_t)((test_angle&0x3f80) >> 7);//high byte
				datatosend[2] = (uint8_t)(test_angle&0x007f);//low byte
				motornum++;
				//now send to data
				HAL_UART_Transmit(&huart7,datatosend,3,1);
				//delayUs(100);
				osDelay(100);
			}
		//}
		//else
		//	osDelay(1);
	}
}

/* StartJ3uartport function */
//uart5
void StartJ3uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J3vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			uint8_t datatosend[3];
			while(motornum < 1)
			{
				if(motornum>=anglevector.servonum)
				{
					motornum = 0;
					break;
				}
				//every 1 mini second control one motor...
				datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
		//		datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
			//	datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				uint8_t test_angle = 7500;
				datatosend[1] = (uint8_t)((test_angle&0x3f80) >> 7);//high byte
				datatosend[2] = (uint8_t)(test_angle&0x007f);//low byte

				motornum++;
				//now send to data
				HAL_UART_Transmit(&huart5,datatosend,3,1);
				//delayUs(100);
				osDelay(100);
			}
		//}
		//else
		//	osDelay(1);
	}
}

/* StartJ4uartport function */
//uart4
void StartJ4uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J4vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			uint8_t datatosend[3];
			while(motornum < 1)
			{
				if(motornum>=anglevector.servonum)
				{
					motornum = 0;
					break;
				}
				//every 1 mini second control one motor...
				datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
				//datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
				//datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				uint8_t test_angle = 7500;
				datatosend[1] = (uint8_t)((test_angle&0x3f80) >> 7);//high byte
				datatosend[2] = (uint8_t)(test_angle&0x007f);//low byte
				motornum++;
				//now send to data
				HAL_UART_Transmit(&huart4,datatosend,3,1);
				//delayUs(100);
				osDelay(100);
			}
		//}
		//else
		//	osDelay(1);
	}
}

/* StartJ5uartport function */
//uart3
void StartJ5uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J5vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			uint8_t datatosend[3];
			while(motornum < 1)
			{
				if(motornum>=anglevector.servonum)
				{
					motornum = 0;
					break;
				}
				//every 1 mini second control one motor...
				datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
				//datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
				//datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				uint8_t test_angle = 7500;
				datatosend[1] = (uint8_t)((test_angle&0x3f80) >> 7);//high byte
				datatosend[2] = (uint8_t)(test_angle&0x007f);//low byte
				motornum++;
				//now send to data
				HAL_UART_Transmit(&huart3,datatosend,3,1);
				//delayUs(100);
				osDelay(100);
			}
		//}
		//else
		//	osDelay(1);
	}

}

/* StartJ6uartport function */
//uart1
void StartJ6uartport(void const * argument)
{
	pvector anglevector;
	uint8_t motornum = 0;
	for(;;)
	{
		//wait for the vector data..
		//if(xQueuePeek(J6vectorqueueHandle,&anglevector,0)==pdPASS)
		//{
			uint8_t datatosend[3];
			while(motornum < 1)
			{
				if(motornum>=anglevector.servonum)
				{
					motornum = 0;
					break;
				}
				//every 1 mini second control one motor...
				datatosend[0] = 0x80 + motornum + anglevector.servoIDstart;
				//datatosend[1] = (uint8_t)((anglevector.angle[motornum]&0x3f80) >> 7);//high byte
				//datatosend[2] = (uint8_t)(anglevector.angle[motornum]&0x007f);//low byte
				uint8_t test_angle = 7500;
				datatosend[1] = (uint8_t)((test_angle&0x3f80) >> 7);//high byte
				datatosend[2] = (uint8_t)(test_angle&0x007f);//low byte
				motornum++;
				//now send to data
				HAL_UART_Transmit(&huart1,datatosend,3,1);
				//delayUs(100);
				osDelay(100);
			}
		//}
		//else
		//	osDelay(1);
	}

}
