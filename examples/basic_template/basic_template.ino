#include "ThermalPrinter.h"

const int outputPin = 6;
const int inputPin = 5;

void setup() {
  ThermalPrinter printer(5, 6);
  printer.online();
  printer.reset();

  // do something with the printer
  printer.offline();
}

void loop() {
}
