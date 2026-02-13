#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "bit.h"


/* Function to turn off specified bit */
int turnOffBit(int bit, int ith_bit){
    return bit & ~(1 << (ith_bit - 1));
}

/* Function to turn on specified bit */
int turnOnBit(int bit, int ith_bit){
    return bit | (1 << (ith_bit - 1));
}

/* Toggle the specfied bit */
int toggleBit(int bit, int ith_bit){
    return bit ^ (1 << (ith_bit - 1));
}

/* Function to check if a specified bit is HIGH */
bool set_bit_check (int bit, int check){
    return (bit & (1 << (check - 1))) != 0;
}

/* Function to perform two's complement */
int twosComplement(int bit){
    return ((~bit) + 1);
}