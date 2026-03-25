#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

#define GPIO ((NRF_GPIO_REG*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REG;

#define BUTTON_1_PIN 13
#define BUTTON_2_PIN 14
#define BUTTON_3_PIN 15
#define BUTTON_4_PIN 16

#define LED_MATRIX_START_PIN 17
#define LED_MATRIX_END_PIN 20

#endif
