/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author alumno1 r.horcasm@alumnos.upm.es
 * @author alumno2 v.mendizabal@alumnos.upm.es
 * @date fecha 16/02/2024
 */

#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_system.h"

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BUTTON_0_ID 0x00

/* TODO: revisar estos 2 valores*/
#define BUTTON_0_GPIO 0x00
#define BUTTON_0_PIN 0x00
/* TODO: revisar estos 2 valores*/

#define BUTTON_0_DEBOUNCE_TIME_MS 0x96

/* Typedefs --------------------------------------------------------------------*/
typedef struct
{
    GPIO_TypeDef *p_port;
    uint8_t pin;
    bool flag_pressed;
} port_button_hw_t;

/* Global variables */
extern port_button_hw_t  buttons_arr[];

/* Function prototypes and explanation -------------------------------------------------*/


/**
 * @brief Return the count of the System tick in milliseconds.
 *
 * @return uint32_t
 */
uint32_t port_button_get_tick ();

/**
 * @brief Configure the HW specifications of a given button.
 * 
 * @param button_id	Button ID. This index is used to select the element of the buttons_arr[] array
 */
void port_button_init (uint32_t button_id	)	;

/**
 * @brief Return the status of the button (pressed or not)
 * 
 * @param button_id	Button ID. This index is used to select the element of the buttons_arr[] array
 * @return true If the button has been pressed
 * @return false If the button has not been pressed
 */
bool port_button_is_pressed	(uint32_t button_id	)	;


#endif
