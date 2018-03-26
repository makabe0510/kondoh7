
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include "adc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/***************
 * port anglevector holder...
 * every holder need to be initialized...
 * servonum means how man servos are in this port
 * servoIDstart means the start ID....
 */
static pvector portJ1_anglevector = {.servonum=7,.servoIDstart=1};
static pvector portJ2_anglevector = {.servonum=7,.servoIDstart=1};
static pvector portJ3_anglevector = {.servonum=7,.servoIDstart=1};
static pvector portJ4_anglevector = {.servonum=7,.servoIDstart=1};
static pvector portJ5_anglevector = {.servonum=7,.servoIDstart=1};
static pvector portJ6_anglevector = {.servonum=7,.servoIDstart=1};
/***************
 * queues...
 */
extern osMessageQId J1vectorqueueHandle;
extern osMessageQId J2vectorqueueHandle;
extern osMessageQId J3vectorqueueHandle;
extern osMessageQId J4vectorqueueHandle;
extern osMessageQId J5vectorqueueHandle;
extern osMessageQId J6vectorqueueHandle;

/***************
 * receive the angle vector of each port
 */
#define TXHEADER 0xF8
#define UART8BYTES sizeof(pvector)+2
uint8_t rx_buff[UART8BYTES];
uint8_t rx_servo[6];

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	//error...
//	_Error_Handler("isrSensors.c, uart error",53);
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart8.Instance)
	{
		static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if(rx_buff[0]==TXHEADER)
		{
			switch (rx_buff[1])
			{
			case 1:  //port 1
				portJ1_anglevector.servonum = rx_buff[2]==0?portJ1_anglevector.servonum:rx_buff[2];
				portJ1_anglevector.servoIDstart = rx_buff[3]==0?portJ1_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ1_anglevector.servonum;i++)
					portJ1_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J1vectorqueueHandle,&portJ1_anglevector, &xHigherPriorityTaskWoken);
				break;
			case 2:  //port 1
				portJ2_anglevector.servonum = rx_buff[2]==0?portJ2_anglevector.servonum:rx_buff[2];
				portJ2_anglevector.servoIDstart = rx_buff[3]==0?portJ2_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ2_anglevector.servonum;i++)
					portJ2_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J2vectorqueueHandle,&portJ2_anglevector, &xHigherPriorityTaskWoken);
				break;
			case 3:  //port 1
				portJ3_anglevector.servonum = rx_buff[2]==0?portJ3_anglevector.servonum:rx_buff[2];
				portJ3_anglevector.servoIDstart = rx_buff[3]==0?portJ3_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ3_anglevector.servonum;i++)
					portJ3_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J3vectorqueueHandle,&portJ3_anglevector, &xHigherPriorityTaskWoken);
				break;
			case 4:  //port 1
				portJ4_anglevector.servonum = rx_buff[2]==0?portJ4_anglevector.servonum:rx_buff[2];
				portJ4_anglevector.servoIDstart = rx_buff[3]==0?portJ4_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ4_anglevector.servonum;i++)
					portJ4_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J4vectorqueueHandle,&portJ4_anglevector, &xHigherPriorityTaskWoken);
				break;
			case 5:  //port 1
				portJ5_anglevector.servonum = rx_buff[2]==0?portJ5_anglevector.servonum:rx_buff[2];
				portJ5_anglevector.servoIDstart = rx_buff[3]==0?portJ5_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ5_anglevector.servonum;i++)
					portJ5_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J5vectorqueueHandle,&portJ5_anglevector, &xHigherPriorityTaskWoken);
				break;
			case 6:  //port 1
				portJ6_anglevector.servonum = rx_buff[2]==0?portJ6_anglevector.servonum:rx_buff[2];
				portJ6_anglevector.servoIDstart = rx_buff[3]==0?portJ6_anglevector.servoIDstart:rx_buff[3];
				for(uint8_t i = 0;i<portJ6_anglevector.servonum;i++)
					portJ6_anglevector.angle[i] = *(uint16_t *)&rx_buff[4+2*i];
				xQueueOverwriteFromISR(J6vectorqueueHandle,&portJ6_anglevector, &xHigherPriorityTaskWoken);
				break;
			default:
				break;
			}

		}
				//continue IT
		HAL_UART_Receive_IT(&huart8,rx_buff,UART8BYTES);
			//call a context switch if needed..
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}


	//receive from port 2...
	if(huart->Instance==huart7.Instance)
	{
		// static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		if(rx_servo[0]-rx_servo[3] == 0x80) //then data OK...
		{
			uint8_t data[3];
			data[0] = rx_servo[3];
			data[1] = rx_servo[4];
			data[2] = rx_servo[5];
			HAL_UART_Transmit(&huart8,data,2,1);
		}
			//call a context switch if needed..
		// portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
