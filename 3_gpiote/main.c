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

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}


