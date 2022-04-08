#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>


void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while (1) {
        /* printf("Hello World!\n");
        printf("\tBonjour");
        printf("\bR");
        printf("\n");
        printf("Buongiorno\r");
        printf("Ciao");
        printf("\f"); */
        for (int i = 0; i < 30; i++) {;
            printf("%u\n",i);
        }
        
        hlt();
    }
}
