#ifndef __TIME_H__
#define __TIME_H__

#define F_OSC 0x1234BD
#define HORLOGE 1000

int cpt;

void init_timer();

void traitement_timer();

void conversion(int* res, int c);

#endif