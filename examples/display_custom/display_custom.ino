/*
 * display_custom.ino
 * Example for digital tube.
 *  
 * Copyright (c) 2018 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: sep. 2018
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <Wire.h>


#include "grove_alphanumeric_display.h"

Seeed_Digital_Tube tube;


void setup()
{
    Wire.begin();
    
    // If using two digital tubes, use this configuration.
    // tube.setTubeType(TYPE_2,TYPE_2_DEFAULT_I2C_ADDR);

    // If using four digital tubes, use this configuration.
    tube.setTubeType(TYPE_4,TYPE_4_DEFAULT_I2C_ADDR);
    

    tube.setBrightness(15);
    tube.setBlinkRate(BLINK_1HZ);
    
    
}


void displayCustom()
{
    tube.clearBuf();
    tube.setTubeSingleChar(FIRST_TUBE,'t');
    tube.setTubeSingleChar(SECOND_TUBE,'T');

    //if using two digital tubes,there's no third&fourth channel.

    tube.setTubeSingleNum(THIRD_TUBE,5);
    tube.setTubeSingleNum(FOURTH_TUBE,5);

    // The location of point is different between two&four digital tubes.
    tube.setPoint(true,false);

    tube.display();
}

void loop()
{
    displayCustom();
    delay(2000);
}