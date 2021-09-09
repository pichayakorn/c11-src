#include <stdio.h>
#include <stdbool.h>
/* Base register address header file */
#include "stm32l1xx.h"
/* Base LL driver included */
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_bus.h"
/* DAC driver included */
#include "stm32l1xx_ll_dac.h"
/* EXTI driver included */
#include "stm32l1xx_ll_exti.h"
/* LCD driver included */
#include "stm32l1xx_ll_lcd.h"
#include "stm32l152_glass_lcd.h"
/* Configuration */
#include "systemclock_config.h"
#include "c11_stm32l152rb_config.h"
#include "irqhandler_config.h"
/* Configuration */
#include "game_setting.h"

int main()
{
    /* C11:Count 24 game register configuration */
    C11_STM32L152RB_CONFIG();

    while(1){

    }
}
