/*
 * winner.h
 * Lauren Dwyer
 * x00168331
 */

#ifndef WINNER_H_
#define WINNER_H_

#include <msp430.h>
#include <stdint.h>
#include "mtxdisp.h"
#include "switch.h"
#include "delay.h"

static char player = 2;
static uint8_t ch = BIT7;
static uint8_t search = BIT7;
static uint8_t b;
int playerWon(uint8_t BGR[8][3],uint8_t RES_GREEN[8][3],uint8_t RES_RED[8][3],uint8_t RES_DRAW[8][3],int player,uint8_t move,unsigned int row, int col);

#endif /* WINNER_H_ */

