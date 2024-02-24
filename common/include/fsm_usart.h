/**
 * @file fsm_usart.h
 * @brief Header for fsm_usart.c file.
 * @author Rafael Horcas Mateo (r.horcasm@alumnos.upm.es)
 * @author Victor Mendizabal Gimeno (v.mendizabal@alumnos.upm.es)
 * @date fecha
 */

#ifndef FSM_USART_H_
#define FSM_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include <fsm.h>

/* HW dependent includes */
#include "port_usart.h"

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
/**
 * @brief Enumerator for the USART finite state machine.
 * This enumerator defines the different states that the USART finite state machine can be in. Each state represents a specific condition or step in the USART communication process.
 */
enum FSM_USART {
     WAIT_DATA = 0, /*!<Starting state. Also comes here when data has been send or read*/
     SEND_DATA      /*!<State to send data*/
};

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the USART FSM.
 */
typedef struct
{
    fsm_t f;                                    /*!<USART FSM*/
    bool data_received;                         /*!<Flag to indicate that a data has been received*/
    char in_data [USART_INPUT_BUFFER_LENGTH];   /*!<Input data*/
    char out_data [USART_OUTPUT_BUFFER_LENGTH]; /*!<Output data*/
    uint8_t usart_id;                           /*!<USART ID. Must be unique*/
} fsm_usart_t ;

/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Create a new USART FSM.
 * @param usart_id	Unique USART identifier number
 * @return A pointer to the USART FSM
*/
fsm_t * fsm_usart_new (uint32_t usart_id);

/**
 * @brief Initialize a USART FSM.
 * @param p_this	Pointer to an fsm_t struct than contains an fsm_usart_t struct
 * @param usart_id	Unique USART identifier number
*/
void fsm_usart_init (fsm_t *p_this, uint32_t usart_id);

/**
 * @brief Check if data has been received.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_usart_t struct
 * @return true
 * @return false
*/
bool fsm_usart_check_data_received (fsm_t *p_this);

/**
 * @brief Get the data received.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_usart_t struct
 * @param p_data Pointer to the array where the data will be copied from the in_data array
*/
void fsm_usart_get_in_data (fsm_t *p_this, char *p_data);

/**
 * @brief Set the data to send.
 * @param p_this	Pointer to an fsm_t struct than contains an fsm_usart_t struct
 * @param p_data	Pointer to an array from where the data will be copied to the out_data array
*/
void fsm_usart_set_out_data (fsm_t *p_this, char *p_data);

/**
 * @brief Reset the input data buffer.
 * @param p_this  
*/
void fsm_usart_reset_input_data (fsm_t *p_this);

/**
 * @brief Check if the USART FSM is active, or not.
 * @param p_this Pointer to an fsm_t struct than contains an fsm_usart_t struct
 * @return true
 * @return false
*/
bool fsm_usart_check_activity (fsm_t *p_this);

/**
 * @brief Disable the USART RX interrupt.
 * @param p_this
*/
void fsm_usart_disable_rx_interrupt (fsm_t *p_this);

/**
 * @brief Disable the USART TX interrupt.
 * @param p_this
*/
void fsm_usart_disable_tx_interrupt (fsm_t *p_this);

/**
 * @brief Enable the USART RX interrupt.
 * @param p_this
*/
void fsm_usart_enable_rx_interrupt (fsm_t *p_this);

/**
 * @brief Enable the USART TX interrupts.
 * @param p_this
*/
void fsm_usart_enable_tx_interrupt (fsm_t *p_this);


#endif /* FSM_USART_H_ */

