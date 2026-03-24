#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <sys/types.h> // ssize_t

#include "gpio.h"
#include "uart.h"

ssize_t _write(int fd, const void *buf, size_t count) {
  char * letter = (char *)(buf);
  for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
  }
  return count;
}

void button_init(){ 
  /* Configure buttons as inputs with pull-up resistors */
  for (uint8_t i_btn = 0; i_btn < 4; i_btn++) {
    GPIO->PIN_CNF[BUTTON_1_PIN + i_btn] = (3 << 2);
  }

}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		// GPIO->OUTCLR = (1 << i);

    GPIO->OUTSET = (1 << i); // Set pins 17-20 high to turn off LED matrix (active low)
	}

	// Configure buttons -> see button_init()
  button_init();

  // UART init 
  uart_init();

	volatile int sleep = 0;

  bool btn_states[4]      = { false };
  bool prev_btn_states[4] = { false };
  bool recv_led_state   = false;

	while(1){
    for (uint8_t i_btn = 0; i_btn < 4; i_btn++) {
      btn_states[i_btn] = (GPIO->IN & (1 << (BUTTON_1_PIN + i_btn))) == 0; // Active low
    }

    if(btn_states[0] && !prev_btn_states[0]) { // Button 1 pressed
      uart_send('A');
    }
    prev_btn_states[0] = btn_states[0];

    if(btn_states[1] && !prev_btn_states[1]) { // Button 2 pressed
      uart_send('B');
    }
    prev_btn_states[1] = btn_states[1];

    if(btn_states[2] && !prev_btn_states[2]) { // Button 3 pressed
      iprintf("The average grade in TTK%d was in %d was: %c\n\r", 4235, 2022, 'B');
    }
    prev_btn_states[2] = btn_states[2];

    if (btn_states[0])  {GPIO->OUTCLR = (1 << 17);} // Turn on LED
    else                {GPIO->OUTSET = (1 << 17);} // Turn off LED

    if (btn_states[1])  {GPIO->OUTCLR = (0b01 << 18);}
    else                {GPIO->OUTSET = (0b01 << 18);}

    char recvd = uart_read();
    if (recvd != '\0') {
      if (recv_led_state) GPIO->OUTCLR = (0b11 << 19);
      else                GPIO->OUTSET = (0b11 << 19);
      recv_led_state = !recv_led_state;
    }

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}

