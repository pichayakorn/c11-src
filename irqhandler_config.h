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

#ifndef __irqHandler_conf
#define __irqHandler_conf

//bool state_user_btn = false;
bool state_m1 = false;
bool state_m2 = false;

void EXTI0_IRQHandler(void) {
	// Check if EXTI0 bit is seted by interrupt
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);				    // Clear pending bit by writing 1
	}
}

void EXTI15_10_IRQHandler(void) {
	/* Check if EXTI11 bit is seted by interrupt */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11)) {
        //if (!(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_11))) {
            if (state_m1 == false) {
                state_m1 = true;
                LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
            }
            else {
                state_m1 = false;
                LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
            }
        //}
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);			    // Clear pending bit by writing 1
    }
    
    /* Check if EXTI12 bit is seted by interrupt */
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12)) {
        //if (!(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_12))) {
            if (state_m2 == false) {
                state_m2 = true;
                LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
            }
            else {
                state_m2 = false;
                LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
            }
        //}
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);			    // Clear pending bit by writing 1
    }
}

#endif
