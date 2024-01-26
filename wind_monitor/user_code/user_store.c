#include "user_sampling.h"
#include "sys.h"
#include "os.h"

#include "user_store.h"

#include "led.h"
#include "adc.h"
#include "usart.h"
#include "exti.h"
#include "flash.h"

//flash存储方式：0：数据首页位置，256：数据缓冲开始
static uint8_t data_buf_temp[300];//100组数据缓冲区


uint8_t * store_init(uint8_t *p_index, uint8_t *p_num)
{
	uint8_t buf[2] = {0};
	SPI_Flash_Read(buf,256,4);
	SPI_Flash_Read(data_buf_temp,512,300);
	
	*p_index = buf[0];
    *p_num   = buf[1];
	
	return data_buf_temp;
}

void store(uint8_t index, uint8_t num)
{
	uint8_t buf[2] = {0};
	
	buf[0] = index;
	buf[1] = num;
	
	SPI_Flash_Write(buf,256,4);
	SPI_Flash_Write(data_buf_temp,512,256);
	SPI_Flash_Write(&(data_buf_temp[256]),768,300-256);
}
