#ifndef _LIGHT_H
#define _LIGHT_H

#include "sys.h"

extern uint8_t zkrt_SetFlag;
extern uint8_t zkrt_SetFlagCounter;
extern uint8_t zkrt_LastSetFlag;
extern uint8_t BlinkFlag ;
extern uint32_t stand_count;

void app_msg_handle(void);
void check_light_value(void);
#endif

