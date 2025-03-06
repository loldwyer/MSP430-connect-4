/*
 * winner.c
 * Lauren Dwyer
 * x00168331
 */
#include "winner.h"
#include "playermove.h"
#include "mtxdisp.h"
#include "delay.h"
#include "switch.h"
#include <msp430.h>
#include <stdio.h>
int playerWon(uint8_t BGR[8][3],uint8_t RES_GREEN[8][3],uint8_t RES_RED[8][3],uint8_t RES_DRAW[8][3],int player,uint8_t move,unsigned int row,int col){
    unsigned int r, c,m;
    //horizontal
    unsigned char b;
    unsigned int cnt=0;
    unsigned int game=0;

    unsigned char n;
    for(b=0x80;b>0x01;b=b>>1){  //check each bit in the row one after the other
        if(BGR[row][player]&b){ //if a bit in a row is lit check the other bits in the row
            cnt++; //increment counter
            if(cnt>=4){  //i.e, if win

                if(player==GREEN){        //if the winning player is green
                    //make all LEDs the colour of the winning player
                    //changed to print "WIN" in main.c code
                    RES_GREEN[8][player];
                    lightMtx(RES_GREEN);

                }
                if(player==RED){
                    RES_RED[8][player];
                    lightMtx(RES_RED);
                }
                return 1; //stops the user from making a move selection
            }
        }else
            cnt=0;  //start again
    }


    //vertical
    if (row<=4)  //check the rows below (check the column)
        {
          if ((BGR[row+1][player]&move)&&     //check row+1
             (BGR[row+2][player]&move)&&
           (BGR[row+3][player]&move))
          {
              if(player==GREEN){
                  RES_GREEN[8][player];
                  lightMtx(RES_GREEN);
              }
              if(player==RED){
                  RES_RED[8][player];
                  lightMtx(RES_RED);
              }
              return 1;
          }
        }


  //diagonal win - bottom "/"
    cnt = 1;
    for(r=row+1, m=move<<1;   r<8 && m!=0;    r++, m<<=1){
        if(BGR[r][player]&m){
            cnt++;
            if(cnt>=4)
                {
                if(player==GREEN){
                    RES_GREEN[8][player];
                    lightMtx(RES_GREEN);
                }
                if(player==RED){
                    RES_RED[8][player];
                    lightMtx(RES_RED);
                }
                return 1;
                }
        }else {
            break;
        }
    }

    //diagonal win - top "/"
    for(r=row-1, m=move>>1;   r>1 && m!=0;    r--, m>>=1){
        if(BGR[r][player]&m){
            cnt++;
            if(cnt>=4)
                {
                if(player==GREEN){
                    RES_GREEN[8][player];
                    lightMtx(RES_GREEN);
                }
                if(player==RED){
                    RES_RED[8][player];
                    lightMtx(RES_RED);
                }
                return 1;
                }
        }else {
            break;
        }
    }
    //diagonal win - top "\"
    for(r=row-1, m=move<<1;   r>1 && m!=0;    r--, m<<=1){
        if(BGR[r][player]&m){
            cnt++;
            if(cnt>=4)
                {
                if(player==GREEN){
                    RES_GREEN[8][player];
                    lightMtx(RES_GREEN);
                }
                if(player==RED){
                    RES_RED[8][player];
                    lightMtx(RES_RED);
                }
                return 1;}
        }else {
            break;
        }
    }
    //diagonal win - bottom "\"
    for(r=row+1, m=move>>1;   r<8 && m!=0;    r++, m>>=1){
        if(BGR[r][player]&m){
            cnt++;
            if(cnt>=4){
                if(player==GREEN){
                    RES_GREEN[8][player];
                    lightMtx(RES_GREEN);
                }
                if(player==RED){
                    RES_RED[8][player];
                    lightMtx(RES_RED);
                }
                return 1;
            }
        }else {
            break;
        }
    }
    return 0;
}


