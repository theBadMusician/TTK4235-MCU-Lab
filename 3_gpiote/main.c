#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <sys/types.h> // ssize_t

#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void button_init(){ 
  /* Configure buttons as inputs with pull-up resistors */
  for (uint8_t i_btn = 0; i_btn < 4; i_btn++) {
    GPIO->PIN_CNF[BUTTON_1_PIN + i_btn] = (3 << 2);
  }
}

void led_init(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		// GPIO->OUTCLR = (1 << i);
    GPIO->OUTSET = (1 << i); // Set pins 17-20 high to turn off LED matrix (active low)
	}
}

void gpiote_init(){
  // Button Event
  GPIOTE->CONFIG[0] = GPIOTE_CONFIG_MODE_EVENT |
                      GPIOTE_CONFIG_PSEL(BUTTON_1_PIN) |
                      GPIOTE_CONFIG_POLARITY_HiToLo;

  for (uint8_t i_led = 0; i_led < 4; i_led++) {
    GPIOTE->CONFIG[i_led + 1] = GPIOTE_CONFIG_MODE_TASK |
                                GPIOTE_CONFIG_PSEL(LED_MATRIX_START_PIN + i_led) |
                                GPIOTE_CONFIG_POLARITY_TOGGLE |
                                GPIOTE_CONFIG_OUTINIT_HI;
  }
}

void ppi_init(){
  for (uint8_t i = 0; i < 4; i++) {
    PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[i + 1]);

    PPI->CHENSET = (1 << i);
  }
}

int main(){
	// Config btns and leds
  button_init();
  led_init();
  gpiote_init();
  ppi_init();

	volatile int sleep = 0;
	while(1){
    // for (uint8_t i_btn = 0; i_btn < 4; i_btn++) {
    //   btn_states[i_btn] = (GPIO->IN & (1 << (BUTTON_1_PIN + i_btn))) == 0; // Active low
    // }
    // 
    // if (!recv_led_state) {
    //   if (btn_states[0])  {GPIO->OUTCLR = (1 << 17);} // Turn on LED
    //   else                {GPIO->OUTSET = (1 << 17);} // Turn off LED
    //
    //   if (btn_states[1])  {GPIO->OUTCLR = (0b01 << 18);}
    //   else                {GPIO->OUTSET = (0b01 << 18);}
    //
    //   if (btn_states[2])  {GPIO->OUTCLR = (0b01 << 19);}
    //   else                {GPIO->OUTSET = (0b01 << 19);}
    //
    //   if (btn_states[3])  {GPIO->OUTCLR = (0b01 << 20);}
    //   else                {GPIO->OUTSET = (0b01 << 20);}
    // }
    // 
    // else {
    //   if (btn_states[0])  {GPIO->OUTSET = (1 << 17);} // Turn on LED
    //   else                {GPIO->OUTCLR = (1 << 17);} // Turn off LED
    //
    //   if (btn_states[1])  {GPIO->OUTSET = (0b01 << 18);}
    //   else                {GPIO->OUTCLR = (0b01 << 18);}
    //
    //   if (btn_states[2])  {GPIO->OUTSET = (0b01 << 19);}
    //   else                {GPIO->OUTCLR = (0b01 << 19);}
    //
    //   if (btn_states[3])  {GPIO->OUTSET = (0b01 << 20);}
    //   else                {GPIO->OUTCLR = (0b01 << 20);}
    // }
    //
    // if(btn_states[0] && !prev_btn_states[0]) { // Button 1 pressed
    // }
    // prev_btn_states[0] = btn_states[0];
    //
    // if(btn_states[1] && !prev_btn_states[1]) { // Button 2 pressed
    // }
    // prev_btn_states[1] = btn_states[1];
    //
    // if(btn_states[2] && !prev_btn_states[2]) { // Button 3 pressed
    // }
    // prev_btn_states[2] = btn_states[2];
    //
    // if(btn_states[3] && !prev_btn_states[3]) { // Button 4 pressed
    // }
    // prev_btn_states[3] = btn_states[3];

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}


