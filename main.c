#include <stdio.h>
#include <stdbool.h>

#include "stm32l1xx.h"
/* Base LL driver included */
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_lcd.h"
#include "stm32l1xx_ll_dac.h"
#include "stm32l1xx_ll_exti.h"
#include "stm32l152_glass_lcd.h"
/* Configuration */
#include "systemclock_config.h"

int main()
{
    /* Declare struct for GPIO config */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
//    /* Declare struct for DAC config */
//    LL_DAC_InitTypeDef DAC_InitStruct;

//    SystemClock_Config();               // Max-perfomance configure
//    LCD_GLASS_Init();                   // LCD low-level init
    
    /* Enable GPIOA and GPIOC clock */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    
    /* Enable DAC clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);

    /* Config Usr-Btn GPIOA PA0 as input */
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers 
    
    /* Config DAC GPIOA PA5 as analog */
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers 
    
    LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
    
    
    
    while(1){
        LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF);
    }

}
