#ifndef BIT_H
#define BIT_H

/****
 * @purpose: To turn OFF ith bit
 * @args: Am integer number to check and an int to specify bit location
****/
int turnOffBit(int n, int i);

/****
 * @purpose: To turn ON ith bit
 * @args: An integer number to check and an int to specify bit location
****/
int turnOnBit(int bit, int ith_bit);

/****
 * @purpose: To toggle ith bit
 * @args: An integer number to check and an int to specify bit location
****/
int toggleBit(int bit, int ith_bit);

/****
 * @purpose: To check if a specified bit is ON
 * @args: An integer number to check and an int to specify bit location
****/
bool set_bit_check(int bit, int check);

int twosComplement(int bit);

#endif