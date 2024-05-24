/**
 * @file fsm_buzzer.h
 * @brief Header for fsm_buzzer.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 05/04/2024
 */

#ifndef FSM_BUZZER_H_
#define FSM_BUZZER_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include <fsm.h>
#include "melodies.h"

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Enums */
/**
 * @brief Enumerator for the buzzer finite state machine.
 * 
 */
enum FSM_BUZZER {
    WAIT_START = 0,  /*!<Starting state. Also comes here when a melody has been played*/
    PLAY_NOTE,       /*!<State to play a note*/
    PAUSE_NOTE,      /*!<State to pause the player*/
    WAIT_NOTE ,      /*!<State to wait for the duration of the note*/ 
    WAIT_MELODY,     /*!<State to wait for a new melody*/
};

/**
 * @brief Enumeration of possible states actions on the player, either from the user or from the player itself.
 * 
 */
enum USER_ACTIONS {
    STOP, /*!<Player is stopped or requested to stop*/
    PLAY, /*!<Player is playing or requested to play*/
    PAUSE /*!<Player is requested to pause*/
};


/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief BUZZER FSM structure 
 * 
 */
typedef struct
{
    fsm_t f;                /*!< Buzzer melody player FSM */
    melody_t * p_melody;    /*!< Pointer to the melody to play */
    uint32_t note_index;    /*!< Index of the current note*/
    uint8_t buzzer_id;      /*!< Buzzer melody player ID */
    uint8_t user_action;    /*!< Action to perform on the player*/
    double player_speed;    /*!< Speed of the player*/
} fsm_buzzer_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Set the melody to play.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param p_melody 
 */
void fsm_buzzer_set_melody (fsm_t *p_this, const melody_t *p_melody);

/**
 * @brief Set the speed of the player.
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param speed Speed of the player
 */
void fsm_buzzer_set_speed (fsm_t *p_this, double speed);

/**
 * @brief Set the action to perform on the player
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param action Action to perform on the player
 */
void fsm_buzzer_set_action (fsm_t *p_this, uint8_t action);

/**
 * @brief Get the action of the user perform on the player
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return uint8_t Action to perform on the player
 */
uint8_t fsm_buzzer_get_action (fsm_t *p_this);

/**
 * @brief Creates a new buzzer FSM
 * 
 * @param buzzer_id Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return fsm_t* A pointer to the new buzzer finite state machine
 */
fsm_t * fsm_buzzer_new (uint32_t buzzer_id);

/**
 * @brief Initialize a buzzer FSM
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @param buzzer_id Unique buzzer ID
 */
void fsm_buzzer_init (fsm_t *p_this, uint32_t buzzer_id);

/**
 * @brief Check if the buzzer FSM is playing a melody
 * 
 * @param p_this Pointer to an fsm_t struct than contains an fsm_buzzer_t struct
 * @return true if the player is playing or paused
 * @return false if the player is stopped
 */
bool fsm_buzzer_check_activity (fsm_t *p_this);

#endif /* FSM_BUZZER_H_ */