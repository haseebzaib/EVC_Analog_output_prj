/*
 * sio.h
 *
 *  Created on: Jun 10, 2024
 *      Author: user
 */

#ifndef SIO_SIO_H_
#define SIO_SIO_H_

#include "main.h"
#include "usart.h"

extern __IO uint8_t uart_event;
#define sio_UartEvent_Nequal uart_event != 1
#define sio_resUartEvent()  uart_event = 0
#define sio_setUartEvent()  uart_event = 1




extern void sio_check_UartEvent(uint32_t time_ms);

//#define tx_buf 500
//#define rx_buf 500

/*** ASCII-Codes ***/
#define _LF  0x0A
#define _SOH 0x01

struct SioStruct {

	uint8_t *rx;  //received interrupt message
	uint8_t *tx;   //transmit interrupt message
	uint32_t txSize; //size of transmit data
    uint8_t Echar; //end character to end the transmition
    uint8_t Echar_rx; //received character to compare with Echar
};

extern uint8_t S0TxBuf[];
extern uint8_t S0RxBuf[];

#define Analog_O_Uart huart1

extern __IO struct SioStruct uart_control_block;


extern void sio_task();
extern void sio_init();

#endif /* SIO_SIO_H_ */
