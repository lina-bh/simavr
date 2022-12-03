#!/bin/sh
DESTDIR=/usr/local
TRIPLE="obj-$(clang -dumpmachine)"
mkdir -p "${DESTDIR}/include/simavr/avr"
install -m644 sim/*.h "${DESTDIR}/include/simavr/"
install -m644 sim_core_*.h "${DESTDIR}/include/simavr"
install -m644 sim/avr/*.h "${DESTDIR}/include/simavr/avr"
install "${TRIPLE}/libsimavr.a" "${DESTDIR}/lib/"
#pkgconfig stuff
#linux avr so stuff
install "${TRIPLE}/run_avr.elf" "${DESTDIR}/bin/simavr"
