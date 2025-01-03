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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <string.h>

#include "fsarchiver.h"
#include "dico.h"
#include "common.h"
#include "archinfo.h"
#include "archreader.h"
#include "error.h"
#include "connect_c_cpp.h"
extern char home1[100];

char *compalgostr(int algo)
{
    switch (algo)
    {
        case COMPRESS_NONE:    return "none";
        case COMPRESS_LZO:     return "lzo";
        case COMPRESS_GZIP:    return "gzip";
        case COMPRESS_BZIP2:   return "bzip2";
        case COMPRESS_LZMA:    return "lzma";
	case COMPRESS_LZ4:     return "lz4";
        case COMPRESS_ZSTD:    return "zstd";
        default:               return "unknown";
    }
}

char *cryptalgostr(int algo)
{
    switch (algo)
    {
        case ENCRYPT_NONE:     return "none";
        case ENCRYPT_BLOWFISH: return "blowfish";
        default:               return "unknown";
    }
}

int archinfo_show_mainhead(carchreader *ai, cdico *dicomainhead)
{
    char buffer[256];
    char home[100];
    if (!ai || !dicomainhead)
    {   errprintf("a parameter is null\n");
        return -1;
    }
    printf("====================== archive information ======================\n"); 
   printf( "Archive type: \t\t\t%s\n", (ai->archtype==ARCHTYPE_FILESYSTEMS)?"filesystems":"flat files"); 
    if ((ai->archtype==ARCHTYPE_FILESYSTEMS)) 
        printf("Filesystems count: \t%ld\n", (long)ai->fscount); 
         
    printf("Archive id: \t\t\t%.8x\n", (unsigned int)ai->archid); 
    printf("Archive file format: \t\t%s\n", ai->filefmt); 
    printf("Archive created with: \t\t%s\n", ai->creatver); 
    printf("Archive creation date: \t\t%s\n", format_time(buffer, sizeof(buffer), ai->creattime)); 
    printf("Archive label: \t\t\t%s\n", ai->label); 
    if (ai->minfsaver > 0) // fsarchiver < 0.6.7 had no per-archive minfsaver version requirement 
        printf("Minimum fsarchiver version:\t%d.%d.%d.%d\n", (int)FSA_VERSION_GET_A(ai->minfsaver), 
            (int)FSA_VERSION_GET_B(ai->minfsaver), (int)FSA_VERSION_GET_C(ai->minfsaver), (int)FSA_VERSION_GET_D(ai->minfsaver)); 
    printf("Compression level: \t\t%d (%s level %d)\n", ai->fsacomp, compalgostr(ai->compalgo), ai->complevel); 
    printf("Encryption algorithm: \t\t%s\n", cryptalgostr(ai->cryptalgo)); 
    printf("\n"); 
    meldungen_uebergeben(cryptalgostr(ai->cryptalgo),1); 
    
    return 0;
}

int archinfo_show_fshead(cdico *dicofshead, int fsid)
{
    char magic[FSA_SIZEOF_MAGIC+1];
    char fsbuf[FSA_MAX_FSNAMELEN];
    u32 temp32;
    u64 temp64;
    u64 fsbytestotal;
    u64 fsbytesused;
    char buffer[256];
    char fslabel[256];
    char fsuuid[256];
    char fsorigdev[256];
    char home[100];
       
    // init
    memset(magic, 0, sizeof(magic));
    
    if (!dicofshead)
    {   errprintf("dicofshead is null\n");
        return -1;
    }
    
    if (dico_get_data(dicofshead, 0, FSYSHEADKEY_FILESYSTEM, fsbuf, sizeof(fsbuf), NULL)!=0)
    {   errprintf("cannot find FSYSHEADKEY_FILESYSTEM in filesystem-header\n");
        return -1;
    }

    if (dico_get_u64(dicofshead, 0, FSYSHEADKEY_BYTESTOTAL, &fsbytestotal)!=0)
    {   errprintf("cannot find FSYSHEADKEY_BYTESTOTAL in filesystem-header\n");
        return -1;
    }
    
    if (dico_get_u64(dicofshead, 0, FSYSHEADKEY_BYTESUSED, &fsbytesused)!=0)
    {   errprintf("cannot find FSYSHEADKEY_BYTESUSED in filesystem-header\n");
        return -1;
    }
    
    if (dico_get_string(dicofshead, 0, FSYSHEADKEY_FSLABEL, fslabel, sizeof(fslabel))<0)
        snprintf(fslabel, sizeof(fslabel), "<none>");
    
    if (dico_get_string(dicofshead, 0, FSYSHEADKEY_ORIGDEV, fsorigdev, sizeof(fsorigdev))<0)
        snprintf(fsorigdev, sizeof(fsorigdev), "<unknown>");
    
    // filesystem uuid: maybe an ntfs uuid or an unix uuid
    snprintf(fsuuid, sizeof(fsuuid), "<none>");
    if (dico_get_u64(dicofshead, 0, FSYSHEADKEY_NTFSUUID, &temp64)==0)
        snprintf(fsuuid, sizeof(fsuuid), "%016llX", (long long unsigned int)temp64);
    else if (dico_get_u32(dicofshead, 0, FSYSHEADKEY_FSVFATSERIAL, &temp32)==0)
        snprintf(fsuuid, sizeof(fsuuid), "%08lX", (long unsigned int)temp32);
    else if (dico_get_string(dicofshead, 0, FSYSHEADKEY_FSUUID, buffer, sizeof(buffer))==0 && strlen(buffer)==36)
        snprintf(fsuuid, sizeof(fsuuid), "%s", buffer);
    
   printf("===================== filesystem information ====================\n"); 
    printf("Filesystem id in archive: \t%ld\n", (long)fsid); 
    printf("Filesystem format: \t\t%s\n", fsbuf); 
    printf("Filesystem label: \t\t%s\n", fslabel); 
    printf("Filesystem uuid: \t\t%s\n", fsuuid); 
    printf("Original device: \t\t%s\n", fsorigdev); 
    printf("Original filesystem size: \t%s (%lld bytes)\n", format_size(fsbytestotal, buffer, sizeof(buffer), 'h'), (long long)fsbytestotal); 
    printf("Space used in filesystem: \t%s (%lld bytes)\n", format_size(fsbytesused, buffer, sizeof(buffer), 'h'), (long long)fsbytesused); 
    printf("\n"); 
    meldungen_uebergeben(fsuuid,3); 
    meldungen_uebergeben(fsorigdev,2);
    werte_uebergeben(200,15);
    
    return 0;
}

