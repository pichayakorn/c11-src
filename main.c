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

bool state = false;
char disp_str[7];

int main()
{
    /* Declare struct for GPIO config */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
//    /* Declare struct for DAC config */
//    LL_DAC_InitTypeDef DAC_InitStruct;

    SystemClock_Config();               // Max-perfomance configure
    LCD_GLASS_Init();                   // LCD low-level init
    
    /* Enable GPIOA and GPIOC clock */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    
    /* Enable DAC clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
    
    /* Enable System configuration controller clock */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    /* Config Usr-Btn GPIOA PA0 as input */
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* Config Matrix-switch1 GPIOA PA12 as input */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* Config Matrix-switch2 GPIOA PC12 as input */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* Config DAC GPIOA PA5 as analog */
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers 
    
    LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
    
    /* EXTI Line 0 (EXTI0) for PA0 */
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_0);
    
    /* EXTI Line 12 (EXTI12) for PA12 AND PC12 */
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE12);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE12);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_12);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_12);
    
    //NVIC_EnableIRQ((IRQn_Type) 6);
    //NVIC_SetPriority((IRQn_Type) 6, 0);
    NVIC_EnableIRQ((IRQn_Type) 40);
    NVIC_SetPriority((IRQn_Type) 40, 1);
    
    
    
    while(1){
        //LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF);
    }

}

//void EXTI0_IRQHandler(void) {
//	// Check if EXTI0 bit is set
//	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0)) {
//		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);				// Clear pending bit by writing 1
//		/* Jump here if rising edge detected */
//        if (state == false) {
//            sprintf(disp_str, "LD: ON");
//			LCD_GLASS_DisplayString((uint8_t*)disp_str);
//            state = true;               // LED4 state: on
//        }
//        else {
//            sprintf(disp_str, "LD:OFF");
//			LCD_GLASS_DisplayString((uint8_t*)disp_str);
//            state = false;              // LED4 state: off
//        }
//	}
//}

void EXTI15_10_IRQHandler(void) {
	// Check if EXTI12 bit is set
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12)) {
		
		/* Jump here if rising edge detected */
        if (state == false) {
            sprintf(disp_str, "LD: ON");
			LCD_GLASS_DisplayString((uint8_t*)disp_str);
            state = true;               // LED4 state: on
        }
        else {
            sprintf(disp_str, "LD:OFF");
			LCD_GLASS_DisplayString((uint8_t*)disp_str);
            state = false;              // LED4 state: off
        }
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);			// Clear pending bit by writing 1
	}
}

