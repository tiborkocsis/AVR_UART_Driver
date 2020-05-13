/**
  ******************************************************************************
  * @file    avr_hal_uart.h
  * @author  Tibor Kocsis
  * @brief   Header file of UART module
  ******************************************************************************
  */

#ifndef AVR_HAL_UART
#define AVR_HAL_UART

/* includes */
#include <stdint.h>
#include "avr_hal_uart_api.h"

/** 
  * @brief  type of UART structure
  */  
typedef struct
{
  uint8_t  Initialized;
  uint8_t  TxInProgress;
  uint8_t  *pTxBuffer;
  uint16_t TxCounter;
  uint8_t  RxBuffer[HAL_UART_CONFIG_RX_BUF_SIZE];
  uint16_t RxBufIdxHead;
  uint16_t RxBufIdxTail;
  uint8_t  RxOverFlow;
  uint8_t  RxParityError;
} HAL_UART_Type;

/* Hardware layer functions */
void HAL_UART_Config_Hw(void);
void HAL_UART_Put_TxChar(uint8_t Char);
uint8_t HAL_UART_Get_RxChar(void);
void HAL_UART_Put_TxParity(uint8_t Parity);
uint8_t HAL_UART_Get_RxParity(void);

/* Interrupt service routines */
void HAL_UART_Tx_ISR(void);
void HAL_UART_TxComplete_ISR(void);
void HAL_UART_Rx_ISR(void);

uint8_t HAL_UART_CalcParity(uint8_t Char);

#endif /* AVR_HAL_UART */
