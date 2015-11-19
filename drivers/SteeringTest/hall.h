#ifndef _HALL_H
#define _HALL_H
#ifdef __cplusplus
extern "C"{
#endif

#include <krnl.h>
struct k_t *sem1;
void initHallTimers();
void tSpeed(void);
float getSpeed(int belt);
#endif

#ifdef __cplusplus
} // extern "C"
#endif
