#include "main.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"

extern ImuData getImuData();
ImuData imu_data_; //IMU data

//spi3
void StartImuport (void const * argument)
{
	for(;;)
	{
		imu_data_ = getImuData();
		osDelay(1);
	}
}
