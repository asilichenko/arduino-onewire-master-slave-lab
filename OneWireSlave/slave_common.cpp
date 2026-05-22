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

#include "slave_common.h"

void lineRelease() {
  pinMode(DQ, INPUT);
}

void lineLow() {
  pinMode(DQ, OUTPUT);
  digitalWrite(DQ, LOW);
}

bool lineRead() {
  return digitalRead(DQ);
}

void blink(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(25);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

String byteToBin(uint8_t b) {
  String s = "";
  for (int i = 7; i >= 0; i--) s += ((b >> i) & 1) ? '1' : '0';
  return s;
}

String byteToHex(uint8_t b) {
  char buf[3];
  sprintf(buf, "%02X", b);  // uppercase hex with leading zero
  return String(buf);
}