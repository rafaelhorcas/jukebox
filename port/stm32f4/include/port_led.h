/**
 * @file port_led.h
 * @brief Header for port_led.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 23/05/2024
 */

#ifndef PORT_LED_H_
#define PORT_LED_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* HW dependent includes */
#include "port_system.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define LED_0_ID 0x00                    /*!<LED Identifier*/
#define LED_0_GPIO GPIOC                 /*!<LED GPIO port*/
#define LED_0_PIN 0x02                   /*!<LED GPIO pin*/
#define LED_1_ID 0x01                    /*!<LED Identifier*/
#define LED_1_GPIO GPIOC                 /*!<LED GPIO port*/
#define LED_1_PIN 0x03                   /*!<LED GPIO pin*/
#define ODR5_MASK_LED0 ( GPIO_ODR_OD0 << LED_0_PIN ) /*!< Mask for ODR register using LED_0_PIN */
#define IDR5_MASK_LED0 ( GPIO_IDR_ID0 << LED_0_PIN ) /*!< Mask for IDR register using LED_0_PIN */
#define ODR5_MASK_LED1 ( GPIO_ODR_OD0 << LED_1_PIN ) /*!< Mask for ODR register using LED_1_PIN */
#define IDR5_MASK_LED1 ( GPIO_IDR_ID0 << LED_1_PIN ) /*!< Mask for IDR register using LED_1_PIN */

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the HW dependencies of a LED.
 * 
 */
typedef struct
{
    GPIO_TypeDef *p_port;   /*!<GPIO where the LED is connected*/
    uint8_t pin;            /*!<Pin where the LED is connected*/
    bool melody_start;  /*!< Flag that represents that a melody is playing*/
    bool melody_end;    /*!< Flag that represents that a melody has finished*/
} port_led_hw_t;         

/* Global variables */
/**
 * @brief Array of hardware LEDs.
 * 
 */
extern port_led_hw_t led_arr[];

/**
 * @brief Initialize the given LED by configuring the provided hardware specifications.
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 */
void port_led_init(uint32_t led_id);

/**
 * @brief Checks the status of the LED to determine whether its ON or OFF
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 * @return true 
 * @return false 
 */
bool port_led_get(uint32_t led_id);


/**
 * @brief Check if a melody is playing
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 * @return true 
 * @return false 
 */
bool port_check_melody_start(uint32_t led_id);

/**
 * @brief Check if the melody has ended
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 * @return true 
 * @return false 
 */
bool port_check_melody_end(uint32_t led_id);

/**
 * @brief Turns on the LED.
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 */
void port_led_turn_on(uint32_t led_id);

/**
 * @brief Turns off the LED.
 * 
 * @param led_id LED ID. This index is used to select the element of the LEDs_arr[] array.
 */
void port_led_turn_off(uint32_t led_id);

#endif