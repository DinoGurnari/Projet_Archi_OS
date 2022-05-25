#include <n7OS/time.h>
#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/console.h>

extern void handler_timer();

int frequence = F_OSC/HORLOGE;

void init_timer() {
    // Initialisation de la frequence
    outb(0x34, 0x43);
    outb(frequence & 0xFF, 0x40);
    outb(frequence >> 8, 0x40);
    // Initialisation de l'IT
    init_irq_entry(0x20, (uint32_t) handler_timer);
    cpt = 0;

    outb(inb(0x21)&0xfe, 0x21);

}

void traitement_timer() {
    // Acquittement
    outb(0x20, 0x20);
    // Incrémentation
    cpt++;

    int tps[3];
    conversion(tps, cpt);
    
    update_timer(tps);

}

void conversion(int* res, int c) {
    int nbr_sec = c/HORLOGE;

    res[0] = nbr_sec/3600;      // heures
    res[1] = (nbr_sec%3600)/60; // minutes
    res[2] = (nbr_sec%3600)%60; // secondes
}