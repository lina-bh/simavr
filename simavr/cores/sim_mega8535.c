/*
	sim_mega8535.c

	Copyright 2008, 2009, 2022 Michel Pollet <buserror@gmail.com>

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

#include "sim_avr.h"

#define SIM_VECTOR_SIZE 2
#define SIM_MMCU "atmega8535"
#define SIM_CORENAME mcu_mega8535

#define _AVR_IO_H_
#define __ASSEMBLER__
#include "avr/iom8535.h"

#define ICP_PORT PORTD
#define ICP_PIN 6

#define OC1A_PORT PORTD
#define OC1A_PIN 5

#define OC2_PORT PORTD
#define OC2_PIN 7

#define OC1B_PORT PORTD
#define OC1B_PIN 4

#define EXT_CLOCK0_PORT PORTB
#define EXT_CLOCK0_PIN 0

#define EXT_CLOCK1_PORT PORTB
#define EXT_CLOCK1_PIN 1

#define USART_RXC_vect 11
#define USART_TXC_vect 13
// instantiate the new core
#include "sim_megax.h"

static avr_t * make()
{
	return avr_core_allocate(&SIM_CORENAME.core, sizeof(struct mcu_t));
}

avr_kind_t mega8535 = {
	.names = { "atmega8535" },
	.make = make
};

