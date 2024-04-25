/**
 * @file fsm_jukebox.c
 * @brief Jukebox FSM main file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 25/02/2024
 */

/* Includes ------------------------------------------------------------------*/
// Standard C includes
#include <stdlib.h>
#include <string.h> // strcmp
#include <stdio.h>  // sprintf

// Other includes
#include "fsm.h"
#include "fsm_jukebox.h"
#include "fsm_button.h"
#include "fsm_usart.h"
#include "fsm_buzzer.h"
#include "port_system.h"
#include "port_usart.h"

/* Defines ------------------------------------------------------------------*/
#define MAX(a, b) ((a) > (b) ? (a) : (b)) /*!< Macro to get the maximum of two values. */

/* Private functions */
/**
 * @brief Parse the message received by the USART.
 * 
 * Given data received by the USART, this function parses the message and extracts the command and the parameter (if available).
 * 
 * > 1. Split the message by space using function `strtok()` \n
 * > 2. If there's a token (command), copy it to the `p_command` variable. Otherwise, return `false` \n
 * > 3. Extract the parameter (if available). To do so, get the next token using function `strtok()`. If there's a token, copy it to the `p_param` variable. Otherwise, copy an empty string to the `p_param` variable \n
 * > 4. Return `true` indicating that the message has been parsed correctly \n
 * 
 * @param p_message Pointer to the message received by the USART.
 * @param p_command Pointer to store the command extracted from the message. 
 * @param p_param Pointer to store the parameter extracted from the message. 
 * @return true if the message has been parsed correctly 
 * @return false if the message has not been parsed correctly 
 */
bool _parse_message(char *p_message, char *p_command, char *p_param){
    char *p_token = strtok(p_message, " "); // Split the message by space

    // If there's a token (command), copy it to the command variable
    if (p_token != NULL)
    {
        strcpy(p_command, p_token);
    }
    else
    {
        // No command found, you might return an error or handle it as needed
        // The USART driver of the computer sends an empty at initialization, so we will ignore it
        return false;
    }

    // Extract the parameter (if available)
    p_token = strtok(NULL, " "); // Get the next token

    if (p_token != NULL)
    {
        strcpy(p_param, p_token);
    }
    else
    {
        strcpy(p_param, " "); // NO param found
    }
    return true;
}

/**
 * @brief Execute the command received by the USART.
 * 
 * @param p_fsm_jukebox Pointer to the Jukebox FSM.
 * @param p_command Pointer to the command to be executed.
 * @param p_param Pointer to the parameter of the command to be executed.
 */
void _execute_command(fsm_jukebox_t *p_fsm_jukebox, char *p_command, char *p_param ){

}	

/**
 * @brief Set the next song to be played.
 * 
 * @param p_fsm_jukebox Pointer to the Jukebox FSM
 */
void _set_next_song(fsm_jukebox_t *p_fsm_jukebox){

}	

/**
 * @brief Array representing the transitions table of the FSM Jukebox
 * 
 */
fsm_trans_t fsm_trans_jukebox[] = {

};

/* State machine input or transition functions */
/**
 * @brief Check if any of the elements of the system is active
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_activity(fsm_t *p_this){

}

/**
 * @brief Check if the USART has received data
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_command_received(fsm_t *p_this){

}

/**
 * @brief Check if the buzzer has finished playing the melody
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_melody_finished(fsm_t *p_this){

}

/**
 * @brief Check if the button has been pressed for the required time to load the next song
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_next_song_button(fsm_t *p_this){

}

/**
 * @brief Check if all the is system active
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_no_activity(fsm_t *p_this){

}

/**
 * @brief Check if the button has been pressed for the required time to turn OFF the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_off(fsm_t *p_this){

}

/**
 * @brief Check if the button has been pressed for the required time to turn ON the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_on(fsm_t *p_this){

}

/* State machine output or action functions */
/**
 * @brief Load the next song
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_load_next_song(fsm_t *p_this){

}

/**
 * @brief Read the command received by the USART
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_read_command(fsm_t *p_this){

}

/**
 * @brief Start the low power mode while the Jukebox is OFF
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_off(fsm_t *p_this){

}

/**
 * @brief Start the low power mode while the Jukebox is waiting for a command
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_wait_command(fsm_t *p_this){

}

/**
 * @brief Start the low power mode while the Jukebox is OFF
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_while_off(fsm_t *p_this){

}

/**
 * @brief Start the low power mode while the Jukebox is ON
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_while_on(fsm_t *p_this){

}

/**
 * @brief After playing the intro melody, start the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_start_jukebox(fsm_t *p_this){

}

/**
 * @brief Initialize the Jukebox by playing the intro melody, at the beginning of the program
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_start_up(fsm_t *p_this){

}

/**
 * @brief Turn the Jukebox OFF
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_stop_jukebox(fsm_t *p_this){

}

/* Public functions */
fsm_t *fsm_jukebox_new(fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms){
    fsm_t *p_fsm = malloc(sizeof(fsm_jukebox_t));

    fsm_jukebox_init(p_fsm, p_fsm_button, on_off_press_time_ms, p_fsm_usart, p_fsm_buzzer, next_song_press_time_ms);
    
    return p_fsm;
}

fsm_t *fsm_jukebox_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms){

}