/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Platform
#define HEADER_Platform
/*
htop - openbsd/Platform.h
(C) 2014 Hisham H. Muhammad
(C) 2015 Michael McConville
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Action.h"
#include "BatteryMeter.h"
#include "SignalsPanel.h"

extern ProcessFieldData Process_fields[];


#define MAXCPU 256
// XXX: probably should be a struct member
/*
 * Copyright (c) 1984, 1989, William LeFebvre, Rice University
 * Copyright (c) 1989, 1990, 1992, William LeFebvre, Northwestern University
 *
 * Taken directly from OpenBSD's top(1).
 *
 * percentages(cnt, out, new, old, diffs) - calculate percentage change
 * between array "old" and "new", putting the percentages in "out".
 * "cnt" is size of each array and "diffs" is used for scratch space.
 * The array "old" is updated on each call.
 * The routine assumes modulo arithmetic.  This function is especially
 * useful on BSD machines for calculating cpu state percentages.
 */
extern ScreenDefaults Platform_defaultScreens[];

extern const unsigned int Platform_numberOfDefaultScreens;

extern int Platform_numberOfFields;

/*
 * See /usr/include/sys/signal.h
 */
extern const SignalItem Platform_signals[];

extern const unsigned int Platform_numberOfSignals;

void Platform_setBindings(Htop_Action* keys);

extern MeterClass* Platform_meterTypes[];

// preserved from FreeBSD port
int Platform_getUptime();

void Platform_getLoadAverage(double* one, double* five, double* fifteen);

int Platform_getMaxPid();

double Platform_setCPUValues(Meter* this, int cpu);

void Platform_setMemoryValues(Meter* this);

/*
 * Copyright (c) 1994 Thorsten Lockert <tholo@sigmasoft.com>
 * All rights reserved.
 *
 * Taken almost directly from OpenBSD's top(1)
 */
void Platform_setSwapValues(Meter* this);

void Platform_setTasksValues(Meter* this);

char* Platform_getProcessEnv(pid_t pid);

#endif
