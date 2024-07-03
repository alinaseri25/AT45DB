#include "AT45DB.h"

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

//=======================================

void init_AT45DB(SPI_HandleTypeDef *_spi,GPIO_TypeDef *_GPIOx,uint16_t _GPIO_PIN)
{
	spi_flash = _spi;
	CS_GPIO = _GPIOx;
	CS_GPIO_PIN = _GPIO_PIN;
	
	CS_Set();
	SendCommand[0] = 0x3D;
	SendCommand[1] = 0x2A;
	SendCommand[2] = 0x80;
	SendCommand[3] = 0xA6;
	HAL_SPI_Transmit(spi_flash,SendCommand,4,1);
	CS_Reset();
}

uint8_t* ReadID(void)
{
	CS_Set();
	SendCommand[0] = 0x9F;
	HAL_SPI_Transmit(spi_flash,SendCommand,1,1);
	HAL_SPI_Receive(spi_flash,Data,6,1);
	CS_Reset();
	return Data;
}

void Erase_page(uint32_t address)
{
	uint16_t w1;
	uint16_t w2;
	uint8_t cmd1; 
	uint8_t cmd2;  
	uint8_t cmd3;  
	uint8_t cmd4;  

	w1 = Get_High_Word(address);	
	w2 = Get_Low_Word(address);	

	cmd1 = Get_High_Byte(w1);
	cmd1 = 0x82;
	cmd2 = Get_Low_Byte(w1);
	cmd3 = Get_High_Byte(w2);
	cmd4 = Get_Low_Byte(w2);

	CS_Set();
	SendCommand[0] = cmd1;
	SendCommand[1] = cmd2;
	SendCommand[2] = cmd3;
	SendCommand[3] = cmd4;
	HAL_SPI_Transmit(spi_flash,SendCommand,4,1);
	CS_Reset();
}

void write_45db_Byte(uint32_t address,uint8_t data)
{
	uint16_t w1;
	uint16_t w2;
	uint8_t cmd1; 
  uint8_t cmd2;  
  uint8_t cmd3;  
  uint8_t cmd4;  
	//int i;
		
	w1 = Get_High_Word(address);
	w2 = Get_Low_Word(address);	
				 
	cmd1 = Get_High_Byte(w1);
	cmd1 = 0x82;
	cmd2 = Get_Low_Byte(w1);
	cmd3 = Get_High_Byte(w2);
	cmd4 = Get_Low_Byte(w2);
	
	CS_Set();
	SendCommand[0] = cmd1;
	SendCommand[1] = cmd2;
	SendCommand[2] = cmd3;
	SendCommand[3] = cmd4;
	SendCommand[4] = data;
	HAL_SPI_Transmit(spi_flash,SendCommand,5,1);
	CS_Reset();
}

void write_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len)
{
	//uint8_t byte;
	uint16_t w1;
	uint16_t w2;
	uint8_t cmd1; 
  uint8_t cmd2;  
  uint8_t cmd3;  
  uint8_t cmd4;  
	//int i;
		
	w1 = Get_High_Word(address);
	w2 = Get_Low_Word(address);	
				 
	cmd1 = Get_High_Byte(w1);
	cmd1 = 0x82;
	cmd2 = Get_Low_Byte(w1);
	cmd3 = Get_High_Byte(w2);
	cmd4 = Get_Low_Byte(w2);
	
	CS_Set();
	SendCommand[0] = cmd1;
	SendCommand[1] = cmd2;
	SendCommand[2] = cmd3;
	SendCommand[3] = cmd4;
	HAL_SPI_Transmit(spi_flash,SendCommand,4,1);
	HAL_SPI_Transmit(spi_flash,_data,_Len,10);
	/*for(i=0;i<_Len;i++)
	{
		byte = _data[i];
		HAL_SPI_Transmit(spi_flash,&byte,1,1);
		byte = 0;
		HAL_SPI_Transmit(spi_flash,&byte,1,1);
	}*/
	CS_Reset();
}

uint8_t read_45db_Byte(uint32_t address)
{
	uint8_t data;
	uint16_t w1;
	uint16_t w2;
	//int i;

	uint8_t cmd1; 
  uint8_t cmd2;  
  uint8_t cmd3;  
  uint8_t cmd4;  
	
	w1 = Get_High_Word(address);	
	w2 = Get_Low_Word(address);	
				 
	cmd1 = Get_High_Byte(w1);
	cmd1 = 0x0b;
	cmd2 = Get_Low_Byte(w1);
	cmd3 = Get_High_Byte(w2);
	cmd4 = Get_Low_Byte(w2);

	CS_Set();
	
	SendCommand[0] = cmd1;
	SendCommand[1] = cmd2;
	SendCommand[2] = cmd3;
	SendCommand[3] = cmd4;
	HAL_SPI_Transmit(spi_flash,SendCommand,4,1);
	
	HAL_SPI_Receive(spi_flash,&data,1,1);
	CS_Reset();
	
	return data;
}

void read_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len)
{
	//uint8_t data;
	uint16_t w1;
	uint16_t w2;
	//int i;

	uint8_t cmd1; 
  uint8_t cmd2;  
  uint8_t cmd3;  
  uint8_t cmd4;  
	
	w1 = Get_High_Word(address);	
	w2 = Get_Low_Word(address);	
				 
	cmd1 = Get_High_Byte(w1);
	cmd1 = 0x0b;
	cmd2 = Get_Low_Byte(w1);
	cmd3 = Get_High_Byte(w2);
	cmd4 = Get_Low_Byte(w2);

	CS_Set();
	
	SendCommand[0] = cmd1;
	SendCommand[1] = cmd2;
	SendCommand[2] = cmd3;
	SendCommand[3] = cmd4;
	SendCommand[4] = 0;
	HAL_SPI_Transmit(spi_flash,SendCommand,5,1);
	
	/*for(i=0;i<_Len;i++)
	{
		_data[i] = spi_send(0);
	}*/
	HAL_SPI_Receive(spi_flash,_data,_Len,100);
	
	CS_Reset();
}

//=======================================

uint16_t Get_High_Word(uint32_t data)
{
	uint16_t d;
	d = data >> 16;
	return d;
}

uint16_t Get_Low_Word(uint32_t data)
{
	uint16_t d;
	d = data  & 0x0000ffff;
	return d;
}

uint8_t Get_High_Byte(uint16_t data)
{
	uint8_t d;
	d = data >> 8;
	return d;
}

uint8_t Get_Low_Byte(uint16_t data)
{
	uint8_t d;
	d = data  & 0x00ff;
	return d;
}

void CS_Set(void)
{
	HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_RESET);
}

void CS_Reset(void)
{
	HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_SET);
}

uint8_t spi_send (uint8_t outb) 
{
	uint8_t retdata;
  HAL_SPI_Transmit(spi_flash,&outb,1,1);
  HAL_SPI_Receive(spi_flash,&retdata,1,1);
	return retdata;
}
