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
#include "slave_presence.h"
#include "slave_read.h"
#include "slave_write.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println();
  Serial.println("+------------------------+");
  Serial.println("| 1-Wire [ slave ] start |");
  Serial.println("+------------------------+");

  lineRelease();
}

void testPresence() {
  if (!waitReset()) return;
  sendPresence();
  Serial.println("ping");
}

void testReadWriteBit() {
  if (!waitReset()) return;
  sendPresence();

  uint8_t data = readBit();
  if (data == 0xFF) {
    Serial.println("Read error");
    return;
  }

  writeBit(data & 1);

  Serial.print("Read: 0b");
  Serial.println(data, BIN);
}

uint8_t testReadByte() {
  if (!waitReset()) return;
  sendPresence();

  int data = readByte();
  if (data < 0) {
    Serial.println("Read error");
    return;
  }

  Serial.print("Read:  0b");
  Serial.print(byteToBin(data));
  Serial.print("; 0x");
  Serial.println(byteToHex(data));

  return data;
}

void testReadWriteByte() {
  Serial.println();

  int dataIn = testReadByte();
  if (dataIn < 0) {
    Serial.println("Read error");
    return;
  }

  uint8_t dataOut = ~dataIn;
  writeByte(dataOut);

  Serial.print("Write: 0b");
  Serial.print(byteToBin(dataOut));
  Serial.print("; 0x");
  Serial.println(byteToHex(dataOut));
}

void loop() {
  String testCase = "presence";

  if (testCase == "presence") testPresence();
  else if (testCase == "read_write_bit") testReadWriteBit();
  else if (testCase == "read_byte") testReadByte();
  else if (testCase == "read_write_byte") testReadWriteByte();
  else {
    Serial.print("Test case is not defined: \"");
    Serial.print(testCase);
    Serial.println("\"");
    blink(10);
    delay(2000);
    return;
  }

  blink(2);
}
