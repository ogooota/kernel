#ifndef __IRQ_H
#define __IRQ_H

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1

#define ICW1_ICW4      0x01
#define ICW1_SINGLE    0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_INIT      0x10

#define ICW4_8086 0x01

#define CASCADE_IRQ 2

#endif
