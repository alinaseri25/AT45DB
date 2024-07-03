#ifndef __AT45DB_H
#define __AT45DB_H

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


class AT45DB
{
public:
	void AT45DB(SPI_HandleTypeDef *_spi,GPIO_TypeDef *_GPIOx,uint16_t _GPIO_PIN);
	uint8_t* ReadID(void);
	void Erase_page(uint32_t address);
	void write_45db_Byte(uint32_t address,uint8_t data);
	uint8_t read_45db_Byte(uint32_t address);
	void write_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len);
	void read_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len);
private:
	SPI_HandleTypeDef *spi_flash;
	GPIO_TypeDef *CS_GPIO;
	uint16_t CS_GPIO_PIN;
	uint8_t SendCommand[20],Data[512];

	void CS_Set(void);
	void CS_Reset(void);
	uint8_t spi_send (uint8_t outb);
	uint16_t Get_High_Word(uint32_t data);
	uint16_t Get_Low_Word(uint32_t data);
	uint8_t Get_High_Byte(uint16_t data);
	uint8_t Get_Low_Byte(uint16_t data);
};
#endif // __AT45DB_H