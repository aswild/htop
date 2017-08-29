/*
htop - ThermalMeter.c
(C) 2017 Allen Wild
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "CRT.h"
#include "ThermalMeter.h"

/*{
#include "Meter.h"
extern void ThermalMeter_init(Meter *this);
extern void ThermalMeter_updateValues(Meter *this, char *buf, int size);
}*/

int ThermalMeter_attributes[] = {
    METER_VALUE // the font color type
};

MeterClass ThermalMeter_class = {
    .super = {
        .extends = Class(Meter),
        .delete = Meter_delete
    },
    .updateValues = ThermalMeter_updateValues,
    .init = ThermalMeter_init,
    .defaultMode = TEXT_METERMODE,
    .maxItems = 1,
    .total = 100.0,
    .attributes = ThermalMeter_attributes,
    .name = "Thermal",
    .uiName = "Temperature",
    .caption = "Temp: ",
};
