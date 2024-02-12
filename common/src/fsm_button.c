/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author Rafael Horcas Mateo r.horcasm@alumnos.upm.es
 * @author Victor Mendizabal Gimeno v.mendizabal@alumnos.upm.es
 * @date 09/02/2024
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_button.h"
#include "port_button.h"


/* State machine input or transition functions */


/* State machine output or action functions */


/* Other auxiliary functions */
static bool check_button_pressed(fsm_t * p_this){
    return port_button_is_pressed();
}

static bool check_button_released(fsm_t * p_this){
    return !port_button_is_pressed();
}

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);

    /* TO-DO alumnos: */
}
