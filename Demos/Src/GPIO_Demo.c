/*
 * @Description: GPIO test demo
 * @version: v1.0
 * @Company: Xi'an Action power electric co.,LTD.
 * @Author: yangyouguo
 * @Date: 2020-01-02 23:06:56
 * @LastEditors  : yangyouguo
 * @LastEditTime : 2020-01-03 12:24:25
 */

#include "main.h"
#include "GPIO_Demo.h"
/**
 * @name: Led
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: nono
 */
void Led(void)
{
    static uint8_t led_cnt = 0;
    for (;;)
    {
        if (led_cnt++ % 10 > 5)
        {
            LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
        }
        else
        {
            LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
        }
        LL_mDelay(200);
    }
}
/**
 * @name: Led
 * @test: test font
 * @msg: 
 * @param {type} 
 * @return: none
 */
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