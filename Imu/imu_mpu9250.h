#ifndef IMU_MPU9250_H_
#define IMU_MPU9250_H_

#ifndef __cplusplus
#error "Please define __cplusplus, because this is a c++ based file "
#endif

#include "stm32h7xx_hal.h"
#include <array>
#include <stdint.h>
#include <main.h>

using Vector3d = std::array<int16_t, 3>;

#define SPI_POLLING_MODE 0
#define SPI_DMA_MODE 1
#define SPI_MODE SPI_POLLING_MODE
#define SENSOR_DATA_LENGTH 7

#define IMU_SPI_CS_H      HAL_GPIO_WritePin(IMUCS_GPIO_Port, IMUCS_Pin, GPIO_PIN_SET)
#define IMU_SPI_CS_L      HAL_GPIO_WritePin(IMUCS_GPIO_Port, IMUCS_Pin, GPIO_PIN_RESET)

/* magenetometer update at about 100Hz, but the entire sensor data polling process is at 1KHz, should add prescaler for mag */
#define MAG_PRESCALER 4
/* magnetometer has bad noise bacause of the polling process, I think. So, we use a threshold filter method to remove the outlier */

class Imu {
public:

	Imu(){}
	~Imu(){}
	void init(SPI_HandleTypeDef* hspi);

	static const uint8_t GYRO_DLPF_CFG = 0x01;//0x04 //0: 250Hz, 0.97ms; 3: 41Hz, 5.9ms(kduino); 4: 20Hz: 9.9ms
	static const uint8_t ACC_DLPF_CFG = 0x03; //0x03: 41Hz, 11.80ms
	static const uint8_t MAG_ADDRESS = 0x0C;
	static const uint8_t MAG_DATA_REGISTER = 0x03;

	static const uint8_t GYRO_ADDRESS =  0x43;
	static const uint8_t ACC_ADDRESS =  0x3B;
	static const uint8_t MAG_SPI_ADDRESS = 0x49;

	static uint8_t adc_[SENSOR_DATA_LENGTH];

	void update();
	bool getUpdate() { return update_; }
	void setUpdate(bool update) { update_ = update; }
	Vector3d  getAcc(){return acc_;}
	Vector3d  getGyro(){return gyro_;}
	Vector3d  getMag(){return mag_;}

	ImuData getData()
	{
		ImuData data;
		data.acc[0] = getAcc()[0];
		data.acc[1] = getAcc()[1];
		data.acc[2] = getAcc()[2];
		data.gyro[0] = getGyro()[0];
		data.gyro[1] = getGyro()[1];
		data.gyro[2] = getGyro()[2];
		data.mag[0] = getMag()[0];
		data.mag[1] = getMag()[1];
		data.mag[2] = getMag()[2];
		return data;
	}

private:

	SPI_HandleTypeDef* hspi_;
	Vector3d acc_, gyro_, mag_;
	uint8_t dummy_[SENSOR_DATA_LENGTH];
	bool update_;

	void gyroInit(void);
	void accInit(void);
	void magInit(void);
	void pollingRead (void);
	void process (void);
	void mpuWrite(uint8_t address, uint8_t value);
	uint8_t mpuRead(uint8_t address);
};

#endif
