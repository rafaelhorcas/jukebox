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

void port_led_init(uint32_t led_id){
    GPIO_TypeDef *p_port = leds_arr[led_id].p_port;
    uint8_t pin = leds_arr[led_id].pin;
    port_system_gpio_config(p_port, pin, GPIO_MODE_OUT, GPIO_PUPDR_NOPULL);
    port_system_gpio_config_exti(p_port, pin, TRIGGER_RISING_EDGE);    
}

void port_led_on(uint32_t led_id){

    leds_arr[led_id].is_illuminated = true;
}

void port_led_off(uint32_t led_id){

    leds_arr[led_id].is_illuminated = false;
}

bool port_led_is_illuminated(uint32_t led_id){
    return leds_arr[led_id].is_illuminated;
}
