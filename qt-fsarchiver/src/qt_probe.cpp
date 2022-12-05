/*
 * fsarchiver: Filesystem Archiver
 * 
 * Copyright (C) 2008-2018 Francois Dupoux.  All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include <blkid.h>
#include <QString>
#include <QtGui>
#include "fsarchiver.h"
#include "qt_probe.h"
extern "C" {
#include "oper_probe.h"
#include "devinfo.h"
#include "common.h"
}
extern QString partition1[100][5];

struct s_diskinfo
{
    bool detailed;
    char format[256];
    char title[256];
};

 
//Auslesen der Partitionen Aufruf aus mainwindow.cpp
// =======================================================
QString PartitionString(int i, int j)
{
    QString Partition_Name;
    Partition_Name = partition1[i][j];
    return (Partition_Name);
    
} 


int qt_probe()
{
    struct s_devinfo blkdev[FSA_MAX_BLKDEVICES];
    int diskcount;
    int partcount;
    char temp[1024];
    //char cFormat[1024];
    int res;
    int i;
    int j = 0;
    int pos = 0;
    QString partition_;
    

    // ---- 0. get info from /proc/partitions + libblkid

   if ((res=partlist_getlist(blkdev, FSA_MAX_BLKDEVICES, &diskcount, &partcount))<1)
   {   printf("keine Disk und Partition entdeckt\n");
        return -1;
    }
    
    // ---- 2. show filesystem information
    if (partcount>0)
    {

     for (i=0; i < res; i++)
        {
            if (blkdev[i].devtype==BLKDEV_FILESYSDEV)
            {
             partition1[i][0] = partlist_getinfo(temp, sizeof(temp), &blkdev[i], 0), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 0));
             partition_ = partition1[i][0];
	     pos = partition_.indexOf("ram");
             pos = pos + partition_.indexOf("loop");
             pos = pos + partition_.indexOf("ramzswap");
             pos = pos + partition_.indexOf("zram");
             if (partition1[i][0] != "" && pos == -4){
                 j = j + 1;
                //Daten in ein Array übernehmen vielleicht für einen bessere Formatierung im Listfeld
                  //Device
                partition1[j][0]= partlist_getinfo(temp, sizeof(temp), &blkdev[i], 0), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 0));
              // File system 
                partition1[j][1]= partlist_getinfo(temp, sizeof(temp), &blkdev[i], 1), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 1)); 
                // Size  
                partition1[j][2]= partlist_getinfo(temp, sizeof(temp), &blkdev[i], 3), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 3));
                //UUID 
                partition1[j][3]= partlist_getinfo(temp, sizeof(temp), &blkdev[i], 7), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 7));
                //Bezeichnung
		partition1[j][4]= partlist_getinfo(temp, sizeof(temp), &blkdev[i], 2), strlen(partlist_getinfo(temp, sizeof(temp), &blkdev[i], 2));  
		}
             }
        }
    }
    else
    {
        printf("Es wurde keine Festplatte erkannt!\n");
    }
    return 0;
}
















