/*
 * File:   main.c
 * Author: Roland Pelayo
 *
 * Created on October 2, 2020, 5:40 PM
 */

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <math.h>

//function prototypes
void enableExtInterrupt();
void setupPorts();
void flashLEDs();

//main routine
void main(void) {
    enableExtInterrupt();
    setupPorts();
    while(1){
        //check if button is pressed
        if(RC0 == 0){
            //if pressed, flash all LEDs
            flashLEDs();
        }
        //main routine is sequential flashing
        for(int j=0;j<8;j++){
            PORTD = pow(2,j); //1, 2, 4, 8, 16, 32, 64, 128
            __delay_ms(200);
        }
    }
    return;
}
//enable external interrupt routine
void enableExtInterrupt(){
    GIE = 1;
    INTE = 1;
}
//setup output and input pins routine
void setupPorts(){
    TRISB0 = 1;
    TRISC0 = 1;
    TRISD = 0;
}
//flash LEDs regular routine
void flashLEDs(){
    for(int i=0;i<3;i++){
        PORTD = 0;
        __delay_ms(200);
        PORTD = 255;
        __delay_ms(200);
    }
}
//flash LEDs interrupt routine
void __interrupt () ISR(){
    //check if both external interrupt enable and flag bits are set
    if(INTE && INTF){
        for(int i=0;i<3;i++){
            PORTD = 0;
            __delay_ms(200);
            PORTD = 255;
            __delay_ms(200);
        } 
    } 
    //clear interrupt flag
    INTF = 0;
    return;
}