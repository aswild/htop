/*
htop - Thermal.c
(C) 2017 Allen Wild
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Meter.h"

void ThermalMeter_init(Meter *this) {
    (void)this; // no-op, suppress unused parameter warning
}

void ThermalMeter_updateValues(Meter *this, char *buf, int size) {
    (void)this;
    (void)buf;
    (void)size;
}
