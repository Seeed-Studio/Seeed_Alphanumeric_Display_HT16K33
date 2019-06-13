/*
 * number_increment_2.ino
 * Driver for digital tube.
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
#include "grove_dual_alphanumeric_display.h"

/*********************************************************/
/*****NOTICE : This example only for dual_alphanumeric****/
/*********************************************************/

#define NUMERIC_I2C_ADDR  0x70

Digital_Tube2 tube;
char hex_str[255] = {0};

void setup()
{
    Wire.begin();
    tube.init(NUMERIC_I2C_ADDR);
    tube.setBrightness(15);
    tube.setBlinkRate(BLINK_OFF);
    
}

char* numToHexString(unsigned int num)
{
    if(num <= 0xf){
        sprintf(hex_str,"0%x",num);
        for(int i=0;i<2;i++)
        {
            if(hex_str[i] >= 'a' && hex_str[i] <= 'z')
            {
                hex_str[i] -=0x20;
            }
        }
        return hex_str;
    }
    sprintf(hex_str,"%x",num);
    for(int i=0;i<2;i++)
    {
        if(hex_str[i] >= 'a' && hex_str[i] <= 'z')
        {
            hex_str[i] -=0x20;
        }
    }
    return hex_str;
}


void loop()
{
    for(int i=0;i<0xff;i++)
    {
        tube.displayString(numToHexString(i),0);
        delay(300);
    }
}