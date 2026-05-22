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

#include <OneWire.h>

#define DQ 10
OneWire oneWireBus(DQ);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println();
  Serial.println("+-------------------------+");
  Serial.println("| 1-Wire [ master ] start |");
  Serial.println("+-------------------------+");
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

void testPresence() {
  bool isSlavePresent = oneWireBus.reset();
  Serial.println("ping: " + String(isSlavePresent ? "present" : "absent"));
}

void testWriteBit(uint8_t data) {
  if (!oneWireBus.reset()) return;
  oneWireBus.write_bit(data);
  Serial.println("Wrote: 0b" + String(data, BIN));
}

void testReadBit(uint8_t data) {
  Serial.println();
  testWriteBit(data);
  data = oneWireBus.read_bit();
  Serial.println("Read:  0b" + String(data, BIN));
}

void testWriteByte(uint8_t data) {
  if (!oneWireBus.reset()) return;
  oneWireBus.write(data);
  Serial.println("Wrote: 0b" + byteToBin(data) + "; 0x" + byteToHex(data));
}

void testWriteReadByte(uint8_t dataOut) {
  Serial.println();

  testWriteByte(dataOut);
  uint8_t dataIn = oneWireBus.read();

  uint8_t checkSum = dataOut + dataIn;

  Serial.println("Read:  0b" + byteToBin(dataIn) + "; 0x" + byteToHex(dataIn));
  Serial.println("Check: 0b" + byteToBin(checkSum) + "; 0x" + byteToHex(checkSum));
}

void loop() {
  String testCase = "presence";

  if (testCase == "presence") testPresence();

  else if (testCase == "write_bit_1") testWriteBit(1);
  else if (testCase == "write_bit_0") testWriteBit(0);

  else if (testCase == "read_bit_1") testReadBit(1);
  else if (testCase == "read_bit_0") testReadBit(0);

  else if (testCase == "wrtite_byte") testWriteByte(0xAC);
  else if (testCase == "write_read_byte") testWriteReadByte(0xAC);

  else Serial.println("Test case undefined: " + testCase);

  delay(1000);
}
