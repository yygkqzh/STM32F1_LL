/*
 * @Description: 
 * @version: 
 * @Company: Xi'an Action power electric co.,LTD.
 * @Author: yangyouguo
 * @Date: 2020-01-03 12:40:05
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-03 19:28:42
 */


#pragma once
#include <string.h>
void uart_transmit(void);
void uart_transmit_dma(void);
void uart_interrupt_receive_configuration(void);
void uart_receive_interrupt_callback(void);
void uart_rx_dma_configuration(void);
void uart_receive_dma_callback(void);