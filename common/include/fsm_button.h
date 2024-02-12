/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author Rafael Horcas Mateo r.horcasm@alumnos.upm.es
 * @author Victor Mendizabal Gimeno v.mendizabal@alumnos.upm.es
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
    BUTTON_RELEASED = 0,  /*!<Starting State*/
    BUTTON_RELEASED_WAIT, /*!<*/
    BUTTON_PRESSED,       /*!<*/
    BUTTON_PRESSED_WAIT , /*!<*/ 
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
    uint32_t button_id;     /*!< ID del botón */
} fsm_button_t;

/* Function prototypes and documentation ---------------------------------------*/
/**
 * @brief Creates a new FSM for measuring how long the button is pressed.
 *
 * @note this function uses malloc to save memory space in the heap for the FSM.
 * @note If you are done with the FSM, you must call fsm_destroy to free memory.
 *
 * @param debounce_time time (in ms) the FSM will wait in intermediate steps to avoid mechanical gltiches.
 *
 * @return fsm_t* pointer to the button FSM.
 */
fsm_t * fsm_button_new(uint32_t debounce_time);

/**
 * @brief Initializes all the parameters for an FSM that measures how long the button is pressed.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to button FSM (we already provide this) \n
 * > ✅ 2. Initialize its inner FSM (we already provide this) \n
 * > ✅ 3. Fill all the fields of the button FSM to their initial value \n
 * > ✅ 4. Configure the GPIO of the button accordingly.
 *
 * @param p_fsm pointer to the FSM.
 * @param debounce_time time (in ms) the FSM will wait in intermediate steps to avoid mechanical gltiches.
 */
void fsm_button_init(fsm_t *p_fsm, uint32_t debounce_time);

/**
 * @brief it returns the latest duration measured by the button FSM.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to button FSM \n
 * > ✅ 2. return the value of the duration counter
 *
 * @param p_fsm pointer to the button FSM.
 * @return uint32_t amount of time (in ms) that the button has been pressed.
 */
uint32_t fsm_button_get_duration(fsm_t *p_fsm);

/**
 * @brief It sets the duration measured by the button FSM to 0.
 * 
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. Cast pointer to button FSM \n
 * > ✅ 2. set duration counter to 0
 *
 * @param p_fsm pointer to the button FSM.
 */
void fsm_button_reset_duration(fsm_t *p_fsm);

bool fsm_button_check_activity(fsm_t *p_this);

#endif // FSM_BUTTON_H_

