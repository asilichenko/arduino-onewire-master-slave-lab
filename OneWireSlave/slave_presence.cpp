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

#include "slave_presence.h"

/**
  Wait until low pulse.
  Return true if low pulse duration between 480us and 960us.
*/
bool waitReset() {
  // wait until bus becomes low
  while (lineRead()) {}

  // save start time
  uint32_t startLow = micros();

  // wait until bus release pullup
  while (!lineRead()) {}

  // calculate duration of the low pulse
  uint32_t lowPulseDuration = micros() - startLow;

  return lowPulseDuration > 450 && lowPulseDuration <= 960;
}

/**
  Bus should be High due to Resistor Pullup.
  Wait 15-60 us as Presence Detect High.
  Low line for 60-240 us as Presence Detect Low.
  Release line, it should become High due to Resistor Pullup.
*/
void sendPresence() {
  // Presence Detect High: 15-60 us
  delayMicroseconds(25);

  // Presence Detect Low: 60-240 us
  lineLow();
  delayMicroseconds(125);

  // Resistor Pullup
  lineRelease();
}