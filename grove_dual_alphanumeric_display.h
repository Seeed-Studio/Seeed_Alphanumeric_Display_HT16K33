/* 
 * grove_dual_alphanumeric_display.h
 * A library for Grove - dual_alphanumeric_display
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jerry Yip
 * Create Time: 2018-06
 * Version    : 0.1
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

#ifndef __GROVE_DUAL_ALPHANUMERIC_DISPLAY_H__
#define __GROVE_DUAL_ALPHANUMERIC_DISPLAY_H__

#include <Arduino.h>
#include "Wire.h"

#include "HT16K33_driver.h"

#define HT16K33_DEFAULT_I2C_ADDR    0x70
#define MAX_BIG_BUFFER_SIZE         (8*20)   



typedef enum
{
    SECOND_TUBE,
    FIRST_TUBE,
}TubeNum_2;




class Digital_Tube2 : public HT16K33 {

public:
    Digital_Tube2();

    void clear();


    void displayNum(unsigned long int num,unsigned int interval);
    void displayString(char *str,unsigned int interval);

    void setDispBuf(TubeNum_2 num,char byte);
    void displayFull();
    void display_two_tube(char byte1,char byte2);

private:
    // Low1 High1 Low2 High2 ... Low8 High8
    uint8_t _buffer[16]; 
    uint8_t _big_buffer[MAX_BIG_BUFFER_SIZE];
    uint16_t _cursor_start, _cursor_end, _cursor_steps;
    uint16_t _ms;
    orientation_type_t _orientation;
    int8_t _offset_x, _offset_y;
    bool isLegalToDisplay(char byte);
};

#endif //__GROVE_LED_MATRIX_DRIVER_HT16K33__