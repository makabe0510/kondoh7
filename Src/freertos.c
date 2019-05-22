/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "main.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId idleTaskHandle;
osThreadId LED1TaskHandle;
osThreadId LED2TaskHandle;
osThreadId J1uartportHandle;
osThreadId J2uartportHandle;
osThreadId J3uartportHandle;
osThreadId J4uartportHandle;
osThreadId J5uartportHandle;
osThreadId J6uartportHandle;
osMessageQId J1vectorqueueHandle;
osMessageQId J2vectorqueueHandle;
osMessageQId J3vectorqueueHandle;
osMessageQId J4vectorqueueHandle;
osMessageQId J5vectorqueueHandle;
osMessageQId J6vectorqueueHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartidleTask(void const * argument);
void StartLED1Task(void const * argument);
void StartLED2Task(void const * argument);
void StartJ1uartport(void const * argument);
void StartJ2uartport(void const * argument);
void StartJ3uartport(void const * argument);
void StartJ4uartport(void const * argument);
void StartJ5uartport(void const * argument);
void StartJ6uartport(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of idleTask */
  osThreadDef(idleTask, StartidleTask, osPriorityIdle, 0, 128);
  idleTaskHandle = osThreadCreate(osThread(idleTask), NULL);

  /* definition and creation of LED1Task */
  osThreadDef(LED1Task, StartLED1Task, osPriorityIdle, 0, 128);
  LED1TaskHandle = osThreadCreate(osThread(LED1Task), NULL);

  /* definition and creation of LED2Task */
  //osThreadDef(LED2Task, StartLED2Task, osPriorityIdle, 0, 128);
  //LED2TaskHandle = osThreadCreate(osThread(LED2Task), NULL);

  /* definition and creation of J1uartport */
  osThreadDef(J1uartport, StartJ1uartport, osPriorityLow, 0, 128);
  J1uartportHandle = osThreadCreate(osThread(J1uartport), NULL);

  /* definition and creation of J2uartport */
  //osThreadDef(J2uartport, StartJ2uartport, osPriorityIdle, 0, 128);
  //J2uartportHandle = osThreadCreate(osThread(J2uartport), NULL);

  /* definition and creation of J3uartport */
  //osThreadDef(J3uartport, StartJ3uartport, osPriorityIdle, 0, 128);
  //J3uartportHandle = osThreadCreate(osThread(J3uartport), NULL);

  /* definition and creation of J4uartport */
  //osThreadDef(J4uartport, StartJ4uartport, osPriorityIdle, 0, 128);
  //J4uartportHandle = osThreadCreate(osThread(J4uartport), NULL);

  /* definition and creation of J5uartport */
  //osThreadDef(J5uartport, StartJ5uartport, osPriorityIdle, 0, 128);
  //J5uartportHandle = osThreadCreate(osThread(J5uartport), NULL);

  /* definition and creation of J6uartport */
  //osThreadDef(J6uartport, StartJ6uartport, osPriorityIdle, 0, 128);
  //J6uartportHandle = osThreadCreate(osThread(J6uartport), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of J1vectorqueue */
  osMessageQDef(J1vectorqueue, 1, pvector);
  J1vectorqueueHandle = osMessageCreate(osMessageQ(J1vectorqueue), NULL);

  /* definition and creation of J2vectorqueue */
  //osMessageQDef(J2vectorqueue, 1, pvector);
  //J2vectorqueueHandle = osMessageCreate(osMessageQ(J2vectorqueue), NULL);

  /* definition and creation of J3vectorqueue */
  //osMessageQDef(J3vectorqueue, 1, pvector);
  //J3vectorqueueHandle = osMessageCreate(osMessageQ(J3vectorqueue), NULL);

  /* definition and creation of J4vectorqueue */
  //osMessageQDef(J4vectorqueue, 1, pvector);
  //J4vectorqueueHandle = osMessageCreate(osMessageQ(J4vectorqueue), NULL);

  /* definition and creation of J5vectorqueue */
  //osMessageQDef(J5vectorqueue, 1, pvector);
  //J5vectorqueueHandle = osMessageCreate(osMessageQ(J5vectorqueue), NULL);

  /* definition and creation of J6vectorqueue */
  //osMessageQDef(J6vectorqueue, 1, pvector);
  //J6vectorqueueHandle = osMessageCreate(osMessageQ(J6vectorqueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartidleTask function */
void StartidleTask(void const * argument)
{

  /* USER CODE BEGIN StartidleTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartidleTask */
}

/* StartLED1Task function */
__weak void StartLED1Task(void const * argument)
{
  /* USER CODE BEGIN StartLED1Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLED1Task */
}

/* StartLED2Task function */
__weak void StartLED2Task(void const * argument)
{
  /* USER CODE BEGIN StartLED2Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLED2Task */
}

/* StartJ1uartport function */
__weak void StartJ1uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ1uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ1uartport */
}

/* StartJ2uartport function */
__weak void StartJ2uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ2uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ2uartport */
}

/* StartJ3uartport function */
__weak void StartJ3uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ3uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ3uartport */
}

/* StartJ4uartport function */
__weak void StartJ4uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ4uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ4uartport */
}

/* StartJ5uartport function */
__weak void StartJ5uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ5uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ5uartport */
}

/* StartJ6uartport function */
__weak void StartJ6uartport(void const * argument)
{
  /* USER CODE BEGIN StartJ6uartport */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartJ6uartport */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
