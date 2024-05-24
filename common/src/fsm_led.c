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
 * @brief Check if a melody is playing
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 * @return true 
 * @return false 
 */
bool check_melody_start(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    return port_check_melody_start(p_led->led_id);
}

/**
 * @brief Check if the melody has finished
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 * @return true 
 * @return false 
 */
bool check_melody_end(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    return port_check_melody_end(p_led->led_id);
}

/* State machine output or action functions */
/**
 * @brief Turns the LED on.
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 */
void do_turn_on(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    port_led_turn_on(p_led->led_id);
    p_led->is_illuminated=true;
}

/**
 * @brief Turn the LED off
 * 
 * @param p_this fsm_t Pointer to the LED FSM.
 */
void do_turn_off(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this;
    port_led_turn_off(p_led->led_id);
    p_led->is_illuminated=false;
}

/**
 * @brief Array representing the transitions table of the FSM button
 * 
 * @image html fsm_led_states.png
 */
static fsm_trans_t fsm_trans_led[] = {
    { LED_OFF, check_melody_start, LED_ON, do_turn_on },
    { LED_ON , check_melody_end, LED_OFF, do_turn_off },
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
    p_led->led_id = led_id;
    port_led_init(led_id);
}

bool fsm_led_check_activity(fsm_t *p_this){
    fsm_led_t *p_led = (fsm_led_t *)p_this; 
    return(p_led->f.current_state != LED_OFF);
}

void fsm_led_turn_on(uint32_t led_id){
    port_led_turn_on(led_id);
}

void fsm_led_turn_off(uint32_t led_id){
    port_led_turn_off(led_id);
}