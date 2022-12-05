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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

// nur für msgprintf(MSG_FORCE
#include "dico.h"
//	#include "dichl.h"
//	#include "common.h"
//#include "oper_save.h"
//#include "strlist.h"
//#include "filesys.h"
//#include "fs_ext2.h"
//#include "fs_xfs.h"
//#include "fs_reiserfs.h"
//#include "fs_reiser4.h"
//#include "fs_jfs.h"
//#include "fs_btrfs.h"
//#include "fs_ntfs.h"
//#include "thread_comp.h"
//#include "thread_archio.h"
//#include "crypto.h"
#include "error.h"
#include <stdio.h>
//#include <mntent.h>
//#include <sys/stat.h>
#include <sys/vfs.h>
// nur für msgprintf(MSG_FORCE
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include "fsarchiver.h"
#include "connect_c_cpp.h"

float prozent;
float Anzahl_File_zu_sichern;
float Anzahl_File_gesichert;
float h_links;
float h_links_;
float EndeThreadMeldung;
float numberfile;
float numberfile_;
float numberfolder;
float numberfolder_;
float s_links;
float s_links_;
float s_special;
float s_special_;
float s_err_;
float arch_art;
float ret_fsarchiver;
char* key ;
char fsorigdev[100];
extern int btrfs_flag;


int createar(){
   bool probedetailed = 0;  //=True Anzeige Label zB C-System
   //bool probedetailed = 1;  //=False Anzeige UUID
   int test = 0;
   //test = oper_probe(probedetailed);
   return test;
}

void werte_uebergeben(float prozess, int auswahl){
     if (auswahl ==1){
         // bei kleinen Verzeichnissen ist das Ende der Sicherung bzw Wiederherstellung bereits erreicht, bevor werte_uebergeben
         // aufgerufen wird. Das bedeutet, dass der prozess auf 0 zurückgesetzt wird.
         // Um dennoch die 99% oder 100% abrufen zu können, musste nachfolgende Abhängigkeit eingeschoben werden.
         if (prozess != 0)
     	     prozent = prozess;
         }
     if (auswahl ==2){
         if (prozess != 0)
     	    Anzahl_File_zu_sichern = prozess;
         }
     if (auswahl ==3)
         if (prozess != 0){ 
     	    Anzahl_File_gesichert = prozess;
         }
     if (auswahl ==4)
         if (prozess != 0){ 
     	    EndeThreadMeldung = prozess;
         }
     if (auswahl ==5)
            h_links_ = prozess;
     if (auswahl ==6){
         if (prozess != 0)
     	    numberfile = prozess;
         }
     if (auswahl ==7)
         if (prozess != 0){ 
     	    numberfolder = prozess;
         }
     if (auswahl ==8)
         if (prozess != 0){ 
     	    s_links = prozess;
         }
     if (auswahl ==9)
         if (prozess != 0){ 
     	    h_links = prozess;
         }
     if (auswahl ==10)
         if (prozess != 0){ 
     	    s_special = prozess;
         }
     if (auswahl ==11)
      	    s_special_ = prozess;
     if (auswahl ==12)
    	    numberfile_ = prozess;
     if (auswahl ==13)
     	    numberfolder_ = prozess;
     if (auswahl ==14)
     	    s_links_ = prozess;
     if (auswahl ==15)
     	    arch_art = prozess;
     if (auswahl ==16)
     	    s_err_ = prozess;
     if (auswahl ==17)
     	    ret_fsarchiver = prozess;	    
   }

float werte_holen(int auswahl){
      if (auswahl ==1)        
     	return prozent;
      if (auswahl ==2)
     	return Anzahl_File_zu_sichern;
      if (auswahl ==3)
     	return Anzahl_File_gesichert;
      if (auswahl ==4)
     	return EndeThreadMeldung;
      if (auswahl ==5)
     	return h_links_;
      if (auswahl ==6)
     	return numberfile;
      if (auswahl ==7)
     	return numberfolder;
      if (auswahl ==8)
     	return s_links;
      if (auswahl ==9)
     	return h_links;
      if (auswahl ==10)
     	return s_special;
      if (auswahl ==11)
     	return s_special_;
      if (auswahl ==12)
     	return numberfile_;
      if (auswahl ==13)
     	return numberfolder_;
      if (auswahl ==14)
     	return s_links_;
      if (auswahl ==15)
     	return arch_art;
      if (auswahl ==16)
     	return s_err_;
      if (auswahl ==17)
     	return ret_fsarchiver;	
      return -1;
    }
 
void werte_reset(){
      prozent = 0;        
      Anzahl_File_zu_sichern = 0;
      Anzahl_File_gesichert = 0;
      h_links = 0;
      h_links_ = 0;
      numberfile = 0;
      numberfile_ = 0;
      numberfolder = 0;
      numberfolder_ = 0;
      s_links = 0;
      s_links_ = 0;
      s_special = 0;
      s_special_ = 0;
      s_err_ = 0;
   }

void meldungen_uebergeben(char* meldung, int auswahl){
     if (auswahl ==1) {
         key = meldung;
         }
     if (auswahl ==2) {
     	 strncpy(fsorigdev,meldung,100);
         fsorigdev[99] = 0;
         }
    }

char *meldungen_holen(int auswahl){
      if (auswahl ==1) {
         return key;
      }
      if (auswahl ==2)  
        return fsorigdev;
      return "-1";
      
}

float df(char *device, const char *mountPoint, int flag )
{
	struct statfs s;
	long blocks_used;
	long blocks_percent_used;

	if (statfs(mountPoint, &s) != 0) {
		perror(mountPoint);
		return 1;
	}

	if (s.f_blocks > 0) {
		blocks_used = s.f_blocks - s.f_bfree;
		blocks_percent_used = (long)
			(blocks_used * 100.0 / (blocks_used + s.f_bavail) + 0.5);
		/*
		printf("%-20s %9ld %9ld %9ld %3ld%% %s\n",
			   device,
			   (long) (s.f_blocks * (s.f_bsize / 1024.0)),
			   (long) ((s.f_blocks - s.f_bfree) * (s.f_bsize / 1024.0)),
			   (long) (s.f_bavail * (s.f_bsize / 1024.0)),
			   blocks_percent_used, mountPoint);
*/
	}
   switch (flag)
        {
   	case 1:		return (blocks_percent_used);
      case 2:		return (long) (s.f_blocks * (s.f_bsize / 1024000.0));
	   case 3:		return (long) ((s.f_blocks - s.f_bfree) * (s.f_bsize / 1024000.0));	
	   case 4:		return (long) (s.f_bavail * (s.f_bsize / 1024000.0));
	   default:		return 0;
       }		
			  
}




float freesize(char *Partition,char *mount, int flag)
{
float prozent=df(Partition, mount, flag);
 	return prozent;
}

int btrfs_flag_uebergeben(){
     if (btrfs_flag == 1) {
         return 1;
         }
     return 0;
  }














