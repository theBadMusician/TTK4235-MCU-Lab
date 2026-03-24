#include "uart.h"
#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"


void uart_init() {
  GPIO->PIN_CNF[UART_RX_PIN] = 0;
  GPIO->PIN_CNF[UART_TX_PIN] = (0b0001);

  UART->PSELTXD   = UART_TX_PIN;
  UART->PSELRXD   = UART_RX_PIN;

  UART->BAUDRATE  = 0x00275000;

  UART->PSELRTS   = 0xffffffff;
  UART->PSELCTS   = 0xffffffff;
  
  UART->ENABLE    = 4;

  UART->TASKS_STARTRX = true;
}

void uart_send(char letter) {
  UART->TASKS_STARTTX = true;
  UART->TXD = letter;
  while (!UART->EVENTS_TXDRDY);

  UART->TASKS_STOPTX = true;
  UART->EVENTS_TXDRDY = false;
}

char uart_read() {
  // Enabled all of the time?
  // UART->TASKS_STARTRX = true;

  // early return
  if (!UART->EVENTS_RXDRDY) return '\0';

  UART->EVENTS_RXDRDY = 0;

  return UART->RXD;
}
