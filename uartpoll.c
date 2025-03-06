/*
 * uartpoll.c
 *
 *  Created on: 26 Apr 2022
 *      Author: laure
 */


#include "uartpoll.h"
#include <msp430.h>
#include <string.h>
#include <stdlib.h>


void initUart()
{
    //Configure DCO for 1MHz clock
    if (CALBC1_1MHZ == 0xFF)
    {                                   // If calibration constant is not present
        while (1)
            ;                           // loop forever
    }
    DCOCTL = 0;                         // Calibrate DCO to 1MHz
    BCSCTL1 = CALBC1_1MHZ;              //
    DCOCTL = CALDCO_1MHZ;               //

    //Configure UART for 9600 baud rate
    P1SEL |= (BIT1 + BIT2);             // Select secondary peripheral module function
    P1SEL2 |= (BIT1 + BIT2);            // P1.1=UCA0RXD P1.2=UCA0TXD
    UCA0CTL1 = 0;                       // No Parity, LSb first, 8-bits, 1 stop-bit, UART mode
    UCA0CTL1 |= UCSSEL_2;               // Use SMCLK from DCO
    UCA0BR0 = 104;                      // Set clock divider for 9600 baud from 1MHz clock
    UCA0BR1 = 0;                        // from 1MHz 9600
    UCA0MCTL = UCBRS0;                  // Set Modulation (UCBRSx = 1)
    UCA0CTL1 &= ~UCSWRST;               // remove reset from USCI

    outStr(RESET);
    outStr(CLRSCR);
    outStr(GOHOME);
    outStr(SHOWCUR);
}

void outStr(char *s)                    // Transmit string pointed to by s
{
    while (*s != '\0')                  // While we have not reached the end of the string
    {
        outChr(*s);                     // Send character pointed to by s
        s++;                            // Go on to next character in string
    }
}

void outChr(char c)                     // Tx character
{
    while (!(IFG2 & UCA0TXIFG))
        ;                               // Is Tx register ready?
    UCA0TXBUF = c;                      // Load register with c
}

void inStr(char *s)                     // Read string into buffer s
{
    char ch = inChr();                  // Receive first character
    while (ch != '\r')
    {                                   // While ch is not the <Return> character
        *s = ch;                        // Put it into s array element
        ch = inChr();                   // Receive next character
        s++;                            // Go on to next position in array
    }
    *s = '\0';                          // Terminate string with null character
}

char inChr()                            // Rx character
{
    while (!(IFG2 & UCA0RXIFG))
        ;                               // Is Rx character available?
    return UCA0RXBUF;                   // Read it
}

void itoa(char *s, int x)               // Convert int to ascii and store in buffer s
{
    char *p, *q, *t, temp;
    int d;
    int neg = x < 0;                    // Is x negative
    x = abs(x);                         // Make x positive if necessary

    if(x==0)                            // Special case x is zero
    {
        s[0]='0';
        s[1]='\0';
        return;
    }

    t = s;
    while (x > 0)                       // While there are digits left
    {
        d = x % 10;                     // Extract Least Sig. digit from x
        *t++ = d + '0';                 // Convert digit to ascii and append to s
        x = x / 10;
    }

    if (neg)
    {                                   // If negative
        *t++ = '-';                     // Append - sign
    }
    *t = '\0';                          // Terminate

    //reverse string so that the digits and sign are in the correct order
    for (p = s, q = s + strlen(s) - 1; p < q; p++, q--)
    {
        temp = *p;
        *p = *q;
        *q = temp;
    }
}
