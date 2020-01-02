/*
 * @Description: GPIO test demo
 * @version: v1.0
 * @Company: Xi'an Action Power
 * @Author: yangyouguo
 * @Date: 2020-01-02 23:06:56
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-02 23:33:13
 */


#include "main.h"
#include "GPIO_Demo.h"

void Led(void)
{
    static uint16_t led_cnt = 0;

    if (led_cnt++ % 1000 > 500)
    {
        LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
    }
    else
    {
        LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
    }
}

void Key(void)
{
    if (LL_GPIO_IsOutputPinSet(KEY0_GPIO_Port, KEY0_Pin) == 1)
    {
        //key0 is up
    }
    else
    {
        //key0 is down
    }
}