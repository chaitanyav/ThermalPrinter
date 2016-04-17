#Arduino library for mini thermal printer#


### Components required to experiment with the mini thermal printer ###
* [Thermal Paper roll](https://www.adafruit.com/products/599)
* [Mini Thermal Prniter](https://www.adafruit.com/products/597)
* [Power Supply 5v 4A](https://www.adafruit.com/products/1466)
* [Female DC Power Adapter](https://www.adafruit.com/products/368)
* [Terminal Block](https://www.adafruit.com/products/724)
* [Jumper Wires Male to Male, Male to Female](http://www.amazon.com/gp/product/B00AC4NQYG/ref=s9_dcacsd_bhz_bw_c_x_1)
* [Arduino](http://www.amazon.com/keyestudio-development-board-compatible-arduino/dp/B0168B39N4)

###References###
------------
[Mini Thermal Product datasheet](https://cdn-shop.adafruit.com/datasheets/A2-user+manual.pdf)

####Examples####
--------------
* Basic setup
   ```
     ThermalPrinter printer(5, 6);
     printer.online();
     printer.reset();
     // do something with printer

     printer.offline();
   ```

* Printing the PC437, PC850 Characters
   ```
     ....
     printer.finePrintSettings();

     // select PC437 character code
     printer.characterCodeTable(0);
     printer.writeString("PC437 Code Table:");
     printer.lineFeed();

     for(int i = 0; i <= 0xFF; i++) {
       printer.writeCharacter(i);
     }
     printer.lineFeeds(4);

     // select  PC850 character code
     printer.characterCodeTable(1);
     printer.writeString("PC850 Code Table:");
     printer.lineFeed();

     for(int i = 0; i <= 0xFF; i++) {
       printer.writeCharacter(i);
     }
     printer.lineFeeds(4);
   ```
   ![Character Codes](http://i.imgur.com/mhJOxTc.jpg)

 * Justify text to left, middle and right
   ```
     // align left
     printer.alignMode(LEFT);
     printer.writeString("Left");
     printer.lineFeeds(3);

     // align middle
     printer.alignMode(MIDDLE);
     printer.writeString("Middle");
     printer.lineFeeds(3);

     //align right
     printer.alignMode(RIGHT);
     printer.writeString("Right");
     printer.lineFeeds(3);
   ```
    ![Justify Text](http://i.imgur.com/S2mpNWw.jpg)
 * Reverse Mode
   ```
     printer.reverseMode(true);

     printer.writeString("*******************************");
     printer.lineFeed();

     printer.writeString("This is reverse mode!!! :-) :-)");
     printer.lineFeed();

     printer.writeString("*******************************");
     printer.lineFeed();

     printer.reverseMode(false);
   ```
   ![Reverse Mode](http://i.imgur.com/NkfduOZ.jpg)
* Character control commands
  ```
    printer.bold(true);
    printer.writeString("This is bold text");
    printer.bold(false);
    printer.lineFeed();

    printer.writeString("This is normal text");
    printer.lineFeed();

    printer.underline(1);
    printer.writeString("This is underline 1");
    printer.lineFeed();

    printer.underline(2);
    printer.writeString("This in underline 2");
    printer.lineFeed();
    printer.underline(0); // no underline

    printer.mode(0x10);
    printer.writeString("Double height");
    printer.lineFeed();

    printer.mode(0x20);
    printer.writeString("Double width");
    printer.lineFeed();

    printer.mode(0x08);
    printer.writeString("Emphasized text");
    printer.lineFeed();
  ```
  ![Character control commands](http://i.imgur.com/JUfi8VS.jpg)