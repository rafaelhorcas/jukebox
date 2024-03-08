/**
 * @file port_usart.c
 * @brief Portable functions to interact with the USART FSM library.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date fecha 08/03/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <string.h>
#include <stdlib.h>

/* HW dependent libraries */
#include "port_system.h"
#include "port_usart.h"

/* Global variables */
/**
 * @brief Array of elements that represents the HW characteristics of the USARTs. This is an extern variable that is declared in port_usart.h.
 * 
 */
port_usart_hw_t usart_arr[] = {
    [USART_0_ID] = {.p_usart = USART_0, .p_port_tx = USART_0_GPIO_TX, .p_port_rx = USART_0_GPIO_RX, .pin_tx= USART_0_PIN_TX, .pin_rx= USART_0_PIN_RX, .alt_func_tx = USART_0_AF_TX,
                    .alt_func_rx = USART_0_AF_RX, .input_buffer = USART_INPUT_BUFFER_LENGTH, .read_complete = false, .write_complete = false,
                    .i_idx = 0, .output_buffer = USART_OUTPUT_BUFFER_LENGTH, .o_idx = 0}
};

/* Private functions */
void _reset_buffer(char *buffer, uint32_t length){
   memset(buffer, EMPTY_BUFFER_CONSTANT, length);
}


/* Public functions */
// TO-DO ALUMNOS
void port_usart_init(uint32_t usart_id){
    USART_TypeDef *p_usart = usart_arr[usart_id].p_usart;
    GPIO_TypeDef *p_port_tx = usart_arr[usart_id].p_port_tx;
    GPIO_TypeDef *p_port_rx = usart_arr[usart_id].p_port_rx;
    uint8_t pin_tx = usart_arr[usart_id].pin_tx;
    uint8_t pin_rx = usart_arr[usart_id].pin_rx;
    uint8_t alt_func_tx = usart_arr[usart_id].alt_func_tx;
    uint8_t alt_func_rx = usart_arr[usart_id].alt_func_rx;

    port_system_gpio_config(p_port_tx, pin_tx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);
    port_system_gpio_config(p_port_rx, pin_rx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);

    port_system_gpio_config_alternate(p_port_tx, pin_tx, GPIO_MODE_ALTERNATE);
    port_system_gpio_config_alternate(p_port_rx, pin_rx, GPIO_MODE_ALTERNATE);

    // Enable USART interrupts globally
    if (p_usart == USART3)
    {
        NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
        NVIC_EnableIRQ(USART3_IRQn);
    }
    // 416,66 USART_BRR 
    if (p_usart == USART3){
        RCC -> AHB1ENR |= RCC_APB1ENR_USART3EN ;
    }
}

void port_usart_get_from_input_buffer(uint32_t usart_id, char *p_buffer){
    port_usart_hw_t p_usart = usart_arr[usart_id];
    memcpy(p_buffer, p_usart.input_buffer, USART_INPUT_BUFFER_LENGTH);
}

bool port_usart_get_txr_status(uint32_t usart_id){
    return usart_arr[usart_id].write_complete;
}

void port_usart_copy_to_output_buffer(uint32_t usart_id, char *p_data, uint32_t length){
    port_usart_hw_t p_usart = usart_arr[usart_id];
    memcpy(p_usart.input_buffer, p_data, length);
}

void port_usart_reset_input_buffer(uint32_t usart_id){
    _reset_buffer(usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
    usart_arr[usart_id].read_complete = false;
}

void port_usart_reset_output_buffer(uint32_t usart_id){
    _reset_buffer(usart_arr[usart_id].output_buffer, USART_OUTPUT_BUFFER_LENGTH);
    usart_arr[usart_id].write_complete = false;
}

bool port_usart_rx_done(uint32_t usart_id){
    return usart_arr[usart_id].read_complete;
}

bool port_usart_tx_done(uint32_t usart_id){
    return usart_arr[usart_id].write_complete;
}

// TO-DO ALUMNOS
void port_usart_store_data(uint32_t usart_id){
    char data = USART3 -> DR;
    if (data != END_CHAR_CONSTANT){
        uint32_t input_index = usart_arr[usart_id].i_idx;
        if (input_index >= USART_INPUT_BUFFER_LENGTH){
            usart_arr[usart_id].i_idx = 0;
        }
        // ni idea xddd
    }
    else {
        usart_arr[usart_id].read_complete = true;
        port_usart_reset_input_buffer(usart_id);
    }
}

// TO-DO ALUMNOS
void port_usart_write_data(uint32_t	usart_id){

}

void port_usart_enable_rx_interrupt(uint32_t usart_id){
    USART1 -> CR1 |= USART_CR1_RXNEIE;
}

void port_usart_enable_tx_interrupt(uint32_t usart_id){
    USART1 -> CR1 |= USART_CR1_TXEIE;
}

void port_usart_disable_rx_interrupt(uint32_t usart_id){
    USART1 -> CR1 &= USART_CR1_RXNEIE;
}

void port_usart_disable_tx_interrupt(uint32_t usart_id){
    USART1 -> CR1 &= USART_CR1_TXEIE;
}