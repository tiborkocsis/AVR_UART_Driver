/**
  ******************************************************************************
  * @file    avr_hal_uart_api.h
  * @author  Tibor Kocsis
  * @brief   Api Header file of UART module
  ******************************************************************************
  */

#ifndef AVR_HAL_UART_API
#define AVR_HAL_UART_API

/* includes */
#include <stdint.h>

/* Configuration values */
#define HAL_UART_CONFIG_BAUDRATE    9600
#define HAL_UART_CONFIG_PARITY_USED 1
#define HAL_UART_CONFIG_PARITY_ODD  1
#define HAL_UART_CONFIG_RX_BUF_SIZE 16

/* Public types */

/** 
  * @brief  type of UART return values
  */  
typedef enum 
{
  HAL_UART_OK         = 0U,
  HAL_UART_ERROR      = 1U,
  HAL_UART_BUSY       = 2U,
  HAL_UART_NO_RX_CHAR = 3U
} HAL_UART_RetType;


/* Public functions */
HAL_UART_RetType HAL_UART_Init(void);
HAL_UART_RetType HAL_UART_Transmit(uint8_t *pData, uint16_t Size);
HAL_UART_RetType HAL_UART_GetChar(uint8_t *pData);


#endif /* AVR_HAL_UART_API */
