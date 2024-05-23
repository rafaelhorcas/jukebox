/**
 * @file fsm_led.c
 * @brief LED FSM main file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 23/05/2024
 */

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
/* Other includes */

#include "fsm_led.h"
#include "port_led.h"

/* State machine input or transition functions */
/**
 * @brief Check if the led is set to iluminate
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 * @return true 
 * @return false 
 */
bool check_illuminated(fsm_t *p_this){
    // TO-DO
    return true;
}

/**
 * @brief Check if the led is not set to iluminate
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 * @return true 
 * @return false 
 */
bool check_not_illuminated(fsm_t *p_this){
    return check_illuminated(p_this);
}

/* State machine output or action functions */
/**
 * @brief Turns the LED on
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 */
void do_turn_on(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    port_led_on(p_led->led_id);
}

/**
 * @brief Turn the LED off
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 */
void do_turn_off(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    port_led_off(p_led->led_id);
}

/**
 * @brief Array representing the transitions table of the FSM button
 * 
 * @image html fsm_button_states.png
 */
static fsm_trans_t fsm_trans_led[] = {
    { OFF, check_not_illuminated, ON, do_turn_on },
    { ON , check_illuminated, OFF, do_turn_off },
    { -1 , NULL , -1, NULL }
};

/* Other auxiliary functions */

/* FSM public functions */
fsm_t * fsm_led_new( uint32_t led_id){
    fsm_t *p_fsm = malloc(sizeof(fsm_led_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure)*/
    fsm_led_init(p_fsm, led_id);
    return p_fsm;
}

void fsm_led_init(fsm_t *p_this, uint32_t led_id){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    fsm_init(&p_led->f, fsm_trans_led);
    port_button_init(p_led->led_id);
}
