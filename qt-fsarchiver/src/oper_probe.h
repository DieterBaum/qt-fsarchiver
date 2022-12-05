/*
 * fsarchiver: Filesystem Archiver
 * 
 * Copyright (C) 2008-2022 Francois Dupoux.  All rights reserved.
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
 * Homepage: http://www.fsarchiver.org
 */

#ifndef __OPER_PROBE_H__
#define __OPER_PROBE_H__

int oper_probe(bool details);
int partlist_getlist(struct s_devinfo *blkdev, int maxblkdev, int *diskcount, int *partcount);
char *partlist_getinfo(char *bufdat, int bufsize, struct s_devinfo *blkdev, int item);

#endif // __OPER_PROBE_H__

