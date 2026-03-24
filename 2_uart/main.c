#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "uart.h"

void button_init(){ 
	GPIO->PIN_CNF[BUTTON_1_PIN] = (3 << 2); // Configure button 1 as input with pull-up resistor
  GPIO->PIN_CNF[BUTTON_2_PIN] = (3 << 2); // Configure button 2 as input with pull-up resistor
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

  bool btn1_state = false;
  bool btn2_state = false;
  bool prev_btn1_state = false;
  bool prev_btn2_state = false;

	while(1){
    btn1_state = (GPIO->IN & (1 << BUTTON_1_PIN)) == 0; // Active low
    btn2_state = (GPIO->IN & (1 << BUTTON_2_PIN)) == 0; // Active low

    if(btn1_state && !prev_btn1_state) { // Button 1 pressed
      uart_send('A');
    }
    prev_btn1_state = btn1_state;

    if(btn2_state && !prev_btn2_state) { // Button 2 pressed
      uart_send('B');
    }
    prev_btn2_state = btn2_state; 

    if (btn1_state) {GPIO->OUTCLR = (1 << 17);} // Turn on LED
    else            {GPIO->OUTSET = (1 << 17);} // Turn off LED

    if (btn2_state) {GPIO->OUTCLR = (0b01 << 18);}
    else            {GPIO->OUTSET = (0b01 << 18);}

    char recvd = uart_read();
    if (recvd != '\0') {
      GPIO->OUTCLR = (3 << 19);

      sleep = 10000;
		  while(--sleep); // Delay

      GPIO->OUTSET = (0b11 << 19);
    }



		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}

