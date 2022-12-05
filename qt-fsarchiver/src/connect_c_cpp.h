/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2022 Dieter Baum.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#ifndef __CONNECT_C_CPP_H__
#define __CONNECT_C_CPP_H__

int createar();
int fsarchiver_aufruf(int argc, char *anlage0, char *anlage1, char *anlage2, char *anlage3, char *anlage4, char *anlage5, char *anlage6, char *anlage7,char *anlage8,char *anlage9,char *anlage10, char *anlage11, char *anlage12,char *anlage13,char *anlage14);
void werte_uebergeben(float prozess, int anzahl);
float werte_holen(int auswahl);
void meldungen_uebergeben(char * meldung, int auswahl);
void werte_reset();
char *meldungen_holen(int auswahl);
float df(char *device, const char *mountPoint, int flag);
float freesize(char *Partition,char *mount, int flag);
int btrfs_flag_uebergeben();

#endif // __CONNECT_C_CPP_H__












