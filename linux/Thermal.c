/*
htop - Thermal.c
(C) 2017 Allen Wild
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include "Meter.h"

#define MAX_ZONES 6
#define MAX_PATHLEN 64
#define MAX_TYPELEN 64

#define SYS_THERMAL "/sys/class/thermal"
#define SYS_THERMAL_ZONE SYS_THERMAL "/thermal_zone%d"
#define SYS_THERMAL_ZONE_TYPE SYS_THERMAL_ZONE "/type"
#define SYS_THERMAL_ZONE_TEMP SYS_THERMAL_ZONE "/temp"

#define THERMAL_ZONE "thermal_zone"
#define THERMAL_ZONE_LEN strlen(THERMAL_ZONE)

typedef struct {
    int valid;
    char type[MAX_TYPELEN];
} thermal_zone_t;

static thermal_zone_t zones[MAX_ZONES];
static int found_zones;

void ThermalMeter_init(Meter *this) {
    FILE *fp;
    DIR *dir;
    struct dirent *de;
    char path_buf[MAX_PATHLEN] = {0};

    (void)this; // suppress unused parameter warning

    memset(zones, 0, sizeof(zones));
    found_zones = 0;

    if ((dir = opendir(SYS_THERMAL)) == NULL) {
        return;
    }

    while ((de = readdir(dir)) != NULL) {
        if (!strncmp(de->d_name, THERMAL_ZONE, THERMAL_ZONE_LEN)) {
            int i = (int)strtol(de->d_name + THERMAL_ZONE_LEN, NULL, 10);
            if (i >= MAX_ZONES) {
                continue;
            }

            snprintf(path_buf, sizeof(path_buf), SYS_THERMAL_ZONE_TEMP, i);
            if (access(path_buf, R_OK)) {
                // unable to read temp file, skip
                continue;
            }

            zones[i].valid = 1;
            found_zones++;
            snprintf(path_buf, sizeof(path_buf), SYS_THERMAL_ZONE_TYPE, i);
            if ((fp = fopen(path_buf, "r")) != NULL) {
                char *newline;
                size_t r;
                memset(&zones[i].type, 0, MAX_TYPELEN);
                r = fread(&zones[i].type, 1, MAX_TYPELEN-1, fp);
                fclose(fp);
                if (r < 1) {
                    strncpy((char*)&zones[i].type, "[unknown]", MAX_TYPELEN);
                }
                else if ((newline = strchr(zones[i].type, '\n')) != NULL) {
                    *newline = '\0';
                }
            }
        }
    }
    closedir(dir);
}

void ThermalMeter_updateValues(Meter *this, char *buf, int size) {
    FILE *fp;
    char path_buf[MAX_PATHLEN] = {0};
    char temp_buf[8] = {0};
    int i, len = 0;

    (void)this; // suppress unused parameter warning

    if (!found_zones) {
        snprintf(buf, size, "[not available]");
        return;
    }

    for (i = 0; i < MAX_ZONES; i++) {
        if (!zones[i].valid) {
            continue;
        }
        snprintf(path_buf, sizeof(path_buf), SYS_THERMAL_ZONE_TEMP, i);
        if ((fp = fopen(path_buf, "r")) != NULL) {
            long ltemp;
            float ftemp;
            if (fread(temp_buf, 1, sizeof(temp_buf), fp) < 1) {
                ltemp = 0;
            } else {
                ltemp = strtol(temp_buf, NULL, 10);
            }
            ftemp = ltemp / 1000.0;
            len += snprintf(buf + len, size - len, "%s: %.1f, ", zones[i].type, ftemp);
            fclose(fp);
        }
    }
    // strip trailing ", "
    buf[len - 2] = '\0';
}
