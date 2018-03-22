
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
#include "gpio.h"

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* StartLED1Task function */
void StartLED1Task(void const * argument)
{

  /* USER CODE BEGIN StartLED1Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
	  osDelay(300);
  }
  /* USER CODE END StartLED1Task */
}

/* StartLED2Task function */
void StartLED2Task(void const * argument)
{
  /* USER CODE BEGIN StartLED2Task */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	  osDelay(600);
  }
  /* USER CODE END StartLED2Task */
}
