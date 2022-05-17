#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/irq.h>
#include <stdio.h>
#include <unistd.h>
#include <n7OS/sys.h>
#include <n7OS/time.h>

extern void init_irq();

void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // Init
        init_irq();
        init_syscall();
        init_timer();
        sti();

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
        
        // Envoie interruption 50
        //__asm__("int $50"::);
        
        /* if (example() == 1) {
            printf("Appel systeme example ok\n");
        }
        shutdown(1); */

        hlt();
    }
}
