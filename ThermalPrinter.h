#ifndef ThermalPrinter_h
#define ThermalPrinter_h

#include <SoftwareSerial.h>

#define BAUD_RATE 19200
#define DELAY 100

enum align {LEFT, MIDDLE, RIGHT};

class ThermalPrinter {
  public:
  ThermalPrinter(const int rx, const int tx);
  ~ThermalPrinter();
  
  //control commands
  void settings(uint8_t a, uint8_t b, uint8_t c);
  void density(uint8_t n);
  void sleep(uint8_t n);
  void wake();
  
  //line spacing commands
  void defaultLineSpacing();
  void alignMode(align a);
  void lineSpacing(uint8_t n);
  void leftBlankChars(uint8_t n);
 
  //character commands
  void mode(uint8_t n);
  void enlargeMode(uint8_t n);
  void doubleWidthMode(bool m);
  void bold(bool b);
  void underline(uint8_t n);
  void updownMode(bool updown);
  void reverseMode(bool reverse);
 
  //print commands
  void tab();
  void online();
  void offline();
  void lineFeed();
  void lineFeeds(uint8_t n);
  void dotFeed(uint8_t n);
  void reset();
  
  // status commandsvoid
  void transmitStatusToHost();
  void asbStatus(uint8_t n); 
  
  // test
  void testPage();
  
  private: 
  // serial methods
  void ascii(char c);
  void write(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e);
  void write(uint8_t a, uint8_t b, uint8_t c);
  void write(uint8_t a, uint8_t b);
  void write(uint8_t a);
  
  SoftwareSerial *_serial;
};
#endif