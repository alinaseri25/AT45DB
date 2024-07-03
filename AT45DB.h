#include "stm32f4xx_hal.h"
//#include "cmsis_os.h"

void init_AT45DB(SPI_HandleTypeDef *_spi,GPIO_TypeDef *_GPIOx,uint16_t _GPIO_PIN);
uint8_t* ReadID(void);
void Erase_page(uint32_t address);
void write_45db_Byte(uint32_t address,uint8_t data);
uint8_t read_45db_Byte(uint32_t address);
void write_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len);
void read_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len);
