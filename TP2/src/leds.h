#include <stdint.h>

/**
 * @brief Initialize the leds
 * @param address: The address of the port to which the leds are connected
 * @return 0 if the leds were initialized successfully, -1 otherwise
 */
int Leds_Init(uint16_t *address);

/**
 * @brief Turn on a specific led
 * @param led: The number of the led to turn on
 * @return 0 if the led was turned on successfully, -1 otherwise
 */
int Leds_TurnOn(int led);

/**
 * @brief Turn off a specific led
 * @param led: The number of the led to turn off
 * @return 0 if the led was turned off successfully, -1 otherwise
 */
int Leds_TurnOff(int led);

/**
 * @brief Turn on all the leds
 * @return 0 if all the leds were turned on successfully, -1 otherwise
 */
int Led_TurnAllOn(void);

/**
 * @brief Check if a specific led is on
 * @param led: The number of the led to check
 * @return 1 if the led is on, 0 otherwise
 */
int Leds_IsLedOn(int led);
