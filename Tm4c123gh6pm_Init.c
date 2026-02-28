/**
 * @file Tm4c123gh6pm_Init.c
 * @brief Board-specific initialization implementation for TM4C123GH6PM
 * 
 * This module implements the board-level initialization for the
 * TM4C123GH6PM microcontroller on the Tiva LaunchPad. It orchestrates
 * the initialization of core system components in the correct order.
 * 
 * The initialization sequence is critical for proper system operation:
 * 1. Clock system must be configured first (everything depends on it)
 * 2. SysTick timer can then be configured using the known clock frequency
 * 
 * @note Always include the corresponding header first to ensure
 *       consistency between interface and implementation
 */

/* A .c file includes its own HEADER first to verify declarations match */
#include "Tm4c123gh6pm_Init.h"

/* System and peripheral headers */
#include "tm4c123gh6pm.h"  /* Hardware register definitions */
#include "SysTick.h"        /* SysTick timer interface */
#include "GPIO.h"           /* GPIO interface (for potential future use) */
#include "Clock.h"          /* Clock configuration interface */

/**
 * @brief Initialize all board-specific hardware
 * 
 * Performs complete system initialization in the correct sequence:
 * 
 * 1. **Clock Initialization** (Clock_Init())
 *    - Configures the system clock (default 16 MHz)
 *    - Must be first because all peripherals depend on the clock
 * 
 * 2. **SysTick Initialization** (SysTick_Init())
 *    - Sets up 1ms system tick for timekeeping
 *    - Depends on clock frequency for correct reload value
 * 
 * This function centralizes all startup initialization, making it
 * easy to ensure proper initialization order and to add new
 * initialization steps in the future.
 * 
 * @note This function should be called exactly once at system startup
 * @note No other initialization should be performed before this
 * 
 * @warning Calling this function multiple times may cause issues
 * @warning Do not call any time-dependent functions before this
 * 
 * @see Clock_Init() For detailed clock configuration
 * @see SysTick_Init() For SysTick timer setup
 * 
 * Usage example:
 * @code
 * int main(void) {
 *     Tm4c123gh6pm_Init();  // Initialize everything
 *     
 *     // Now safe to use peripherals and time functions
 *     GPIO_ConfigureOutput(GPIO_PORTF, 1U);
 *     LED_on(&red_LED);
 *     delay_ms(500);
 *     
 *     while(1) {
 *         // Application code
 *     }
 * }
 * @endcode
 */
void Tm4c123gh6pm_Init(void)
{
    /* 1. Initialize the Clock system first
     *    Clock must be configured before any peripheral that depends on it,
     *    including SysTick which needs the clock frequency for timing.
     */
    Clock_Init();
    
    /* 2. Initialize SysTick timer for 1ms system tick
     *    Depends on Clock_Init() to have correct System_Core_Clock value.
     *    Provides timebase for delays, timeouts, and scheduler.
     */
    SysTick_Init();
    
    /* Future initialization steps can be added here:
     * - GPIO pin configurations
     * - Interrupt priority settings
     * - Peripheral clock enables
     * - etc.
     */
}