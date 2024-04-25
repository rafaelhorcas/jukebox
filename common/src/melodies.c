/**
 * @file melodies.c
 * @brief Melodies source file.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */

/* Includes ------------------------------------------------------------------*/
#include "melodies.h"

/* Melodies ------------------------------------------------------------------*/
// Melody Happy Birthday
#define HAPPY_BIRTHDAY_LENGTH 25 /*!< Happy Birthday melody length */

/**
 * @brief Happy Birthday melody notes.
 *
 * This array contains the frequencies of the notes for the Happy Birthday song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double happy_birthday_notes[HAPPY_BIRTHDAY_LENGTH] = {
    DO4, DO4, RE4, DO4, FA4, MI4, DO4, DO4, RE4, DO4, SOL4, FA4, DO4, DO4, DO5, LA4, FA4, MI4, RE4, LAs4, LAs4, LA4, FA4, SOL4, FA4};

/**
 * @brief Happy Birthday melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Happy Birthday song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t happy_birthday_durations[HAPPY_BIRTHDAY_LENGTH] = {
    300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 400, 400, 300, 100, 400, 400, 400, 800};

/**
 * @brief Happy Birthday melody struct.
 *
 * This struct contains the information of the Happy Birthday melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t happy_birthday_melody = {.p_name = "happy_birthday",
                                        .p_notes = (double *)happy_birthday_notes,
                                        .p_durations = (uint16_t *)happy_birthday_durations,
                                        .melody_length = HAPPY_BIRTHDAY_LENGTH};

// Tetris melody
#define TETRIS_LENGTH 40 /*!< Tetris melody length */

/**
 * @brief Tetris melody notes.
 *
 * This array contains the frequencies of the notes for the Tetris song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double tetris_notes[TETRIS_LENGTH] = {
        MI5, SI4, DO5, RE5, DO5, SI4, LA4, LA4, DO5, MI5, RE5, DO5, SI4, DO5, RE5, MI5, DO5, LA4,
        LA4, LA4, SI4, DO5, RE5, FA4, LA5, SOL5, FA5, MI5, DO5, MI5, RE5, DO5, SI4, SI4, LA4, RE5,
        MI5, DO5, LA4, LA4};

/** 
 * @brief Tetris melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Tetris song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t tetris_durations[TETRIS_LENGTH] = {
    400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 600, 200, 400, 400, 400, 400, 200, 200, 200, 200,
    600, 200, 400, 200, 200, 600, 200, 400, 200, 200, 400, 200, 200, 400, 400, 400, 400, 400};

/**
 * @brief Tetris melody struct.
 * 
 * This struct contains the information of the Tetris melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t tetris_melody = {.p_name = "tetris",
                                .p_notes = (double *)tetris_notes,
                                .p_durations = (uint16_t *)tetris_durations,
                                .melody_length = TETRIS_LENGTH};

// Scale Melody
#define SCALE_MELODY_LENGTH 8   /*!< Scale melody length */

/**
 * @brief Scale melody notes.
 *
 * This array contains the frequencies of the notes for the scale song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double scale_melody_notes[SCALE_MELODY_LENGTH] = {
    DO4, RE4, MI4, FA4, SOL4, LA4, SI4, DO5};

/**
 * @brief Scale melody durations in miliseconds.
 * 
 * This array contains the duration of each note in the scale song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t scale_melody_durations[SCALE_MELODY_LENGTH] = {
    250, 250, 250, 250, 250, 250, 250, 250};

/**
 * @brief Scale melody struct.
 * 
 * This struct contains the information of the scale melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t scale_melody = {.p_name = "scale",
                               .p_notes = (double *)scale_melody_notes,
                               .p_durations = (uint16_t *)scale_melody_durations,
                               .melody_length = SCALE_MELODY_LENGTH};


// Ave Maria by David Bisbal melody
#define AVEMARIA_LENGTH 44 /*!< Ave Maria by David Bisbal melody length */

/**
 * @brief Ave Maria by David Bisbal melody notes.
 *
 * This array contains the frequencies of the notes for the Ave Maria by David Bisbal song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double avemaria_notes[AVEMARIA_LENGTH] = {
    MI5, RE5, DO5, RE5, DO5, MI5, MI5, RE5, DO5, RE5, DO5, MI5, RE5, DO5, RE5, MI5, FA5, FA5, MI5, DO5, RE5, DO5, MI5, RE5, DO5, RE5, DO5, MI5, MI5, RE5, DO5, RE5, DO5, MI5, RE5, DO5, RE5, MI5, FA5, FA5, MI5, DO5, RE5, DO5};

/** 
 * @brief Ave Maria by David Bisbal melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Ave Maria by David Bisbal song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t avemaria_durations[AVEMARIA_LENGTH] = {
    200, 200, 200, 200, 400, 400, 200, 200, 200, 200, 600, 200, 200, 200, 200, 400, 400, 200, 200, 200, 400, 400, 200, 200, 200, 200, 400, 400, 200, 200, 200, 200, 600, 200, 200, 200, 200, 400, 400, 200, 200, 200, 400, 400 };

/**
 * @brief Ave Maria by David Bisbal melody struct.
 * 
 * This struct contains the information of the Ave Maria by David Bisbal melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t avemaria_melody = {.p_name = "Ave Maria by David Bisbal",
                                .p_notes = (double *)avemaria_notes,
                                .p_durations = (uint16_t *)avemaria_durations,
                                .melody_length = AVEMARIA_LENGTH};

// Himno del Partido Popular (PP) melody
#define PP_HYMN_LENGTH 70 /*!< PP Hymn melody length */

/**
 * @brief PP Hymn melody notes.
 *
 * This array contains the frequencies of the notes for the PP Hymn melody.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the melody.
 */
static const double pp_hymn_notes[PP_HYMN_LENGTH] = {
    DO4, MI4, DO4, FA4, DO4, MI4, RE4, DO4, FA4, FA4, DO4, MI4, SOL4, DO3, SOL4, LA4, SOL4, FA4, RE3, RE3, DO3, MI3, DO3, FA3, DO3, MI3, RE3, DO3, FA3, FA3, DO3, MI3, DO3, FA3, DO3, MI3, RE3, DO3, RE3,
    DO4, MI4, DO4, FA4, DO4, MI4, RE4, DO4, FA4, FA4, DO4, MI4, SOL4, DO3, SOL4, LA4, SOL4, FA4, RE3, RE3, DO3, MI3, SI4, RE3, LA4, DO3, SI4, LA4, FA3, MI3, DO3, LA4, DO3,};

/** 
 * @brief PP Hymn melody durations in milliseconds.
 *
 * This array contains the duration of each note in the PP Hymn melody.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the melody.
 */
static const uint16_t pp_hymn_durations[PP_HYMN_LENGTH] = {
    100, 300, 100, 300, 100, 100, 100, 100, 200, 200, 100, 300, 100, 300, 100, 100, 100, 100, 200, 200, 100, 300, 100, 300, 100, 100, 100, 100, 200, 200, 100, 300, 100, 300, 100, 100, 100, 100, 400,
    100, 300, 100, 300, 100, 100, 100, 100, 200, 200, 100, 300, 100, 300, 100, 100, 100, 100, 200, 200, 100, 300, 100, 300, 100, 100, 100, 100, 600, 100, 100, 100, 100  
    };
// 100 corchea, 200 negra, 300 negra+punto, 400 blanca
/**
 * @brief PP Hymn melody struct.
 * 
 * This struct contains the information of the PP Hymn melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t pp_hymn_melody = {.p_name = "PP Hymn",
                                  .p_notes = (double *)pp_hymn_notes,
                                  .p_durations = (uint16_t *)pp_hymn_durations,
                                  .melody_length = PP_HYMN_LENGTH};
