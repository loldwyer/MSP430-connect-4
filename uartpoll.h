/*
 * uartpoll.h
 *
 *  Created on: 26 Apr 2022
 *      Author: laure
 */

#ifndef UARTPOLL_H_
#define UARTPOLL_H_


#define GOHOME "\x1b[H"                       // Home
#define WHITERED "\x1b[0;31;107m"           // White background, red foreground robot
#define HIDECUR "\x1b[?25l"                   // Hide Cursor
#define SHOWCUR "\x1b[?25h"                   // Show Cursor
#define CLRSCR "\x1b[2J"                      // Clear Screen
#define RESET "\x1b[0;97;40m"                 // Reset graphics mode
#define GOTO(L, C) "\x1b[" #L ";" #C "H"      // Goto Line Column.  "Esc[Line;ColumnH"

void initUart();
void outStr(char* s);
void outChr(char c);
void inStr(char* s);
char inChr();
void itoa(char* s, int x);





#endif /* UARTPOLL_H_ */
