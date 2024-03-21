/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date fecha 16/02/2024
 */

#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* HW dependent includes */
#include "port_system.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BUTTON_0_ID 0x00                    /*!<Button Identifier*/
#define BUTTON_0_GPIO GPIOC                 /*!<Button GPIO port*/
#define BUTTON_0_PIN 0x0D                   /*!<Button GPIO pin*/
#define BUTTON_0_DEBOUNCE_TIME_MS 0x96      /*!<Button debounce time*/

/* La placa tiene 8 puertos A-H. Cada uno tiene 16 lineas/pines. Cada puerto tiene un registros de 32bits, esto es, 2 bits para cada pin del puerto.
En nuestro caso, el botón de usuario, B1, usa Puerto C, pin 13.
*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the HW dependencies of a button.
 * 
 */
typedef struct
{
    GPIO_TypeDef *p_port;
    uint8_t pin;
    bool flag_pressed;
} port_button_hw_t;

/* Global variables */
/**
 * @brief Array of elements that represents the HW characteristics of the buttons.
 * This is an extern variable that is defined in port_button.c . It represents an array of hardware buttons.
 * This is an extern variable that is declared in port_button.h.
 */
extern port_button_hw_t buttons_arr[];

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Returns in milliseconds the count of System tick.
 *
 * @return uint32_t
 */
uint32_t port_button_get_tick ();

/**
 * @brief Initializes the given button by configuring the provided hardware specifications.
 * 
 * @param button_id	Button ID. This index is used to select the element of the buttons_arr[] array
 */
void port_button_init (uint32_t button_id)	;

/**
 * @brief Returns the status of the button (pressed or not)
 * 
 * @param button_id	Button ID. This index is used to select the element of the buttons_arr[] array
 * @return true if the button has been pressed
 * @return false if the button has not been pressed
 */
bool port_button_is_pressed	(uint32_t button_id	)	;

#endif
