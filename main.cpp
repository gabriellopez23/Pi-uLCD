#include "platform.h"
#include "ulcd.h"


int main(int argc, char* argv) {
    uLCD_4DGL uLCD;
    uLCD.printf("\nHello uLCD World\n"); //Default Green on black text
    uLCD.printf("\n  Starting Demo...");
    uLCD.text_width(4); //4X size text
    uLCD.text_height(4);
    uLCD.color(RED);
    for (int i=10; i>=0; --i) {
        uLCD.locate(1,2);
        uLCD.printf("%2D",i);
        wait(.5);
    }
    uLCD.cls();
    uLCD.printf("Change baudrate......");
    uLCD.baudrate(230400); //jack up baud rate to max for fast display
    //if demo hangs here - try lower baud rates
    //
    // printf text only full screen mode demo
    uLCD.background_color(BLUE);
    uLCD.cls();
    uLCD.locate(0,0);
    uLCD.color(WHITE);
    uLCD.textbackground_color(BLUE);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    int i=0;
    while(i<64) {
        if(i%16==0) uLCD.cls();
        uLCD.printf("TxtLine %2D Page %D\n",i%16,i/16 );
        i++; //16 lines with 18 charaters per line
    }
    wait(0.5);
    //demo graphics commands
    uLCD.background_color(BLACK);
    uLCD.cls();
    uLCD.background_color(DGREY);
    uLCD.filled_circle(60, 50, 30, 0xFF00FF);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0x0000FF);
    uLCD.line(0, 0, 80, 60, 0xFF0000);
    uLCD.filled_rectangle(50, 50, 100, 90, 0x00FF00);
    uLCD.pixel(60, 60, BLACK);
    uLCD.read_pixel(120, 70);
    uLCD.circle(120, 60, 10, BLACK);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(TRANSPARENT);
    uLCD.text_bold(ON);
    uLCD.text_char('B', 9, 8, BLACK);
    uLCD.text_char('I',10, 8, BLACK);
    uLCD.text_char('G',11, 8, BLACK);
    uLCD.text_italic(ON);
    uLCD.text_string("This is a test of string", 1, 4, FONT_7X8, WHITE);
    wait(2);
 
//Bouncing Ball Demo
    float fx=50.0,fy=21.0,vx=1.0,vy=0.4;
    int x=50,y=21,radius=4;
    uLCD.background_color(BLACK);
    uLCD.cls();
    //draw walls
    uLCD.line(0, 0, 127, 0, WHITE);
    uLCD.line(127, 0, 127, 127, WHITE);
    uLCD.line(127, 127, 0, 127, WHITE);
    uLCD.line(0, 127, 0, 0, WHITE);
    for (int i=0; i<1500; i++) {
        //draw ball
        uLCD.filled_circle(x, y, radius, RED);
        //bounce off edge walls and slow down a bit?
        if ((x<=radius+1) || (x>=126-radius)) vx = -.90*vx;
        if ((y<=radius+1) || (y>=126-radius)) vy = -.90*vy;
        //erase old ball location
        uLCD.filled_circle(x, y, radius, BLACK);
        //move ball
        fx=fx+vx;
        fy=fy+vy;
        x=(int)fx;
        y=(int)fy;
    }
    return 0;
}