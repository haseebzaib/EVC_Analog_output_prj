/*
 * app_main.h
 *
 *  Created on: Jun 10, 2024
 *      Author: user
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "main.h"

struct dac161s997_dev_t {
	SPI_HandleTypeDef *hspi;
	GPIO_TypeDef  *cs_port;
	uint32_t cs_num;
};



extern void app_main();

#endif /* APP_MAIN_H_ */
