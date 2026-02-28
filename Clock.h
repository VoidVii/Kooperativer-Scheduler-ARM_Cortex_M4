/**
 * @file Clock.h
 * @brief System clock configuration interface
 * 
 * This header defines the interface for system clock initialization
 * and provides access to clock-related constants.
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

/**
 * @brief System core clock frequency in Hz
 * 
 * This constant defines the current system clock frequency.
 * Default is 16,000,000 Hz (16 MHz) after reset.
 * 
 * @note Used by SysTick_Reload_Value() to calculate 1ms period
 */
#define System_Core_Clock 16000000U

/**
 * @brief Initialize the system clock
 * 
 * Configures the system clock to the desired frequency.
 * Currently configured for default 16 MHz operation.
 * 
 * @note Must be called before any peripheral initialization
 * @see SysTick_Init() depends on this configuration
 */
void Clock_Init(void);

/**
 * @brief Calculate SysTick reload value for 1ms period
 * 
 * @return 24-bit reload value for SysTick timer
 * 
 * @note Result = (System_Core_Clock / 1000) - 1
 * @see SysTick_Init() uses this value
 */
uint32_t SysTick_Reload_Value(void);

#endif /* CLOCK_H_ */