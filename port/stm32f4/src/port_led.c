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
    [LED_0_ID] = {.p_port = LED_0_GPIO, .pin = LED_0_PIN, .melody_start = false, .melody_end = true},
    [LED_1_ID] = {.p_port = LED_1_GPIO, .pin = LED_1_PIN, .melody_start = false, .melody_end = true},
};

/* Public functions -----------------------------------------------------------*/
void port_led_init(uint32_t led_id){
    GPIO_TypeDef *p_port = leds_arr[led_id].p_port;
    uint8_t pin = leds_arr[led_id].pin;
    port_system_gpio_config(p_port, pin, GPIO_MODE_OUT, GPIO_PUPDR_NOPULL);
    port_system_gpio_config_exti(p_port, pin, TRIGGER_RISING_EDGE);
    port_system_gpio_exti_enable(pin, 1, 0);
}

bool port_led_get(uint32_t led_id) {
    // Definimos las máscaras según sea el LED0 o LED1
    uint32_t IDR_MASK;
    if (led_id == LED_0_ID) {
        IDR_MASK = IDR5_MASK_LED0;
    } else if (led_id == LED_1_ID) {
        IDR_MASK = IDR5_MASK_LED1;
    }
    uint32_t current_value = (LED_0_GPIO->IDR & IDR_MASK);
    return current_value;
}
void port_led_turn_on(uint32_t led_id) {
    // Definimos la máscara según sea el LED0 o LED1
    uint32_t ODR_MASK;
    if (led_id == LED_0_ID) {
        ODR_MASK = ODR5_MASK_LED0;
    } else if (led_id == LED_1_ID) {
        ODR_MASK = ODR5_MASK_LED1;
    }
    // Se usa la GPIO del LED0 porque ambos para ambos es el mismo
    LED_0_GPIO->ODR |= ODR_MASK;
}

void port_led_turn_off(uint32_t led_id) {
    // Definimos la máscara según sea el LED0 o LED1
    uint32_t ODR_MASK;
    if (led_id == LED_0_ID) {
        ODR_MASK = ODR5_MASK_LED0;
    } else if (led_id == LED_1_ID) {
        ODR_MASK = ODR5_MASK_LED1;
    }
    // Se usa la GPIO del LED0 porque ambos para ambos es el mismo
    LED_0_GPIO->ODR &= ~ODR_MASK;
}

bool port_check_melody_start(uint32_t led_id){
    return leds_arr[led_id].melody_start;
}

bool port_check_melody_end(uint32_t led_id){
    return leds_arr[led_id].melody_end;
}