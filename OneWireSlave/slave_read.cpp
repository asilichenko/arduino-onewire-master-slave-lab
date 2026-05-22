/*
  MIT License

  Copyright (c) 2026 Oleksii Sylichenko

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "slave_read.h"

/**
  After exiting, the bus line should be released.

  Sampling window:
  t=0µs   falling edge (master starts the slot)
  t=1µs   master may release the line (write 1, minimum per spec)
  t=6µs   typical master release timing for write 1
  t=10µs  ← sample here (safe zone)
  t=15µs  latest point at which the master guarantees the bus state
  t=60µs  end of slot, master releases the line for write 0
  t=61µs  recovery
*/
uint8_t readBit() {
  long start = micros();
  while (lineRead()) {                               // wait for the falling edge from the master
    if (micros() - start > TIMEOUT_US) return 0xFF;  // timeout
  }

  delayMicroseconds(10);

  uint8_t bit = lineRead();

  start = micros();
  while (!lineRead()) {                              // if line is LOW wait until it is released
    if (micros() - start > TIMEOUT_US) return 0xFF;  // protection against lock-up
  }

  delayMicroseconds(3);  // small delay to avoid signal bouncing

  return bit;
}

/**
  After exit the bus line should be released.
*/
int readByte() {
  uint8_t v = 0;
  for (int i = 0; i < 8; i++) {
    uint8_t data = readBit();
    if (data == 0xFF) return -1;
    if (data) v |= (1 << i);
  }
  return v;
}