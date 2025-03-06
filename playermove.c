/*
 * placeMove.c
 * Lauren Dwyer
 * x00168331
 */
#include "playermove.h"
#include "mtxdisp.h"
#include "delay.h"
#include "switch.h"
#include <msp430.h>
#include "winner.h"

uint8_t placeMove(uint8_t BGR[8][3], int player,uint8_t move)
{
    uint8_t litLeds;
    int row=7;
    litLeds=BGR[7][RED]|BGR[7][GREEN];
    while((litLeds & move)!=0)
    {
        row--;
        litLeds=BGR[row][RED]|BGR[row][GREEN];

    }
    BGR[row][player] |= move;
    return row;
}


uint8_t getMove( uint8_t BGR[8][3], unsigned int player)
{
    unsigned char val,litLEDs;
    volatile long x;
    uint8_t ch=0x02;
    do{
        if(ch>0x02) //0x02 is the end of the user selection space, when the counter reaches this point without a selction having been made it will return to the start of the row
        {
            ch = ch >> 1; //move right by 1 until the counter reaches 0x02
        } else{
            ch=0x80; //start of row
        }
        BGR[0][player]=ch;
        lightMtx(BGR);

        for(x=0;x<10000;x++);
        val=readSwitchDB();  //read the switches input to tell when a move has been made
        litLEDs = BGR[2][GREEN]|BGR[2][RED]; //2 players, either red or green

    }while(val!=DOWN||(litLEDs&ch)!=0); //when the switch has been pressed then there must be a lit LED placed into the game-space in the indicated position
    BGR[0][player]=0x00;
    return ch;
}


