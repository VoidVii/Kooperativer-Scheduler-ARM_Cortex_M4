/* 
Possible solution when using too many LEDs:

// Individual variables for clear access
LED_t red_LED = { .write = RED_LED_ON, ... };
LED_t blue_LED = { .write = BLUE_LED_ON, ... };
LED_t green_LED = { .write = GREEN_LED_ON, ... };

// Additional array for collective operations
LED_t *allLEDs[] = { &red_LED, &blue_LED, &green_LED };
const uint8_t NUM_LEDS = 3;

// Then: Individual access
LED_toggle(&red_LED);

// Or all together
for(int i = 0; i < NUM_LEDS; i++) {
    LED_off(allLEDs[i]);  // Turn all off
}
*/
#include "Tm4c123gh6pm_Init.h"
#include "SysTick.h"
#include "GPIO.h"
#include "Clock.h"
#include "LED.h"
#include "Coop_Scheduler.h"
#include "Debounce_Switch.h"
#include <stdint.h>

/************************** Functions for Object-Handling ********************/
/**
 * @brief Write function for red LED (Port F, Pin 1)
 * @param Value 1 = ON, 0 = OFF (according to activeHigh setting)
 */
void RED_LED_ON(uint8_t Value){
    GPIO_WritePin(GPIO_PORTF, 1U, Value);
}

/**
 * @brief Write function for blue LED (Port F, Pin 2)
 * @param Value 1 = ON, 0 = OFF (according to activeHigh setting)
 */
void BLUE_LED_ON(uint8_t Value){
    GPIO_WritePin(GPIO_PORTF, 2U, Value);
}

/**
 * @brief Write function for green LED (Port F, Pin 3)
 * @param Value 1 = ON, 0 = OFF (according to activeHigh setting)
 */
void GREEN_LED_ON(uint8_t Value){
    GPIO_WritePin(GPIO_PORTF, 3U, Value);
}

/**
 * @brief Read function for Switch 1 (Port F, Pin 4)
 * @return 1 = released (pull-up), 0 = pressed
 */
uint8_t read_Switch1(void){
    return GPIO_ReadPin(GPIO_PORTF, 4U);
}

/**
 * @brief Read function for Switch 2 (Port F, Pin 0)
 * @return 1 = released (pull-up), 0 = pressed
 */
uint8_t read_Switch2(void){
    return GPIO_ReadPin(GPIO_PORTF, 0U);
}

/****************************** Build Objects  ********************************/
/* LED Objects - each with its own write function and state */
LED_t red_LED = {
    .write = RED_LED_ON,        // Function to write to this specific LED
    .currentState = 0U,          // Current state: 0 = OFF, 1 = ON
    .activeHigh = 1U,             // 1 = HIGH turns LED on, 0 = LOW turns LED on
};

LED_t blue_LED = {
    .write = BLUE_LED_ON,
    .currentState = 0U,
    .activeHigh = 1U,
};

LED_t green_LED = {
    .write = GREEN_LED_ON,
    .currentState = 0U,
    .activeHigh = 1U,
};

/* Switch Objects - each with its own read function and debounce state */
Switch_t Switch1 ={
    .read = read_Switch1,        // Function to read this specific switch
    .lastDebounceTime = 0U,       // Timestamp of last state change (for debouncing)
    .lastReading = 1U,            // Last raw reading from GPIO (1 = released with pull-up)
    .switchState = 1U              // Current debounced state (1 = released)
};

Switch_t Switch2 ={
    .read = read_Switch2,
    .lastDebounceTime = 0U,
    .lastReading = 1U,
    .switchState = 1U
};

/**************************** Functions for Task-Handling  ********************/
/**
 * @brief Task function for red LED - blinks every 300ms
 * Uses static variable to remember last blink time
 */
void redLED(void){
    static uint32_t lastBlink = 0U;    // Timestamp of last blink (persists between calls)
    uint32_t now = GetTickCounter();    // Current system time in ms
    
    if(now - lastBlink >= 300U){        // 300ms elapsed?
        LED_toggle(&red_LED);            // Toggle the red LED
        lastBlink = now;                  // Update last blink time
    }
}

/**
 * @brief Task function for Switch 1 - detects falling edge (press)
 * Toggles blue LED when switch is pressed
 */
void Switch_1(void){
    static uint8_t lastState_1 = 1U;     // Previous switch state (1 = released)
    uint32_t state = debounce_switch(&Switch1);  // Get current debounced state
    
    // Falling edge detection: was released (1), now pressed (0)
    if(state == 0U && lastState_1 == 1U){
        LED_toggle(&blue_LED);            // Toggle blue LED on press
    }
    
    lastState_1 = state;                   // Save current state for next detection
}

/**
 * @brief Task function for Switch 2 - detects falling edge (press)
 * Toggles green LED when switch is pressed
 */
void Switch_2(void){
    static uint8_t lastState_2 = 1U;     // Previous switch state (1 = released)
    uint32_t state = debounce_switch(&Switch2);  // Get current debounced state
    
    // Falling edge detection: was released (1), now pressed (0)
    if(state == 0U && lastState_2 == 1U){
        LED_toggle(&green_LED);           // Toggle green LED on press
    }
    
    lastState_2 = state;                   // Save current state for next detection
}

/******************************* Build Tasks *********************************/
/**
 * Task array for the cooperative scheduler
 * Each task has a period, last run time, and function to call
 */
Task_t Task[] = {
    /* Task for red LED blinking */
    {
        .period = 250U,           // Check every 250ms (actual blink timing inside task)
        .lastRun = 0U,             // Initialize last run time to 0
        .sched = redLED            // Function to call
    },
    /* Task for Switch 1 debouncing and detection */
    {
        .period = 20U,             // Check every 20ms (good for debouncing)
        .lastRun = 0U,
        .sched = Switch_1
    },
    /* Task for Switch 2 debouncing and detection */
    {
        .period = 21U,             // Slightly different period to avoid phase lock
        .lastRun = 0U,
        .sched = Switch_2
    }
};

/* Calculate correct number of tasks: Total size / Element size */
uint32_t numTasks = sizeof(Task) / sizeof(Task[0]);

/**
 * @brief Main function - program entry point
 * Initializes hardware and runs the scheduler forever
 */
int main()
{
    // Initialize system modules
    Tm4c123gh6pm_Init();
    
    GPIO_EnablePort(GPIO_PORTF);      // Enable clock for Port F
    
    // Configure GPIO pins
    GPIO_ConfigureInput(GPIO_PORTF, 4U);   // Switch 1 as input
    GPIO_ConfigureInput(GPIO_PORTF, 0U);   // Switch 2 as input
    GPIO_ConfigureOutput(GPIO_PORTF, 1U);  // Red LED as output
    GPIO_ConfigureOutput(GPIO_PORTF, 2U);  // Blue LED as output
    GPIO_ConfigureOutput(GPIO_PORTF, 3U);  // Green LED as output
    
    // Initialize all LEDs to OFF state
    LED_off(&red_LED);
    LED_off(&blue_LED);
    LED_off(&green_LED);
    
    // Main super loop - runs forever
    while(1)
    {
        uint32_t now = GetTickCounter();           // Get current system time
        Task_update(Task, numTasks, now);          // Run the scheduler
    }
}