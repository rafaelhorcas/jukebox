/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 09/02/2024
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "fsm_button.h"
#include "port_button.h"


/* State machine input or transition functions */

/**
 * @brief Check if the button has been pressed.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 * @return true
 * @return false
 */
static bool check_button_pressed(fsm_t * p_this){
    fsm_button_t * p_button = ( fsm_button_t *) p_this ;
    return port_button_is_pressed(p_button->button_id);
}

/**
 * @brief Check if the button has been released.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 * @return true
 * @return false
 */
static bool check_button_released(fsm_t * p_this){
    fsm_button_t * p_button = ( fsm_button_t *) p_this;
    return !port_button_is_pressed(p_button->button_id);
}

/**
 * @brief Check if the debounce-time has passed.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 * @return true
 * @return false
 */
static bool check_timeout(fsm_t * p_this)	
{
    fsm_button_t * p_button = ( fsm_button_t *) p_this ;
    uint32_t tick_now = port_button_get_tick();
    return tick_now > p_button -> next_timeout;
}

/* State machine output or action functions */
/**
 * @brief Store the system tick when the button was pressed.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 */
static void do_store_tick_pressed(fsm_t *p_this)
{
    fsm_button_t *p_button = ( fsm_button_t *) p_this;
    uint32_t tick_now = port_button_get_tick();
    p_button -> tick_pressed = tick_now ;
    p_button -> next_timeout = tick_now + p_button -> debounce_time ;
}

/**
 * @brief Store the duration of the button pressed.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 */
static void do_set_duration(fsm_t *p_this)
{
    fsm_button_t *p_button = ( fsm_button_t *) p_this ;
    uint32_t tick_now = port_button_get_tick();

    p_button -> duration = tick_now - p_button -> tick_pressed ;
    p_button -> next_timeout = tick_now + p_button -> debounce_time ;
}

/**
 * @brief Array representing the transitions table of the FSM button
 * 
 * @image html fsm_button_states.png
 */
static fsm_trans_t fsm_trans_button[] = {
    { BUTTON_RELEASED , check_button_pressed , BUTTON_PRESSED_WAIT , do_store_tick_pressed },
    { BUTTON_PRESSED_WAIT , check_timeout , BUTTON_PRESSED , NULL },
    { BUTTON_PRESSED , check_button_released , BUTTON_RELEASED_WAIT , do_set_duration } ,
    { BUTTON_RELEASED_WAIT , check_timeout , BUTTON_RELEASED , NULL },
    { -1 , NULL , -1, NULL }
};

/* Other auxiliary functions */

/* FSM public functions */
uint32_t fsm_button_get_duration (fsm_t *p_this){
    fsm_button_t * p_button = (fsm_button_t *) p_this;
    return p_button -> duration;
}

void fsm_button_reset_duration (fsm_t *p_fsm ){
    fsm_button_t * p_button = ( fsm_button_t *) p_fsm ;
    p_button -> duration = 0;
}

fsm_t * fsm_button_new(uint32_t debounce_time, uint32_t button_id){
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id){
    fsm_button_t *p_button = (fsm_button_t *)p_this;
    fsm_init(&p_button->f, fsm_trans_button);
    p_button -> debounce_time = debounce_time ;
    p_button -> button_id = button_id;
    p_button -> tick_pressed = 0;
    p_button -> duration = 0;
    port_button_init(p_button->button_id);
}

bool fsm_button_check_activity(fsm_t *p_this){
    
}