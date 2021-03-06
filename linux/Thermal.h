/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Thermal
#define HEADER_Thermal
/*
htop - Thermal.h
(C) 2017 Allen Wild
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define MAX_ZONES 6
#define MAX_PATHLEN 64
#define MAX_TYPELEN 64

#define SYS_THERMAL "/sys/class/thermal"
#define SYS_THERMAL_ZONE SYS_THERMAL "/thermal_zone%d"
#define SYS_THERMAL_ZONE_TYPE SYS_THERMAL_ZONE "/type"
#define SYS_THERMAL_ZONE_TEMP SYS_THERMAL_ZONE "/temp"

#define THERMAL_ZONE "thermal_zone"
#define THERMAL_ZONE_LEN strlen(THERMAL_ZONE)



void ThermalMeter_init(Meter *this);

void ThermalMeter_updateValues(Meter *this, char *buf, int size);

#endif
