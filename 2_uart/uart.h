#ifndef UART_H
#define UART_H

#include <stdint.h>

#define __UART_BASE_ADDRESS__ 0x40002000

typedef struct {
  /* Tasks: 0x000 - 0x01C */
  volatile uint32_t TASKS_STARTRX;  // 0x000
  volatile uint32_t TASKS_STOPRX;   // 0x004
  volatile uint32_t TASKS_STARTTX;  // 0x008
  volatile uint32_t TASKS_STOPTX;   // 0x00C
  volatile uint32_t RESERVED0[3];   // Padding for 0x010, 0x014, 0x018
  volatile uint32_t TASKS_SUSPEND;  // 0x01C

  /* Events: 0x100 - 0x144 */
  volatile uint32_t RESERVED1[56];  // Gap from 0x020 to 0x0FC
  volatile uint32_t EVENTS_CTS;     // 0x100
  volatile uint32_t EVENTS_NCTS;    // 0x104
  volatile uint32_t EVENTS_RXDRDY;  // 0x108
  volatile uint32_t RESERVED2[4];   // Gap from 0x10C to 0x118
  volatile uint32_t EVENTS_TXDRDY;  // 0x11C
  volatile uint32_t RESERVED3[1];   // Padding for 0x120
  volatile uint32_t EVENTS_ERROR;   // 0x124
  volatile uint32_t RESERVED4[7];   // Gap from 0x128 to 0x140
  volatile uint32_t EVENTS_RXTO;    // 0x144

  /* Configuration & Control: 0x200 - 0x56C */
  volatile uint32_t RESERVED5[46];  // Gap from 0x148 to 0x1FC
  volatile uint32_t SHORTS;         // 0x200
  volatile uint32_t RESERVED6[64];  // Gap from 0x204 to 0x300
  volatile uint32_t INTENSET;       // 0x304
  volatile uint32_t INTENCLR;       // 0x308
  volatile uint32_t RESERVED7[93];  // Gap from 0x30C to 0x47C
  volatile uint32_t ERRORSRC;       // 0x480
  volatile uint32_t RESERVED8[31];  // Gap from 0x484 to 0x4FC
  volatile uint32_t ENABLE;         // 0x500
  volatile uint32_t RESERVED9[1];   // Padding for 0x504
  volatile uint32_t PSELRTS;        // 0x508
  volatile uint32_t PSELTXD;        // 0x50C
  volatile uint32_t PSELCTS;        // 0x510
  volatile uint32_t PSELRXD;        // 0x514
  volatile uint32_t RXD;            // 0x518
  volatile uint32_t TXD;            // 0x51C
  volatile uint32_t RESERVED10[1];  // Padding for 0x520
  volatile uint32_t BAUDRATE;       // 0x524
  volatile uint32_t RESERVED11[17]; // Gap from 0x528 to 0x568
  volatile uint32_t CONFIG;         // 0x56C
} NRF_UART_REG;

#define UART ((NRF_UART_REG*)__UART_BASE_ADDRESS__)


void uart_init();
void uart_send(char letter);
char uart_read();


#endif // UART_H
