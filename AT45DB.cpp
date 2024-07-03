#include "AT45DB.hpp"

void AT45DB::AT45DB(SPI_HandleTypeDef *_spi,GPIO_TypeDef *_GPIOx,uint16_t _GPIO_PIN)
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

uint8_t* AT45DB::ReadID(void)
{
	CS_Set();
	SendCommand[0] = 0x9F;
	HAL_SPI_Transmit(spi_flash,SendCommand,1,1);
	HAL_SPI_Receive(spi_flash,Data,6,1);
	CS_Reset();
	return Data;
}

void AT45DB::Erase_page(uint32_t address)
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

void AT45DB::write_45db_Byte(uint32_t address,uint8_t data)
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
	SendCommand[4] = data;
	HAL_SPI_Transmit(spi_flash,SendCommand,5,1);
	CS_Reset();
}

void AT45DB::write_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len)
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
	HAL_SPI_Transmit(spi_flash,_data,_Len,100);
	CS_Reset();
}

uint8_t AT45DB::read_45db_Byte(uint32_t address)
{
	uint8_t data;
	uint16_t w1;
	uint16_t w2;

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

void AT45DB::read_45db_Array(uint32_t address,uint8_t *_data,uint32_t _Len)
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
	HAL_SPI_Receive(spi_flash,_data,_Len,100);
	
	CS_Reset();
}

//=======================================

uint16_t AT45DB::Get_High_Word(uint32_t data)
{
	uint16_t d;
	d = data >> 16;
	return d;
}

uint16_t AT45DB::Get_Low_Word(uint32_t data)
{
	uint16_t d;
	d = data  & 0x0000ffff;
	return d;
}

uint8_t AT45DB::Get_High_Byte(uint16_t data)
{
	uint8_t d;
	d = data >> 8;
	return d;
}

uint8_t AT45DB::Get_Low_Byte(uint16_t data)
{
	uint8_t d;
	d = data  & 0x00ff;
	return d;
}

void AT45DB::CS_Set(void)
{
	HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_RESET);
}

void AT45DB::CS_Reset(void)
{
	HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_SET);
}

uint8_t AT45DB::spi_send (uint8_t outb) 
{
	uint8_t retdata;
	HAL_SPI_Transmit(spi_flash,&outb,1,1);
	HAL_SPI_Receive(spi_flash,&retdata,1,1);
	return retdata;
}
