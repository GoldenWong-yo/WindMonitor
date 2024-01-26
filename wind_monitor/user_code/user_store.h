#ifndef USER_STORE_H
#define USER_STORE_H

#include "sys.h"

uint8_t * store_init(uint8_t *p_index, uint8_t *p_num);

void store(uint8_t index, uint8_t num);

#endif  /* Avoid multiple inclusion */
