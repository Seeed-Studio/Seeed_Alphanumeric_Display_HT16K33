/* 
 * grove_dual_alphanumeric_display.cpp
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

#include "grove_dual_alphanumeric_display.h"


Digital_Tube2::Digital_Tube2()
{
    _orientation = DISPLAY_ROTATE_0;
    _offset_x = 0;
    _offset_y = 0;
    _cursor_start = 0;
    _cursor_end = 0;
    _cursor_steps = 1;
    _ms = 100;
}

bool Digital_Tube2::isLegalToDisplay(char byte)
{
    if( !((byte >= '.' && byte <= '9') || (byte >= 'A' && byte <= 'Z') ) )
        return false;
    return true;
}

uint16_t g_display_font_2[]={
    // 0x0000,                 // display nothing.
    0x4000,                 // '.'
    0x0000,                 //  '/'   display nothing.
    0xa145,                 // '0'
    0x8001,                 // '1'
    0x3107,                 // '2'
    0xb007,                 // '3'
    0x9043,                 // '4'
    0xb046,                 // '5'
    0xb146,                 // '6'
    0x8005,                 // '7'
    0xb147,                 // '8'
    0xb047,                 // '9'
    0x9147,                 // 'A'
    0xb415,                 // 'B'
    0x2144,                 // 'C'
    0xa415,                 // 'D'
    0x3146,                 // 'E'
    0x1146,                 // 'F'
    0xb144,                 // 'G'
    0x9143,                 // 'H'
    0x2414,                 // 'I'
    0xA101,                 // 'J'
    0x0c18,                 // 'K'
    0x2140,                 // 'L'
    0x8169,                 // 'M'
    0x8961,                 // 'N'
    0xa145,                 // 'O'
    0x1147,                 // 'P'
    0xa945,                 // 'Q'
    0x1947,                 // 'R'
    0x2824,                 // 'S'
    0x0414,                 // 'T'
    0xa141,                 // 'U'
    0x8821,                 // 'V'
    0x8b41,                 // 'W'
    0x0a28,                 // 'X'
    0x0428,                 // 'Y'
    0x220c,                 // 'Z'
    0x0000,                 // ilegal num
};


void Digital_Tube2::display_two_tube(char byte1,char byte2)
{
    if(!isLegalToDisplay(byte1))  
    {
        byte1 = '/';
    }
    if(!isLegalToDisplay(byte2))  
    {
        byte2 = '/';
    }
    setDispBuf(FIRST_TUBE,byte1);                  //The order of tube is reversed
    setDispBuf(SECOND_TUBE,byte2);
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}


void Digital_Tube2::setDispBuf(TubeNum_2 num,char byte)
{
    if((byte >='.' && byte <= '9'))
    {
        _buffer[num*2+2] = g_display_font_2[byte-'0'+2] >> 8;
        _buffer[num*2+3] = g_display_font_2[byte-'0'+2];
    }
    else
    {
        _buffer[num*2+2] = g_display_font_2[byte-'A'+10+2] >> 8;
        _buffer[num*2+3] = g_display_font_2[byte-'A'+10+2];
    }
}

/**If the param num <100,The tubes display static number,otherwise,it displays scroll number.
 * When it displays scroll number,the param interval is scrolling interval(ms) .
 * 
 * */

void Digital_Tube2::displayNum(unsigned long int num,unsigned int interval)
{
    char first_tube_byte = 0,second_tube_byte = 0;
    int i = 0;
    int high_bit = 0;
    char num_array[32] = {0};
    if(num > 99) 
    {
        while(num)
        {
            num_array[i] = (num % 10)+0x30;
            num /= 10;
            i++;
        }
        for(;i >= 2;i-=2)
        {
            first_tube_byte = num_array[i-1];
            second_tube_byte = num_array[i-2];

            if(!isLegalToDisplay(first_tube_byte))  
            {
                first_tube_byte = '/';
            }
            if(!isLegalToDisplay(second_tube_byte))  
            {
                second_tube_byte = '/';
            }
            setDispBuf(FIRST_TUBE,first_tube_byte);
            setDispBuf(SECOND_TUBE,second_tube_byte);
            writeBytes(_addr, 0x00, 16, _buffer);
            delay(interval);
            
        }
        if(1 == i){
            first_tube_byte = num_array[0];
            second_tube_byte = '/';
            setDispBuf(FIRST_TUBE,first_tube_byte);
            setDispBuf(SECOND_TUBE,second_tube_byte);
            writeBytes(_addr, 0x00, 16, _buffer);
            delay(interval);
        }
        clear();
        
    }
    else
    {
        first_tube_byte = (num / 10) + 0x30;
        second_tube_byte = (num % 10 ) + 0x30;
        if(!isLegalToDisplay(first_tube_byte))  
        {
            first_tube_byte = '/';
        }
        if(!isLegalToDisplay(second_tube_byte))  
        {
            second_tube_byte = '/';
        }
        
        setDispBuf(FIRST_TUBE,first_tube_byte);
        setDispBuf(SECOND_TUBE,second_tube_byte);

        writeBytes(_addr, 0x00, 16, _buffer);
        delay(_ms);
    }    
}

/**If the param-str's len less than 2,The tubes display static string,otherwise,it displays scroll string.
 * When it displays scroll string,the param interval is scrolling interval(ms) .
 * Node:The library does not support lower case letters. 
 * */
void Digital_Tube2::displayString(char *str,unsigned int interval)
{
    char first_tube_byte = 0,second_tube_byte = 0;
    int len = 0;
    len = strlen(str);
    if(len < 2)
    {
        if(len == 1)
        {
            first_tube_byte = str[0];
        }
        else
        {
            first_tube_byte = '/';
        }
        second_tube_byte = '/';
    }
    else if(2 == len)
    {
        first_tube_byte = str[0];
        second_tube_byte = str[1];
        if(!isLegalToDisplay(first_tube_byte))  
        {
            first_tube_byte = '/';
        }
        if(!isLegalToDisplay(second_tube_byte))  
        {
            second_tube_byte = '/';
        }
        
        setDispBuf(FIRST_TUBE,first_tube_byte);
        setDispBuf(SECOND_TUBE,second_tube_byte);

        writeBytes(_addr, 0x00, 16, _buffer);
        delay(_ms);
    }
    else
    {
        if(len >255 ) len = 255;
        for(int i=0;i<len;i += 2)
        {
            first_tube_byte = str[i];
            second_tube_byte = str[i+1];

            if(!isLegalToDisplay(first_tube_byte))  
            {
                first_tube_byte = '/';
            }
            if(!isLegalToDisplay(second_tube_byte))  
            {
                second_tube_byte = '/';
            }
            setDispBuf(FIRST_TUBE,first_tube_byte);
            setDispBuf(SECOND_TUBE,second_tube_byte);
            writeBytes(_addr, 0x00, 16, _buffer);
            delay(interval);
            if(i+2 == len-1)
            {
                first_tube_byte = str[len-1];
                second_tube_byte = '/';
                setDispBuf(FIRST_TUBE,first_tube_byte);
                setDispBuf(SECOND_TUBE,second_tube_byte);
                writeBytes(_addr, 0x00, 16, _buffer);
                delay(interval);
                break;
            }
        }
    }
    
}

void Digital_Tube2::displayFull()
{
    for(int i=0;i<4;i++)
    {
        _buffer[i+2] = 0xff;
    }
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}

void Digital_Tube2::clear()
{
    memset(_buffer, 0, sizeof(_buffer));
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}

/*
bool HT16K33::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data)
{
    Wire.beginTransmission(devAddr);
    Wire.write((uint8_t) regAddr);
    for (uint8_t i = 0; i < length; i++) {
        Wire.write((uint8_t) data[i]);
    }
     Wire.endTransmission();
}
*/
