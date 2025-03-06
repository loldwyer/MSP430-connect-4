/*main.c
 * Lauren Dwyer
 * x00168331
 */
#include <msp430.h> 
#include <stdint.h>
#include "mtxdisp.h"
#include "delay.h"
#include "playermove.h"
#include "switch.h"
#include "winner.h"
#include "uartpoll.h"

char buf[15]=""; //stores game count that is printed to PUTTY using UART
int game=0; //used to count number of games that have been player

int main(void)
{
    while(1){ //while the code is runnable

    //design of the game space (blue grid)
    uint8_t BGR[8][3]={         {0x01,0x00,0x00},
                                {0xFF,0x00,0x00},
                                {0x01,0x00,0x00},
                                {0x01,0x00,0x00},
                                {0x01,0x00,0x00},
                                {0x01,0x00,0x00},
                                {0x01,0x00,0x00},
                                {0x01,0x000,0x00}  };

    //make every LED green
    uint8_t RES_GREEN[8][3]={   {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00},
                                {0x00,0xFF,0x00}  };

    //make every LED red
    uint8_t RES_RED[8][3]={     {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF},
                                {0x00,0x00,0xFF}  };

    //make half the LEDs red and half of them green
    uint8_t RES_DRAW[8][3]={    {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F},
                                {0x00,0xF0,0x0F}  };

    //write the word win to the LED matrix
    uint8_t score[3][8] = {{0x54,0x54,0x54,0x54,0x54,0x54,0x28},  //W
                           {0x10,0x10,0x10,0x10,0x10,0x10,0x10},  //I
                           {0x44,0x64,0x54,0x4C,0x44,0x44,0x44}   //N
    };

    volatile long x,y=2;
    int player = RED;
    int numOfMoves = 0;
    unsigned int col=8;

    uint8_t move;
    int place;
    int win;

    initUart(); //Initialize UART communications
    WDTCTL = WDTPW | WDTHOLD;        // Stop watch-dog timer
    initialiseSwitch();//set up switch for reading
    initMtx(); //initialize the LED matrix display
    clearMtx();  //empty the matrix

    do{
        if(player==RED){    //switch between the players once a move has been made
            player = GREEN;
        }
        else{
            player = RED;   //if player is RED, the next player is GREEN
        }
        move = getMove(BGR,player);  //see playermove.c
        place = placeMove(BGR,player,move);  //see playermove.c

        numOfMoves++; //increment counter
        lightMtx(BGR); //display the game space

        //see winner.c
        win=playerWon(BGR,RES_GREEN,RES_RED,RES_DRAW,player,move,place,col);
    }while(numOfMoves<64 && !win); //if no one has won and the game space is not full, repeat

    if(numOfMoves==64){  //if the game-space is filled with non-winning moves
        lightMtx(RES_DRAW);
    }

    //clear bgr
    int f,g;
    for(f=0;f<8;f++){      //rows
        for(g=0;g<3;g++){  //colours
            BGR[f][g]=0x00; //clear bgr
        }
    }

    if(win){    //if someone wins a game
        game++; //increment game counter
        outStr(GOTO(8,5));  //see PUTTY console
        outStr("game=");
        outStr(GOTO(8,20));
        itoa(buf,game);
        outStr(buf);    //update PUTTY game tracker

        for(f=0;f<=4;f++){ //letters
            for(g=0;g<9;g++){ //rows
                BGR[g][player]=score[0][g]; //write WIN to matrix when winner is found
                delay(30000);
                lightMtx(BGR);
            }
        }
        for(f=0;f<=4;f++){
            for(g=0;g<9;g++){

                delay(30000);
                BGR[g][player]=score[1][g];
                lightMtx(BGR);
            }
        }
        for(f=0;f<=4;f++){ //letters
            for(g=0;g<9;g++){ //rows

                delay(30000);
                BGR[g][player]=score[2][g];
                lightMtx(BGR);
                delay(30000);
            }
        }
    }
    delay(30000);
    }

    delay(30000);
    return 0;
}

