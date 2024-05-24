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
 * @brief Set the next song to be played.
 * 
 * @param p_fsm_jukebox Pointer to the Jukebox FSM
 */
void _set_next_song(fsm_jukebox_t *p_fsm_jukebox){
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
    if(p_fsm_jukebox->melody_idx >= MELODIES_MEMORY_SIZE){
        p_fsm_jukebox->melody_idx = 0;
    }
    if(p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].melody_length == 0){
        p_fsm_jukebox->melody_idx = 0;
    }
    p_fsm_jukebox->p_melody= p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;
    printf("Playing %s\n", p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name);
    fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, &p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx]);
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
    p_fsm_jukebox->melody_idx++;
}

/**
 * @brief Execute the command received by the USART.
 * 
 * @param p_fsm_jukebox Pointer to the Jukebox FSM.
 * @param p_command Pointer to the command to be executed.
 * @param p_param Pointer to the parameter of the command to be executed.
 */
void _execute_command(fsm_jukebox_t *p_fsm_jukebox, char *p_command, char *p_param ){
    if(!strcmp(p_command,"play")){
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);      
    }
    else if(!strcmp(p_command, "stop")){
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);        
    }
    else if(!strcmp(p_command, "pause")){
        fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PAUSE);               
    }
    else if(!strcmp(p_command, "speed")){
        double param = atof(p_param);
        fsm_buzzer_set_speed(p_fsm_jukebox->p_fsm_buzzer, MAX(param, 0.1));                
    }
    else if(!strcmp(p_command, "next")){
        _set_next_song(p_fsm_jukebox);               
    }
    else if(!strcmp(p_command, "select")){
        uint32_t melody_selected = atoi(p_param);
        if(p_fsm_jukebox->melodies[melody_selected].melody_length != 0){
            p_fsm_jukebox->melody_idx = melody_selected;
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);            
            fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, &p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx]);
            p_fsm_jukebox->p_melody= p_fsm_jukebox->melodies[p_fsm_jukebox->melody_idx].p_name;
            fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
        }
        else{
            fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, "Error: Melody not found\n");
        }              
    }
    else if(!strcmp(p_command, "info")){
        char msg[USART_OUTPUT_BUFFER_LENGTH];
        sprintf(msg,"Playing %s\n", p_fsm_jukebox->p_melody);
        fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, msg);
    }
    else {
        fsm_usart_set_out_data(p_fsm_jukebox->p_fsm_usart, "Error: Command not found\n");
    }
    return;
}	

/* State machine input or transition functions */
/**
 * @brief Check if any of the elements of the system is active
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_activity(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    //return (fsm_button_check_activity(p_fsm_jukebox->p_fsm_button) || fsm_buzzer_check_activity(p_fsm_jukebox->p_fsm_buzzer) || fsm_usart_check_activity(p_fsm_jukebox->p_fsm_usart));
    bool a = fsm_button_check_activity(p_fsm_jukebox->p_fsm_button);
    bool b = fsm_buzzer_check_activity(p_fsm_jukebox->p_fsm_buzzer);
    bool c = fsm_usart_check_activity(p_fsm_jukebox->p_fsm_usart);
    return (a || b || c);
}

/**
 * @brief Check if the USART has received data
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_command_received(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    return(fsm_usart_check_data_received(p_fsm_jukebox->p_fsm_usart));
}

/**
 * @brief Check if the buzzer has finished playing the melody
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_melody_finished(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    return(fsm_buzzer_get_action(p_fsm_jukebox->p_fsm_buzzer) == STOP);
}

/**
 * @brief Check if the button has been pressed for the required time to load the next song
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_next_song_button(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    uint32_t duracion = fsm_button_get_duration(p_fsm_jukebox->p_fsm_button);
    return((duracion > 0)&& (duracion > p_fsm_jukebox->next_song_press_time_ms) && (duracion < p_fsm_jukebox->on_off_press_time_ms));
}

/**
 * @brief Check if all the is system active
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_no_activity(fsm_t *p_this){
    return(!check_activity(p_this));
}

/**
 * @brief Check if the button has been pressed for the required time to turn ON the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_on(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    uint32_t duracion = fsm_button_get_duration(p_fsm_jukebox->p_fsm_button);
    return((duracion > 0) && (duracion > p_fsm_jukebox->on_off_press_time_ms));
}

/**
 * @brief Check if the button has been pressed for the required time to turn OFF the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 * @return true 
 * @return false 
 */
static bool check_off(fsm_t *p_this){
    return check_on(p_this);
}

/* State machine output or action functions */
/**
 * @brief Load the next song
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_load_next_song(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    _set_next_song(p_fsm_jukebox);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
}

/**
 * @brief Read the command received by the USART
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_read_command(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    char p_message[USART_INPUT_BUFFER_LENGTH];
    char p_command[USART_INPUT_BUFFER_LENGTH];
    char p_param[USART_INPUT_BUFFER_LENGTH];
    fsm_usart_get_in_data(p_fsm_jukebox->p_fsm_usart, p_message);
    bool valid = _parse_message(p_message, p_command, p_param);
    if(valid){
        _execute_command(p_fsm_jukebox, p_command, p_param);
    }
    fsm_usart_reset_input_data(p_fsm_jukebox->p_fsm_usart);
}

/**
 * @brief Start the low power mode while the Jukebox is OFF
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_off(fsm_t *p_this){
    port_system_sleep();
}

/**
 * @brief Start the low power mode while the Jukebox is waiting for a command
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_wait_command(fsm_t *p_this){
    port_system_sleep();
}

/**
 * @brief Start the low power mode while the Jukebox is OFF
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_while_off(fsm_t *p_this){
    port_system_sleep();
}

/**
 * @brief Start the low power mode while the Jukebox is ON
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_sleep_while_on(fsm_t *p_this){
    port_system_sleep();
}

/**
 * @brief After playing the intro melody, start the Jukebox
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_start_jukebox(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    p_fsm_jukebox->melody_idx = 0;
    p_fsm_jukebox->p_melody = scale_melody.p_name;
}

/**
 * @brief Initialize the Jukebox by playing the intro melody, at the beginning of the program
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_start_up(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
    fsm_usart_enable_rx_interrupt(p_fsm_jukebox->p_fsm_usart);
    printf("JUKEBOX ON\n");
    fsm_buzzer_set_speed(p_fsm_jukebox->p_fsm_buzzer, 1.0);
    fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, &scale_melody);
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
}

/**
 * @brief Turn the Jukebox OFF after playing the outro melody.
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_t
 */
static void do_stop_jukebox(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
    fsm_usart_disable_rx_interrupt(p_fsm_jukebox->p_fsm_usart);
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, STOP);
}

/**
 * @brief Shut down the Jukebox by playing the outro melody, at the end of the program
 * 
 * @param p_this Pointer to an fsm_t struct that contains an fsm_jukebox_
 */
static void do_shutdown_jukebox(fsm_t *p_this){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t  *)(p_this);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
    fsm_usart_disable_rx_interrupt(p_fsm_jukebox->p_fsm_usart);
    printf("JUKEBOX OFF\n");
    fsm_buzzer_set_speed(p_fsm_jukebox->p_fsm_buzzer, 1.0);
    fsm_buzzer_set_melody(p_fsm_jukebox->p_fsm_buzzer, &inverse_scale_melody);
    fsm_buzzer_set_action(p_fsm_jukebox->p_fsm_buzzer, PLAY);
    fsm_button_reset_duration(p_fsm_jukebox->p_fsm_button);
}

/**
 * @brief Array representing the transitions table of the FSM Jukebox
 * > This FSM diagram is not the same as implemented in Version 4 of the project. This is the Version 5 Jukebox FSM which includes a new state SHUT DOWN. For more information look at section Version 5 in the main page of the API \n
 * @image html fsm_jukebox_states.png
 * 
 */
fsm_trans_t fsm_trans_jukebox[] = {
    { OFF, check_on, START_UP, do_start_up},
    { OFF, check_no_activity, SLEEP_WHILE_OFF, do_sleep_off},
    { START_UP, check_melody_finished, WAIT_COMMAND, do_start_jukebox},
    { WAIT_COMMAND, check_next_song_button, WAIT_COMMAND, do_load_next_song},
    { WAIT_COMMAND, check_command_received, WAIT_COMMAND, do_read_command},
    { WAIT_COMMAND, check_no_activity, SLEEP_WHILE_ON, do_sleep_wait_command},
    { WAIT_COMMAND, check_off, SHUT_DOWN, do_shutdown_jukebox},
    { SHUT_DOWN, check_melody_finished, OFF, do_stop_jukebox},
    { SLEEP_WHILE_ON, check_no_activity, SLEEP_WHILE_ON, do_sleep_while_on},
    { SLEEP_WHILE_ON, check_activity, WAIT_COMMAND, NULL},
    { SLEEP_WHILE_OFF, check_no_activity, SLEEP_WHILE_OFF, do_sleep_while_off},
    { SLEEP_WHILE_OFF, check_activity, OFF, NULL},
    { -1 , NULL , -1, NULL }
};

/* Public functions */
fsm_t *fsm_jukebox_new(fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms){
    fsm_t *p_fsm = malloc(sizeof(fsm_jukebox_t));
    fsm_jukebox_init(p_fsm, p_fsm_button, on_off_press_time_ms, p_fsm_usart, p_fsm_buzzer, next_song_press_time_ms);
    return p_fsm;
}

void fsm_jukebox_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms){
    fsm_jukebox_t *p_fsm_jukebox = (fsm_jukebox_t *)(p_this);
    fsm_init(p_this, fsm_trans_jukebox);
    p_fsm_jukebox->p_fsm_button = p_fsm_button;
    p_fsm_jukebox->p_fsm_usart = p_fsm_usart;
    p_fsm_jukebox->p_fsm_buzzer = p_fsm_buzzer;
    p_fsm_jukebox->on_off_press_time_ms = on_off_press_time_ms;
    p_fsm_jukebox->next_song_press_time_ms = next_song_press_time_ms;
    p_fsm_jukebox->melody_idx = 0;
    memset(p_fsm_jukebox->melodies, 0, sizeof(p_fsm_jukebox->melodies));
    p_fsm_jukebox->melodies[0] = tetris_melody;
    p_fsm_jukebox->melodies[1] = happy_birthday_melody;
    p_fsm_jukebox->melodies[2] = avemaria_melody;
    p_fsm_jukebox->melodies[3] = pp_hymn_melody;
}