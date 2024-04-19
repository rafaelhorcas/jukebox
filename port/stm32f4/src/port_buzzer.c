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
#define ALT_FUNC2_TIM3 0x02

port_buzzer_hw_t buzzers_arr[]= {
    [BUZZER_0_ID] = {.p_port = BUZZER_0_GPIO, .pin = BUZZER_0_PIN, .alt_func = ALT_FUNC2_TIM3, .note_end = false},
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
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->CR1 &= ~ TIM_CR1_CEN; //poner a 0
    TIM2->CR1 |= TIM_CR1_ARPE; //poner a 1
    TIM2->SR &= ~ TIM_SR_UIF;
    TIM2->DIER |= TIM_DIER_UIE;

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
   if (buzzer_id == BUZZER_0_ID)
  {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->CR1 &= ~ TIM_CR1_CEN;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CNT = 0;
    TIM3->ARR = 0;
    TIM3->PSC = 0;
    TIM3->EGR = TIM_EGR_UG;
    TIM3->CCER &= ~TIM_CCER_CC1E;
    TIM3->CCMR1 |= BASE_MASK_TO_POS(6, 4);
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
  }
}	


/* Public functions -----------------------------------------------------------*/

void port_buzzer_init(uint32_t buzzer_id)
{
  port_system_gpio_config(buzzers_arr[buzzer_id].p_port, buzzers_arr[buzzer_id].pin, GPIO_MODE_ALTERNATE, GPIO_PUPDR_NOPULL);
  port_system_gpio_config_alternate(buzzers_arr[buzzer_id].p_port, buzzers_arr[buzzer_id].pin, buzzers_arr[buzzer_id].alt_func);
  _timer_duration_setup(buzzer_id);
  _timer_pwm_setup(buzzer_id);
}

bool port_buzzer_get_note_timeout(uint32_t buzzer_id){
  if (buzzer_id == BUZZER_0_ID){
    return buzzers_arr[buzzer_id].note_end;
  }
  return false;
}

void port_buzzer_set_note_duration(uint32_t buzzer_id, uint32_t duration_ms){
  //1. Deshabilitar el timer y resetear la cuenta
  TIM2->CR1 &= ~TIM_CR1_CEN;
  TIM2->CNT = 0;
  //2. Convertir a double duration_ms y SystemCoreClock 
  double sysclk_as_double = (double)SystemCoreClock;
  double s_as_double = (double)duration_ms/1000;
  //3. Calcular el valor inicial de PSC
  double ARR_max = 65535.0; 
  double PSC_min = round(((sysclk_as_double * s_as_double) / (ARR_max + 1)) - 1);
  //4. Recalcular ARR 
  double ARR = round(((sysclk_as_double * s_as_double) / (PSC_min + 1)) - 1);
  //5. Comprobar que ARR>65535.0
  if(ARR > 65535.0){
    PSC_min++;
    ARR = round(((sysclk_as_double * s_as_double) / (PSC_min + 1)) - 1);
  }
  //6. Precargar ARR y PSC en los registros correspondientes
  TIM2->ARR = ARR;
  TIM2->PSC = PSC_min;
  //7. Cargar ARR y PSC en los registros correspondientes
  TIM2->EGR = TIM_EGR_UG;
  //8. Configurar flag note_end
  buzzers_arr[buzzer_id].note_end = false;
  //9. Habilitar el timer
  TIM2->CR1 |= TIM_CR1_CEN;
}

void port_buzzer_set_note_frequency	(	uint32_t buzzer_id, double frequency_hz){
  //1. Si la frecuencia es 0 se deshabilita el timer
  if(frequency_hz == 0){
  TIM3->CR1 &= ~TIM_CR1_CEN;
  return;   
  }

  //2.
  double sysclk_as_double = (double)SystemCoreClock;
  double ARR_max = 65535.0; 
  double PSC_min = round(((sysclk_as_double * (1/frequency_hz)) / (ARR_max + 1)) - 1);
  //Recalcular ARR 
  double ARR = round(((sysclk_as_double * (1/frequency_hz)) / (PSC_min + 1)) - 1);
  //Comprobar que ARR>65535.0
  if(ARR > 65535.0){
    PSC_min++;
    ARR = round(((sysclk_as_double * (1/frequency_hz)) / (PSC_min + 1)) - 1);
  }
  //Precargar ARR y PSC en los registros correspondientes
  TIM3->ARR = ARR;
  TIM3->PSC = PSC_min;

  //3. PWM pulse width to BUZZER_PWM_DC.
  TIM3->CCR1 = BUZZER_PWM_DC * (ARR + 1); 
  //4.
  TIM3->EGR = TIM_EGR_UG;
  //5.
  TIM3->CCER |= TIM_CCER_CC1E;
  //6.
  TIM3->CR1 |= TIM_CR1_CEN;
}

void port_buzzer_stop(uint32_t buzzer_id){
  if(buzzer_id == BUZZER_0_ID){
    TIM2-> CR1 &= ~TIM_CR1_CEN;
    TIM3-> CR1 &= ~TIM_CR1_CEN;
  }
  return;
}