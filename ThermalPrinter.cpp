#include "ThermalPrinter.h"

ThermalPrinter::ThermalPrinter(const int rx, const int tx){
  _serial = new SoftwareSerial(rx, tx);
  _serial->begin(BAUD_RATE);
}

ThermalPrinter::~ThermalPrinter() {
  delete _serial;
}

void ThermalPrinter::testPage() {
  write(0x12, 0x54);
}

// Set “max heating dots”,”heating time”, “heating interval”
// a = 0-255 Max printing dots，Unit(8dots)，Default:8(64 dots)
// b = 3-255 Heating time，Unit(10us),Default:80(800us)
// c = 0-255 Heating interval,Unit(10us)，Default:2(20us)
// The more max heating dots, the more peak current will cost
// whenprinting, the faster printing speed. The max heating dots is
// 8*(n1+1)
// The more heating time, the more density , but the slower printing
// speed. If heating time is too short, blank page may occur.
// The more heating interval, the more clear, but the slower
// printingspeed.
void ThermalPrinter::settings(uint8_t a, uint8_t b, uint8_t c) {
  if ((b >= 3 && b <= 255)) {
    write(0x1b, 0x37, a, b, c);
  }
}

void ThermalPrinter::finePrintSettings() {
  settings(0x64, 0x64, 0x0A);
}

//D4..D0 of n is used to set the printing density
//Density is 50% + 5% * n(D4-D0) printing density
//D7..D5 of n is used to set the printing break time
//Break time is n(D7-D5)*250us
void ThermalPrinter::density(uint8_t n) {
  write(0x12, 0x23, n);
}

// Setting the time for control board to enter sleep mode.
// n = 0-255 The time waiting for sleep after printing finished，
// Unit(Second)，Default:0(don’t sleep)
void ThermalPrinter::sleep(uint8_t n) {
  if (n > 0) {
    write(0x1b, 0x38, n);
  }
}

// When control board is in sleep mode, host must send one byte(0xff)
// to wake up control board. And waiting 50ms, then send printing
// command and data.
void ThermalPrinter::wake() {
  write(0xff);
  delay(DELAY);
}

// default is 32 dots
void ThermalPrinter::defaultLineSpacing() {
  write(0x1b, 0x32);
}

// sets line spacing to n dots 0 - 255
void ThermalPrinter::lineSpacing(uint8_t n) {
  write(0x1b, 0x33, n);
}

void ThermalPrinter::alignMode(align a) {
  if (a == LEFT || a == MIDDLE || a == RIGHT) {
    write(0x1b, 0x61, a);
  }
}

void ThermalPrinter::leftBlankChars(uint8_t n) {
  if (n >= 0 && n <= 47) {
    write(0x1b, 0x42, n);
  }
}

// 0000 0010 for reverse mode
// 0000 0100 for updown mode
// 0000 1000 for emphasized mode
// 0001 0000 for double height mode
// 0010 0000 for double width mode
// 0100 0000 for delete line mode
void ThermalPrinter::mode(uint8_t n) {
  write(0x1b, 0x21, n);
}

// bits 0..3 1 height enlarge
// bits 4..7 1 width enlarge
void ThermalPrinter::enlargeMode(uint8_t n) {
  write(0x1d, 0x21, n);
}

void ThermalPrinter::doubleWidthMode(bool m) {
  if (m) {
    write(0x1b, 0x0e);
  } else {
    write(0x1b, 0x14);
  }
}

void ThermalPrinter::bold(bool b) {
  if (b) {
    write(0x1b, 0x45, 0x01);
  } else {
    write(0x1b, 0x45, 0x00);
  }
}

// n = 0 no underline
// n = 1 thin line
// n = 2 thick line
void ThermalPrinter::underline(uint8_t n) {
  if (n >= 0 && n <= 2) {
    write(0x1b, 0x2d, n);
  }
}

void ThermalPrinter::updownMode(bool updown) {
  if (updown) {
    write(0x1b, 0x7b, 0x01);
  } else {
    write(0x1b, 0x7b, 0x00);
  }
}

void ThermalPrinter::reverseMode(bool reverse) {
  if (reverse) {
    write(0x1d, 0x42, 0x01);
  } else {
    write(0x1d, 0x42, 0x00);
  }
}

// Select an internal character set n as follows:
// 0:USA       5:Sweden 10:Denmark II
// 1:France    6:Italy  11:Spain II
// 2:Germany   7:Spain1 12:Latin America
// 3:U.K.      8:Japan  13:Korea
// 4:Denmark 1 9:Norway
void ThermalPrinter::characterSet(uint8_t n) {
  if(n >= 0 && n <= 13) {
    write(0x1b, 0x52, n);
  }
}

// Select a character code:
// 0 for PC437 1 for PC850
void ThermalPrinter::characterCodeTable(uint8_t n) {
  if(n == 0 || n == 1) {
    write(0x1b, 0x74, n);
  }
}

void ThermalPrinter::writeCharacter(char c) {
  _serial->print(c);
}

void ThermalPrinter::writeString(const char *str) {
  _serial->print(str);
}

void ThermalPrinter::write(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e) {
  _serial->write(a);
  _serial->write(b);
  _serial->write(c);
  _serial->write(d);
  _serial->write(e);
}

void ThermalPrinter::write(uint8_t a, uint8_t b, uint8_t c) {
  _serial->write(a);
  _serial->write(b);
  _serial->write(c);
}

void ThermalPrinter::write(uint8_t a) {
  _serial->write(a);
}

void ThermalPrinter::write(uint8_t a, uint8_t b) {
  _serial->write(a);
  _serial->write(b);
}

// begin print commands
void ThermalPrinter::tab() {
  write(0x09);
}

void ThermalPrinter::online() {
  write(0x1b, 0x3d, 0x01);
}

void ThermalPrinter::offline() {
  write(0x1b, 0x3d, 0x00);
}

void ThermalPrinter::lineFeed() {
  write(0x0A);
}

void ThermalPrinter::lineFeeds(uint8_t n) {
  write(0x1b, 0x64, n);
}

void ThermalPrinter::dotFeed(uint8_t n) {
  write(0x1b, 0x4a, n);
}

// Initializes the printer
// The print buffer is cleared
// Reset the param to default value
// return to standard mode
// Delete user-defined characters
void ThermalPrinter::reset() {
  write(0x1b, 0x40);
}

void ThermalPrinter::asbStatus(uint8_t n) {
  if (n == 4 || n == 32 || n == 36) {
    write(0x1d, 0x61, n);
  }
}

// Transmit board status to host
// Return:
// P<Paper>V<Voltage>T<Degree>
// Example: P1V72T30 Mean:Paper Ready,Current voltage 7.2V,Printer degree:30
void ThermalPrinter::transmitStatusToHost() {
  write(0x1b, 0x76, 0x00);
}
