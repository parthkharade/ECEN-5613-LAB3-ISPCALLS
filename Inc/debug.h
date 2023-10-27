#ifndef DEBUG_H_
#define DEBUG_H_
#define DEBUG
#include "stdint.h"
#ifdef DEBUG
#define DEBUGPORT(X) mark_location((X))
#else
#define DEBUGPORT(X)
#endif
/**
 * @brief Writes a value to the location 0xFFFF, used as a debugging utility.
 * 
 * @param val 
 */
void mark_location(uint8_t val);
#endif
