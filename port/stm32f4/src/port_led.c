/**
 * @file port_led.c
 * @brief File containing functions related to the HW of the LEDs.
 * This file defines an internal struct which contains the HW information of the LEDs.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 23/05/2024 
 */

/* Includes ------------------------------------------------------------------*/
#include "port_led.h"

/* Global variables ------------------------------------------------------------*/
port_led_hw_t leds_arr[] = {
    [LED_0_ID] = {.p_port = LED_0_GPIO, .pin = LED_0_PIN, .is_illuminated=false},
    [LED_1_ID] = {.p_port = LED_1_GPIO, .pin = LED_1_PIN, .is_illuminated=false},
};

/* Public functions -----------------------------------------------------------*/
void port_led_init(uint32_t led_id){
    GPIO_TypeDef *p_port = leds_arr[led_id].p_port;
    uint8_t pin = leds_arr[led_id].pin;
    port_system_gpio_config(p_port, pin, GPIO_MODE_OUT, GPIO_PUPDR_NOPULL);
}

bool port_led_get(uint32_t led_id) {
    // Creamos las máscaras según sea el LED0 o LED1
    uint32_t ODR_MASK, IDR_MASK;
    if (led_id == LED_0_ID) {
        ODR_MASK = ODR5_MASK_LED0;
        IDR_MASK = IDR5_MASK_LED0;
    } else if (led_id == LED_1_ID) {
        ODR_MASK = ODR5_MASK_LED1;
        IDR_MASK = IDR5_MASK_LED1;
    }
    // Leemos el valor del LED en IDR
    uint32_t current_value = (LED_0_GPIO->IDR & IDR_MASK);
    leds_arr[led_id].is_illuminated = current_value;
    return current_value;
}

void port_led_toggle (uint32_t led_id){
    // Creamos las máscaras según sea el LED0 o LED1
    uint32_t ODR_MASK, IDR_MASK;
    if (led_id == LED_0_ID) {
        ODR_MASK = ODR5_MASK_LED0;
        IDR_MASK = IDR5_MASK_LED0;
    } else if (led_id == LED_1_ID) {
        ODR_MASK = ODR5_MASK_LED1;
        IDR_MASK = IDR5_MASK_LED1;
    }
    // Leemos el valor previo del LED en IDR
    uint32_t prev_value = ( LED_0_GPIO -> IDR & IDR_MASK );
    // Segun corresponda , apagamos o encendemos el LED en ODR. Ponemos LED_O_GPIO pq ambos LEDs tienen el mismo.
    if ( prev_value ){
        LED_0_GPIO -> ODR &= ~ ODR_MASK ;
        leds_arr[led_id].is_illuminated = false;
    }
    else{
        LED_0_GPIO-> ODR |= ODR_MASK ;
        leds_arr[led_id].is_illuminated = true;
    }
}

//Faltan las funciones de cuando se llama a las check en fsm_led
