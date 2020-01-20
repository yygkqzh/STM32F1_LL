/*
 * @Description: 
 * @version: 
 * @Company: Xi'an Action power electric co.,LTD.
 * @Author: yangyouguo
 * @Date: 2020-01-06 22:17:03
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-06 23:37:18
 */

#pragma once
#include "spi.h"

uint8_t spi_write_read_byte(SPI_TypeDef *spi,uint8_t write_data);