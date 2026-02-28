/**
 * @file Tm4c123gh6pm_Init.h
 * @brief Board-specific initialization interface for TM4C123GH6PM
 * 
 * This header provides the interface for board-level initialization
 * of the TM4C123GH6PM microcontroller on the Tiva LaunchPad.
 * It handles essential system initialization including clock and SysTick.
 */

#ifndef TM4C123GH6PM_INIT_H_
#define TM4C123GH6PM_INIT_H_

#include <stdint.h>

/**
 * @brief Initialize board-specific hardware
 * 
 * Performs all necessary initialization for the Tiva LaunchPad:
 * - Configures the system clock (default 16 MHz)
 * - Initializes the SysTick timer for 1ms interrupts
 * 
 * This function should be called at the very beginning of main()
 * before any other peripheral initialization or application code.
 * 
 * @note Clock_Init() is called internally to set up system clock
 * @note SysTick_Init() is called internally for timekeeping
 * 
 * @warning Must be called before using any time-dependent functions
 * @warning Only call once at system startup (not multiple times)
 * 
 * @see Clock_Init() For detailed clock configuration
 * @see SysTick_Init() For SysTick timer setup
 * 
 * Usage example:
 * @code
 * int main(void) {
 *     Tm4c123gh6pm_Init();  // Initialize board first
 *     // ... rest of application
 * }
 * @endcode
 */
void Tm4c123gh6pm_Init(void);

#endif /* TM4C123GH6PM_INIT_H_ */