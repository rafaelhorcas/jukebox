/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 09/02/2024
 */

#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include "fsm.h"

/* Defines -------------------------------------------------------------------*/
enum FSM_BUTTON {
    BUTTON_RELEASED = 0,  /*!<Starting state. Also comes here when the button has been released*/
    BUTTON_RELEASED_WAIT, /*!<State to perform the anti-debounce mechanism for a falling edge*/
    BUTTON_PRESSED,       /*!<State while the button is being pressed*/
    BUTTON_PRESSED_WAIT , /*!<State to perform the anti-debounce mechanism for a rising edge*/ 
};

/* Typedefs ------------------------------------------------------------------*/
/**
 * @brief Button FSM structure 
 * 
 */
typedef struct
{
    fsm_t f;                /*!< Internal FSM from the library */
    uint32_t debounce_time; /*!< Button debounce time in ms */
    uint32_t next_timeout;  /*!< Next timeout for the debounce in ms */
    uint32_t tick_pressed;  /*!< Number of system ticks when the button was pressed */
    uint32_t duration;      /*!< How much time the button has been pressed */
    uint32_t button_id;     /*!< Button ID*/
} fsm_button_t;

/* Function prototypes and documentation ---------------------------------------*/
/**
 * @brief Creates a new FSM for measuring how long the button is pressed.
 *
 * @note this function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_destroy to free memory.
 *
 * @param debounce_time time (in ms) the FSM will wait in intermediate steps to avoid mechanical gltiches.
 * @param button_id	Unique button identifier number
 *
 * @return fsm_t* pointer to the button FSM.
 */
fsm_t * fsm_button_new(uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Initializes all the parameters for an FSM that measures how long the button is pressed.
 *
 * @param p_this	Pointer to an fsm_t struct than contains an fsm_button_t.
 * @param debounce_time	Anti-debounce time in milliseconds
 * @param button_id	Unique button identifier number
 */
void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Returns the latest duration measured by the button FSM.
 *
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t
 * @return uint32_t amount of time (in ms) that the button has been pressed.
 */
uint32_t fsm_button_get_duration(fsm_t *p_this);

/**
 * @brief Sets the duration measured by the button FSM to 0.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_button_t.
 */
void fsm_button_reset_duration(fsm_t *p_this);

/** 
 * @brief Check if the button FSM is active, or not. The button is inactive when it is in the status BUTTON_RELEASED.
 * @param p_this	Pointer to an fsm_t struct than contains an fsm_button_t.
 * @return true
 * @return
 */  
bool fsm_button_check_activity(fsm_t *p_this);

#endif // FSM_BUTTON_H_

