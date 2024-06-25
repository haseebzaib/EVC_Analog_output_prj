/*
 * app_main.c
 *
 *  Created on: Jun 10, 2024
 *      Author: user
 */


#include "app_main.h"
#include "spi.h"
#include "sio.h"
#include "main.h"
#include "dac161s997.h"


/*time for byte complete in millisecond*/
#define byte_cmplt_time_ms 300
/*data complete time in millisecond*/
#define data_cmplt_time_ms 500


uint32_t status = 0;
uint8_t end;
int32_t start_time;
int32_t end_time;
int32_t pulse_time;
uint8_t i =0;
uint8_t data_rcv = 0;
union  bit8_to_bit32
{
       uint32_t L;
       uint8_t B[4];
};


union bit8_to_bit32 conv;

dac161s997_dev_t dac_dev =
{

.hspi    = &hspi1,
.cs_port = CS__GPIO_Port,
.cs_num  = CS__Pin

};

int dac161s997_spi_xfer(dac161s997_dev_t *dev, uint8_t *tx_buf,
		uint8_t *rx_buf, size_t size) {
	int err = 0;
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_num, GPIO_PIN_RESET);
    err = HAL_SPI_TransmitReceive(dev->hspi, tx_buf, rx_buf, size, 5000);
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_num, GPIO_PIN_SET);

    return err;
}


void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	data_rcv = 1;
	start_time = HAL_GetTick();

}


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{

	if(data_rcv)
	{
		data_rcv = 0;
		end_time = HAL_GetTick();
		pulse_time = end_time - start_time;
		if(pulse_time >= byte_cmplt_time_ms && pulse_time < data_cmplt_time_ms)
		{
			i++;
			pulse_time = 0;
			//i = i%4;
		}
		else if(pulse_time >= data_cmplt_time_ms)
		{
			end = 1;
			pulse_time = 0;

		}
		else
		{
			conv.B[i] = pulse_time;
		}
	}
}

void app_main()
{

	dac161s997_init(&dac_dev);
    dac161s997_set_output(&dac_dev, 4000000);
	dac161s997_get_status(&dac_dev, &status);
	while(1)
	{
		if(end)
		{
			end = 0;
			i=0;
		    dac161s997_set_output(&dac_dev, (int32_t)conv.L);
			conv.L = 0;
		}
		dac161s997_get_status(&dac_dev, &status);
		HAL_Delay(400);
	}
}
