/* 
 * Grove_LED_Matrix_Driver_HT16K33.h
 * A library for Grove - LED Matrix Driver(HT16K33 with 8x8 LED Matrix)
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jerry Yip
 * Create Time: 2018-06
 * Version    : 0.1
 * Change Log :
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : downey 
 * Create Time: 2018-06
 * Version    : 1.1
 * Change Log :for digital tube development.
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
#include "Wire.h"

HT16K33::HT16K33()
{
}

void HT16K33::init(uint8_t addr)
{
    _addr = addr;
    // turn on oscillator
    writeBytes(_addr, 0x21, 0, (uint8_t *)NULL);
}

/*brightness:0-15*/
void HT16K33::setBrightness(uint8_t brightness)
{
    writeBytes(_addr, (0xE0 | brightness), 0, (uint8_t *)NULL);
}


void HT16K33::setBlinkRate(blink_type_t blink_type)
{
    writeBytes(_addr, (0x80 | 0x01 | (blink_type << 1)), 0, (uint8_t *)NULL);
}

Digital_Tube::Digital_Tube()
{
    _orientation = DISPLAY_ROTATE_0;
    _offset_x = 0;
    _offset_y = 0;
    _cursor_start = 0;
    _cursor_end = 0;
    _cursor_steps = 1;
    _ms = 100;
}

bool Digital_Tube::isLegalToDisplay(char byte)
{
    if( !((byte >= '.' && byte <= '9') || (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z') ) )
        return false;
    return true;
}

uint16_t g_display_font[]={
    // 0x0000,                 // display nothing.
    0x0080,                 // 'upper .'
    0x2000,                 // 'lower .'
    0x4478,                 // '0'
    0x0060,                 // '1'
    0x0758,                 // '2'
    0x0770,                 // '3'
    0x4360,                 // '4'
    0x4730,                 // '5'
    0x4738,                 // '6'
    0x0070,                 // '7'
    0x4778,                 // '8'
    0x4770,                 // '9'
    0x4378,                 // 'A'
    0x2d70,                 // 'B'
    0x4418,                 // 'C'
    0x2c70,                 // 'D'
    0x4718,                 // 'E'
    0x4318,                 // 'F'
    0x4538,                 // 'G'
    0x4368,                 // 'H'
    0x2c10,                 // 'I'
    0x0478,                 // 'J'
    0x2806,                 // 'K'
    0x4408,                 // 'L'
    0x40ea,                 // 'M'
    0x40ec,                 // 'N'
    0x4478,                 // 'O'
    0x4358,                 // 'P'
    0x447c,                 // 'Q'
    0x435c,                 // 'R'
    0x0494,                 // 'S'
    0x2810,                 // 'T'
    0x4468,                 // 'U'
    0x500a,                 // 'V'
    0x506c,                 // 'W'
    0x1086,                 // 'X'
    0x0882,                 // 'Y'
    0x1412,                 // 'Z'
    0x0000,                 //  '/' ilegal num
};



/**@brief Display number,If the param-num's len less than 4(or equal to),The tubes display static number,otherwise,it displays scroll number.
 * When it displays scroll number,the param interval is scrolling interval(ms) .. 
 * @param num the number to display.
 * @param interval :the interval of scroll number.
 * */
void Digital_Tube::displayNum(uint32_t num,uint32_t interval)
{
    char num_str[15] = {0};
    sprintf(num_str,"%ld",(uint32_t)num);
    displayString(num_str,interval);
}



void Digital_Tube::shiftDisplay(char *origin_disp_buf,char new_item)
{
    char temp[TUBE_COUNT] = {0};
    memcpy(temp,&origin_disp_buf[1],TUBE_COUNT-1);
    temp[TUBE_COUNT-1] = new_item;
    memcpy(origin_disp_buf,temp,TUBE_COUNT);
    for(int i =0;i< TUBE_COUNT;i++)
    {
        setTubeBuf(i+1,g_display_font[get_char_index(temp[i])]);
    }
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}

/**@brief Display string,If the param-str's len less than 4(or equal to),The tubes display static string,otherwise,it displays scroll string.
 * When it displays scroll string,the param interval is scrolling interval(ms) .. 
 * @param str the str to display.
 * @param interval :the interval of scroll string.
 * */
void Digital_Tube::displayString(char *str,uint32_t interval)
{
    char first_tube_byte = 0,second_tube_byte = 0;
    int len = 0;
    clearBuf();
    len = strlen(str);
    if(TUBE_COUNT >= len)
    {
        for(int i=0;i<len;i++)
        {
            setTubeBuf(TUBE_COUNT-len+i+1,g_display_font[get_char_index(str[i])]);  //Convert number to char;
        }
        writeBytes(_addr, 0x00, 16, _buffer);
        delay(_ms);
        
    }
    else
    {
        if(len > 255 ) len = 255;
        char origin_disp_buf[TUBE_COUNT]={0};
        for(int i=0;i<len;i++)
        {
            shiftDisplay(origin_disp_buf,str[i]);
            delay(interval);
        }
    }
}


void Digital_Tube::clear()
{
    memset(_buffer, 0, sizeof(_buffer));
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}


void Digital_Tube::fulDisplay()
{
    uint8_t buf[16] = {0};
    memcpy(_buffer,buf,sizeof(buf));
    memset(_buffer, 0xff, sizeof(_buffer));
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}


void Digital_Tube::replace_bit12(TubeNum tube_num,bool bit1,bool bit2)
{
    switch(tube_num)
    {
        case FIRST_TUBE:

        _buffer[10] |= (bit1<<4);
        _buffer[10] |= (bit2<<3);
        break;
        case SECOND_TUBE:
        _buffer[10] |= (bit1<<6);
        _buffer[11] |= (bit2<<6);
        break;
        case THIRD_TUBE:
        _buffer[10] |= (bit1<<5);
        _buffer[11] |= (bit2<<1);
        break;
        case FOURTH_TUBE:
        _buffer[11] |= (bit1<<2);
        _buffer[11] |= (bit2<<0);
        break;
        default:break;
    }
}

void Digital_Tube::setPoint(bool upper_on,bool lower_on)
{
    if(upper_on){
        _buffer[10] |= g_display_font[0];
        _buffer[11] |= g_display_font[0]>>8;
    }
    if(lower_on){
        _buffer[10] |= g_display_font[1];
        _buffer[11] |= g_display_font[1]>>8;
    }
}


void Digital_Tube::setTubeBuf(TubeNum tube_num,uint16_t value)
{
    
    _buffer[tube_num*2] = value;
    _buffer[tube_num*2+1] = value >> 8;
    replace_bit12(tube_num,value&0x02,value&0x04);
}

/**@brief Specify the display char of a digital tube. 
 * @param tube_num The number of tube ,total 4.
 * @param c ,The char to display
 * */
void Digital_Tube::setTubeSingleChar(TubeNum tube_num,char c)
{
    if(!(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) )
    {
        return ;
    }
    uint16_t value = g_display_font[get_char_index(c)];
    _buffer[tube_num*2] = value;
    _buffer[tube_num*2+1] = value >> 8;
    replace_bit12(tube_num,value&0x02,value&0x04);
}

/**@brief Specify the display number of a digital tube. 
 * @param tube_num The number of tube ,total 4.
 * @param num ,The number to display
 * */
void Digital_Tube::setTubeSingleNum(TubeNum tube_num,char num)
{
    if( !((num >= 0) && (num <= 9)) )
        return ;
    uint16_t value = g_display_font[get_char_index(num+0x30)];
    _buffer[tube_num*2] = value;
    _buffer[tube_num*2+1] = value >> 8;
    replace_bit12(tube_num,value&0x02,value&0x04);
}


void Digital_Tube::display_one_tube(TubeNum tube_num,uint16_t value)
{
    _buffer[tube_num*2] = value;
    _buffer[tube_num*2+1] = value >> 8;
    replace_bit12(tube_num,value&0x02,value&0x04);
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}


void Digital_Tube::clearBuf()
{
    memset(_buffer,0,sizeof(_buffer));
}

int Digital_Tube::get_char_index(char c)
{
    if((c >= '0') && (c <= '9'))
    {
        return c-0x30+2;
    }
    else if((c >= 'A') && (c <= 'Z'))
    {
        return c-0x37+2;
    }
    else if((c >= 'a') && (c <= 'z'))
    {
        return c-0x57+2;
    }
    else
    {
        return '/'+2;
    }
}



void Digital_Tube::display()
{
    writeBytes(_addr, 0x00, 16, _buffer);
    delay(_ms);
}


bool HT16K33::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data)
{
    Wire.beginTransmission(devAddr);
    Wire.write((uint8_t) regAddr);
    for (uint8_t i = 0; i < length; i++) {
        Wire.write((uint8_t) data[i]);
    }
     Wire.endTransmission();
}



