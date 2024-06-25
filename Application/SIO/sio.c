/*
 * sio.c
 *
 *  Created on: Jun 10, 2024
 *      Author: user
 */

#include "main.h"
#include "sio.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"

GLOBAL __IO uint8_t uart_event = 0;
LOCAL uint32_t prev_time = 0;






/*
 *Checks for uart event for set time
 *time is in ms
 */
GLOBAL void sio_check_UartEvent(uint32_t time_ms)
{

	switch(time_ms)
	{

	case 0:
	{
		 while(sio_UartEvent_Nequal)  //just wait for event dont perform anything else
		 {

		 }
			 break;
	}

	default:
	 {
		 prev_time = HAL_GetTick(); //we get new time before going into while
		 while(sio_UartEvent_Nequal && (HAL_GetTick() - prev_time < time_ms)); //wait here until get event or time passes
	     break;
	 }


	}

}











/*Variables*/
LOCAL uint8_t *pRx; //Pointer to examine RX buffer
GLOBAL uint8_t S0TxBuf[25]; /* Send buffer to EVC*/
GLOBAL uint8_t S0RxBuf[25]; /* Receieve buffer from EVC */
uint8_t opRq_buf[] = "senddata";







__IO struct SioStruct uart_control_block;

/*Function Prototypes*/
LOCAL void sio_RxIntS0(UART_HandleTypeDef *huart);
//LOCAL void sio_TxIntS0 (UART_HandleTypeDef *huart);
LOCAL void sio_RxBlockStart();
LOCAL void sio_TxBlockStart(char *buf);

LOCAL uint16_t sio_uart_rxRec(UART_HandleTypeDef *huart) {
	uint16_t uhErr = (uint16_t) huart->ErrorCode;
	uint16_t uhData;

	if (huart->RxState == HAL_UART_STATE_BUSY_RX) {
		/* uhdata = (uint16_t) READ_REG(huart->Instance->RDR);
		 if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
		 {
		 tmp = (uint16_t*) huart->pRxBuffPtr ;
		 *tmp = (uint16_t)(uhdata & uhMask);
		 // huart->pRxBuffPtr +=2;
		 }
		 else
		 {
		 // *huart->pRxBuffPtr++ = (uint8_t)(uhdata & (uint8_t)uhMask);
		 *huart->pRxBuffPtr = (uint8_t)(uhdata & (uint8_t)uhMask);
		 }*/
		uhData = ((uint16_t) READ_REG(huart->Instance->RDR)) & huart->Mask;

		if (uhErr != HAL_UART_ERROR_NONE)
			uhData |= (uhErr << 8);

		return (uhData);	// HAL_OK
	} else {
		/* Clear RXNE interrupt flag */
		__HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);

		return (0);	// HAL_BUSY
	}
}






/*
 * Create Receiving block for uart communication
 */
LOCAL void sio_RxBlockStart() {
	sio_resUartEvent();
	memset(S0RxBuf, 0, sizeof(S0RxBuf));

	uart_control_block.rx = S0RxBuf;
	uart_control_block.Echar = _LF;

	HAL_UART_Receive_IT(&Analog_O_Uart, uart_control_block.rx, 1);

	Analog_O_Uart.RxISR = &sio_RxIntS0;

}

/*
 * Create transmittion  block for uart communication
 */
LOCAL void sio_TxBlockStart(char *buf) {
	sio_resUartEvent();
	memset(S0TxBuf, 0, sizeof(S0TxBuf));

	sprintf((char*) S0TxBuf, "%s", buf);

	uart_control_block.tx = S0TxBuf;
	uart_control_block.txSize = strlen((const char*) S0TxBuf);

	HAL_UART_Transmit_IT(&Analog_O_Uart, uart_control_block.tx,
			uart_control_block.txSize);

}











/*
 * Opening request prompt from EVC
 * we make request buffer here
 */
LOCAL void sio_opRq() {
	if (*pRx++ != '?')		// after / must ? come
			{
		return;
	}

//	if (memcmp(pRx, opRq_buf, strlen((const char*) opRq_buf)) == 0) {
//
//		for (int i = 0; i < ANALOG_INP; i++) {
//
//			//for (int j = 0; j < 2; j++) {
//				Err = ani_Mess(i, &ad_val[i]);
//
//				if (Err) {
//					sprintf((char*) ad_buf[i], "%s", "ERR"); //error
//				} else {
////				int integerPart = (int)ad_val[i];
////				int decimalPart = ((int)(ad_val[i]*N_DECIMAL_POINTS_PRECISION)%N_DECIMAL_POINTS_PRECISION);
////				sprintf((char *)ad_buf[i], "%d.%04d",integerPart,decimalPart);//cant use float due to memory constrains
//					sprintf((char*) ad_buf[i], "%.5f", ad_val[i]);
//					//floatToString(ad_val[i],(char *)ad_buf[i],25,6);
//				}
//
//			//}
//
//		}
//
//		sprintf(Tx_buffer, "\x01IN1:%s,IN2:%s,IN3:%s,IN4:%s!\x0A",
//				(char*) ad_buf[0], (char*) ad_buf[1], (char*) ad_buf[2],
//				(char*) ad_buf[3]);
//
//		sio_TxBlockStart(Tx_buffer);
//		util_check_UartEvent(2000);
//
//	} else {
//		return;
//	}

}





/*
 * Main task for handling all the communication related to uart
 */
GLOBAL void sio_task() {
	sio_init();
	sio_RxBlockStart();
	sio_check_UartEvent(15000);   //we wait here until we receive something
//	sio_TxBlockStart((char *)S0RxBuf);
//	util_check_UartEvent(2000);

	pRx = S0RxBuf;

	switch (*pRx++) //for future more cases can be added if needed
	{
	case '/': //opening request
	{
		sio_opRq();
		break;
	}
	default: {
		HAL_UART_DeInit(&Analog_O_Uart);
		MX_USART1_UART_Init();
		break;
	}
	}

}



/*Initializes Uart interfaces
 *Also sets interrupt callback handler
 */
GLOBAL void sio_init() {

	memset((void*) &uart_control_block, 0, sizeof(uart_control_block)); // reset control block

}



/***Interrupt Routines****/

/*
 * Interrupt handling for Received Data
 */
LOCAL void sio_RxIntS0(UART_HandleTypeDef *huart) {

	//  HAL_UART_Receive_IT(&Analog_I_Uart,   uart_control_block.rx, 1); //we enable it again to reive another interrupt
	uart_control_block.Echar_rx = (uint8_t) sio_uart_rxRec(huart);
	*uart_control_block.rx++ = (uint8_t) sio_uart_rxRec(huart);

	if (uart_control_block.Echar == uart_control_block.Echar_rx) //we received end char so string is finish
			{
		huart->RxISR = NULL;
		sio_setUartEvent();
	}

}

/*
 * Interrupt handling for sent Data
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	sio_setUartEvent();
}
