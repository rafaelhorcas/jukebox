/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */
// Include HW dependencies:

// Include headers of different port elements:
#include "port_system.h"
#include "port_button.h"
#include "port_usart.h"
#include "port_buzzer.h"

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 *
 */
void SysTick_Handler(void){
    uint32_t tickstart = port_system_get_millis();
    port_system_set_millis(tickstart + 1);
}

/**
 * @brief This function handles Px10-Px15 global interrupts.
 * First, this function identifies the pin which has raised the interruption. Then, perform the desired action. Before leaving it cleans the interrupt pending register.
 */
void EXTI15_10_IRQHandler ( void ){
   /* ISR user button */
    if (EXTI -> PR & BIT_POS_TO_MASK (buttons_arr [BUTTON_0_ID].pin))
    {
        bool nivel = port_system_gpio_read(buttons_arr [BUTTON_0_ID].p_port, buttons_arr [BUTTON_0_ID].pin);
        if(nivel){
            buttons_arr[BUTTON_0_ID].flag_pressed = false;
        }
        else {
            buttons_arr[BUTTON_0_ID].flag_pressed = true;
        }

    }
    EXTI -> PR |= BIT_POS_TO_MASK (buttons_arr[BUTTON_0_ID].pin); 
}

/**
 * @brief This function handles USART3 global interrupt.
 * First, this function identifies the pin which has raised the interruption. Then, perform the desired action. Before leaving it cleans the interrupt pending register.
 * 
 */
void USART3_IRQHandler(void){
    if (USART_0->CR1 & USART_CR1_RXNEIE){
        if (USART_0->SR & USART_SR_RXNE){
            port_usart_store_data(USART_0_ID);
        }
        
    }
    if (USART_0->CR1 & USART_CR1_TXEIE){
        if (USART_0->SR & USART_SR_TXE){
            port_usart_write_data(USART_0_ID);
        }
    }
}

void TIM2_IRQHandler(void){
    TIM2->SR &= ~ TIM_SR_UIF;
    buzzers_arr[BUZZER_0_ID].note_end = true;
}	 


