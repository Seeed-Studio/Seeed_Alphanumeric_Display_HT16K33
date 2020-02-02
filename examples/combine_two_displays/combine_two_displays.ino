#include <Wire.h>

#include "grove_alphanumeric_display.h"

Seeed_Digital_Tube tube1;
Seeed_Digital_Tube tube2;

/**
    NOTICE:Every tubes display has the same default i2c address.
          if you want to combine two(or more)display in one project,you should change the
             i2c address,by soldering the pad of device's backside.
          please refer to our wiki to get more details.
 * */
#define I2C_ADDR_AFTER_CHANGE_FOUR  0x75
#define I2C_ADDR_DEFAULT_FOUR       0x71



void setup() {
    Wire.begin();

    // If using four digital tubes, use this configuration.
    tube1.setTubeType(TYPE_4, I2C_ADDR_AFTER_CHANGE_FOUR);

    tube1.setBrightness(15);
    tube1.setBlinkRate(BLINK_OFF);

    // If using four digital tubes, use this configuration.
    tube2.setTubeType(TYPE_4, I2C_ADDR_DEFAULT_FOUR);

    tube2.setBrightness(15);
    tube2.setBlinkRate(BLINK_OFF);

}


void loop() {
    tube1.displayNum(1234);
    delay(100);

    tube2.displayNum(5678);
    delay(100);

    while (1);
}




