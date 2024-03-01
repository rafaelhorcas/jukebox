/**
 * @file port_usart.h
 * @brief Header for port_usart.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 01/03/2024
 */
#ifndef PORT_USART_H_
#define PORT_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>


/* HW dependent includes */
#include "stm32f4xx.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define USART_0_ID 0x0
#define USART_0 USART3
#define USART_0_GPIO_TX GPIOB
#define USART_0_GPIO_RX GPIOC
#define USART_0_PIN_TX 0xA
#define USART_0_PIN_RX 0xB
#define USART_0_AF_TX 0x7
#define USART_0_AF_RX 0x7
#define USART_INPUT_BUFFER_LENGTH 0xA
#define USART_OUTPUT_BUFFER_LENGTH 0x64
#define EMPTY_BUFFER_CONSTANT 0x0
#define END_CHAR_CONSTANT 0xA

/* Typedefs --------------------------------------------------------------------*/
typedef struct {
    USART_TypeDef *p_usart;
    GPIO_TypeDef *p_port_tx;
    GPIO_TypeDef *p_port_rx;
    uint8_t pin_tx;
    uint8_t pin_rx;
    uint8_t alt_func_tx;
    uint8_t alt_func_rx;
    char input_buffer [USART_INPUT_BUFFER_LENGTH];
    uint8_t i_idx;
    bool read_complete;
    char output_buffer [USART_OUTPUT_BUFFER_LENGTH];
    uint8_t o_idx;
    bool write_complete;
}port_usart_hw_t;

/* Global variables */
extern port_usart_hw_t usart_arr[];

/* Function prototypes and explanation -------------------------------------------------*/


#endif