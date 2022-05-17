#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#define SIZETAB 1999

__UINT16_TYPE__ *scr_tab = (__UINT16_TYPE__ *) 0xB8000;
__UINT8_TYPE__ style = 0xF;
int currentPos;

void console_putcursor(int position) {
    // On récupère la position et on la coupe en deux;
    __UINT8_TYPE__ posCursor8[2] = { position & 0xff, position >> 8 };

    // Envoie des bits de poids faibles
    outb(0xF, 0x3D4);
    outb(posCursor8[0], 0x3D5);

    // Envoie des bits de poids forts
    outb(0xE, 0x3D4);
    outb(posCursor8[1], 0x3D5);
}

void setCursor(int position) {
    currentPos = position;
    console_putcursor(position);
}

void update_timer(int* tps){
    int buffer = currentPos;

    currentPos = 72;
    console_putcursor(72);

    printf("%2d:%2d:%2d", tps[0], tps[1], tps[2]); //CHANGER TO PUTCHAR
    
    currentPos = buffer;
    console_putcursor(buffer);
}

void console_putchar(const char c) {
    if (c > 31 && c < 127) {
        // Si c'est un caractère affichable
        scr_tab[currentPos] = (style << 8) | c;
        // On bouge le curseur
        console_putcursor(++currentPos);

    } else if (c == '\b') {
        // Si c'est décalage à la clonne de gauche (BS)
        scr_tab[currentPos] = ' ';
        // On bouge le curseur
        console_putcursor(--currentPos);

    } else if (c == '\t') {
        // Si c'est un tab (HT) de 4 espaces
        for (int i = 0; i < 4; i++) {
            scr_tab[currentPos] = 0x00;
            currentPos++;
        }
        // On bouge le curseur
        console_putcursor(currentPos);

    } else if (c == '\n') {
        // Si c'est un retour à la ligne (LF)
        int newPos = 80*((currentPos/80) + 1);
        // On bouge le curseur
        currentPos = newPos;
        console_putcursor(currentPos);

    } else if (c == '\f') {
        // Si c'est une suppression et retour en (0;0) (FF)
        for (int i = SIZETAB; i >= 0; i--) {
            scr_tab[i] = 0x00;
        }
        currentPos = 0;
        console_putcursor(currentPos);

    } else if (c == '\r') {
        // Si c'est un retour à la colonne 0 (CR)
        int column = currentPos%80;
        // On bouge le curseur
        currentPos -= column; 
        console_putcursor(currentPos);

    } else {

    }
    
}

// Permet de décaler les lignes vers le haut d'une ligne et nettoie la dernière
void slideUp() {
    for (int i = 0; i < SIZETAB - 80; i++) {
        scr_tab[i] = scr_tab[i+80];
    }
    for (int j = SIZETAB - 80; j < SIZETAB; j++) {
        scr_tab[j]= 0x00;
    }
    currentPos = SIZETAB - 79;
    console_putcursor(currentPos);
}

void console_putbytes(const char *s, int len) {
    for (int i = 0; i < len; i++) {
        // On regarde s'il y a un dépassement de ligne
        if (currentPos >= SIZETAB) {
            slideUp();
        }
        console_putchar(s[i]);
    }
}

void setStyle(__UINT8_TYPE__ newStyle) {
    style = newStyle;
}
