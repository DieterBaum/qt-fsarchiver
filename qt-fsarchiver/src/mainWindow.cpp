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

#include "mainWindow.h"
#include <string.h>
#include <iostream>
#include <time.h>
#include <sys/times.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <mntent.h>
#include <QtGui>
#include <QInputDialog>
#include "filedialog.h"
#include "setting.h"
#include "mbr.h"
#include "clone.h"
#include "dir.h"
#include "qt_probe.h"
#include "order.h"
extern "C" {
#include "connect_c_cpp.h"
#include "fsarchiver.h"
}
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

using namespace std;

//QString Datum_akt("");
QString partition_;
QString UUID;
string partition_str;
QString folder;
QString folder1;
QString _Datum;
QString DateiName("") ;
extern int btrfs_flag;
extern QString list_;
extern int dialog_auswertung;
extern int show_flag;
extern QString parameter[15];
extern QString partition1[100][5];
extern int sleepfaktor;
extern QString part[100][10];
extern QString folder_file_;
QString widget[100];
int endeThread;
int sekunde_elapsed;
int minute_elapsed;
int sekunde_summe;
QStringList items_kerne_;
QStringList items_GB;
QStringList items_zstd;
QString partition_typ_;
QString partition_typ;
QString part_art;
QString zip_[11];
QString SicherungsDateiName;
QString SicherungsFolderFileName;
int dummy_prozent;
int flag_View; 
int flag_end;
int sekunde_tara; 
int thread_run;
QString pid1;
QString befehl_pbr;
int stopFlag;
int row_1;
QString order_name;
int order = 0;
int run_ = 0;
QString widget_2_[100]; // ordername
QString widget_2[100]; // attribute
int live_flag;
QString part_list;
int rootpassword = 0;
int zstd_level;
QString part_size_compress;
float size_folder_float;
float part_size_compress_float;
QString size_folder;
int esc_ = 0;
int live_save = 0;
int end_mediafolder = 0;

extern "C"
{
int fsarchiver_main(int argc, char**argv);
}
int fsarchiver_aufruf(int argc, char *anlage0=NULL, char *anlage1=NULL, char *anlage2=NULL, char *anlage3=NULL, char *anlage4=NULL, char *anlage5=NULL, char *anlage6=NULL, char *anlage7=NULL, char *anlage8=NULL, char *anlage9=NULL, char *anlage10=NULL, char *anlage11=NULL, char *anlage12=NULL, char *anlage13=NULL, char *anlage14=NULL)
{
    char *argv[15];
    int ret;
    QString str;
    argv[0] = anlage0;
    argv[1] = anlage1;
    argv[2] = anlage2;
    argv[3] = anlage3;
    argv[4] = anlage4;
    argv[5] = anlage5;
    argv[6] = anlage6;
    argv[7] = anlage7;
    argv[8] = anlage8;
    argv[9] = anlage9;
    argv[10] = anlage10;
    argv[11] = anlage11;
    argv[12] = anlage12;
    argv[13] = anlage13;
    argv[14] = anlage14;
    if (geteuid() != 0) // 0 is the UID of the root  1000 von home user
	{
      qDebug() << "The program must be started with root privileges";
      return 1;
	}
    //Prüfung ob qt-fsarchiver schon gestartet ist	
      QString filename = "/etc/pid.txt";
      QFile file(filename);
      QTextStream ds(&file);
      QString befehl;
      if(file.open(QIODevice::ReadWrite | QIODevice::Text))
         {
         befehl = "ps -C qt-fsarchiver 1> " +  filename;
         if (system (befehl.toLatin1().data()))
             befehl = "";
         QString pid_nummer = ds.readLine();
         pid_nummer = ds.readLine();
         pid_nummer = ds.readLine();
         int found = pid_nummer.indexOf("qt-fsarchiver");
         if(found > -1)
           {
           qDebug() << "qt-fsarchiver must be started only once";
           return 1; 
           }   
	 }
	 file.close();
	 befehl = "rm /etc/pid.txt";
	 if (system (befehl.toLatin1().data()))
             befehl = "";
  //  printf(("fsarchiver_aufruf in connect_cpp %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n"),argc, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14]);
    ret=fsarchiver_main(argc, argv);
    str = anlage1;
    if (str != "archinfo")
       {
       if (ret == 0)
           werte_uebergeben(10,17);
       if (ret != 0) 
           werte_uebergeben(11,17);   
       }
    if (str == "archinfo"){
       if (ret == 0)
           werte_uebergeben(12,17);
       if (ret != 0) 
           werte_uebergeben(13,17);   
       }
 return ret;
}

MWindow::MWindow()
{
   if(list_ != "")
      make_direct();
   if (dialog_auswertung == 6 or dialog_auswertung == 7)
        return;
   questionLabel = new QLabel;
   QStringList dummy;
   QStringList partition_kurz;
   QString partition1_;
   QStringList items; 
   int pos = 0, pos1 = 0;
   int i = 0, j = 0;
   QString tmp;
   int temp = 0;
   QString rootpath = QDir::rootPath();
   QString homepath = QDir::homePath(); 
   QString befehl;  
   setupUi(this);
   rdBt_saveFsArchiv->setChecked(true);
   dirModel = new QFileSystemModel;
   selModel = new QItemSelectionModel(dirModel);
   treeView->setModel(dirModel);
   treeView->setSelectionModel(selModel);
   treeView->setEnabled(true);
   QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
   dirModel->setRootPath(QDir::rootPath());
   treeView->setRootIndex(cwdIndex);
//   groupBox->setFlat (true);
   pushButton_restore->setEnabled(false);
   // Signal-Slot-Verbindungen  Werkzeugleiste
   //connect( action_Beenden, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
   connect( action_Beenden, SIGNAL(triggered(bool)), this, SLOT(esc_end()));
   connect( action_partition_save, SIGNAL(triggered(bool)),this, SLOT(save_button()));
   connect( action_partition_restore, SIGNAL(triggered(bool)),this, SLOT(restore_button()));
   connect( action_Information, SIGNAL(triggered(bool)),this, SLOT(info()));
   connect( action_Einstellungen, SIGNAL(triggered(bool)),this, SLOT(einstellungen()));
   connect( action_mbr_save, SIGNAL(triggered(bool)), this, SLOT(mbr_save()));
   connect( action_mbr_restore, SIGNAL(triggered(bool)), this, SLOT(mbr_restore()));
   connect( action_dir_save, SIGNAL(triggered(bool)), this, SLOT(dir_save()));
   connect( action_dir_restore, SIGNAL(triggered(bool)), this, SLOT(dir_restore()));
   connect( action_CloneDrive, SIGNAL(triggered(bool)), this, SLOT(clone_save()));
   connect( actionClone_HD, SIGNAL(triggered(bool)), this, SLOT(clone_save()));
   connect( action_Order_list_edit, SIGNAL(triggered(bool)), this, SLOT(order_edit()));
   connect( action_Order, SIGNAL(triggered(bool)), this, SLOT(make_order()));
   connect( pushButton_order, SIGNAL( clicked() ), this, SLOT(listWidget2_auslesen()));
   //schließt alle Fenster
   //connect( pushButton_end, SIGNAL( clicked() ), qApp, SLOT(quit()));
   connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(del_mediafolder()));
   //schließt das aktuelle (this)Fenster:
   connect( pushButton_save, SIGNAL( clicked() ), this, SLOT(savePartition()));
   connect( pushButton_restore, SIGNAL( clicked() ), this, SLOT(restorePartition()));
   connect( pushButton_partition, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
   connect( pushButton_folder, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
   connect( rdBt_saveFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( rdBt_restoreFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
   connect( chk_hidden, SIGNAL( clicked() ), this, SLOT(chkhidden()));
   connect( chk_split, SIGNAL( clicked() ), this, SLOT(chkGB()));
   connect( cmd_zstd, SIGNAL( clicked() ), this, SLOT(zip_einlesen()));
   // Zeitgeber für Berechnung remainingTime
   timer = new QTimer(this);
   live_flag = 0;
   if (live_flag == 1)
      {
      action_Order_list_edit->setEnabled(false); //Aktionen sind nicht erreichbar
      action_Order->setEnabled(false);
      }
   items_kerne_ << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12"<<  "13" << "14" << "15" << "16" <<  "17" << "18" << "19" << "20";
   cmb_kerne->addItems (items_kerne_);
   items_kerne_.clear();
   items_GB << "2" << "4" << "4,7";
   cmb_GB->addItems (items_GB);
   items_GB.clear();
   items_zstd << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" <<  "17" << "18" << "19" << "20" << "21" << "22";
   cmb_zstd->addItems (items_zstd);
   items_zstd.clear();
   zip_[0]=(tr("lz4", "lz4"));
   zip_[1]=(tr("lzo", "lzo"));
   zip_[2]=(tr("gzip fast","gzip fast"));
   zip_[3]=(tr("gzip standard","gzip standard"));
   zip_[4]=(tr("qzip best","qzip best"));
   zip_[5]=(tr("bzip2 fast","bzip2 fast"));
   zip_[6]=(tr("bzip2 good"," bzip2 good"));
   zip_[7]=(tr("lzma fast","lzma fast"));
   zip_[8]=(tr("lzma medium","lzma medium"));
   zip_[9]=(tr("lzma best","lzma best"));
   zip_[10]=(tr("zstd","zstd"));
   items << zip_[0] << zip_[1] << zip_[2] << zip_[3] <<  zip_[4];
   cmb_zip->addItems (items);
   items.clear();
   items << zip_[5] << zip_[6] << zip_[7] << zip_[8] << zip_[9] << zip_[10];
   cmb_zip->addItems (items);
   items.clear();
   QDir dir1(homepath + "/.config/qt5-fsarchiver");
   if (!dir1.exists()){
      befehl = "mkdir " + homepath + "/.config/qt5-fsarchiver 2>/dev/null" ;
      if(system (befehl.toLatin1().data()))
          befehl = "";
      }
   QDir dir2(rootpath + "/.config/qt5-fsarchiver");
   if (!dir1.exists()){
      befehl = "mkdir " + rootpath + "/.config/qt5-fsarchiver 2>/dev/null" ;
      if(system (befehl.toLatin1().data()))
          befehl = "";
      }
   // wegen Suse
   QDir dir3("/media");
   QString media = "/media";
   if (!dir3.exists()){
       befehl = "mkdir " + media + " 2>/dev/null" ;
       if(system (befehl.toLatin1().data()))
          befehl = "";
       }
   // beim Abbruch einer Sicherung bleiben eventuell Daten in /tmp/fsa erhalten.
   // Bei ersten Start werden eventuell vorhandene Dateien gelöscht.
   // Daher darf nach dem Abbruch von Live-Sicherungen keinenfalls die Daten in /tmp/fsa gelöscht werden
   // Das System sürzt ab!!
   // Sind in /tmp/fsa Dateien vom gleichen Tag vorhanden, werden diese nicht gelöcht. So wird der Systemabsturz verhindert.

    QDate date = QDate::currentDate();
    QString dw = date.toString("yyyyMMdd");
    
    QDir dir4("/tmp/fsa");
    if (dir4.exists())
         {
        befehl = "dir /tmp/fsa 1> " +  homepath + "/.config/qt5-fsarchiver/tmp.txt";
        if(system (befehl.toLatin1().data()))
            befehl = "";
        temp = 1;    
        }
    QString filename = homepath + "/.config/qt5-fsarchiver/tmp.txt";
    QFile file4(filename);
    QTextStream ds(&file4);
    QThread::msleep(10 * sleepfaktor);
    if( file4.open(QIODevice::ReadOnly|QIODevice::Text)) 
       {
       while (!ds.atEnd())
    	  {
      	  tmp= ds.readLine();
      	  pos = tmp.indexOf(dw);
      	     if(pos > -1)
      	        {
      	        temp = 1;
      	        break;
      	        }
   	      if( tmp.isEmpty() )
         	 break;
          } 
   	  file4.close();
   	} 
   int pida1 = pid_ermitteln();
   if (pida1 == 1 && temp == 0)
      {
       befehl = "rm -r -f /tmp/fsa 2>/dev/null"; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
       }
   else 
       qDebug() << "/tmp/fsa wird nicht gelöscht"; 
   befehl = "rm " + homepath + "/.config/qt5-fsarchiver/tmp.txt 2>/dev/null"; 
   if(system (befehl.toLatin1().data()))
       befehl = "";
   if (pida1 > 1) 
       {
       QMessageBox::warning(this,tr("Note", "Hinweis"),
       	tr("Qt-fsarchiver can only be started once. The program must be terminated..\n", "Qt-fsarchiver kann nur einmal gestartet werden. Das Programm muss beendet werden.\n"));
      return;
      }
   j = 0; 
   // /home/user/.qt5-fs-client entfernen  wird nicht mehr benötigt, da das Arbeiten mit dem Netzwerk aus dem Code entfernt wurde 
   befehl = "rm -r " + homepath + "/.qt5-fs-client 2>/dev/null"; 
   if(system (befehl.toLatin1().data()))
      befehl = "";
   // Ini-Datei auslesenc
   QFile file(homepath + "/.config/qt5-fsarchiver/qt5-fsarchiver.conf");
   QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
   if (file.exists()) {
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("Kompression").toInt();
        cmb_zip -> setCurrentIndex(auswertung); 
        if (auswertung == 10)
            cmb_zstd->setEnabled(true);
        else
            cmb_zstd->setEnabled(false);
        if (auswertung != 10)
            cmb_zstd->setEnabled(false);    
        auswertung = setting.value("Kerne").toInt();       
        cmb_kerne -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("overwrite").toInt();
        if (auswertung ==1)
           chk_overwrite->setChecked(true); 
        auswertung = setting.value("pbr").toInt();
        if (auswertung ==1)
           chk_pbr->setChecked(true); 
        auswertung = setting.value("tip").toInt();
        if (auswertung ==1)
           chk_Beschreibung->setChecked(true);  
        auswertung = setting.value("key").toInt();
        if (auswertung ==1)
           chk_key->setChecked(true); 
	auswertung = setting.value("hidden").toInt();
        if (auswertung ==1)
           chk_hidden->setChecked(true);
        auswertung = setting.value("Passwort").toInt(); 
        if (auswertung ==1)
           	lineKey ->setEchoMode(QLineEdit::Normal);
        else
		lineKey ->setEchoMode(QLineEdit::Password); 
	zstd_level = setting.value("zstd").toInt();
        cmb_zstd -> setCurrentIndex(zstd_level-1);	
        setting.endGroup();
        } 
   else {
        lineKey ->setEchoMode(QLineEdit::Password);
        cmb_kerne -> setCurrentIndex(0);
        chk_Beschreibung->setChecked(true);
        chk_overwrite->setChecked(true);
        cmb_zip -> setCurrentIndex(10);
        setting.beginGroup("Basiseinstellungen");
        setting.setValue("showPrg",1); 
        setting.setValue("ssh",1); 
        setting.setValue("sshfs",1); 
        setting.setValue("dummy",2);
        setting.endGroup();
        cmb_zstd -> setCurrentIndex(7);
        cmb_zstd->setEnabled(true);
        }
   label_4->setEnabled(false);
   chk_overwrite->setEnabled(true);
   cmb_zip->setEnabled(false);
   cmb_GB->setEnabled(false);
   chk_Beschreibung->setEnabled(true);
   chk_Beschreibung->setChecked(true);
   label->setEnabled(false);
        starteinstellung();
        if (geteuid() == 0) // 0 is the UID of the root  1000 von home user
	{
 	qt_probe();
 	for (i=1; i < 100; i++)
           {
           for (j=0; j < 5; j++)
              {
              if (partition1[i][1] != "")
                 {
                 part[i-1][j] = partition1[i][j];
                 }
               }
            }
           format();
           j = 2 ;
           i=0;
           while (j > 1)
	   {
		j = widget[i+1].length();
                partition_ = part[i][0]; // z.B. sda1
		UUID = part[i][3];
                partition_typ = part[i][1];
                pos = partition_typ.indexOf("fat");
                if (pos > -1)
		   partition_typ = "vfat";
                pos = partition_typ.indexOf("ext3");
                pos1 = partition_typ.indexOf("ext4");
                if (pos > -1 || pos1 > -1)
		    partition_typ = "ext";
		partition_ = "/dev/"+ partition_;     
                //Prüfen ob System oder Home Partition
                part_art = mtab_einlesen(partition_); // Partition übergeben
                if (!is_mounted(partition_.toLatin1().data()))
                   { 
                   if (part_art !="system" or part_art != "home" or part_art == "boot" or part_art == "boot/efi")
                     {
			         if (partition_typ == "ext" || partition_typ == "btrfs"|| partition_typ == "vfat" || partition_typ ==  "ntfs" )
                   		{
                   	 	befehl = "mkdir -m 0777 /media/" + part[i][0];
                        if(system (befehl.toLatin1().data()))
                                   befehl = "";
                        befehl = "mount /dev/" + part[i][0] + " /media/" + part[i][0];
                        if(system (befehl.toLatin1().data()))
                                   befehl = "";
                         	}
                        }
 		     }
                i++;
        	if (i > 99)
           	{
           	break;
           	}
           }
        partition_ = "" ;
      	}
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("showPrg").toInt();
        setting.endGroup();
        if (auswertung ==1 and show_flag == 0){
        int ret = questionMessage(tr("The file /usr/share/doc/qt-fsarchiver/doc/Readme contains instructions for using the program. Do you still want to see this note? You can change this in the basic settings.", "In der Datei /usr/share/doc/qt-fsarchiver/doc/Liesmich sind Hinweise zur Nutzung des Programms enthalten. Wollen Sie diesen Hinweis weiterhin sehen? Sie können dies in den Basiseinstellungen ändern."));
    		if (ret == 2){
		//Basiseinstellungen ändern
        	QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
        	setting.beginGroup("Basiseinstellungen");
        	setting.setValue("showPrg",0);
        	setting.endGroup();
                }
        show_flag = 1;
	} 
}

void MWindow::chkkey(){
     Qt::CheckState state;
     state = chk_key->checkState();
     if (state == Qt::Checked)
        lineKey->setEnabled(true);
     else 
        lineKey->setEnabled(false);

}

void MWindow::chkhidden(){
     Qt::CheckState state;
     state = chk_hidden->checkState();
     if (rdBt_saveFsArchiv->isChecked())
        starteinstellung();   
     else
        rdButton_auslesen();
}


void MWindow::chkGB(){
     Qt::CheckState state;
     state = chk_split->checkState();
     if (state == Qt::Checked)
        cmb_GB->setEnabled(true);
     else 
        cmb_GB->setEnabled(false);
}

void MWindow::save_button(){
     rdBt_saveFsArchiv->setChecked(true);
     rdButton_auslesen();
}

void MWindow::restore_button(){
     rdBt_restoreFsArchiv->setChecked(true);
     rdButton_auslesen();
}

void MWindow::rdButton_auslesen()
     {
     order = 0;
     Qt::CheckState state;
     state= chk_hidden->checkState();
     QStringList filters;
     label_Partition->setText (tr("Existing partitions:", "vorhandene Partitionen"));
     if (rdBt_saveFsArchiv->isChecked())
        {
	starteinstellung();
        }
     if (rdBt_restoreFsArchiv->isChecked())
        {
 		label_folder->setText (tr("Backup File", "Sicherungsdatei"));
      		pushButton_restore->setText (tr("Partition restore", "Partition zurückschreiben"));
                pushButton_restore->setEnabled(true);
                pushButton_save->setEnabled(false);
                lineEdit_DateiName->setEnabled(false);
                label_4->setEnabled(false);
                chk_overwrite->setEnabled(false);
                cmb_zip->setEnabled(false);
                cmb_zstd->setEnabled(false);
                chk_Beschreibung->setEnabled(false);
                label->setEnabled(false);
                label_2->setEnabled(false);
                label_3->setEnabled(false);
                AnzahlsaveFile->setEnabled(false);
                AnzahlgesicherteFile->setEnabled(false);
                chk_key->setText (tr("Decrypt\nbackup. key:",
		 "Sicherung\nentschlüsseln. Schlüssel")); 
                chk_split->setEnabled(false); 
		chk_pbr->setEnabled(false); 
                filters << "*.fsa";
                if (state == Qt::Checked)
               	        dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	    	else	
	       		dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   		dirModel->setNameFilters(filters);
   		listWidget_2->setHidden(true);
         }
     } 

void MWindow::starteinstellung()
     {
     Qt::CheckState state;
     state= chk_hidden->checkState();
     QStringList filters;
            label_folder->setText (tr("Backup directory", "Sicherungsverzeichnis"));
            lineEdit_DateiName->setEnabled(true);
            pushButton_restore->setEnabled(false);
            pushButton_save->setEnabled(true);
            label_4->setEnabled(true);
            chk_overwrite->setEnabled(true);
            cmb_zip->setEnabled(true);
           // cmb_zstd->setEnabled(true);
            chk_Beschreibung->setEnabled(true);
            label->setEnabled(true);
            label_2->setEnabled(true);
            label_3->setEnabled(true);
            AnzahlsaveFile->setEnabled(true);
            AnzahlgesicherteFile->setEnabled(true);
            chk_key->setText (tr("Encrypt\nbackup. key:", "Sicherung\nverschlüsseln. Schlüssel"));
            chk_split->setEnabled(true); 
            chk_pbr->setEnabled(true);  
            chkkey(); 
            filters << "*.*";
            listWidget_2->setHidden(true);
            if (state == Qt::Checked){
              if (rdBt_saveFsArchiv->isChecked())
		dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot | QDir::Hidden);
              else 
   	        dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
	    }		
	    if (state != Qt::Checked){
              if (rdBt_saveFsArchiv->isChecked())
		dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot);
              else 
   	        dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	    }
   	    dirModel->setNameFilters(filters);  
}

int MWindow::savePartition() 
{
QString homepath = QDir::homePath();
if(order == 1)
{
   save_restorePartiiton_list();
   run_ = 1;
   return 1;
}  
     QFile file(folder);
     QString befehl;
     QString text;
     QString attribute;
     Qt::CheckState state;
     Qt::CheckState state1;
     Qt::CheckState state3;
     int err = 0;
     char * part_;
     QString keyText = "";
     QString compress = "";
     int found = 0; 
     int zip;
     int zip_zstd;
     bool ok;
     int i = 0;
     run_ = 1;
     int len = 0;
     int result = 0;
     indicator_reset();
     if (rdBt_saveFsArchiv->isChecked())
     {
      	if (folder == "")
           {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select from the backup directory.\n", "Bitte wählen Sie das Sicherungsverzeichnis aus.\n"));
		return 0 ;
           }
        if (partition_ == "")
           {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select the partition you want to back up.", "Bitte wählen Sie die zu sichernde Partition aus.\n"));
		return 0 ;
           }
        state = chk_key->checkState();
        if (state == Qt::Checked)
           {
            keyText = lineKey->text();
            len = keyText.size();
            if (len < 6 || len > 64) 
                {
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                return 0 ; 
                }
           }  
        DateiName = lineEdit_DateiName->text();    
        if (DateiName == "")
           {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please select the file name of the backup.\n", 
		"Bitte wählen Sie den Dateinamen der Sicherung aus.\n"));
		return 0 ;
           }
         state = chk_key->checkState();
         if (state == Qt::Checked)
             {
             found = DateiName.indexOf("-key");
             if(found == -1)
                 DateiName = DateiName + "-key";
             lineEdit_DateiName ->setText(DateiName);
             } 
        //Überprüfen ob im Dateinamen "/" enthalten ist. Wird durch "-" ersetzt
        found = DateiName.indexOf("/");
        while (found > -1){
          found = DateiName.indexOf("/");
          if (found > -1)
             	DateiName.replace(found, 1, "-"); 
        }
                //Überprüfen ob im Dateinamen "+" enthalten ist. Wird durch "-" ersetzt
        found = DateiName.indexOf("+");
        while (found > -1){
          found = DateiName.indexOf("+");
          if (found > -1)
             	DateiName.replace(found, 1, "-"); 
        }

        //Überprüfen ob im Dateinamen " " enthalten ist. Wird durch "-" ersetzt
        found = DateiName.indexOf(" ");
        while (found > -1){
          found = DateiName.indexOf(" ");
          if (found > -1)
             	DateiName.replace(found, 1, "-"); 
        }
        if (file.open(QIODevice::ReadOnly))
        	  {
                QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("You have selected a file. You must select a directory\n",
		 "Sie haben eine Datei ausgewählt. Sie müssen ein Verzeichnis auswählen\n"));
		file.close();
		return 0 ;
 	        }
 	 Zeit_auslesen();
         state= chk_Beschreibung->checkState();
         //Überprüfung ob gemounted
         part_ = partition_.toLatin1().data();
         char  dev_[50] = "/dev/";
	 strcat (dev_ , part_);  // String zusammenfügen: dev_  = dev_ + part_
         int liveFlag = 0;
         zip = cmb_zip->currentIndex();
         QString dummy = partition_;
	 // Werte sammeln und nach file_dialog übergeben, Partition ist eingehängt
         part_art = mtab_einlesen("/dev/" + partition_);
         int row = listWidget->currentRow();
         // freien Speicherplatz ermitteln
         result = size_determine("", folder);
         // size_folder ist der freie Speicherplatz im Sicherungspfad
         beschreibungstext("/dev/" + partition_, DateiName + "-" + _Datum + ".fsa", zip, row, size_folder, folder);
         partition_ = dummy;
         if (is_mounted(dev_)) 
         {
                   part_art = mtab_einlesen("/dev/" + partition_);
                   //Überprüfung on LVM vorhanden und ob gemounted
                   if(part_art == "system" or part_art == "home")
                      liveFlag = 1;
                   //Überprüfung ob System oder Home Partition
                   int ret = 1; 
                   if (part_art == "system")
                	{
                	ret = questionMessage(tr("The system partition to be backed up is mounted. Do you want to perform a live backup?", "Die zu sichernde Systempartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
                        if (ret == 2)
                           return 0;
                        if (ret == 1)
                           liveFlag = 1;
                	}
                  if (part_art == "home")
                	{
                	ret = questionMessage(tr("The home partition to be backed up is mounted. Do you want to perform a live backup?", "Die zu sichernde Homepartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
                        if (ret == 2)
                           return 0;
                        if (ret == 1)
                           liveFlag = 1;
                	}
                   if (part_art != "system" || part_art != "home")
                	{
                           if (liveFlag == 0)
                            {
                             if(partition_.indexOf("dm-") > -1)   //Live-DVD mit LVM und Raid
                                 befehl = "umount /media/" + partition_; 
                             else                                 //Live-DVD ohne LVM und Raid
                                 befehl = "umount /dev/" + partition_; 
                             err = system (befehl.toLatin1().data());
                             if(part[row_1][7] != "") // Sichern von LVM und Raid, keine Live-DVD
                                 {
                                 befehl = "umount " + part[row_1][7]; 
                                 err = err + system (befehl.toLatin1().data());
                                 }
                            } 
                           if (err != 0 && liveFlag == 0)
                                {
				QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The partition", "Die Partition ")   + partition_ + tr("cannot be unmounted. The program is aborted.\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ; 
                                }  
                 	}
                }

                        for(i=0; i<15; i++)
                           parameter[i] = "";
                        if (rdBt_saveFsArchiv->isChecked())
           		{
                                int indizierung;
                                state = chk_overwrite->checkState();
                                state1 = chk_key->checkState(); 
                                state3 = chk_split->checkState();
                                keyText = lineKey->text();
                                parameter[0] = "fsarchiver";
       				parameter[1] = "savefs"; 
                                zip = cmb_zip->currentIndex();
                                zip_zstd = cmb_zstd->currentIndex() +1;
                                if (zip < 10)
                                {
                                compress = QString::number(zip);
                                compress = "-z" + compress;
                                parameter[2] = compress;
                                }
                                if (zip == 10)
                                   {
                                   compress = "-Z" + QString::number(zip_zstd);
                                   parameter[2] = compress;
                                }
                                int kerne = cmb_kerne->currentIndex()+1;
                                QString index = QString::number(kerne);
                                if (index == "0")
                                    index = "1";
                                parameter[3] = "-j" + index;
                                indizierung = 4;
                                if (state == Qt::Checked) //Überschreiben ja
                                    {
                                    parameter[4] = "-o";
                                    indizierung = 5;
				    }
				 if (partition_typ ==  "ntfs")
				    {
				    parameter[indizierung] = "-x";
				    indizierung ++;
				    }	
                                 if (state1 == Qt::Checked)   //Schlüssel ja
                                    { 
                                    //Wiederholung der Eingabe und prüfen auf Übereinstimmung
                                    if(rootpassword == 1)
                                       text = QInputDialog::getText(this, tr("Enter password again","Passwort nochmals eingeben"),
                                       (tr("Password:","Passwort")), QLineEdit::Normal,"", &ok);
                                    else
                                       text = QInputDialog::getText(this, tr("Enter password again","Passwort nochmals eingeben"),
                                       (tr("Password:","Passwort")), QLineEdit::Password,"", &ok);
                                    if (!ok)  //Cancel Programm wird beendet
                                         kill_end();
                                    if (keyText != text)
                                          {
                                          QMessageBox::about(this,tr("Note", "Hinweis"),
         	                          tr("The passwords do not match.\n", "Die Passwörter stimmen nicht überein.\n"));
                                          return 0;
                                          }
                                    parameter[indizierung] = "-c";
	    			    parameter[indizierung + 1] = keyText;
                                    len = parameter[indizierung + 1].size();
               			    if (len < 6 || len > 64) 
               			        {
                  			QMessageBox::about(this,tr("Note", "Hinweis"),
         	  			tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  			return 0 ; 
               				}
                                     indizierung = indizierung + 2;  
				     }
				 QString save_part_art = identify_save_part(folder);
                                 int GB = cmb_GB->currentIndex()+1;
                                 QString splitsize = "1900"; 
                                 if (GB == 1 )
                                    splitsize = "1900";
                                 if (GB == 2) 
                                    splitsize = "3800"; 
				 if (GB == 3) 
                                    splitsize = "4400";
				 if (state3 == Qt::Checked)   //Archiv splitten 
                                     {
                                      parameter[indizierung] = "-s" + splitsize;
                                      indizierung = indizierung + 1;
                                      }
	                         // wenn Archiv splitten gewählt wurde und eine FAT-Partition entdeckt wird, hat der nachfolgende Code Vorrang
				 if (save_part_art == "vfat")   //Archivdatei auf 4 GB begrenzen splitten 
                                     {
                                      if (state3 == Qt::Checked)
					 indizierung = indizierung - 1;
                                      if (splitsize == "4400")
                                         splitsize = "3800"; 
              			      parameter[indizierung] = "-s " + splitsize;
                                      indizierung = indizierung + 1;
				      }
                                 if (liveFlag == 1)
                                      {
                                      parameter[indizierung] = "-A";
	    			      parameter[indizierung + 1] = "-a";
                                      indizierung = indizierung + 2; 
                                      }
                                 QString partitionsart = part[row_1][1];
                                 QString partitionsart_ = widget[row_1];
                                 QFile file_suse(".snapshots");
                                 if (file.exists())
                                    {
                                    parameter[indizierung] = "--exclude=.snapshots";
                                    indizierung = indizierung + 1;
                                    }
       				 int pos_a = partitionsart_.indexOf("ntfs");
                		 if (pos_a > -1)
		                    {
				  // Windows Auslagerungsdatei swapfile.sys  und hiberfil.sys von der Sicherung immer ausschließen
                                  parameter[indizierung] = "--exclude=swapfile.sys";
                                  indizierung = indizierung + 1;
                                 // parameter[indizierung] = "--exclude=hyberfil.sys";
                                 // indizierung = indizierung + 1;
				     }
                                 parameter[indizierung] = (folder + "/" + DateiName + "-" + _Datum + ".fsa");
				// Vorbereitung für pbr
                                befehl_pbr = ""; 
				state = chk_pbr->checkState();
				if (state == Qt::Checked)
                                  {
                                  befehl_pbr = "dd if=/dev/" + partition_ + " 'of=" + folder + "/" + DateiName + "-" + _Datum + ".pbr' bs=512 count=1";
                                  if (system (befehl_pbr.toLatin1().data()))
                                     befehl = "";
                                  }
                                  SicherungsFolderFileName = parameter[indizierung];
                                  parameter[indizierung + 1] = ("/dev/" + partition_);
                                  QFile f(parameter[indizierung]);
                                  if  (parameter[4] != "-o" && (f.exists())){
				       QMessageBox::warning(this, tr("Note", "Hinweis"), 
				      tr("The partition file", "Die Partitionsdatei") + parameter[indizierung] + tr(" already exists. The backup is not performed\n", " ist bereits vorhanden. Die Sicherung wird nicht durchgeführt\n") );
                  			  return 0 ; 
               				}
                                  state = chk_Beschreibung->checkState(); 
				  if (rdBt_saveFsArchiv->isChecked() && (state == Qt::Checked))
            			  {
			 	  dialog_auswertung = 2;
             			  folder_file();
             			  FileDialog Filedialog;
     	     			  FileDialog *dlg = new FileDialog;
     	     			 // dlg->show(); nicht modal
             			 int wert = dlg->exec();
             			 if (wert == 0 && dialog_auswertung == 2)
                		  {
                		  QMessageBox::warning(this,tr("Note", "Hinweis"),
         			  tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
				  pushButton_save->setEnabled(true);
                                  chk_pbr->setEnabled(true);
                		  return 0;
                		  }
             			}
//qDebug() << "Befehl" << parameter[0] << parameter[1] << parameter[2] << parameter[3] << parameter[4] << parameter[5] << parameter[6] << parameter[7] << parameter[8] << parameter[9] << parameter[10] << indizierung + 2;
                                
                                // Größe der Partition ermitteln, in die gesichert wird.
                                result = size_determine(part_size_compress, folder);
                                if(result == 2)  
              			   {
                			QMessageBox::about(this,tr("Note", "Hinweis"),
         				tr("There is not enough space on the hard disk for the backup. The backup is canceled.", "Auf der festplatte ist nicht genügend Platz für die Sicherung vorhanden. Die Sicherung wird abgebrochen.\n"));
					return 1 ;
               			   }

                                // Argumente in txt-Datei schreiben
				QString attribute; 
				for ( int i=0; i<15; i++)
  				  {
  				  if (parameter[i] != " ")
     				  attribute = attribute + " " + parameter[i];
  				  }
  				int ind = indizierung +2;  
				state = chk_pbr->checkState(); 
				if (state == Qt::Checked) 
				   {
				   indizierung = indizierung + 102;
				   attribute = QString::number(indizierung)  + attribute; //Pbr mitsichern
				   }
				else 
				   attribute = QString::number(indizierung + 2)  + attribute;  //ohne PBR
	         		state = chk_key->checkState(); // mit Verschlüsselung wird kein Auftrag gespeichert
	         		if (state == Qt::Checked) 
		                    save_attribut(attribute,0);
		                else 
		                    save_attribut(attribute,1); 
		                thread1.setValues(ind,"0");     
		              	pushButton_end->setEnabled(false);  
                                pushButton_save->setEnabled(false);
                                chk_pbr->setEnabled(true); 
                                flag_View = 1;
                                werte_reset();
  				timer->singleShot(1000, this , SLOT(ViewProzent( ))) ;
                                stopFlag = 0;
                                this->setCursor(Qt::WaitCursor);
  				startThread1(); // fsarchiver wird im Thread ausgeführt
                                statusBar()->showMessage(tr("The backup is performed", "Die Sicherung wird durchgeführt"), 15000);
        		        }
                    }
           return 0;
}

int MWindow::size_determine(QString part_size_compress, QString folder)
{
qDebug() << "part_size_compress, QString folder" << part_size_compress << folder;
QString homepath = QDir::homePath();
QString befehl;
QString filename = homepath + "/.config/qt5-fsarchiver/size.txt";
QFile file(filename);
QTextStream ds(&file);
QStringList size;
QString size_;
QString size_folder_;
QString part_size_compress_;
int pos;

QString text;
befehl = "df -hl 1> " +  homepath + "/.config/qt5-fsarchiver/size.txt";
        if(system (befehl.toLatin1().data()))
             befehl = "";
        QThread::msleep(10 * sleepfaktor);
        if( file.open(QIODevice::ReadOnly|QIODevice::Text)) 
           {
           size_ = ds.readLine();
    	   while (!ds.atEnd())
      	      {
      	      // size splitten
      	      size = size_.split(QRegularExpression("\\s+"));
      	      pos = folder.indexOf(size[5]);
      	      if(pos == 0 && size[5] != "/")
      	        size_folder = size[3];
   	      if( size_.isEmpty() )
         	 break;
              size_ = ds.readLine();
       	    } 
   	    file.close();
   	  } 
   	  if (part_size_compress == "")
   	     return 3;
   	  size_folder_ = size_folder.right(1);
   	  part_size_compress_ = part_size_compress.right(2);
   	  part_size_compress_ = part_size_compress_.left(1);
          size_folder = size_folder.left(size_folder.size() -1);
          part_size_compress = part_size_compress.left(part_size_compress.size() -2);
          pos = size_folder.indexOf(",");
          if (pos > 0)
             size_folder.replace(pos, 1, "."); 
          pos = part_size_compress.indexOf(",");
          if (pos > 0)
             part_size_compress.replace(pos, 1, ".");
          size_folder_float = size_folder.toFloat(); 
           
          part_size_compress_float = part_size_compress.toFloat(); 
          if (size_folder_ == "G") 
             size_folder_float = size_folder_float * 1000;  
          if (size_folder_ == "T") 
             size_folder_float = size_folder_float * 1000000; 
          if (part_size_compress_ == "G") 
             part_size_compress_float = part_size_compress_float * 1000;  
          if (part_size_compress_ == "T") 
             part_size_compress_float = part_size_compress_float * 1000000;
          if (size_folder_float  > part_size_compress_float * 1.2) //vorsichtshalber um 20% vergrößern
           	return 1;
          else
                return 2; 
}


void MWindow::ViewProzent()
{
int prozent = 0 ;
QString sekunde;
int sekunde_ = 0;
QString minute;
int minute_ = 0;
int meldung = 0;
int anzahl = 0;
int anzahl1 = 0;
QString text_integer;
//if (endeThread !=1)
if (endeThread ==0)
{
 timer->singleShot( 1000, this , SLOT(ViewProzent( )) ) ;
  elapsedTime();
  this->repaint();
  meldung = werte_holen(4);
  	if (meldung >= 100) // Thread Abschluss mit Fehler
   		return;
if (flag_View == 1)
	{
 	anzahl  = werte_holen(2);
 	text_integer = text_integer.setNum(anzahl);
 	AnzahlsaveFile ->setText(text_integer);
 	anzahl1  = werte_holen(3);
 	text_integer = text_integer.setNum(anzahl1);
 	AnzahlgesicherteFile ->setText(text_integer);
	}
 prozent = werte_holen(1);
 if (dummy_prozent != prozent)
     remainingTime(prozent);
 else {
        if (prozent >= 5)
       {
        // Sekunden nach unten zählen
        // SekundenRemaining einlesen
        sekunde = SekundeRemaining->text();
        sekunde_ = sekunde.toInt();
        minute = MinuteRemaining->text();
        minute_ = minute.toInt();
        if (sekunde_ > 0)
        {
            sekunde_ = sekunde_ - 1;
            if (sekunde_ == 0) 
            {
		if (minute_ > 0)
                {		
			minute_ = minute_ - 1;
                	minute = QString::number(minute_); 
        		MinuteRemaining ->setText(minute);
                       	sekunde_ = 59;
                }
	    }
        }		
        sekunde = QString::number(sekunde_); 
        SekundeRemaining ->setText(sekunde);
	    } 
    }   
 dummy_prozent = prozent;
 }
// bei mehrmaligem Aufruf von fsarchiver wird am Anfang der Sicherung kurzfristig 100 % angezeigt, was falsch ist
 if (prozent != 100 && stopFlag == 0) 
     	progressBar->setValue(prozent);
    return;
} 


int MWindow::restorePartition()
{
QString homepath = QDir::homePath();
if(order == 1)
{
   save_restorePartiiton_list();
   return 1;
}
Qt::CheckState state1;
Qt::CheckState state;
QFile file(folder);
QString DateiName("") ;
int err = 0;
int i = 0;
QString keyText = "";
QString text;
QString befehl;
char * part_;
char * dev_part;
run_ = 1;
int cmp = 0;
QString attribute;
  chk_pbr->setChecked(false); 
  indicator_reset();
  std::string dateiname;
  keyText = lineKey->text();
  state1 = chk_key->checkState();
      {
          if(state1 == Qt::Checked && keyText.isEmpty())  
              {
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("No decryption key was specified.", "Es wurde kein Schlüssel für die Entschlüsselung angegeben.\n"));
		return 1 ;
               }
           if(folder == "")
           {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select the file name of the backup.\n", "Bitte wählen Sie den Dateinamen der Sicherung aus.\n"));
                return 0;
           }
           if (partition_ == "")
           {
          	QMessageBox::about(this,tr("Note","Hinweis"),
         	tr("Please select the partition you want to write back.\n", "Bitte wählen Sie die zurück zu schreibende Partition aus.\n"));
                return 0;
           }
   	   if (file.open(QIODevice::ReadOnly))
        	{
               	if (rdBt_restoreFsArchiv->isChecked())
           		{
                       int pos = testDateiName(".fsa"); 
                       int pos1 = testDateiName("part.fsa");
          	       if (pos > 0 && pos1 > 0)
                                   {
         			   QMessageBox::warning(this, tr("Note", "Hinweis"),
         			   tr("You have selected an incorrect recovery file. The file extension must be .fsa", "Sie haben eine falsche Wiederherstellungsdatei ausgesucht. Die Dateiendung muss .fsa sein."));
                                   return 0;
         			   }
             		}
 		}
	     else
                {
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("You have selected a directory. You must select a file\n", "Sie haben ein Verzeichnis ausgewählt. Sie müssen eine Datei auswählen\n"));
                return 0;
                 }
               chk_Beschreibung->checkState();
            // Archinfo einholen um Originalpartition einzulesen und um Verschlüsselung zu überprüfen
            // Annahme zunächst kein Schlüssel
               for(i=0; i<15; i++)
                  parameter[i] = "";
               parameter[0] = "fsarchiver";
       	       parameter[1] = "archinfo";
               if (state1 != Qt::Checked) 
                   {
               	   parameter[2] = folder;
                   attribute = parameter[0] + " " + parameter[1] + " " + parameter[2];
  		   attribute = "3 " + attribute;
                   save_attribut(attribute,0);
                   fsarchiver_aufruf(3,parameter[0].toLatin1().data(),parameter[1].toLatin1().data(),parameter[2].toLatin1().data(),parameter[3].toLatin1().data());
               	   dev_part = meldungen_holen(2);
               	   QString str2 = dev_part;
              	   if (werte_holen(4) == 103)
              	        {
                  	chk_key->setChecked(true);
                        lineKey->setEnabled(true);
                  	QMessageBox::about(this,tr("Note", "Hinweis"),
         	     	tr("The partition is encrypted. Please enter the key", "Die Partition ist verschlüsselt. Bitte geben Sie den Schlüssel ein\n"));
                   	return 0;
               		} 
        	   }
                   if (state1 == Qt::Checked) 
                        {
            		parameter[2] = "-c";
                        parameter[3] = keyText;
                        if (parameter[3].size() < 6 || parameter[3].size() > 64) {
                  		QMessageBox::about(this,tr("Note", "Hinweis"),
         	  		tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  	lineKey->setText ("");
	                return 0 ; 
               	   		}
			parameter[4] = folder;
                        int retour =  fsarchiver_aufruf(5,parameter[0].toLatin1().data(),parameter[1].toLatin1().data(),parameter[2].toLatin1().data(),parameter[3].toLatin1().data(),parameter[4].toLatin1().data (),parameter[5].toLatin1().data());
                        if ( werte_holen(4) == 107 && retour != 0)
                           {
                           QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                           return 0;
                           }
			dev_part = meldungen_holen(2);
                        }
            //Überprüfen, ob in die Originalpartition zurückgeschrieben werden soll
            part_ = partition_.toLatin1().data();
            char dev_[50] = "/dev/";
	    strcat (dev_ , part_);  // String zusammenfügen: dev_  = dev_ + part_
            // Hier wird verglichen dev_ = die Partition, die zu sichern ist. dev_part = Originalpartition
            cmp = strcmp(dev_,dev_part);
            QString str, str1;
	       str = dev_part;
               str1 = dev_;
            if (cmp != 0){
               // char in QString wandeln
               cmp = questionMessage_warning(tr("The partition to be recovered  ", "Die wiederherzustellende Partition ") + str1 + 
               tr(" does not coincide with the saved  ", " stimmt nicht mit der gesicherten ") + str + tr("Do you want to continue restore?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
               if (cmp == 2)  //nicht wiederherstellen
                  return 0;
            }
       
           if (rdBt_restoreFsArchiv->isChecked())
            	{
                folder_file();	
		QString filename = folder_file_;
                int pos = filename.indexOf("fsa");
        	filename = filename.left(pos);
        	filename.insert(pos, QString("txt"));
                QFile f(filename);
                // Prüfen ob text-Datei vorhanden 
    		if (f.exists())
                    {
           		dialog_auswertung = 3;
           		FileDialog Filedialog;
     	       		FileDialog *dlg = new FileDialog;
     	     		// dlg->show(); nicht modal
             		int wert = dlg->exec();
             		if (wert == 0 && dialog_auswertung == 3)
                	   {
                	   QMessageBox::about(this,tr("Note","Hinweis"),
         		   tr("The restore was aborted by the user", "Das Zurückschreiben wurde vom Benutzer abgebrochen\n"));
                            pushButton_restore->setEnabled(true);
                	   return 0;
                	   }
                       }
		// auf pbr-Datei prüfen
       		pos = filename.indexOf("txt");
       		filename = filename.left(pos);
       		filename.insert(pos, QString("pbr"));
       		QFile f1(filename);
		if (f1.exists())
       			{
 			cmp = questionMessage(tr("There is a file with the contents of the partition boot sector. Do you want to restore the PBR?", "Es ist eine Datei mit dem Inhalt des Partition Boot Sektors vorhanden. Wollen Sie die Wiederherstellung des PBR durchführen?"));
    			if (cmp == 1)  // wiederherstellen
        		   {
        		   befehl_pbr = "dd if="+ filename + " of=/dev/" + partition_ + " bs=512 count=1";
        		   if(system (befehl_pbr.toLatin1().data()))
                              befehl_pbr = ""; 
        		   }
		       }
            	  }
           part_ = partition_.toLatin1().data();
           char  dev1_[50] = "/dev/";
	   strcat (dev1_ , part_);  // String zusammenfügen: dev_  = dev_ + part_   	  
           if (is_mounted(dev1_))
              { 
              if (part_art == "system")
                	{
                        QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The system partition to be recovered is mounted and cannot be written back. Please use a Live-CD.", "Die wiederherzustellende Systempartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return 0;
				      } 
                        
                   if (part_art == "home")
                	{
                        QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The home partition to be restored is mounted and cannot be written back. Please use a live CD.","Die wiederherzustellende Homepartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return 0; 
                        
                	}
                   if (part_art != "system" && part_art != "home")
                	{
                          if(partition_.indexOf("/dm-") > -1)
                              attribute = "/media/" + partition_  + " 2>/dev/null"; //LVM, Raid
                          else
                              attribute = "/dev/" + partition_  + " 2>/dev/null";   // nicht LVM, Raid
                          befehl = "umount " + attribute; //umount
                          err = system (befehl.toLatin1().data());
                          QThread::msleep(200 * sleepfaktor);  
                          if (err != 0)
                                {
				QMessageBox::about(this,tr("Note", "Hinweis"),
         			tr("The partition ", "Die Partition ") + partition_ + tr(" cannot be unmounted. The program is aborted.", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ;
                                }  
                          }
                }
            
        
           if (rdBt_restoreFsArchiv->isChecked())
           {
	     if (partition_typ_ == "btrfs"){
                 befehl = "umount /dev/" + partition_; // unmounten
 		 if(system (befehl.toLatin1().data()))
                    befehl = "";
                 QThread::msleep(50 * sleepfaktor);
                 befehl = "mkfs.btrfs -f /dev/" + partition_; // Partition anlegen
 		if(system (befehl.toLatin1().data()))
                     befehl = "";
                 QThread::msleep(50 * sleepfaktor);
               }  
               QString keyText = lineKey->text();
               state1 = chk_key->checkState(); 
	       parameter[0] = "fsarchiver";
       	       parameter[1] = "restfs"; 
               int kerne = cmb_kerne->currentIndex()+1;
               QString index = QString::number(kerne);
               if (index == "0")
                  index = "1";
               parameter[2] = "-j" + index;
               parameter[3] = folder;
               parameter[4] = "id=0,dest=/dev/" + partition_;
               thread2.setValues(5,"0"); 
               int indizierung = 5;       
               if (state1 == Qt::Checked) { // Verzeichnis mit Schlüssel gesichert
                 thread2.setValues(7,"0"); 
                 parameter[3] = "-c";
                 parameter[4] = keyText;
                 int len = parameter[4].size();
               	    if (len < 6 || len > 64) {
                  	QMessageBox::about(this,tr("Note", "Hinweis"),
         	  	tr("The key length must be between 6 and 64 characters.", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein.\n"));
                  	return 0 ; 
               	   }
                 parameter[5] = folder;
                 parameter[6] = "id=0,dest=/dev/" + partition_;
                 }
//qDebug() << "befehl restore partition" << parameter[0] << parameter[1] << parameter[2] << parameter[3] << parameter[4] << parameter[5] << parameter[6] <<parameter[7];
               QString attribute; 
	       for ( int i=0; i<15; i++)
  		  {
  		  if (parameter[i] != " ")
     		  attribute = attribute + " " + parameter[i];
  		  }
	       attribute = QString::number(indizierung)  + attribute;
               state = chk_key->checkState();
	       if (state == Qt::Checked) 
		   save_attribut(attribute,0);
	       else 
                  save_attribut(attribute,2);
               werte_reset();
               pushButton_restore->setEnabled(false);
               pushButton_end->setEnabled(true); 
               flag_View = 2;
  	       ViewProzent();
               stopFlag = 0;
               this->setCursor(Qt::WaitCursor);
               startThread2(); // fsarchiver wird im Thread ausgeführt
               statusBar()->showMessage(tr("The recovery is performed.", "Die Wiederherstellung wird durchgeführt"), 15000); 
               }
     }
  return 0;              
}   

QString MWindow::Zeit_auslesen(){
    int Tag;
    int Monat;
    int Jahr;
    QString Datum_akt;
    time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
    Tag = nun->tm_mday;
    Monat = nun->tm_mon+1;
    Jahr = nun->tm_year+1900;
    _Datum = Datum_akt.setNum(Tag) + "-" ; 
    _Datum = _Datum + Datum_akt.setNum(Monat) + "-" ;
    _Datum = _Datum + Datum_akt.setNum(Jahr) ;
    return _Datum;
}

void MWindow::listWidget_auslesen() {
    int row;
    row = listWidget->currentRow();
    row_1 = row;
    partition_ = widget[row+1];
    int pos = partition_.indexOf("btrfs");
    if (pos > 0)
       partition_typ_ = "btrfs";
    partition_ = part[row][0]; // z.B. sda1
    UUID = part[row][3];
    partition_typ = part[row][1];
    if (partition_typ == "ntfs" || partition_typ == "vfat")
        chk_pbr->setEnabled(false);
    else 
       chk_pbr->setEnabled(true);
    
}

QString MWindow::UUID_auslesen(int row){
    UUID = part[row][3]; 
    return part[row][3];
}

void MWindow::zip_einlesen() {
int zip = cmb_zip->currentIndex();
    if (zip == 10) 
       cmb_zstd->setEnabled(true);
    else
       cmb_zstd->setEnabled(false);
}	

void MWindow::folder_einlesen() {
   QModelIndex index = treeView->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder =  (dirModel->filePath(index));
}

void MWindow::folder_file() {
   folder_file_ = folder + "/" + DateiName + "-" + _Datum + ".txt";
}

void MWindow::info() {
   QMessageBox::information(
      0, tr("qt-fsarchiver"),
      tr("Backup and restore partitions, directory and MBR.\nversion 2.8.7-0, November 1, 2024",
         "Sichern und Wiederherstellen von Partitionen, Verzeichnissen und MBR Version 2.8.7-0, 1.November 2024"));
      }

int MWindow::Root_Auswertung(){
       if (geteuid() != 0) // 0 is the UID of the root  1000 von home user
	{
     QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The program must be run with root privileges. The program is terminated.", "Das Programm muss mit Root-Rechten gestartet werden. Das Programm wird beendet."));
      return 10;
	}
	else	
	{
        return 20;
    } 
}

int MWindow::testDateiName(string endung)
{
  string str (folder.toLatin1().data());
  size_t found;
  // different member versions of find in the same order as above:
  found=str.find(endung);
  if (found!=string::npos)
     {
        return found;
     }
  else
     {
        return 0;
     } 
}

int MWindow::is_mounted (char* dev_path) {
 	FILE * mtab = NULL;
 	struct mntent * part = NULL;
 	if ( ( mtab = setmntent ("/etc/mtab", "r") ) != NULL) {
  	while ( ( part = getmntent ( mtab) ) != NULL) {
   	if ( ( part->mnt_fsname != NULL ) 
    	&& ( strcmp ( part->mnt_fsname, dev_path ) ) == 0 ) 
    		return  1;
    	if ( ( part->mnt_fsname != NULL ) 
    	&& ( strcmp ( part->mnt_fsname, UUID.toLatin1().data() ) ) == 0 ) 
    		return 1;	
   
  }
  endmntent (mtab);
 }
 return 0;
}

int MWindow::questionMessage(QString frage)
{
	QMessageBox msg(QMessageBox::Question, tr("Note", "Hinweis"), frage);
	QPushButton* yesButton = msg.addButton(tr("Yes", "Ja"), QMessageBox::YesRole);
	QPushButton* noButton = msg.addButton(tr("No", "Nein"), QMessageBox::NoRole);
	msg.exec();
	if (msg.clickedButton() == yesButton)
    		return 1;
	else if (msg.clickedButton() == noButton)
    		return 2;
return 0;    		
}


int MWindow::questionMessage_critical(QString frage)
{
	QMessageBox msg(QMessageBox::Critical, tr("Note", "Hinweis"), frage);
	QPushButton* noButton = msg.addButton(tr("No", "Nein"), QMessageBox::NoRole);
	QPushButton* yesButton = msg.addButton(tr("Yes", "Ja"), QMessageBox::YesRole);
	msg.exec();
	if (msg.clickedButton() == yesButton)
    		return 1;
	else if (msg.clickedButton() == noButton)
    		return 2;
return 0;    		
}

int MWindow::questionMessage_warning(QString frage)
{
	QMessageBox msg(QMessageBox::Warning, tr("Note", "Hinweis"), frage);
	QPushButton* noButton = msg.addButton(tr("No", "Nein"), QMessageBox::NoRole);
	QPushButton* yesButton = msg.addButton(tr("Yes", "Ja"), QMessageBox::YesRole);
	msg.exec();
	if (msg.clickedButton() == yesButton)
    		return 1;
	else if (msg.clickedButton() == noButton)
    		return 2;
return 0;    		
}

void MWindow::order_edit(){
dialog_auswertung = 8;
OrderDialog *dialog = new OrderDialog;
dialog->show();
}

void MWindow::mbr_save () {
     extern int dialog_auswertung;
     dialog_auswertung = 4;
     DialogMBR *dialog = new DialogMBR;
     dialog->show();
}
void MWindow::mbr_restore () {
      extern int dialog_auswertung;
      dialog_auswertung = 5;
      DialogMBR *dialog = new DialogMBR;
      dialog->show();
}

void MWindow::dir_save () {
     extern int dialog_auswertung;
     dialog_auswertung = 4;
     DialogDIR *dialog1 = new DialogDIR;
     dialog1->show();
}
void MWindow::dir_restore () {
      extern int dialog_auswertung;
      dialog_auswertung = 5;
      DialogDIR *dialog1 = new DialogDIR;
      dialog1->show();
}

void MWindow::clone_save () {
     extern int dialog_auswertung;
     dialog_auswertung = 7;
     DialogClone *dialog1 = new DialogClone;
     dialog1->show();
}

void MWindow::einstellungen () {
      DialogSetting *dialog1 = new DialogSetting;
      dialog1->show();
}

void MWindow::format() {
  extern QString add_part[100];
  QString teilstring, space1, space2, space3, dummy;
  int aa, bb, cc, dd;
  int i = 0;
  int j = 0;
  if (add_part[0] == "") //verhindert Änderungen durch Aufruf in net.cpp listWidget_auslesen() MWindow window
     {
     //zunächst prüfen ob Label Einträge vorhanden sind
     partition1[i][0] = "xx";  // bei Mint wird ansonsten die while Schleife nicht ausgeführt
         while (partition1[i][0] != "") {
            dummy =  partition1[i][4];
            if (!dummy.isEmpty())
                 j++;
              i++;   
             } 
         i = 1; 
         if (j > 0)  //mindestens 1 Label Eintrag vorhanden
           {    
           while (partition1[i][0] != "") {
             teilstring = partition1[i][0];
             aa = teilstring.size();
             teilstring = partition1[i][1];
             bb = teilstring.size();
             teilstring = partition1[i][2];
             cc = teilstring.size();
             dd = 12 - aa; 
             space1.fill (' ',dd);
             dd = 15 -bb -cc;
             space2.fill (' ',dd);
             dd = 2;
             space3.fill (' ',dd);
             teilstring = partition1[i][0] + space1 + partition1[i][1] +space2 + partition1[i][2] + space3 + partition1[i][4];
             if (partition1[i][1] != "" ){
                widget[i] = teilstring;
                add_part[i] = teilstring;
                listWidget->addItem (teilstring);
                //Partitionen werden eingetragen
                }
             i++;
            }
         }
         if (j == 0)  //kein Label Eintrag vorhanden
           {    
           while (partition1[i][0] != "") {
              teilstring = partition1[i][0];
              aa = teilstring.size();
              teilstring = partition1[i][1];
              bb = teilstring.size();
              teilstring = partition1[i][2];
              cc = teilstring.size();
              dd = 19 - aa; 
              space1.fill (' ',dd);
              teilstring = partition1[i][0] + space1;
              dd = 21 -bb -cc;
              space2.fill (' ',dd);
              teilstring = partition1[i][0] + space1 + partition1[i][1] +space2 + partition1[i][2];
              if (partition1[i][1] != "" ){
                 widget[i] = teilstring;
                 add_part[i] = teilstring;
                 listWidget->addItem (teilstring);
              //Partitionen werden eingetragen
              }
            i++;
            }
         }
    } 
}

void MWindow::startThread1() {
   if(thread1.isRunning() ) return;
   connect( &thread1, SIGNAL(finished()),
            this, SLOT( thread1Ready()));
   thread_run = 1;
   thread1.start();
}

void MWindow::startThread2() {
   if(thread2.isRunning() ) return;
   connect( &thread2, SIGNAL(finished()),
            this, SLOT( thread2Ready()));
   thread_run = 2;
   thread2.start();
}

int MWindow::question_end() 
{
int ret = 0;
      if (live_save == 1)
           ret = questionMessage_critical(tr("Warning: This is a live backup. Do not exit the program. The system could be destroyed. Do you want to quit anyway?", "Warnung: Das ist eine Live-Sicherung. Beenden Sie nicht das Programm. Das System könnte zerstört werden. Wollen Sie trotzdem beenden?"));
       if (live_save == 0)
            ret = questionMessage_warning(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
     return ret;     
}


void MWindow::closeEvent(QCloseEvent *event) 
{
int ret = 0;
QThread::msleep(10 * sleepfaktor);
QString befehl;
    if(end_mediafolder==0)
       ret = question_end();
    if (ret == 2)
       {
       event->ignore();
       return;
       } 
    if (run_ == 0)
       {
       del_mediafolder();
       esc_end();
       event->accept();
       }
    
      if (ret == 1 )
          {
          esc_ = 1;
          esc_end();
          event->accept();
          }
       run_ = 0;
       
}

void MWindow::thread1Ready()  {
int part_testen;
QString befehl;
   endeThread = endeThread + 1;
   extern int dialog_auswertung;
     if (endeThread == 1) {
       pushButton_end->setEnabled(true);
       pushButton_save->setEnabled(true);
       listWidget_2->setEnabled(true);
       progressBar->setValue(100); 
       SekundeRemaining ->setText("0");
       int break_  = werte_holen(4);
       if (break_ == 120)
           { 
           //Rückmeldung von fsarchiver: Sicherung nicht erfolgreich Kein ausreichender Platz auf der Festplatte
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
            tr("The partition was not backed up successfully. The free space on the hard drive to be backed up was not sufficient or The file is too large. do not use a FAT partition.\n", "Die Partition wurde nicht erfolgreich gesichert. Der freie Speicherplatz auf der Festplatte auf die gesichert werden sollte war nicht ausreichend oder die Datei ist zu groß. Benutzen Sie keine FAT Partition.\n")); 
          QString filename1 = folder_file_;
          QFile f1(filename1);
          // Prüfen ob text-Datei vorhanden 
          if (f1.exists())
             {
              befehl = "rm "  + filename1;
             if(system (befehl.toLatin1().data()))
                befehl = "";
             }
            progressBar->setValue(100);     
	   }
       int anzahl  = werte_holen(2);
       QString text_integer = QString::number(anzahl);
       AnzahlgesicherteFile ->setText(text_integer);
       int cnt_regfile = werte_holen(6);
       QString cnt_regfile_ = QString::number(cnt_regfile);
       int cnt_dir = werte_holen(7);
       QString cnt_dir_ = QString::number(cnt_dir); 
       int cnt_symlinks = werte_holen(8);
       QString cnt_symlinks_ = QString::number(cnt_symlinks); 
       int cnt_hardlinks = werte_holen(9);
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       cnt_hardlinks = cnt_hardlinks + cnt_symlinks;
       cnt_hardlinks_ = QString::number(cnt_hardlinks);
       int cnt_special = werte_holen(10);
       QString cnt_special_;
       cnt_special_ = QString::number(cnt_special);
       int err = werte_holen(17);
       if (dialog_auswertung == 0 and err == 10 and befehl_pbr == "")
           { 
           //Rückmeldung von fsarchiver: Sicherung erfolgreich
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
            tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been backed.", " spezielle Daten wurden gesichert."));
           progressBar->setValue(100);     
	   }
	   
      if (dialog_auswertung == 0 and err == 10 and befehl_pbr != "")
          { 
           //Rückmeldung von fsarchiver: Sicherung erfolgreich
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
        + cnt_special_ + tr(" specials and the Partition Boot Record have been backed.", " spezielle Daten und der Partition Boot Sektor wurden gesichert."));
	  }	
      if (dialog_auswertung == 0 and err != 10)
       {
       pushButton_save->setEnabled(false);
       //Beschreibungsdaten löschen
     	QString filename = folder + "/" + SicherungsDateiName;
        int pos = filename.indexOf("fsa");
       	filename = filename.left(pos);
       	filename.insert(pos, QString("txt"));
        QFile f(filename);
        // Prüfen ob text-Datei vorhanden 
       if (f.exists())  {
          QString befehl = "rm "  + filename;
          if(system (befehl.toLatin1().data()))
              befehl = "";
          }
       if (flag_end == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The backup of the partition was aborted by the user!\n", "Die Sicherung der Partition  wurde vom Benutzer abgebrochen!\n") );
        pushButton_save->setEnabled(true);
	}
       // Prüfen ob Partitionsart unterstützt wird      
       part_testen = werte_holen(3);
       if (part_testen == 110){ 
       QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported.\n", "Der Partitionstyp wird nicht unterstützt.\n" ));
          flag_end = 1;
          } 
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       part_testen = werte_holen(4);
       if (part_testen == 108){
	   QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported. Maybe the partition is encrypted?\n", "Der Partitionstyp wird nicht unterstützt. Vielleicht ist die Partition verschlüsselt?\n" ));
          }
       
       int err_regfile = werte_holen(12);
       QString err_regfile_ = QString::number(err_regfile);
       int err_dir = werte_holen(13);
       QString err_dir_ = QString::number(err_dir); 
       int err_hardlinks = werte_holen(14);
       err_hardlinks = err_hardlinks + werte_holen(16);
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       int err_special = werte_holen(11);
       QString err_special_ = QString::number(err_special);
       if (part_testen <= 108 && flag_end == 0 ){
       	  QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	   tr("The backup of the partition was only partially successful.\n", "Die Sicherung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" specials have been backed\n.", " spezielle Daten wurden gesichert\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" special data was not saved correctly.\n."," spezielle Daten wurden nicht korrekt gesichert.\n"));
	  }
        }
       
     }
  this->setCursor(Qt::ArrowCursor);
  thread_run = 0;
  thread1.exit();
}

void MWindow::thread2Ready()  {
   endeThread = endeThread + 1;
   int meldung = werte_holen(4);
   int i =2;
   if (meldung == 105) {
       QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The partition to be restored is mounted. It must be unmounted first! \n", "Die Partition die wiederhergestellt werden soll, ist eingehängt. Sie muss zunächst ausgehängt werden!\n"));
      endeThread = 0;
       }
   if (endeThread == 1) { 
     pushButton_end->setEnabled(true);
     listWidget_2->setEnabled(false);
     int cnt_regfile = werte_holen(6);
     QString cnt_regfile_ = QString::number(cnt_regfile);
     int cnt_dir = werte_holen(7);
     QString cnt_dir_ = QString::number(cnt_dir); 
     int cnt_hardlinks = 0;
     cnt_hardlinks = werte_holen(8) + werte_holen(9) + werte_holen(16);
     QString cnt_hardlinks_ = QString::number(cnt_hardlinks); 
     int cnt_special = werte_holen(10);
     QString cnt_special_;
     cnt_special_ = QString::number(cnt_special);
     int err = werte_holen(17);
     //Rückmeldung von fsarchiver: Zurückschreiben erfolgreich
     if (err == 10){
       // Ausgabe progressBar durch Timer unterbinden
       stopFlag = 1; 
       pushButton_restore->setEnabled(true);
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
      //PBR herstellen
      i = 2;
      if (befehl_pbr != "") 
    	i = system (befehl_pbr.toLatin1().data());
      if (i!=0 ) { 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" special data has been restored.", " spezielle Daten wurden wieder hergestellt."));
        }
      if (i==0) { 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links ", " Links ") + cnt_special_ + tr(" specials and the Partition Boot Record have been restored.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt."));
        } 
      }  
     if (flag_end == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The restore of the partition was break by user!\n", "Die Wiederherstellung der Partition  wurde vom Benutzer abgebrochen!\n") );
	meldung = 0;
        }
     if (err != 10) {
          // Anzahl nicht korrekt zurückgeschriebene Dateien ausgeben
       pushButton_restore->setEnabled(false);
       int err_special = werte_holen(11);
       QString err_special_ = QString::number(err_special);
       int err_regfile = werte_holen(12);
       QString err_regfile_ = QString::number(err_regfile);
       int err_dir = werte_holen(13);
       QString err_dir_ = QString::number(err_dir); 
       int err_hardlinks = werte_holen(14);
       err_hardlinks = err_hardlinks + werte_holen(16);
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       
      if (i!=0) {  
       QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" specials has been restored\n.", " spezielle Daten wurden wiederhergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
               }
      if (i==0) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" special data and the partition boot sector were restored.\n.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored.\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
                }
        }
     if (meldung == 102) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), tr("You have tried restore a partition. The selected file can only restore directories. Please restart the program.\n", "Sie haben versucht eine Partition wiederherzustellen. Die gewählte Datei kann nur Verzeichnisse wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 103) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben.\n"));
        endeThread = 0;
        lineKey->setText ("");
      }
     if (meldung == 106) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The partition to be written back to is too small.\n", "Die Partition in die zurückgeschrieben wird ist zu klein.\n"));
        endeThread = 0;
        lineKey->setText ("");
      } 
    }
    this->setCursor(Qt::ArrowCursor);
    thread_run = 0;
    thread2.exit();
}

void MWindow::elapsedTime()
 {
    sekunde_elapsed = sekunde_elapsed + 1; 
    sekunde_summe = sekunde_summe + 1; 
    if (sekunde_elapsed == 60) {
        sekunde_elapsed = 0 ;
        minute_elapsed = minute_elapsed + 1;
       }
    QString sekunde_ = QString::number(sekunde_elapsed);
    SekundeElapsed ->setText(sekunde_);
    QString minute_ = QString::number(minute_elapsed);
    MinuteElapsed ->setText(minute_);
}

void MWindow::remainingTime(int prozent)
 {
    if (prozent <= 1) 
       sekunde_tara = sekunde_summe ;
    int sekunde_netto = sekunde_summe - sekunde_tara;

    if (prozent >= 5) {
       double remaining_time =((100 * sekunde_netto/prozent)- sekunde_netto);
       int dummy = (int)remaining_time;
       int min_remaining = (int)(remaining_time/60);
       QString minute_ = QString::number(min_remaining);
       MinuteRemaining ->setText(minute_);
       int sek_remaining = (dummy % 60);
       QString sekunde_ = QString::number(sek_remaining);
       SekundeRemaining ->setText(sekunde_);
    }
}

void MWindow::indicator_reset() {
     // Anzeige zurücksetzen für neuen Aufruf fsarchiver
     werte_reset();
     progressBar->setValue(0);
     AnzahlgesicherteFile ->setText(0);
     AnzahlsaveFile ->setText(0); 
     SekundeRemaining ->setText(" ");
     MinuteRemaining ->setText(" ");
     SekundeElapsed ->setText("0");
     MinuteElapsed ->setText("0");
     sekunde_summe = 0;
     minute_elapsed = 0;
     endeThread = 0;
     sekunde_elapsed = 0;
     minute_elapsed = 0;
}

void MWindow::keyPressEvent(QKeyEvent *event) {
     QWidget::keyPressEvent(event);
     switch( event->key() ) {
         case Qt::Key_Escape:
            int ret = question_end();
            if (ret==1)
                 esc_end(); 
         break;
     }
}

QString MWindow::beschreibungstext(QString partitiontext, QString text, int zip, int row, QString size_folder, QString folder)  
{
FileDialog filedialog; //Create the main widget; 
float prozent;
float compress_[11];
float compress_zstd[23];
QString part_size_;
float part_size;
QString free_part_size_;
float free_part_size;
QString Linuxversion;
QString ubuntu_root;
QString ubuntu_home;
QString compress;
QString mount_point;
QString kernel;
QString foldertext;
QString foldertext1;
int zstd = 0; 
int zip_zstd = 0; 
if(zip > 10)
   {
   }
QString zip_zstd_ = "";
compress_[0] = 0.46;  //lz4
compress_[1] = 0.46;  //lzo
compress_[2] = 0.39;  //gzip fast
compress_[3] = 0.37;  //gzip standard
compress_[4] = 0.365;  //gzip best
compress_[5] = 0.36;  //bzip2 fast
compress_[6] = 0.355;  //bzip2 good
compress_[7] = 0.35; //lzma fast
compress_[8] = 0.322; //lzma medium
compress_[9] = 0.32; //lzma best
compress_zstd[1] = 0.44;  //Z1
compress_zstd[2] = 0.44;  
compress_zstd[3] = 0.44;  
compress_zstd[4] = 0.43;  
compress_zstd[5] = 0.43;  
compress_zstd[6] = 0.42;  
compress_zstd[7] = 0.42;
compress_zstd[8] = 0.41; 
compress_zstd[9] = 0.41; 
compress_zstd[10] = 0.41;  
compress_zstd[11] = 0.41;  
compress_zstd[12] = 0.41;  
compress_zstd[13] = 0.41;  
compress_zstd[14] = 0.41;  
compress_zstd[15] = 0.41;  
compress_zstd[16] = 0.41;  
compress_zstd[17] = 0.40; 
compress_zstd[18] = 0.40; 
compress_zstd[19] = 0.39; 
compress_zstd[20] = 0.39;  
compress_zstd[21] = 0.39;  
compress_zstd[22] = 0.39;  //Z22

if (dialog_auswertung < 6) // darf nicht aufgerufen werden beim Speichern/Wiederherstellen über das Netz
    {
    zstd = cmb_zip->currentIndex();
    zip_zstd = cmb_zstd->currentIndex() + 1;
    zip_zstd_ = QString::number(zip_zstd);
    } 
if (dialog_auswertung == 6 or dialog_auswertung == 7) // wird aufgerufen werden beim Speichern/Wiederherstellen über das Netz
    {
    if(zip > 9)
       {
       zstd = zip;
       zip_zstd = zip -10;
       zip_zstd_ = QString::number(zip_zstd);
       zip = 10;
       zstd = 10;
       }
    } 
compress = zip_[zip];
       if(order == 1)
           zstd = zip;
       if(zstd == 10)
           compress = compress + " level:" + zip_zstd_;
        SicherungsDateiName = text;
        //partition_ = widget[row];
	mount_point = mountpoint(partitiontext);
	//prozentuale Belegung
	prozent = freesize(partitiontext.toLatin1().data(), mount_point.toLatin1().data(), 1); 
	// freier Bereich der Partition
        free_part_size = freesize(partitiontext.toLatin1().data(), mount_point.toLatin1().data(), 3);
       	free_part_size_ =  format(free_part_size);
       	// Gesamter Bereich der Partition
       	part_size = freesize(partitiontext.toLatin1().data(), mount_point.toLatin1().data(), 2);
       	part_size_ =  format(part_size);
        if  (zstd == 10)
            free_part_size = free_part_size * compress_zstd[zip_zstd];
        else
            free_part_size = free_part_size * compress_[zip];
        if(part_size == 0)
           part_size = 1;
        part_size_compress = format(free_part_size);
        text = tr("Backup file name: ", "Sicherungsdateiname: ") + text + "\n" + 
	tr("Partition  name: ", "Partitionsname: ")  
	+ PartitionString(row+1,0) + "\n" + tr("Partition type: ", "Partitionsart: ") 
       	+ PartitionString(row+1,1) + "\n" + tr("UUID: ") +  PartitionString(row+1,3) + "\n" + tr("Description: ", "Bezeichnung: ") + PartitionString(row+1,4) + "\n" + 
       	tr("Partition size: ", "Partitionsgröße: ") + part_size_ + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + 
       	free_part_size_ + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + QString::number(prozent)+ " %" + "\n" + tr("Compression: ", "Kompression: ") + compress + "\n" + 
       	tr("Approximate image file sizes: ", "ungefähre Sicherungsdateigröße: ") + part_size_compress + "\n"; 
        ubuntu_root = tr("to be protected/secured partition: / (root system directory) ", "zu sichernde / gesicherte Partition: / (Wurzel-Systemverzeichnis) ");
        part_art = mtab_einlesen(partitiontext);
	if (part_art == "system"){
		Linuxversion = linux_version();
                kernel = kernel_version();
                text = ubuntu_root + "\n" + tr("Operating system: ", "Betriebsystem: ") + Linuxversion + "\n" + tr("Kernel: ") + kernel + " " + "\n" + text + "\n";
	}
	ubuntu_home = tr("to be protected/secured partition: /home", "zu sichernde/gesicherte Partition: /home");
	if (part_art == "home"){
	        Linuxversion = linux_version();
                kernel = kernel_version();
                text = ubuntu_home + "\n" + tr("Operating system: ", "Betriebsystem: ")  + Linuxversion + " " + "\n"  + tr("Kernel: ") + kernel  + "\n" + text + "\n";
	}
	foldertext = tr("Path of the backup file: ", "Pfad der Sicherungsdatei: ");
	foldertext1 = tr("Free space on the hard disk to be backed up to: ", "Freier Speicherplatz auf der Festplatte auf die gesichert wird: ");
	if (folder != "")
	     text = text + "" + foldertext + " " + folder + "\n" + foldertext1  +  " " + size_folder + "B";
	text = text + "\n" + "\n" + tr("Other notes: ", "weitere Hinweise:");
	filedialog.werte_uebergeben(text);
        return text;
}

QString MWindow::format(float zahl)  {
QString zahl_;
int found;
         if (zahl <= 999){
            zahl = (int) (zahl * 100/1.024);
            zahl = zahl/100;
            // Punkt in Komma wandeln
            zahl_ = QString::number(zahl);
            found=zahl_.indexOf(".");
            if (found > 0)
             	zahl_.replace(found, 1, ","); 
            return zahl_  + tr(" MB");
	 } 
        if (zahl >= 1000000){
            zahl = zahl / 1000000/1.024/1.024/1.024; 
            zahl = (int) (zahl * 100);
            zahl = zahl/100;
            // Punkt in Komma wandeln
            zahl_ = QString::number(zahl);
            found=zahl_.indexOf(".");
            if (found > 0)
             	zahl_.replace(found, 1, ","); 
            return zahl_  + tr(" TB");
	 }    
	if (zahl >= 1000){
            zahl = zahl / 1000/1.024/1.024;
            zahl = (int) (zahl * 100);
            zahl = zahl/100;
            // Punkt in Komma wandeln
            zahl_ = QString::number(zahl);
            found=zahl_.indexOf(".");
            if (found > 0)
             	zahl_.replace(found, 1, ","); 
            return zahl_  + tr(" GB");
	 } 
return "";	 
}

QString MWindow::linux_version()  {
QString homepath = QDir::homePath();
QString befehl;
QString Linuxversion;
int i;
	befehl = "cat /etc/*release 1> " +  homepath + "/.config/qt5-fsarchiver/version.txt";
        if(system (befehl.toLatin1().data()))
             befehl = "";
QString filename = homepath + "/.config/qt5-fsarchiver/version.txt";
QFile file(filename);
        QThread::msleep(10 * sleepfaktor);
        if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           Linuxversion = ds.readLine();
           if (Linuxversion.indexOf("PRETTY_NAME") > -1) {  //Debian
               Linuxversion = Linuxversion.right(Linuxversion.size() -13);
               Linuxversion = Linuxversion.left(Linuxversion.size() -1);
               return Linuxversion;
	   }
     //      if (Linuxversion.indexOf("PRETTY_NAME") == -1) && Linuxversion.indexOf("DISTRIB_ID") == -1) {  //Simply Linux
     //         Linuxversion = ds.readLine(); // Simply Linux
     //         return Linuxversion;
     //      }
           for (i=1; i < 4; i++){
           	Linuxversion = ds.readLine(); // Simply Linux
           }}
           file.close();
           befehl = "rm " + filename;
           if(system (befehl.toLatin1().data()))
              befehl = "";
           if (Linuxversion.indexOf("DISTRIB_DESCRIPTION=") > 0) 
              Linuxversion = Linuxversion.right(Linuxversion.size() -20);
return Linuxversion;
}

QString MWindow::kernel_version()  {
QString homepath = QDir::homePath();
QStringList kernel;
QString kernel_;
QString befehl;
	befehl = "uname -a 1> " +  homepath + "/.config/qt5-fsarchiver/kernel.txt";
        if(system (befehl.toLatin1().data()))
           befehl = "";
QString filename = homepath + "/.config/qt5-fsarchiver/kernel.txt";
	QFile file(filename);
	QThread::msleep(10 * sleepfaktor);
        if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           kernel_ = ds.readLine();
           file.close();
           kernel = kernel_.split(" ");
         }
         befehl = "rm " + filename;
         if(system (befehl.toLatin1().data()))
            befehl = "";
         if (kernel_.indexOf("Debian") > -1)         
		return kernel[0] + " " + kernel[2] ;
         else
		return kernel[0] + " " + kernel[2] +  " " + kernel[11];
}

QString MWindow::identify_save_part(QString save_partition)
{
   QString fileName;
   QString text;
   QStringList items;
   QString save_part;
   QFile file("/etc/mtab");
   QTextStream ds(&file);
   int line = 0;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     text = ds.readLine();
   	while (!ds.atEnd())
      	{
 	    if (text.indexOf(save_partition) > -1)  // Partitionsname gefunden
      	    { 
   	       if (text.indexOf("vfat") > -1) 
      	          return "vfat";
               }
   	       if( text.isEmpty() )
         	 break;
       		line++;
            text = ds.readLine();
      	} 
   	file.close();
     }
  return save_part.toLatin1().data();
}

QString MWindow::mtab_einlesen(QString partition_if_home)
{
   QString fileName;
   QString text;
   QStringList items;
   QString mount_dir;
   QFile file("/etc/mtab");
   QTextStream ds(&file);
   int line = 0;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     text = ds.readLine();
    	while (!ds.atEnd())
      	{
      	if (text.indexOf(partition_if_home) > -1 )  // Partitionsname gefunden,  Ubuntu und Mint
      	    { 
	      items = text.split(" ");  //Einhängepunkt ermitteln
    	      mount_dir = items[1];
              //Überprüfen ob sda1 nicht mit sda10 verwechselt wird
              if (items[0].size() == partition_if_home.size()){
                 if (text.indexOf(" /home") > -1) 
      	            return "home";
                 if (text.indexOf(" / ") > -1) 
      	           return "system";
                 if (text.indexOf("ext4") > -1) 
      	        	return "ext4";
                 if (text.indexOf("ext3") > -1) 
      	        	return "ext3";
                 if (text.indexOf("btrfs") > -1) 
      	        	return "btrfs";
               }
      	    }   
   	       if( text.isEmpty() )
         	 break;
       		line++;
            text = ds.readLine();
          } 
   	file.close();
     }
  return "";
}

//Mountpoint ermitteln
QString MWindow::mountpoint(QString partition)
{
   QString fileName;
   QString text;
   QStringList items;
   QString mount_dir;
   QFile file("/etc/mtab");
   QTextStream ds(&file);
   string text_str;
   int i,j,pos;
   int line = 0;
   QThread::msleep(10 * sleepfaktor);
   text_str = partition.toLatin1().data();
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        text = ds.readLine();
        // hier wird die ersten Zeile der mtab überprüft
	pos = text.indexOf(partition); 
        if (pos > -1)  // Partitionsname gefunden
      	     { 
                items = text.split(" ");  //Einhängepunkt ermitteln
                i = items[0].size();
                j =  text_str.size();
                if (i == j)
    	      	   mount_dir = items[1];
       	     }
   	while (!ds.atEnd())
      	{
	     // hier wird auch die letzte Zeile der mtab überprüft	   	     
	     line++;
             text = ds.readLine();
             pos = text.indexOf(partition); 
             if (pos > -1)  // Partitionsname gefunden
      	     { 
                items = text.split(" ");  //Einhängepunkt ermitteln
                i = items[0].size();
                j =  text_str.size();
                if (i == j)
    	      	   mount_dir = items[1];
       	    }
      	} 
   	file.close();
     }
  return mount_dir;
}

void MWindow::esc_end()
{
pid_t getppid(void);
QString pid1;
QString pid_qt_fsarchiver;
QString befehl = "";
int pida1=getppid();
int ret = 0;
   pid1 = QString::number(pida1);
    ret = question_end();
    if (esc_ == 1) 
        ret = 1;  
    if(ret == 1)
      {
      befehl = "rm "  + SicherungsFolderFileName;
      if(system (befehl.toLatin1().data()))
           befehl = "";
      int pos = SicherungsFolderFileName.indexOf("fsa");
      SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
      
      SicherungsFolderFileName.insert(pos, QString("txt"));
      QFile file(SicherungsFolderFileName);
      if (file.exists()) 
         befehl = "rm "  + SicherungsFolderFileName + " 2>/dev/null";
      // pbr-Datei löschen
      pos = SicherungsFolderFileName.indexOf("txt");
      SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
      SicherungsFolderFileName.insert(pos, QString("pbr"));
      del_mediafolder();
      QFile file1(SicherungsFolderFileName);
      if (file1.exists()) 
         befehl = "rm "  + SicherungsFolderFileName + " 2>/dev/null";;
      if(system (befehl.toLatin1().data()))
         befehl = "";
      // txt und fsa-Datei löschen 
       befehl = "rm " + folder_file_ + " 2>/dev/null";
       if(system (befehl.toLatin1().data()))
          befehl = ""; 
       int found=folder_file_.indexOf(".txt");
       if (found > 0)
           folder_file_.replace(found, 4, ".fsa"); 
       befehl = "rm " + folder_file_ + " 2>/dev/null";
       if(system (befehl.toLatin1().data()))
          befehl = ""; 
      if(pida1 > 1) 
         {       
         befehl = "kill -15 " + pid1;  //qt-fsarchiver abbrechen
         if(system (befehl.toLatin1().data()))
            befehl = "";
         }   
      QApplication::quit();
      }
      if(ret == 2)
        return;    
}

void MWindow::del_mediafolder()
// Programm beenden
// eingehängte Partitionen aushängen und leere Verzeichnisse in /media löschen.
{
end_mediafolder = 1;
QString foldername[100];
      QString homepath = QDir::homePath();
      QString befehl = "cd /media; ls 1> " +  homepath + "/.config/qt5-fsarchiver/media.txt; cd /";
      if(system (befehl.toLatin1().data()))
            befehl = "";
      QString media;
      QString filename = homepath + "/.config/qt5-fsarchiver/media.txt";
      QFile file(filename);
      int zaehler = 0;
      QThread::msleep(10 * sleepfaktor);
      if( file.open(QIODevice::ReadOnly|QIODevice::Text)) 
           {
           QTextStream ds(&file);
           while (!ds.atEnd())
               {
           	   media = ds.readLine();
               if (media.indexOf("sd") > -1 or media.indexOf("nvme") > -1)
                   {
                   foldername[zaehler] = "/media/" + media;
                   QThread::msleep(10 * sleepfaktor);  
                   befehl = "umount " + foldername[zaehler] + " 2>/dev/null";
                   if(system (befehl.toLatin1().data()))
                      befehl = "";
                   befehl = "rmdir " + foldername[zaehler] + " 2>/dev/null";
                   if(system (befehl.toLatin1().data()))
                      befehl = "";
                   zaehler = zaehler + 1;
                  }
               } 
           }    
           file.close();
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";
           filename = homepath + "/.config/qt5-fsarchiver/attribute.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";
           filename = homepath + "/.config/qt5-fsarchiver/efi.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";  
           filename = homepath + "/.config/qt5-fsarchiver/route.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = ""; 
           filename = homepath + "/.config/qt5-fsarchiver/size.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";      
           filename = homepath + "/.config/qt5-fsarchiver/sektornummer.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";   
           filename = homepath + "/.config/qt5-fsarchiver/zeit.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";  
           filename = homepath + "/.config/qt5-fsarchiver/disk.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";                 
           filename = homepath + "/.config/qt5-fsarchiver/pid.txt";
           befehl = "rm " + filename + " 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";
           befehl = "umount -a -t nfs 2>/dev/null";
           if(system (befehl.toLatin1().data()))
               befehl = "";
           QApplication::quit();
 
}

void MWindow::zip_setting_einlesen() {
int zip = cmb_zip->currentIndex();
    if (zip == 10) {
       cmb_zstd->setEnabled(true);
       label_5->setEnabled(true);
       }
    else
       {
       cmb_zstd->setEnabled(false);
       label_5->setEnabled(false);
       }
}

void MWindow::make_order() 
{
QString homepath = QDir::homePath();
QString filename = homepath + "/.config/qt5-fsarchiver/auftrag.db";
QFile file(filename);
QString attribute;
QStringList auftrag;
QString auftrag_;  
int i = 0;
int j = 0;
int found = 0;
int size_ = 0;
        label_Partition->setText (tr("Existing list entries", "vorhandene Listeinträge"));
        order = 1;
        listWidget_2->setHidden(false);
        listWidget_2-> clear();
	file.open(QIODevice::ReadOnly);
        QDataStream stream( &file ); // read the data serialized from the file
        stream >> auftrag_ ;
        file.close(); 
        auftrag = auftrag_.split("##");
        size_ = auftrag.size();
        for(i=0; i < size_ - 1; i++) 
               {
               order_name = auftrag[i];
               order_name = order_name.trimmed();
               attribute = auftrag[i+1];
               found = attribute.indexOf("savefs"); 
               if(order_name != "" && found > -1 )
                    listWidget_2->addItem ("Save: " + order_name);
               if(order_name != "" && found == -1 )
                    listWidget_2->addItem ("Restore: " + order_name); 
               widget_2_[j]= order_name;
               widget_2[j]= attribute;
               if(j > 98)
                  break;  //überlauf wird verhindert
               i++;
               j ++;
               }  
 return;        
       if(i == 0)
           {
           QMessageBox::warning(this,tr("Note", "Hinweis"),
           tr("There is no order available\n", "Es ist kein Autrag vorhanden\n"));
           listWidget_2->setHidden(true);
           listWidget->setHidden(false);
           order = 0;
           }
       file.close(); 
}

void MWindow::save_restorePartiiton_list() 
{
QString text;
QString homepath = QDir::homePath();
QFile file(folder);
QString befehl;
int zip = 0;
int save = 0;
QString str;
QString zip_;
QString attribute;
QString keyText = "";
QString compress = "";
int found = 0; 
int row = 0;
int ret = 0;
QString dummy;
QString partition;
QStringList texte;
QString texte_;
QStringList auftrag;
QString auftrag_;
QString auftrag_datei_name;
QString auftrag_datei_name_fsa;
QString auftrag_datei_name_pbr;
QStringList folder_size;
QString folder_size_;
int size_;
int i = 0;
int j = 0;
int indizierung = 0;
int result = 0;
QString datum = Zeit_auslesen();
     indicator_reset(); 
     row = listWidget_2->currentRow();
     if(row == -1)
       row = 0;
     attribute = widget_2[row]; 
     attribute = attribute.trimmed();
     auftrag = attribute.split(QRegularExpression("\\s+"));
     size_ = auftrag.size();
     auftrag_datei_name_fsa = auftrag[size_ -2];
     SicherungsFolderFileName = auftrag_datei_name_fsa;
     // Pfad ermitteln
     dummy = auftrag_datei_name_fsa;
     ret = dummy.indexOf("/media");
     if(ret > -1)   //Verzeichnis ist auf einer USB-Platte
        {
        found = 1;
        while(found != -1)
           {
           found = dummy.indexOf("/");
           dummy = dummy.right(dummy.size() -found -1);
           }
           dummy = auftrag_datei_name_fsa.left(auftrag_datei_name_fsa.size() - dummy.size()-1); 
           // USB-Platte vorhanden?
           befehl = "df -h | grep /media 1> " +  homepath + "/.config/qt5-fsarchiver/media.txt";
           if(system (befehl.toLatin1().data()))
              befehl = "";
            QString filename = homepath + "/.config/qt5-fsarchiver/media.txt";
            QFile file1(filename);
            QTextStream ds(&file1);
            QThread::msleep(10 * sleepfaktor);
            if(file1.open(QIODevice::ReadWrite | QIODevice::Text))
                {
                while (!ds.atEnd())
                {   
                text = ds.readLine();
                texte = text.split(QRegularExpression("\\s+"));
                text = texte[5];
                found = dummy.indexOf(text);
                if(found == 0)
                   break;
                }
                if (found == -1)
                     {
                     QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("No USB disk is connected, The program is terminated.","Es ist keine USB-Platte angeschlossen, Das Programm wird beendet.\n"));
		                return;
		     }		
             }
             file1.close();
         }  
      for(i=1; i <size_; i++) 
         {
         dummy = auftrag[i];
         dummy = dummy.trimmed(); 
         found = dummy.indexOf(".fsa");
         if(found > -1)
            { 
            auftrag_datei_name = dummy;
            j = i;
            }
         parameter[i-1] = dummy;
         }
         found=auftrag_datei_name.indexOf(".fsa");
         if (found > 0)
             auftrag_datei_name.replace(found, 4, ".txt");  
         // auftrag_datei_name = Name der txt-Datei   
     found = attribute.indexOf("savefs");
     if(found == -1)
         save = 2; //Restore partition
     else
         save = 1;  //Save  partition
      // Partition ermitteln
        found = attribute.indexOf("/dev");
        partition_ = attribute.right(attribute.size() -found -5);
        partition_ = partition_.trimmed();   
      row = 0;
      while (part[row][0] != "")
	   {
            partition_ = part[row][0]; // z.B. sda1
            if(partition_ == part_list)
               break;
            row ++;
           }    
      //Prüfen ob System oder Home Partition
      part_art = mtab_einlesen("/dev/" + partition_);
      if (part_art == "system" && save == 1)
            {
             ret = questionMessage(tr("The system partition to be backed up is mounted. Do you want to perform a live backup?", "Die zu sichernde Systempartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
             if (ret == 1)
                 live_save = 1;
             if (ret == 2)
                return;
             }
             if (part_art == "home" && save == 1)
                {
                ret = questionMessage(tr("The home partition to be backed up is mounted. Do you want to perform a live backup?", "Die zu sichernde Homepartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
                if (ret == 1)
                   live_save = 1;
                if (ret == 2)
                    return;
                 }
        if (part_art == "system" && save == 2)
                	{
                        QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The system partition to be recovered is mounted and cannot be written back. Please use a Live-CD.", "Die wiederherzustellende Systempartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return;
				      } 
                        
                   if (part_art == "home"&& save == 2)
                	{
                        QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The home partition to be restored is mounted and cannot be written back. Please use a live CD.","Die wiederherzustellende Homepartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return; 
                        
                	}  
                 if(save == 2)	//Partition zurückschreiben
                        {
                        auftrag_datei_name_pbr = auftrag_datei_name;
                        found=auftrag_datei_name_pbr.indexOf(".txt");
                        if (found > 0)
                           auftrag_datei_name_pbr.replace(found, 4, ".pbr"); 
                        QFile file2(auftrag_datei_name_pbr);
                        if (file2.exists())
                           {   //PBR-zurückschreiben
                           found=attribute.indexOf("dest=");
                           partition = attribute.right(attribute.size() -found - 5);
                           befehl = "dd if="+ auftrag_datei_name_pbr + " of=" + partition + " bs=512 count=1";
                           if(system (befehl.toLatin1().data()))
                              befehl = ""; 
                           }
                        QFile f(auftrag_datei_name);
                        // Prüfen ob text-Datei vorhanden 
    		        if (f.exists())
                           {
           		   dialog_auswertung = 3;
           		   FileDialog Filedialog;
     	       		   FileDialog *dlg = new FileDialog;
     	     		   int wert = dlg->exec();
             		   if (wert == 0 && dialog_auswertung == 3)
                	       {
                	       QMessageBox::about(this,tr("Note","Hinweis"),
         		       tr("The restore was aborted by the user", "Das Zurückschreiben wurde vom Benutzer abgebrochen\n"));
                               pushButton_restore->setEnabled(true);
                	       return;
                	   }
                        }
            	        dummy = attribute; 
            	        //Partition muss entmounted werden 
                        found = attribute.indexOf("dest=");
                        partition = attribute.right(attribute.size() -found - 5);
                        attribute = partition + " 2>/dev/null";  
                        befehl = "umount " + attribute;  //umount
                        if(system (befehl.toLatin1().data()))
                            befehl = ""; 
                        attribute = dummy;
                        attribute = attribute.trimmed();
                        save_attribut(attribute,0);
                        pushButton_save->setEnabled(false);
                        pushButton_restore->setEnabled(false);
                        pushButton_end->setEnabled(true);
                        listWidget_2->setEnabled(true); 
                        dummy = auftrag[0];
                        indizierung = dummy.toInt();
                        thread2.setValues(indizierung,"0");    
                        flag_View = 2;
  	                ViewProzent();
                        stopFlag = 0;
                        label_Partition->setText (tr("Existing partitions:", "vorhandene Partitionen"));
                        statusBar()->showMessage(tr("The recovery is performed.", "Die Wiederherstellung wird durchgeführt"), 15000); 
                        this->setCursor(Qt::WaitCursor);
  	                startThread2(); // fsarchiver wird im Thread ausgeführt 
  	                return ;
                         } 
    if(save == 1)	//Partition sichern 
        {          	       
          // Werte sammeln und nach file_dialog übergeben
         
        found = attribute.indexOf("-Z");
        if (found > -1)
           zip = 10;
        found = attribute.indexOf("-z");   
        if (found > -1)
           { 
           zip_ = attribute.mid(found+2,1); 
           zip  = zip_.toInt(); 
           }
        Qt::CheckState state;   
        state = chk_key->checkState();
        if(state == Qt::Checked)
           order_name= order_name + "+key"; 
        DateiName = lineEdit_DateiName->text(); 
        found = auftrag_datei_name_fsa.indexOf(DateiName); 
        auftrag_datei_name_fsa = auftrag_datei_name_fsa.left(found) + "" + DateiName + "-" + datum + ".fsa";
        auftrag_datei_name_pbr = auftrag_datei_name_fsa.left(found) + "" + DateiName + "-" + datum + ".pbr";
        auftrag[j] = auftrag_datei_name_fsa;
        parameter[j-1]=auftrag_datei_name_fsa; //Datum wurde aktualisiert
        auftrag[size_ -2] = auftrag_datei_name_fsa;
        folder_size_ = auftrag[size_ -2];
        folder_size = folder_size_.split("/");
        size_ = folder_size.size();
        folder = "";
        for(i=0; i <size_ -1; i++) 
            {
            dummy = folder_size[i];
            dummy = dummy.trimmed(); 
            folder_size[i] = dummy;
            
            folder = folder + folder_size[i] + "/";
            }
        result = size_determine("", folder); 
        // size_folder ist der freie Speicherplatz im Sicherungspfad 
        qDebug() << "vor beschreibung";
        beschreibungstext("/dev/" + partition_, DateiName + "-" + _Datum + ".fsa", zip, row, size_folder, folder);
        dialog_auswertung = 2;
        FileDialog Filedialog;
     	FileDialog *dlg = new FileDialog;
     	int wert = dlg->exec();
     	if (wert == 0 && dialog_auswertung == 2)
              	{
                QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
		pushButton_save->setEnabled(true);
                chk_pbr->setEnabled(true);
                return;
                }
         } 
         found = attribute.indexOf(".fsa");
         partition = attribute.right(attribute.size() -found);  
         //Partition muss entmounted werden    
         attribute = partition + " 2>/dev/null";   
         befehl = "umount " + attribute;  //umount
         if(system (befehl.toLatin1().data()))
             befehl = "";
         dummy = auftrag[0];
         indizierung = dummy.toInt();
         if(indizierung > 100)  //PBR mitsichern
            {
            befehl = "dd if=/dev/" + partition_ + " of=" + auftrag_datei_name_pbr + " bs=512 count=1";
            if(system (befehl.toLatin1().data()))
               befehl = "";
            indizierung = indizierung - 100;   
            } 
           // Größe der Partition ermitteln, in die gesichert wird.
                                result = size_determine(part_size_compress, folder);
                                if(result == 2)  
              			   {
                			QMessageBox::about(this,tr("Note", "Hinweis"),
         				tr("There is not enough space on the hard disk for the backup. The backup is canceled.", "Auf der Festplatte ist nicht genügend Platz für die Sicherung vorhanden. Die Sicherung wird abgebrochen.\n"));
					return;
               			   }   
        thread1.setValues(indizierung,"0");            
        pushButton_end->setEnabled(false);  
        pushButton_save->setEnabled(false);
        pushButton_restore->setEnabled(false);
        listWidget_2->setEnabled(false);
        chk_pbr->setEnabled(true); 
        flag_View = 1;
        ViewProzent();
        werte_reset();
        stopFlag = 0;
        this->setCursor(Qt::WaitCursor);
  	statusBar()->showMessage(tr("The backup is performed", "Die Sicherung wird durchgeführt"), 15000);
        this->setCursor(Qt::WaitCursor);
  	startThread1(); // fsarchiver wird im Thread ausgeführt
             
} 

void MWindow::save_attribut(QString attribut, int zahl)
{
//zahl 1 ist attribute.texte füllen bei einer Sicherung einer Partition
//zahl 2 ist attribute.texte füllen bei Wiederherstellung einer Partition
QString homepath = QDir::homePath();
QString line;
QString text;
QString text1;
int i = 0;
int doppel = 0;
int size_ = 0;
int found = 0;
int found1 = 0;
QString dummy;
QString replace[100];
QString dateiname = homepath + "/.config/qt5-fsarchiver/attribute.txt";
QFile file(dateiname);
dateiname = homepath + "/.config/qt5-fsarchiver/auftrag.db";  
QFile file2(dateiname);  
QStringList auftrag;
QString auftrag_; 
          file.open(QIODevice::WriteOnly);
          QThread::msleep(20 * sleepfaktor);
          QDataStream out(&file);
          out << attribut;
          file.close();
          // zahl 0: nur attribute sichern 
          // zahl 1: Auftrag sichern save Partition
          // zahl 2: Auftrag sichern restore Partition
          if(zahl == 0)
              return;
          if(live_flag == 1) // Bei Live-DVD: nur attribute sichern
              return;      
          if(zahl == 1 )
             order_name = lineEdit_DateiName->text();  //Order_name auslesen = Auftragname 
          if(!file2.exists())
              {
              //Datei wird angelegt
              QThread::msleep(10 * sleepfaktor);
              if (file2.open(QIODevice::ReadWrite)) 
                   {
                   QDataStream out(&file2);
                   attribut = attribut.trimmed();
                   text = order_name + " ## " + attribut + " ## "; 
                   out << text;
                   file2.close();
                   } 
               return;             
              }    
	file2.open(QIODevice::ReadOnly);
	QThread::msleep(10 * sleepfaktor);
        QDataStream stream( &file2 ); // read the data serialized from the file
        stream >> auftrag_ ;
        file2.close(); 
        auftrag = auftrag_.split("##");
        size_ = auftrag.size();
        for(i=0; i <size_ -1; i++) 
            {
            dummy = auftrag[i];
            dummy = dummy.trimmed(); 
            auftrag[i] = dummy;
            text = text + auftrag[i] + " ## ";
            }
        text = text + order_name + " ## " + attribut + " ## "; 
        if(zahl == 1)
            {
            //auf vorhandenen Auftrag prüfen
            for (i=0; i<size_; i++)
                {
                if(order_name == auftrag[i])
                     {
                     auftrag[i+1] = attribut;
                     doppel = 1;
                     break;
                     }
                 }
                 if(doppel == 1)
                    { 
                    text = ""; 
                    for (i=0; i <size_ -1; i++)
                        {
                        if (auftrag[i] != "")
                           text = text + auftrag[i] + " ## ";
                        } 
                  }
               } 
             if(zahl == 2)
                {
                // Partition aus attribut ermitteln
                found = attribut.indexOf("dest=/");
                found1 = attribut.indexOf("-c");
                order_name = attribut.right(attribut.size() -found -5);
                order_name = order_name.trimmed();
                if(found1 > -1)
                    order_name = order_name +"-key";
                //auf vorhandenen Auftrag prüfen
                for (i=0; i<size_; i++)
                    {
                if(order_name == auftrag[i])
                     {
                     auftrag[i+1] = attribut;
                     doppel = 1;
                     break;
                     }
                 }
                 if(doppel == 1)
                    { 
                    text = ""; 
                    for (i=0; i <size_ -1; i++)
                        {
                        if (auftrag[i] != "")
                            text = text + auftrag[i] + " ## ";
                        } 
                  }
               }
               if(zahl == 2 && doppel == 0)    //  Auftragname bei Wiederherstellung festlegen
                   {
                   text = "";
                   for(i=0; i <size_ -1; i++) 
                      {
                      dummy = auftrag[i];
                      dummy = dummy.trimmed(); 
                      auftrag[i] = dummy;
                      text = text + auftrag[i] + " ## ";
                    }
               text = text + order_name + " ## " + attribut + " ## "; 
               }   
         // Daten speichern 
         QThread::msleep(10 * sleepfaktor);   
         file2.open(QIODevice::WriteOnly);
         QDataStream out1(&file2);
         out1 << text;
         file2.close();
}
 
void MWindow::listWidget2_auslesen() {
QString homepath = QDir::homePath();
QString filename = homepath + "/.config/qt5-fsarchiver/auftrag.db";
QFile file(filename);
QStringList auftrag;
QString auftrag_;  
QString attribute;
QString datum;
QString str;
int row = 0;
int monat_ = 0;
int tag_ = 0;
int place[50];
int found = 0;
int j = 0;
int i = 0;
int size_ = 0;
    if(row == -1) 
       row = 0;
    row = listWidget_2->currentRow();
    row_1 = row;

    file.open(QIODevice::ReadOnly);
        QDataStream stream( &file ); // read the data serialized from the file
        stream >> auftrag_ ;
        file.close(); 
        auftrag = auftrag_.split("##");
        size_ = auftrag.size();
        for(i=0; i < size_ - 1; i++) 
               {
               order_name = auftrag[i];
               order_name = order_name.trimmed();
               attribute = auftrag[i+1].trimmed();
               widget_2_[j]= order_name;
               widget_2[j]= attribute;
               if(j > 98)
                  break;  //überlauf wird verhindert
               i++;
               j ++;
               }
    i = 0;           
    j = 0;
    datum = Zeit_auslesen();
    attribute= widget_2[row];
    attribute = attribute.trimmed();
    found = attribute.indexOf("savefs");
     if(found == -1)
         {
         pushButton_restore->setEnabled(true);
         pushButton_save->setEnabled(false);
         }
     else
        {
        pushButton_save->setEnabled(true);
        pushButton_restore->setEnabled(false);
        }
    order_name = widget_2_[row];
    lineEdit_DateiName ->setText(order_name); // Order_name schreiben
    // Pfad der txt Datei ermitteln
    str = attribute;
        while ((j = str.indexOf("/", j)) != -1) {
           if( j >= 0)
              {
              place[i]= j;
              i++;
              }
        ++j;
        } 
    found = attribute.indexOf(order_name);   
    folder_file_ = attribute.mid(place[0],found-place[0]) + order_name + "-" + datum + ".txt"; 
    i = 0;
    j = 0;
    attribute = attribute.trimmed();
        datum = Zeit_auslesen();
        str = attribute;
        while ((j = str.indexOf("-", j)) != -1) {
           if( j >= 0)
              {
              place[i]= j;
              i++;
              }
        ++j;
        } 
        monat_ = place[i-1] - place[i-2];
        tag_ = place[i-2] - place[i-3];
        attribute.replace(place[i-3], tag_ + monat_ + 5, "-" + datum);
        attribute = attribute.trimmed();
        widget_2_[0]= order_name;
        widget_2[0]= attribute;
        save_attribut(attribute,0);
        // zu sichernde Partition ermitteln
        found = attribute.indexOf("/dev");
        part_list = attribute.right(attribute.size() -found -5);
}

void MWindow::kill_end()
{ 
QString pid_bash;
QString befehl;
          pid_bash = pid_ermitteln_("bash"); 
          befehl = "kill -9 " + pid_bash;  //bash abbrechen, sofortiges Beenden
          if(system (befehl.toLatin1().data()))
            befehl = "";
} 

QString MWindow::pid_ermitteln_(QString prozess)
{
QString homepath = QDir::homePath();
QString befehl = "";
QString pid_nummer = "";
QStringList pid;
      QString filename = homepath + "/.config/qt5-fsarchiver/pid.txt";
      QFile file(filename);
      QTextStream ds(&file);
      QThread::msleep(10 * sleepfaktor);
      if(file.open(QIODevice::ReadWrite | QIODevice::Text))
      {
         befehl = "ps -C " + prozess + " 1> " +  filename;
         if (system (befehl.toLatin1().data()))
             befehl = "";
      if(file.size() == 0) 
         return " ";
        pid_nummer = ds.readLine();
        pid_nummer = ds.readLine();
        pid_nummer = pid_nummer.trimmed();        
         }
        file.close();
        befehl = "rm " + filename;
        if (system (befehl.toLatin1().data()))
           befehl = "";
      if (pid_nummer != "")
        {
         pid = pid_nummer.split(" ");
         pid_nummer = pid[0];
         }
        return pid_nummer;
}

int MWindow::pid_ermitteln()
{
QString homepath = QDir::homePath();
QString befehl = "";
QString pid_nummer = "";
QStringList pid;
int found = 0;
int zaehler = 0;
      QString filename = homepath + "/.config/qt5-fsarchiver/pid.txt";
      QFile file(filename);
      QTextStream ds(&file);
      QThread::msleep(10 * sleepfaktor);
      if(file.open(QIODevice::ReadWrite | QIODevice::Text))
         {
         befehl = "ps -C qt-fsarchiver 1> " +  filename;
         if (system (befehl.toLatin1().data()))
             befehl = "";
         while (!ds.atEnd())
             {   
             pid_nummer = ds.readLine();
             found = pid_nummer.indexOf("qt-fsarchiver");
             if(found > -1)
             zaehler ++;
            }
         }
        file.close();
    befehl = "rm " + homepath + "/.config/qt5-fsarchiver/pid.txt"; 
    if(system (befehl.toLatin1().data()))
       befehl = "";     
    return zaehler;
    
}

void MWindow::make_direct()
{
QString homepath = QDir::homePath();
QString attribute;
QString filename = homepath + "/.config/qt5-fsarchiver/auftrag.db";
QFile file(filename);
QStringList auftrag;
QString auftrag_;  
QString auftrag__[16];
int zeit[100][2];
QString dummy;
QString dummy1;
QString befehl;
int zahl = 0;
int zahl1 = 0;
int i = 0;
int j = 0;
int k = 0;
int m = 0;
int found = 0;
int found1= 0;
int size_ = 0;
QString datum;
QString pfad;
QString pfad1;
QString text;
QString beschreibungstext;
QString auftragstext;
int temp;
int temp1;
list_ = list_.right(list_.size() -1);   
list_ = list_.trimmed();
	file.open(QIODevice::ReadOnly);
        QDataStream stream( &file ); // read the data serialized from the file
        stream >> auftrag_ ;
        file.close(); 
        auftrag = auftrag_.split("##");
        size_ = auftrag.size();
        for(i=0; i < size_ - 1; i++) 
           {
           found = auftrag[i].indexOf(list_);
           found1 = auftrag[i].indexOf("/dev");
           if(found1 > -1)
             return;
           if(found > -1)
              {
               attribute = auftrag[i+1];
               break;
              }
           i++;
           }
        found = 0;   
        attribute = attribute.trimmed();
        auftrag = attribute.split(" ");
        size_ = auftrag.size();
        for(i=1; i < size_; i++)
           {
            auftrag__[i] = auftrag[i];
            found = auftrag[i].indexOf(".fsa");
            if(found > -1)
               {
               dummy = auftrag[i];
               zahl1 = i;
               }
           }
        for(i=size_ +1; i < 15; i++)
            auftrag__[i] = "";
        zahl = auftrag[0].toInt(); 
        // aktuelles Datum einfügen 
        datum = Zeit_auslesen(); 
        found = dummy.indexOf("-");
        auftragstext = dummy.left(found);
        auftrag__[zahl1] = dummy.left(found) + "-" + datum;
        //  parameter[zahl1] = auftrag__[zahl1]; //Datum wurde aktualisiert
        pfad = dummy.left(found) + "*.fsa";
        pfad1 = dummy.left(found) + "-" + datum + ".txt";
        auftragstext = auftrag__[zahl-1];
        beschreibungstext = "Backup filename:" + auftragstext + "\nsaved partition:" + auftrag__[zahl].toLatin1();
        QFile file3(pfad1);
        if(file3.open(QIODevice::WriteOnly | QIODevice::Text))
          {
          QTextStream stream(&file3);
          stream << beschreibungstext;
          }
          file3.close();
fsarchiver_aufruf(zahl,auftrag__[1].toLatin1().data(),auftrag__[2].toLatin1().data(),auftrag__[3].toLatin1().data(),auftrag__[4].toLatin1().data(),auftrag__[5].toLatin1().data(),auftrag__[6].toLatin1().data(),auftrag__[7].toLatin1().data(),auftrag__[8].toLatin1().data(),auftrag__[9].toLatin1().data(),auftrag__[10].toLatin1().data(),auftrag__[11].toLatin1().data(),auftrag__[12].toLatin1().data(),auftrag__[13].toLatin1().data(),auftrag__[14].toLatin1().data(),auftrag__[15].toLatin1().data());  

//älteste mehr als 3 Sicherungen entfernen
        befehl = "find " + pfad + " 1> " +  homepath + "/.config/qt5-fsarchiver/pfad.txt";
        if(system (befehl.toLatin1().data()))
          befehl = "";
        QString filename1 = homepath + "/.config/qt5-fsarchiver/pfad.txt";
	QFile file1(filename1);
	QTextStream ds(&file1);
	QThread::msleep(10 * sleepfaktor);
	i = 0;
        if (file1.open(QIODevice::ReadOnly | QIODevice::Text)) 
           {
     	   while (!ds.atEnd())
      	     {
             text = ds.readLine(); 
       	     auftrag__[i] = text;
       	     i++;
      	     }
      	    
      	   }   
   	file.close();
    	if(i > 2)
    	  {
    	   for(k=0; k < i +1; k++)
    	      {
   	      dummy = auftrag__[k];
              QFileInfo resourceInfo(dummy);
              dummy = resourceInfo.lastModified().toString("yyyy-MM-dd");
              // in Systemzeit umrechnen
              befehl = "date -d '" + dummy + "' +%s 1> " +  homepath + "/.config/qt5-fsarchiver/zeit.txt";
              if(system (befehl.toLatin1().data()))
                befehl = "";
              QString filename2 = homepath + "/.config/qt5-fsarchiver/zeit.txt";
	      QFile file2(filename2);
	      QTextStream ds(&file2); 
	      if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
	         {
	         dummy1 =  ds.readLine();
	         zeit[k][0] = dummy1.toInt(); // umgerechnete Datumzahl 
                 zeit[k][1] = k;
                 }
              file2.close();
              } 
              zeit[k-1][0] = 0;
              zeit[k-1][1] = 100;
    	    } 
            for (m = 0; m < k-2; ++m)
            {
               for (j = 0; j < k-2 ; ++j )
               {
               if (zeit[j][0] > zeit[j+1][0])
                {
                temp = zeit[j+1][0];
                temp1 = zeit[j+1][1];
                zeit[j+1][0] = zeit[j][0];
                zeit[j+1][1] = zeit[j][1];
                zeit[j][0] = temp;
                zeit[j][1] = temp1;
                }
              }
            }
            //älteste Dateien löschen
            for (j = 2; j < i-1 ; ++j )
                 {
                 zahl = zeit[j-2][1];
                 befehl = "rm " + auftrag__[zahl];
                 if(system (befehl.toLatin1().data()))
                    befehl = "";
                 found=auftrag__[zahl].indexOf(".fsa");
                 if (found > 0)
                      auftrag__[zahl].replace(found, 4, ".txt"); 
                 befehl = "rm " + auftrag__[zahl];
                 if(system (befehl.toLatin1().data()))
                    befehl = "";
                 } 
            // zeit.txt und pfad.txt löschen  
            befehl = "rm " + homepath + "/.config/qt5-fsarchiver/zeit.txt 2>/dev/null"; 
            if(system (befehl.toLatin1().data()))
                befehl = ""; 
            befehl = "rm " + homepath + "/.config/qt5-fsarchiver/pfad.txt"; 
            if(system (befehl.toLatin1().data()))
                befehl = ""; 
            qApp->quit();
return;            
}






