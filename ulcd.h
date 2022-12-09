#pragma once

#ifndef __ULCD_H__
//
// uLCD_4DGL is a class to drive 4D Systems TFT touch screens
//
// Fork of 4DGL library for 4D Systems LCD displays
// Copyright (C) <2010> Stephane ROCHON <stephane.rochon at free.fr>
// Modifed for Goldelox processor <2013> Jim Hamblen
//
// uLCD_4DGL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// uLCD_4DGL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with uLCD_4DGL.  If not, see <http://www.gnu.org/licenses/>.
 
// @author Stephane Rochon

#include "platform.h"
#include <stdarg.h>


// Debug Verbose off - SGE commands echoed to USB serial for debugmode=1
#ifndef DEBUGMODE
#define DEBUGMODE 0
#endif
 
// Common WAIT value in milliseconds between commands
#define TEMPO 0
 
// 4DGL SGE Function values for Goldelox Processor
#define CLS          '\xD7'
#define BAUDRATE     '\x0B' //null prefix
#define VERSION      '\x08' //null prefix
#define BCKGDCOLOR   '\x6E'
#define TXTBCKGDCOLOR '\x7E'
#define DISPCONTROL  '\x68'
#define SETVOLUME    '\x76'
#define CIRCLE       '\xCD'
#define FCIRCLE      '\xCC'
#define TRIANGLE     '\xC9'
#define LINE         '\xD2'
#define FRECTANGLE   '\xCE'
#define RECTANGLE    '\xCF'
#define ELLIPSE      '\x65' //na
#define PIXEL        '\xCB'
#define READPIXEL    '\xCA'
#define SCREENCOPY   '\x63'  //na?
#define PENSIZE      '\xD8'
#define SETFONT      '\x7D'
#define TEXTMODE     '\x77'
#define TEXTBOLD     '\x76'
#define TEXTITALIC   '\x75'
#define TEXTINVERSE  '\x74'
#define TEXTUNDERLINE '\x73'
#define TEXTWIDTH    '\x7C'
#define TEXTHEIGHT   '\x7B'
#define TEXTCHAR     '\xFE'
#define TEXTSTRING   '\x06'  //null prefix
#define MOVECURSOR   '\xE4'
#define BLITCOM      '\x0A'
#define PUTCHAR      '\xFE'
#define DISPPOWER    '\x66'
//media commands for uSD card
#define MINIT        '\xB1'
#define SBADDRESS    '\xB9'
#define SSADDRESS    '\xB8'
#define READBYTE     '\xB7'
#define READWORD     '\xB6'
#define WRITEBYTE    '\xB5'
#define WRITEWORD    '\xB4'
#define FLUSHMEDIA   '\xB2'
#define DISPLAYIMAGE '\xB3'
#define DISPLAYVIDEO '\xBB'
#define DISPLAYFRAME '\xBA'
 
 
 
// Screen answers
#define ACK          '\x06'
#define NAK          '\x15'
 
 
 
// Screen states
#define OFF          '\x00'
#define ON           '\x01'
 
// Graphics modes
#define SOLID        '\x00'
#define WIREFRAME    '\x01'
 
// Text modes
#define TRANSPARENT  '\x00'
#define OPAQUE       '\x01'
 
// Fonts Sizes
#define FONT_7X8     '\x00' //only builtin font 
#define FONT_5X7     '\x04'
#define FONT_8X8     '\x01'
#define FONT_8X12    '\x02'
#define FONT_12X16   '\x03'
#define MEDIAFONT    '\x07'
 
 
// Data speed
#define BAUD_110     27271
#define BAUD_300     9999
#define BAUD_600     4999
#define BAUD_1200    2499
#define BAUD_2400    1249
#define BAUD_4800    624
#define BAUD_9600    312
#define BAUD_14400   207
#define BAUD_19200   155
#define BAUD_31250   95
#define BAUD_38400   77
#define BAUD_56000   53
#define BAUD_57600   51
#define BAUD_115200  25
#define BAUD_128000  22
#define BAUD_256000  11
#define BAUD_300000  10
#define BAUD_375000  8
#define BAUD_500000  6
#define BAUD_600000  4
#define BAUD_750000  3
#define BAUD_1000000 2
#define BAUD_1500000 1
#define BAUD_3000000 0
 
// Defined Colors
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F
 
// Mode data
#define BACKLIGHT    '\x00'
#define DISPLAY      '\x01'
#define CONTRAST     '\x02'
#define POWER        '\x03'
#define ORIENTATION  '\x04'
#define TOUCH_CTRL   '\x05'
#define IMAGE_FORMAT '\x06'
#define PROTECT_FAT  '\x08'
 
// change this to your specific screen (newer versions) if needed
// Startup orientation is PORTRAIT so SIZE_X must be lesser than SIZE_Y
//uLCD144-G2 is a 128 by 128 pixel display
#define SIZE_X       128
#define SIZE_Y       128
 
#define IS_LANDSCAPE 0
#define IS_PORTRAIT  1
 
// Screen orientation
#define LANDSCAPE    '\x00'
#define LANDSCAPE_R  '\x01'
#define PORTRAIT     '\x02'
#define PORTRAIT_R   '\x03'
 
// Parameters
#define ENABLE       '\x00'
#define DISABLE      '\x01'
#define RESET        '\x02'
 
#define NEW          '\x00'
#define OLD          '\x01'
 
#define DOWN         '\x00'
#define UP           '\x01'
 
#define PROTECT      '\x00'
#define UNPROTECT    '\x02'
 
//**************************************************************************
// \class uLCD_4DGL uLCD_4DGL.h
// \brief This is the main class. It shoud be used like this : uLCD_4GDL myLCD(p9,p10,p11);
/**
Example:
* @code
* // Display a white circle on the screen
* #include "mbed.h"
* #include " uLCD_4DGL.h"
*
* uLCD_4GDL myLCD(p9,p10,p11);
*
* int main() {
*     myLCD.circle(120, 160, 80, WHITE);
* }
* @endcode
*/

using namespace nana;
 
class uLCD_4DGL
{
 
public :
    // TODO: change ints to Pinname
    uLCD_4DGL(const char* sertty = "/dev/ttyS0", int rst = 17);
 
// General Commands *******************************************************************************
 
    /** Clear the entire screen using the current background colour */
    void cls();
 
    /** Reset screen */
    void reset();
 
 
    /** Set serial Baud rate (both sides : screen and mbed)
    * @param Speed Correct BAUD value (see uLCD_4DGL.h)
    */
    void baudrate(int speed);
 
    /** Set background colour to the specified value
    * @param color in HEX RGB like 0xFF00FF
    */
    void background_color(int color);
 
    /** Set screen display mode to specific values
    * @param mode See 4DGL documentation
    * @param value See 4DGL documentation
    */
    void textbackground_color(int color);
 
    /** Set screen display mode to specific values
    * @param mode See 4DGL documentation
    * @param value See 4DGL documentation
    */
    void display_control(char mode);
    void display_power(char mode);
    /** Set internal speaker to specified value
    * @param value Correct range is 8 - 127
    */
    void set_volume(char value);
 
// Graphics Commands *******************************************************************************
 
    /** Draw a circle centered at x,y with a radius and a colour. It uses Pen Size stored value to draw a solid or wireframe circle
    * @param x Horizontal position of the circle centre
    * @param y Vertical position of the circle centre
    * @param radius Radius of the circle
    * @param color Circle color in HEX RGB like 0xFF00FF
    */
    void circle(int x , int y , int radius, int color);

    /** Draw a color-filled circle centered at x,y with a radius and a colour. It uses Pen Size stored value to draw a solid or wireframe circle
    * @param x Horizontal position of the circle centre
    * @param y Vertical position of the circle centre
    * @param radius Radius of the circle
    * @param color Circle color in HEX RGB like 0xFF00FF
    */
    void filled_circle(int x , int y , int radius, int color);

    /** Draw a triangle with x,y of each vertex and a colour.
    * @param x1 Horizontal position of the first vertex
    * @param y1 Vertical position of the first vertex
    * @param x2 Horizontal position of the second vertex
    * @param y2 Vertical position of the second vertex
    * @param x3 Horizontal position of the third vertex
    * @param y3 Vertical position of the third vertex
    * @param color Triangle color in HEX RGB like 0xFF00FF
    */
    void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
    
    /** Draw a line by specifying the x,y of its start and end point and a colour.
    * @param x1 Horizontal position of the start point
    * @param y1 Vertical position of the start point
    * @param x2 Horizontal position of the end point
    * @param y2 Vertical position of the end point
    * @param color Triangle color in HEX RGB like 0xFF00FF
    */
    void line(int x1, int y1, int x2, int y2, int color);

    /** Draw a rectangle with the x,y of the top-right and bottom-left corners and a colour.
    * @param x1 Horizontal position of the top-right corner
    * @param y1 Vertical position of the top-right corner
    * @param x2 Horizontal position of the bottom-left corner
    * @param y2 Vertical position of the bottom-left corner
    * @param color Line color in HEX RGB like 0xFF00FF
    */
    void rectangle(int x1, int y1, int x2, int y2, int color);

    /** Draw a color-filled rectangle with the x,y of the top-right and bottom-left corners and a colour.
    * @param x1 Horizontal position of the top-right corner
    * @param y1 Vertical position of the top-right corner
    * @param x2 Horizontal position of the bottom-left corner
    * @param y2 Vertical position of the bottom-left corner
    * @param color Rectangle color in HEX RGB like 0xFF00FF
    */
    void filled_rectangle(int x1, int y1, int x2, int y2, int color);

    /** Draw a single pixel at x,y and with a colour.
    * @param x Horizontal position of the pixel
    * @param y Vertical position of the pixel
    * @param color Rectangle color in HEX RGB like 0xFF00FF
    */
    void pixel(int x, int y, int color);

    /** Reads the color of a pixel at x,y.
    * @param x Horizontal position of the pixel
    * @param y Vertical position of the pixel
    * @return  Color of the pixel in HEX RGB like 0xFF00FF
    */
    int read_pixel(int x, int y);

    /** Change the pen size to SOLID or WIREFRAME
    * @param mode Pen mode
    */
    void pen_size(char mode);

    /** Draws a block of pixels at x,y and dimensions w,h with their respective colour.
    * @param x Horizontal position of the pixel block
    * @param y Vertical position of the pixel block
    * @param w Width of the pixel block
    * @param h Height of the pixel block
    * @param colors Array of pixel colors in HEX RGB like 0xFF00FF
    */
    void BLIT(int x, int y, int w, int h, int *colors);
 
// printf
    int  printf(const char *fmt, ...);

// Text Commands
    /** Change the text font (in library or SD card) to display
    * @param mode See 4DGL documentation
    */
    void set_font(char mode);

    /** Change the width and height of the text font
    * @param width Font size
    * @param height Font height
    */
    void set_font_size(char width, char height);  

    /** Change the text visibility OPAQUE or TRANSPARENT
    * @param mode See 4DGL documentation
    */
    void text_mode(char mode);

    /** Turn text bold mode ON or OFF
    * @param mode See 4DGL documentation
    */
    void text_bold(char mode);

    /** Turn text italic mode ON or OFF
    * @param mode See 4DGL documentation
    */
    void text_italic(char mode);

    /** Turn text inverse mode ON or OFF
    * @param mode See 4DGL documentation
    */  
    void text_inverse(char mode);

    /** Turn text underline mode ON or OFF
    * @param mode See 4DGL documentation
    */
    void text_underline(char mode);

    /** Adjust text width by a scaling factor
    * @param width Width scaling factor
    */
    void text_width(char mode);

    /** Adjust text height by a scaling factor
    * @param width Height scaling factor
    */
    void text_height(char mode);

    /** Draw single text char at col,row with a colour
    * @param c Text char to draw
    * @param col Horizontal position of the text char
    * @param row Vertical position of the text char
    * @param color Text char color in HEX RGB like 0xFF00FF
    */
    void text_char(char c, char col, char row, int color);

    /** Draw a string at col,row with a colour and font
    * @param s String to draw
    * @param col Horizontal position of the string
    * @param row Vertical position of the string
    * @param font Font of the string 
    * @param color String color in HEX RGB like 0xFF00FF
    */
    void text_string(char * s, char col, char row, char font, int color);

    /** Adjust LCD cursor to position col,row
    * @param col Horizontal position of the cursor
    * @param row Vertical position of the cursor
    */
    void locate(char col, char row);

    /** Set the general text color
    * @param color Text color in HEX RGB like 0xFF00FF
    */   
    void color(int color);

    /** Places a text char at current cursor position
    * @param c Text char to draw
    */  
    void putc(char c);

    /** Places a string at current cursor position
    * @param s String to draw
    */  
    void puts(char *s);
 
//Media Commands
    /** Initializes SD card for media usage
    * @return Serial response from SD card
    */
    int media_init();
    
     /** Set current byte address in the SD card to hi,lo
    * @param hi High word of address
    * @param lo Low word of address
    */
    void set_byte_address(int hi, int lo);
    
     /** Set current sector address in the SD card to hi,lo
    * @param hi High word of address
    * @param lo Low word of address
    */
    void set_sector_address(int hi, int lo);
    
    /** Read a byte from SD card at the current byte address
    * @return Read byte from the current address
    */
    char read_byte();
    
    /** Read a word from SD card at the current byte address
    * @return Read byte from the current address
    */
    int read_word();
    
    /** Write a byte to SD card at the current byte address
    * @param value Data to write into SD card
    */
    void write_byte(int value);
    
    /** Write a word to SD card at the current byte address
    * @param value Data to write into SD card
    */
    int write_word(int value);
    
    /** Deletes the media stored at the current sector address
    */
    void flush_media();

    /** Display on uLCD screen an image from current sector address at x,y
    * @param x Horizontal position of the image
    * @param y Vertical position of the image
    */
    void display_image(int x, int y);

    /** Display on uLCD screen a video from current sector address at x,y
    * @param x Horizontal position of the video
    * @param y Vertical position of the video
    */
    void display_video(int x, int y);

    /** Display on uLCD screen a single frame of video from current sector address at x,y
    * @param x Horizontal position of the frame
    * @param y Vertical position of the frame
    * @param w Frame to display
    */
    void display_frame(int x, int y, int w);
 
// Screen Data
    int type;
    int revision;
    int firmware;
    int reserved1;
    int reserved2;
 
// Text data
    char current_col;
    char current_row;
    int  current_color;
    char current_font;
    char current_orientation;
    char max_col;
    char max_row;
    int current_w, current_h;
    int current_fx, current_fy;
    int current_wf, current_hf;
 
 
protected :
 
    Serial              _cmd;
    DigitalOut          _rst;
    //used by printf
    virtual int _putc(int c) {
        putc(c);
        return 0;
    };
    virtual char _getc() {
        return -1;
    }
 
    void freeBUFFER  (void);
    void writeBYTE   (char);
    void writeBYTEfast   (char);
    int  writeCOMMAND(char *, int);
    int  writeCOMMANDnull(char *, int);
    int  readVERSION (char *, int);
    int  getSTATUS   (char *, int);
    int  version     (void);
#if DEBUGMODE
    Serial pc;
#endif // DEBUGMODE
};
 
typedef unsigned char BYTE;

#define __ULCD_H__
#endif