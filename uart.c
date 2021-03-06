#include "include/uart.h"
void uart_Init(volatile unsigned *sta, volatile unsigned *mode,
               volatile unsigned *brg, unsigned mode_con,
               unsigned sta_con, int baud_rate) {
  uart_Baud(brg, baud_rate);
  *sta = 0;
  *mode = mode_con;
  *sta |= sta_con;
}
/* Transmit one byte. */
void uart_TX(volatile unsigned *tx, volatile unsigned *sta, uint8_t byte) {
  /* Write buffer check. */
  while (*sta & (1 << 9)); 
  *tx = byte;
  while (!(*sta & (1 << 8)));
}

/* Transmit multiple bytes. */
void uart_String(volatile unsigned *tx, volatile unsigned *sta,
                 register uint8_t  *bytes, uint8_t cr) {
  while (*bytes) {
    uart_TX(tx, sta, *bytes);
    bytes++;
  }
  if (cr) {
    uart_TX(tx, sta, 0xA);
  }
}

void uart_Baud(volatile unsigned *brg, int baud_rate) {
  *brg = (PB_CLK / (16 * baud_rate)) - 1;
}

