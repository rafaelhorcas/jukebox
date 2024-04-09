/**
 * @file port_buzzer.c
 * @brief Portable functions to interact with the Buzzer melody player FSM library.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date 09/04/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <math.h>

/* HW dependent libraries */
#include "port_buzzer.h"

/* Global variables */
#define   ALT_FUNC2_TIM3


// Buscar en el datasheet alt_func
port_buzzer_hw_t buzzers_arr[]= {
    [BUZZER_0_ID] = {.p_port = BUZZER_0_GPIO, .pin = BUZZER_0_PIN, .alt_func = 0x00, .note_end = false},
};

/* Private functions */

/**
 * @brief Configure the timer that controls the duration of the note.
 * 
 * @param buzzer_id	Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array
 */
static void _timer_duration_setup(uint32_t buzzer_id)
{
  if (buzzer_id == BUZZER_0_ID)
  {
    // TO-DO alumnos
    


    /* Configure interruptions */
    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0)); 
    NVIC_EnableIRQ(TIM2_IRQn);                                                          
  }
}

/**
 * @brief Configure the timer that controls the PWM of the buzzer.
 * 
 * @param buzzer_id	Buzzer melody player ID. This index is used to select the element of the buzzers_arr[] array
 */
static void _timer_pwm_setup(uint32_t buzzer_id){

}	





/* Public functions -----------------------------------------------------------*/

void port_buzzer_init(uint32_t buzzer_id)
{
  port_buzzer_hw_t buzzer = buzzers_arr[buzzer_id];

  /* TO-DO alumnos */

}

bool port_buzzer_get_note_timeout(uint32_t buzzer_id){

}

void port_buzzer_set_note_duration(uint32_t buzzer_id, uint32_t duration_ms){

}


void port_buzzer_set_note_frequency	(	uint32_t buzzer_id, double frequency_hz){

}

void port_buzzer_stop(uint32_t buzzer_id){

}