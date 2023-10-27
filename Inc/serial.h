#include "stdint.h"

#ifndef SERIAL_H
#define SERIAL_H
/**
 * @brief Accepts a string input from the user and stores in strbuf. Carriage Return marks the end of a string.
 * 
 * @param strbuf : String buffer for accepting an input.
 * @param length : The length of the string buffer. The input is automatically truncated to this length.
 * @return uint8_t 
 */
uint8_t scanf(char *strbuf,uint8_t length);
/**
 * @brief : Leverages the scanf function and interpretes the entered string as a decimal number.
 * 
 * @param num : Buffer to store the interpreted number.
 * @return uint8_t : The number of characters read while interpreting the number. Returns 0 if a invalid number string is entered.
 */
uint8_t scan_num(uint16_t * num);

void print_total_characters();
void reset_total_characters();
#endif
