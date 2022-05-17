#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/irq.h>
#include <stdio.h>

extern void init_irq();

void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while (1) {
/*         printf("\f");
        printf("Hello World!\n");
        printf("\tBonjour");
        printf("\bR");
        printf("\n");
        printf("Buongiorno\r");
        printf("Ciao"); */
        /* for (int i = 0; i < 30; i++) {;
            printf("%u\n",i);
        }
        printf("Fin\n"); */

        printf("\f");
        init_irq();
        sti();
        __asm__("int $50"::);

        hlt();
    }
}
