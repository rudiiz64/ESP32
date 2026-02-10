#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "bit.h"

/* Function to check if a specified bit is HIGH */
bool set_bit_check (uint16_t bit, int check){
    return (bit & (1 << (check - 1))) != 0;
}