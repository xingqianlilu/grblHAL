/*

  serial.h - low level functions for transmitting bytes via the serial port

  Part of Grbl

  Copyright (c) 2017-2019 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdint.h>
#include <stdbool.h>

#define USE_USB

#define TX_BUFFER_SIZE 128      // must be a power of 2
#define RX_BUFFER_SIZE 1024     // must be a power of 2
#define RX_BUFFER_HWM 900
#define RX_BUFFER_LWM 300

#define BUFCOUNT(head, tail, size) ((head >= tail) ? (head - tail) : (size - tail + head))

typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    bool overflow;
//    bool rts_state;
    bool backup;
    char data[RX_BUFFER_SIZE];
} stream_rx_buffer_t;

typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    char data[TX_BUFFER_SIZE];
} stream_tx_buffer_t;

void serialInit(void);
int16_t serialGetC(void);
void serialWriteS(const char *s);
uint16_t serialRxFree(void);
void serialRxFlush(void);
void serialRxCancel(void);

