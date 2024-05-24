/**
 * @file fsm_led.h
 * @brief Header for fsm_led.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 23/05/2024
 */

#ifndef FSM_LED_H_
#define FSM_LED_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include "fsm.h"

/* Defines -------------------------------------------------------------------*/
/**
 * @brief Enumerator that defines the different states the finite state machine can be in.
 * 
 */
enum FSM_LED{
    LED_OFF = 0,  /*!<Starting state. The LED is off*/
    LED_ON,       /*!<The LED is on*/
};

/* Typedefs ------------------------------------------------------------------*/
/**
 * @brief LED FSM structure 
 * 
 */
typedef struct{
    fsm_t f;            /*!< Internal FSM from the library */
    uint32_t led_id;    /*!< LED ID*/
    bool is_illuminated;    /*!<Flag that indicates that the LED has been pressed*/
} fsm_led_t;

/* Function prototypes and documentation ---------------------------------------*/
/**
 * @brief Creates a new LED FSM
 * @param led_id Unique LED identifier number.
 *
 * @return fsm_t Pointer to the LED FSM.
 */
fsm_t* fsm_led_new(uint32_t led_id);

/**
 * @brief Initializes all the parameters of the LED FSM.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_led_t.
 * @param button_id	Unique LED identifier number.
 */
void fsm_led_init(fsm_t *p_this, uint32_t led_id);

/** 
 * @brief Check if the LED is on
 * @param p_this Pointer to an fsm_t struct than contains an fsm_led_t.
 * @return true
 * @return false
 */  
bool fsm_led_check_activity(fsm_t *p_this);

/**
 * @brief Function that turns the LED on.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_led_t.
 */
void fsm_led_turn_on(uint32_t led_id);

/**
 * @brief Function that turns the LED off.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_led_t.
 */
void fsm_led_turn_off(uint32_t led_id);

#endif 

