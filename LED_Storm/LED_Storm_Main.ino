/******************************************************************************
* Author:         Rich Gagliano
* Date Created:   08/29/2014
* Date Modified:  09/08/2014
* File Name:      LED_Storm_Main.ino
*
* Overview:
*    This application governs the logic for the LED Storm game.  The LED Storm
*    game is a simple game often found in child party establishments, like the
*    great Chuck E. Cheese, or Peter Piper Pizza.  The game consists of a ring
*    of LEDs, 2 buttons, and 2 game states.
*
*    State 1:
*      The game is idling waiting for the user to press start.  During this
*      state, the LEDs are turning on and off one at a time in a counter 
*      clock-wise direction. Pressing start moves to State 2.
*
*    State 2:
*      The user has pressed start, and a game has begun.  The LEDs are now
*      moving in a clock-wise direction.  The user must press the action button
*      when a specific LED is lit up.  When the user presses the action button,
*      The LED's stop moving, and if the LED lit up is the winning LED, then a
*      winning sequence is shown, otherwise, the losing sequence is shown. Once
*      the winning or losing sequences finish, the game returns to state 1.
*
*    The application employs custom button, shift_register, and LED_list
*    objects.  Using these, the game is expandable to the desired number of 
*    LEDs.
*
* Updates:
*    (09-08-2014) - Rich Gagliano
*        Added in piezo functionality for victory and failure sounds.
*
******************************************************************************/

#include <button.h>
#include <LED_list.h>
#include <shift_register.h>
#include <victory_sounds.h>

/* Global constants */
const int SR_DATAPIN = 4;    // The data pin for the shift registers
const int SR_LATCHPIN = 5;   // The latch pin for the shift registers
const int SR_CLOCKPIN = 6;   // The clock pin for the shift registers
const int SR_MCLEARPIN = 3;  // The master clear pin for the shift registers
const int BTN_STARTPIN = 10;   // The start button's input pin
const int BTN_ACTIONPIN = 9;  // The action button's input pin
const int PIEZO_PIN = 12;     // The victory and failure piezo sound pin
const int NUM_REGISTERS = 3;  // The number of shift registers
const int WINCON = 8;         // The winning LED pin location
const int WAIT_TIME = 75;     // The delay time between moving LED's

/* Hardware objects */
LED_list ll(NUM_REGISTERS * 8, WINCON - 1, SR_DATAPIN, SR_LATCHPIN, 
            SR_CLOCKPIN, SR_MCLEARPIN, PIEZO_PIN);
button btn_start(BTN_STARTPIN);
button btn_action(BTN_ACTIONPIN);

void setup() {
  /* All setup is handled within the hardware objects */
}

/******************************************************************************
* void loop
* Handles the main program logic:
* Waits for the start button to be pressed
*  - Once pressed, begin a new game
*  - While idling, LEDs move counter-clockwise
******************************************************************************/
void loop() {
  /* Move LEDs counter-clockwise */
  ll.turn_on_prev();
  
  /* Delay by specified amount */
  delay(WAIT_TIME);  
  
  /* Check if the start button has been pressed */
  if (btn_start.is_pressed())
    start_game();
}

/******************************************************************************
* void start_game
* Handles the game logic:
* Waits for the action button to be pressed
*  - Once pressed, the game state is evaluated, and end game sequence shown
*  - While idling, LEDs move clock-wise
******************************************************************************/
void start_game() {
  while (!btn_action.is_pressed()) {
    /* Move LEDs clock-wise */
    ll.turn_on_next();
   
    /* Delay by specified amount */
    delay(WAIT_TIME);  
  }
  
  /* Handle game results */
  ll.end_game();
}
