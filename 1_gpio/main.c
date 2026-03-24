#include <stdint.h>
#include <stdbool.h>

#define __GPIO_BASE_ADDRESS__ 0x50000000
#define __BUTTON_1_PIN__ 13
#define __BUTTON_2_PIN__ 14

// Reserved 1 between 0x524 and 0x700 minus DETECTMODE -> 0x700 - 0x528 = 472 bytes -> 472 / 4 = 118 registers
#define __RESERVED1_SIZE__ 118

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[__RESERVED1_SIZE__];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

#define GPIO ((NRF_GPIO_REGS*)__GPIO_BASE_ADDRESS__)


void button_init(){ 
	GPIO->PIN_CNF[__BUTTON_1_PIN__] = (3 << 2); // Configure button 1 as input with pull-up resistor
  GPIO->PIN_CNF[__BUTTON_2_PIN__] = (3 << 2); // Configure button 2 as input with pull-up resistor
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);

    // GPIO->OUTSET = (1 << i); // Set pins 17-20 high to turn off LED matrix (active low)
	}

	// Configure buttons -> see button_init()
  button_init();

	volatile int sleep = 0;

  bool btn1_state = false;
  bool btn2_state = false;
  bool prev_btn1_state = false;
  bool prev_btn2_state = false;

	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
    btn1_state = (GPIO->IN & (1 << __BUTTON_1_PIN__)) == 0; // Active low

    if(btn1_state && !prev_btn1_state) { // Button 1 pressed
        GPIO->OUTCLR = (0xF << 17); // Turn on LED matrix (pins 17-20)
    }
    prev_btn1_state = btn1_state;

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
    btn2_state = (GPIO->IN & (1 << __BUTTON_2_PIN__)) == 0; // Active low

    if(btn2_state && !prev_btn2_state) { // Button 2 pressed
        GPIO->OUTSET = (0xF << 17); // Turn off LED matrix (pins 17-20)
    }
    prev_btn2_state = btn2_state; 

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
