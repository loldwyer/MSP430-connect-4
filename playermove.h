/*
 * placeMove.h
 * Lauren Dwyer
 * x00168331
 */

#ifndef MOVES_H_
#define MOVES_H_

#include <stdint.h>
#define BLUE 0
#define GREEN 1
#define RED 2

uint8_t placeMove(uint8_t BGR[8][3], int player, uint8_t move);
uint8_t getMove(uint8_t BGR[8][3],unsigned int player);


#endif /* MOVES_H_ */
