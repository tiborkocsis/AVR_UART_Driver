/**
  ******************************************************************************
  * @file    avr_hal_uart.c
  * @author  Tibor Kocsis
  * @brief   UART driver module
  ******************************************************************************
  */

#include <stdio.h>
#include "avr_hal_uart.h"

/* Module variables */
HAL_UART_Type uart;


/**
  * @brief Initialize the UART module according to the specified
  *        parameters in file avr_hal_uart_api.h.
  * @retval HAL_UART_RetType
  */
HAL_UART_RetType HAL_UART_Init(void)
{
  if(uart.Initialized)
  {
    return HAL_UART_ERROR;
  }
  
  /* Initialize Tx status variables */
  uart.TxInProgress = 0;
  uart.pTxBuffer    = NULL;
  uart.TxCounter    = 0;
  
  /* Initialize Rx status variables */
  uart.RxBufIdxHead  = 0;
  uart.RxBufIdxTail  = 0;
  uart.RxOverFlow    = 0;
  uart.RxParityError = 0;

  /* Initialize UART hardware registers */
  HAL_UART_Config_Hw();
  
  uart.Initialized  = 1;
  
  return HAL_UART_OK;
}


/**
  * @brief Send an amount of data.
  * @param pData Pointer to data buffer.
  * @param Size  Number of bytes to be sent.
  * @retval HAL_UART_RetType
  */
HAL_UART_RetType HAL_UART_Transmit(uint8_t *pData, uint16_t Size)
{
  /* Check Initialized and parameters */
  if(!uart.Initialized || pData == NULL || Size == 0)
  {
    return HAL_UART_ERROR;
  }
  
  /* Check Tx status */
  if(uart.TxInProgress)
  {
    return HAL_UART_BUSY;
  }
  
  uart.pTxBuffer = pData + 1;
  uart.TxCounter = Size - 1;
  uart.TxInProgress = 1;
  HAL_UART_Put_TxChar(*pData);
  
  return HAL_UART_OK;
}


/**
  * @brief ISR routine of UART Data Register Empty.
  * @retval None
  */
void HAL_UART_Tx_ISR(void)
{
  if(uart.TxCounter)
  {
#if HAL_UART_CONFIG_PARITY_USED
    HAL_UART_Put_TxParity(HAL_UART_CalcParity(*(uart.pTxBuffer)));
#endif
    HAL_UART_Put_TxChar(*(uart.pTxBuffer));
    uart.pTxBuffer++;
    uart.TxCounter--;
  }
}


/**
  * @brief ISR routine of UART TX Complete.
  * @retval None
  */
void HAL_UART_TxComplete_ISR(void)
{
  if(uart.TxCounter == 0)
  {
    uart.TxInProgress = 0;
  }
}


/**
  * @brief ISR routine of UART Receive Complete.
  * @retval None
  */
void HAL_UART_Rx_ISR(void)
{
  uint8_t RxChar;
  
  if(uart.Initialized)
  {
    if((uint16_t)(uart.RxBufIdxHead - uart.RxBufIdxTail) < HAL_UART_CONFIG_RX_BUF_SIZE)
    {
      RxChar = HAL_UART_Get_RxChar();
#if HAL_UART_CONFIG_PARITY_USED
      if(HAL_UART_CalcParity(RxChar) == HAL_UART_Get_RxParity())
#endif
      {
        uart.RxBuffer[uart.RxBufIdxHead & (HAL_UART_CONFIG_RX_BUF_SIZE - 1)] = RxChar;
        uart.RxBufIdxHead++;
      }
    }
    else
    {
      uart.RxOverFlow = 1;
    }
  }
}


/**
  * @brief Get a character from Rx buffer if there is any.
  * @param pData Pointer where to put the character.
  * @retval HAL_UART_RetType
  */
HAL_UART_RetType HAL_UART_GetChar(uint8_t *pData)
{
  /* Check Initialized and parameter */
  if(!uart.Initialized || pData == NULL)
  {
    return HAL_UART_ERROR;
  }
  
  if((uint16_t)(uart.RxBufIdxHead - uart.RxBufIdxTail) > 0)
  {
    *pData = uart.RxBuffer[uart.RxBufIdxTail & (HAL_UART_CONFIG_RX_BUF_SIZE - 1)];
    uart.RxBufIdxTail++;
    return HAL_UART_OK;
  }
  else
  {
    return HAL_UART_NO_RX_CHAR;
  }
}


/**
  * @brief Calculate even or odd parity bit.
  * @param pData Pointer where to put the character.
  * @retval parity (BIT0)
  */
uint8_t HAL_UART_CalcParity(uint8_t Char)
{
  uint8_t RetVal = 0;
  uint8_t i;
  
  for(i = 1; i < 8; i++)
  {
    if(Char & 1)
    {
      RetVal++;
    }
    Char >>= 1;
  }
#if HAL_UART_CONFIG_PARITY_ODD
  RetVal = ~RetVal;
#endif
  
  return RetVal & 1;
}


/**
  * @brief Initialize the MCU UART module
  * @retval None
  */
void HAL_UART_Config_Hw(void)
{
  // TODO
}


/**
  * @brief Put a char into UART Tx module
  * @param Char Data byte to be transmitted.
  * @retval None
  */
void HAL_UART_Put_TxChar(uint8_t Char)
{
  // TODO
}


/**
  * @brief Get a char from UART Rx module
  * @retval Received character
  */
uint8_t HAL_UART_Get_RxChar(void)
{
  // TODO
  return 0;
}


/**
  * @brief Put parity bit into UART Tx module
  * @param Parity Parity bit (BIT0) to be transmitted.
  * @retval None
  */
void HAL_UART_Put_TxParity(uint8_t Parity)
{
  // TODO
}


/**
  * @brief Get parity bit from UART Rx module
  * @retval Received parity (BIT0)
  */
uint8_t HAL_UART_Get_RxParity(void)
{
  // TODO
  return 0;
}
