/*
 * File:   Ultrasonic_Sensor
 * Author: Mohamed Hamdi
 * please visit my youtube channel:https://www.youtube.com/channel/UCzt_0MFbJiT93KSR74pW6Jw
 */

#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

float calc_dist(void);
void main(void)
{
    //creat distance variable char
    unsigned char dist = 0;
    //set portB to be output pins
    TRISB = 0x00;
    //set portB intial value low
    PORTB = 0X00;
    //set c2 an output pin
    TRISC2 = 0;
    //set c3 an input pin
    TRISC3 = 1;
    //set timer module in timer mode

    //set pre scaler 1:1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1CS = 0;
    while (1)
    {
        dist = calc_dist() / 5;
        switch (dist)
        {
        case 1:
            PORTB = 0x01;
        case 2:
            PORTB = 0x03;
        case 3:
            PORTB = 0x07;
        case 4:
            PORTB = 0x0F;
        default:
            PORTB = 0x00;
        }
        __delay_ms(100);
    }
    return;
}
//--------------------------------------------------------------------------------------------------------------------------
//defintion of calc_dist function
float calc_dist(void)
{
    float distance = 0;
    TMR1 = 0;
    //send trigger pulse to ultrasonic
    RC2 = 1;
    __delay_us(10);
    RC2 = 0;
    //wait for the echo pulse from ultrasonic
    while (!RC3)
        ;
    //turn on timer module
    TMR1ON = 1;
    //wait until the pulse ends
    while (RC3)
        ;
    //turn off the timer
    TMR1ON = 0;
    distance = TMR1 / 58.8;
    return distance;
}