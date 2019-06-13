/*
 * display_custom_4.ino
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


/*********************************************************/
/*****NOTICE : This example only for qual_alphanumeric****/
/*********************************************************/
#include "grove_quad_alphanumeric_display.h"
#define NUMERIC_I2C_ADDR  0x71

Digital_Tube4 tube;


void setup()
{
    Wire.begin();
    tube.init(NUMERIC_I2C_ADDR);
    tube.setBrightness(15);
    tube.setBlinkRate(BLINK_1HZ);
    
}


void displayCustom()
{
    tube.clearBuf();
    tube.setTubeSingleChar(FIRST_TUBE,'t');
    tube.setTubeSingleChar(SECOND_TUBE,'T');
    tube.setTubeSingleNum(THIRD_TUBE,5);
    tube.setTubeSingleNum(FOURTH_TUBE,5);
    tube.setPoint(true,true);
    tube.display();
}

void loop()
{
    displayCustom();
    delay(2000);
}