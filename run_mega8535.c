/*
most of this file is based on:
run_avr.c

Copyright 2008, 2010 Michel Pollet <buserror@gmail.com>

This file is part of simavr.

simavr is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

simavr is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with simavr.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>
#include <simavr/sim_core.h>
#include <simavr/sim_hex.h>
#include <simavr/avr_ioport.h>
#include <simavr/sim_core_decl.h>

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

static avr_t* avr = NULL;

static uint8_t porta = 0;
static void porta_irq_cb(avr_irq_t* irq, uint32_t val, void* param) {
	porta = (porta & ~(1 << irq->irq)) | (val << irq->irq);
}

static uint8_t portb = 0;
static void portb_irq_cb(avr_irq_t* irq, uint32_t val, void* param) {
	portb = (portb & ~(1 << irq->irq)) | (val << irq->irq);
}

int main(int argc, char *argv[]) {
	elf_firmware_t elf;
	uint32_t loadBase = AVR_SEGMENT_OFFSET_FLASH;
	memset(&elf, 0, sizeof(elf));

	if (argc == 1) abort();

	sim_setup_firmware(argv[1], loadBase, &elf, argv[0]);
	avr = avr_make_mcu_by_name("atmega8535");
	avr_init(avr);
	avr_load_firmware(avr, &elf);

	for (int i = 0; i < 8; i++) {
		avr_irq_register_notify(
			avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('A'), i),
			porta_irq_cb,
			NULL
		);
		avr_irq_register_notify(
			avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), i),
			portb_irq_cb,
			NULL
		);
	}
	for (;;) {
		fprintf(stderr, "pc:%02x ", avr->pc>>1);

		eprintf("C%d ", avr->sreg[S_C]);
		eprintf("Z%d ", avr->sreg[S_Z]);
		eprintf("N%d ", avr->sreg[S_N]);
		eprintf("V%d ", avr->sreg[S_V]);
		eprintf("S%d ", avr->sreg[S_S]);
		eprintf("H%d ", avr->sreg[S_H]);
		eprintf("T%d ", avr->sreg[S_T]);
		eprintf("I%d ", avr->sreg[S_I]);
		//eprintf("PORTA=0x%02x PORTB=0x%02x",
		eprintf("PORTA=%u PORTB=%u",
			porta,
			portb);
		eprintf(" ");
		getchar();
		avr_run(avr);
	}
}
