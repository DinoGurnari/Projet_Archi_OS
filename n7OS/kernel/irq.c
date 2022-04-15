#include <inttypes.h>
#include <n7OS/irq.h>


void init_irq_entry(int irq_num, uint32_t addr) {
    idt_entry_t *entry = (idt_entry_t *) &idt[irq_num];
    
    entry->offset_inf = addr & 0xFF;
    entry->offset_sup = addr >> 8;
    entry->sel_segment = KERNEL_CS;
    entry->zero = 0;
    entry->type_attr = 0x9E;
}
