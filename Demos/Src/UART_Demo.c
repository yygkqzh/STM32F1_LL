/*
 * @Description: 
 * @version: V1.0
 * @Company: Xi'an Action power electric co.,LTD.
 * @Author: yangyouguo
 * @Date: 2020-01-03 12:39:48
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-03 19:34:02
 */

#include "main.h"
#include "UART_Demo.h"

static const char *send_buff1 = "This is usart1 poll transmit test send!\n";
static const char *send_buff2 = "This is usart1 interrupt transmit test send!\n";
static const char *send_buff3 = "This is usart1 dma transmit test send!\n";
/**
 * @name: uart transmit poll
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
void uart_transmit(void)
{
    for (;;)
    {
        for (uint8_t i = 0; i < strlen(send_buff1); i++)
        {
            LL_USART_TransmitData8(USART1, send_buff1[i]);
            while (!LL_USART_IsActiveFlag_TC(USART1))
                ;
        }
        LL_mDelay(1000);
    }
}

static void uart_interrupt_transmit_configuration(void)
{
    LL_USART_EnableIT_TC(USART1);
}
/**
 * @name: uart transmit interrupt
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
void uart_transmit_interrupt(void)
{
    uart_interrupt_transmit_configuration();
    for (;;)
    {
        for (uint8_t i = 0; i < strlen(send_buff2); i++)
        {
            LL_USART_TransmitData8(USART1, send_buff2[i]);
            //Determine whether the serial port sending interrupt occurs
            //Clear serial port send interrupt
            while (!LL_USART_IsEnabledIT_TC(USART1))
                ;
            LL_USART_ClearFlag_TC(USART1);
        }
        LL_mDelay(1000);
    }
}

static void uart_tx_dma_configuration(void)
{
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_4);
    LL_USART_ClearFlag_TC(USART1);
    LL_USART_EnableIT_TC(USART1);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4, LL_USART_DMA_GetRegAddr(USART1));
}
/**
 * @name: uart transmit dma
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
void uart_transmit_dma(void)
{
    uart_tx_dma_configuration();
    for (;;)
    {
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)send_buff3);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, strlen(send_buff3));
        LL_USART_EnableDMAReq_TX(USART1);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
        LL_mDelay(1000);
    }
}

void uart_interrupt_receive_configuration(void)
{
    LL_USART_EnableIT_RXNE(USART1);
    LL_USART_EnableIT_ERROR(USART1);
}
/**
 * @name: uart receive interrupt
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
void uart_receive_interrupt_callback(void)
{
    __IO uint32_t received_char;

    /* Read Received character. RXNE flag is cleared by reading of DR register */
    received_char = LL_USART_ReceiveData8(USART1);

    /* Echo received character on TX */
    LL_USART_TransmitData8(USART1, received_char);
}
#define BUFFSIZE 0xff
uint8_t recv_buff[BUFFSIZE] = {0};
uint32_t recv_len = 0;
void uart_rx_dma_configuration(void)
{
    LL_USART_EnableIT_IDLE(USART1);
    LL_USART_EnableIT_ERROR(USART1);
    LL_USART_ClearFlag_ORE(USART1);
    LL_USART_ClearFlag_IDLE(USART1);

    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_5, LL_USART_DMA_GetRegAddr(USART1));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)recv_buff);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, sizeof(recv_buff));
    LL_USART_EnableDMAReq_RX(USART1);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
}
/**
 * @name: uart receive dma
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
void uart_receive_dma_callback(void)
{
    uint32_t temp = 0;

    LL_USART_ClearFlag_IDLE(USART1);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);

    temp = LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_5);
    recv_len = BUFFSIZE - temp;
}