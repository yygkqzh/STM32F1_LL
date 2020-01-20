/*
 * @Description: 
 * @version: V1.0
 * @Company: Xi'an Action power electric co.,LTD.
 * @Author: yangyouguo
 * @Date: 2020-01-06 22:17:17
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-12 13:29:46
 */

#include "main.h"
#include "gpio.h"
#include "SPI_Demo.h"

static void spi_write_byte(SPI_TypeDef *spi, uint8_t write_data)
{
    while (LL_SPI_IsActiveFlag_TXE(spi) != 1)
        ;
    LL_SPI_TransmitData8(spi, write_data);
}

static uint8_t spi_read_byte(SPI_TypeDef *spi)
{
    while (LL_SPI_IsActiveFlag_RXNE(spi) != 1)
        ;
    return LL_SPI_ReceiveData8(spi);
}

uint8_t spi_write_read_byte(SPI_TypeDef *spi, uint8_t write_data)
{
    uint8_t ret = 0;
    spi_write_byte(spi, write_data);
    ret = spi_read_byte(spi);
    return ret;
}


