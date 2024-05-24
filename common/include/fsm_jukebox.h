/**
 * @file fsm_jukebox.h
 * @brief Header for fsm_jukebox.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 25/02/2024
 */
#ifndef FSM_JUKEBOX_H_
#define FSM_JUKEBOX_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>

/* Other includes */
#include <fsm.h>
#include "melodies.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define MELODIES_MEMORY_SIZE 10  /*!<Size of the arrays of melodies*/

/* Enums */
/**
 * @brief Enumerator that defines the different states that the Jukebox finite state machine can be in
 * 
 */
enum FSM_JUKEBOX {
  OFF = 0,          /*!<Starting state. Also comes here when the button has been pressed for the required time to turn OFF the Jukebox*/
  START_UP,         /*!<State to play the intro melody and initialize the Jukebox*/
  WAIT_COMMAND,     /*!<State to wait for a command from the USART*/
  SHUT_DOWN,        /*!<State to play de outro melody to turn off the jukebox*/
  SLEEP_WHILE_OFF,  /*!<State to start the low power mode while the Jukebox is OFF*/
  SLEEP_WHILE_ON    /*!<State to start the low power mode while the Jukebox is ON*/
};

/* Typedefs ------------------------------------------------------------------*/
/**
 * @brief This structure contains the information of a melody, including the name of the melody and the melody itself.
 * 
 */
typedef struct
{
    fsm_t f;                                    /*!<Jukebox FSM*/
    melody_t melodies[MELODIES_MEMORY_SIZE];    /*!<Array of melody names of size MELODIES_MEMORY_SIZE*/
    uint8_t melody_idx;                         /*!<Index of the melody to playing*/
    char *p_melody;                             /*!<Pointer to the name of the melody playing*/
    fsm_t *p_fsm_button;                        /*!<Pointer to the button FSM*/
    uint32_t on_off_press_time_ms;              /*!<Time in ms to consider ON/OFF*/
    fsm_t *p_fsm_usart;                         /*!<Pointer to the USART FSM*/
    fsm_t *p_fsm_buzzer;                        /*!<Pointer to the Buzzer FSM*/
    uint32_t next_song_press_time_ms;           /*!<Time in ms to consider next song*/
    double speed;                               /*!<Speed of the melody playing*/
} fsm_jukebox_t ;

/* Function prototypes and explanation ---------------------------------------*/

/**
 * @brief Create a new Jukebox FSM.
 * 
 * @param p_fsm_button Pointer to the button FSM
 * @param on_off_press_time_ms 	Button press time in milliseconds to turn the system ON or OFF
 * @param p_fsm_usart Pointer to the USART FSM
 * @param p_fsm_buzzer 	Pointer to the buzzer FSM.
 * @param next_song_press_time_ms Button press time in milliseconds to change to the next song.
 * @return fsm_t* A pointer to the button FSM
 */
fsm_t * fsm_jukebox_new(fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms);	

/**
 * @brief Initialize a Jukebox FSM
 * 
 * @param p_this Pointer to the Jukebox FSM
 * @param p_fsm_button Pointer to the button FSM
 * @param on_off_press_time_ms 	Button press time in milliseconds to turn the system ON or OFF
 * @param p_fsm_usart Pointer to the USART FSM
 * @param p_fsm_buzzer 	Pointer to the buzzer FSM.
 * @param next_song_press_time_ms Button press time in milliseconds to change to the next song.
 * @return fsm_t* A pointer to the button FSM
 */
void fsm_jukebox_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms);	

#endif /* FSM_JUKEBOX_H_ */