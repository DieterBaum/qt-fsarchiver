/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2019 Dieter Baum.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/orchar
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
#include <mntent.h>
#include <QtGui>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include "filedialog.h"
#include "setting.h"
#include "net.h"
#include "net_ein.h"
#include "mbr.h"
#include "clone.h"
#include "dir.h"

extern "C" {
}
#include <unistd.h>
#include "treeview.h"
#include "thread.h"

QString Datum_akt("");
QString partition_;
QString UUID;
std::string partition_str;
QString folder;
QString folder1;
QString _Datum;
QString DateiName("") ;
extern int dialog_auswertung;
extern int flag1;
extern QString parameter[15];
extern QString part[100][10];
QString widget[100];
int endeThread;
int sekunde_elapsed;
int minute_elapsed;
int sekunde_summe;
QStringList items_kerne_;
QStringList items_GB;
QStringList items_zstd;
QStringList items_sleep_;
QString partition_typ_;
QString partition_typ;
extern QString password;
extern QString user;
QString userpath;
QString part_art;
QString zip_[11];
QString SicherungsDateiName;
QString SicherungsFolderFileName;
int dummy_prozent;
int flag_View; 
int flag_end;
int sekunde_tara; 
QString pid, pid1;
QString befehl_pbr;
int stopFlag;
int row_1;
int zstd_level;
QString sdx[500];
int show_part = 0;
extern int sleepfaktor;
extern int password_;
int rootpassword = 0;

MWindow::MWindow()
{
   QStringList dummy; 
   QStringList partition_kurz;
   QString partition1_;
   QStringList items;
   QString version = ""; 
   QString version1 = "";
   int pos = 0, pos1 = 0;
   int i = 0;
   int found = 0;
   QString text = "";
   QString befehl;
   QString homepath = QDir::homePath();
   QString rootpath = QDir::rootPath();
   QString attribute;
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
  // groupBox->setFlat (true);
   pushButton_restore->setEnabled(false);
   // Signal-Slot-Verbindungen  Werkzeugleiste
   //connect( action_Beenden, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
   connect( action_Beenden, SIGNAL(triggered(bool)), this, SLOT(del_mediafolder()));
   connect( action_partition_save, SIGNAL(triggered(bool)),this, SLOT(save_button()));
   connect( action_partition_restore, SIGNAL(triggered(bool)),this, SLOT(restore_button()));
   connect( action_partition_save_net, SIGNAL(triggered(bool)),this, SLOT(eingabe_net_save()));
   connect( action_partition_restore_net, SIGNAL(triggered(bool)),this, SLOT(eingabe_net_restore()));
   connect( action_Information, SIGNAL(triggered(bool)),this, SLOT(info()));
   connect( action_Einstellungen, SIGNAL(triggered(bool)),this, SLOT(einstellungen()));
   connect( action_mbr_save, SIGNAL(triggered(bool)), this, SLOT(mbr_save()));
   connect( action_mbr_restore, SIGNAL(triggered(bool)), this, SLOT(mbr_restore()));
   connect( action_dir_save, SIGNAL(triggered(bool)), this, SLOT(dir_save()));
   connect( action_dir_restore, SIGNAL(triggered(bool)), this, SLOT(dir_restore()));
   connect( action_CloneDrive, SIGNAL(triggered(bool)), this, SLOT(clone_save()));
   connect( actionClone_HD, SIGNAL(triggered(bool)), this, SLOT(clone_save()));
   //schließt alle Fenster
   //connect( pushButton_end, SIGNAL( clicked() ), qApp, SLOT(quit()));
   connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(del_mediafolder()));
   //schließt das aktuelle (this)Fenster:
   //connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(close()));	
   connect( pushButton_save, SIGNAL( clicked() ), this, SLOT(savePartition()));
   connect( pushButton_restore, SIGNAL( clicked() ), this, SLOT(restorePartition()));
   // pushButton_partition, pushButton_folder und pushButton_zstd sind dummy Button um einen Slot ansprechen zu können
   connect( pushButton_zstd, SIGNAL( clicked() ), this, SLOT(zip_einlesen())); 
   connect( pushButton_partition, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
   connect( pushButton_partition_2, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
   connect( pushButton_folder, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
   connect( pushButton_folder_2, SIGNAL( clicked() ), this, SLOT(folder_expand()));
   connect(treeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &MWindow::folder_einlesen);
   connect( rdBt_saveFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( rdBt_restoreFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
   connect( chk_hidden, SIGNAL( clicked() ), this, SLOT(chkhidden()));
   connect( chk_split, SIGNAL( clicked() ), this, SLOT(chkGB()));
   connect( cmd_zstd, SIGNAL( clicked() ), this, SLOT(zip_setting_einlesen())); 

   //Benutzername ermitteln
   user = homepath.right(homepath.size() -6);
   userpath = homepath;
   // Zeitgeber für Berechnung remainingTime
   timer = new QTimer(this);
   bool ok;
   int live_flag = 0;
   // 0 = Eingabe Passwort erforderlich, 1 = keine Passworteingabe: Live-DVD, Passwort wird übergeben
   QDir dir1(userpath + "/.config/qt-fsarchiver");
   if (!dir1.exists())
       {
       befehl = " mkdir " + userpath + "/.config/qt-fsarchiver 2>/dev/null";
       if(system (befehl.toLatin1().data()))
          befehl = "";
       }
   // Ini-Datei auslesen, Passwort anzeigen?
   QFile file4(userpath + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
   QSettings setting1("qt-fsarchiver", "qt-fsarchiver");
   file4.open(QIODevice::ReadOnly);
   if (file4.exists()) {
        setting1.beginGroup("Basiseinstellungen");
        int auswertung = setting1.value("Passwort").toInt(); 
        if (auswertung ==1)
           lineKey ->setEchoMode(QLineEdit::Normal);
        else
	   lineKey ->setEchoMode(QLineEdit::Password);
        rootpassword = auswertung;
        setting1.endGroup();
        } 
   if (live_flag == 1)
       password = "ubuntu"; //Fiktives Passwort für die Live-DVD        
   if (live_flag == 0 && password == "")
      {
      do
       {
       if(rootpassword == 1)
          text = QInputDialog::getText(this, tr("Enter sudo-password","Sudo-Passwort eingeben"),
          (tr("sudo-Password:","sudo Passwort")), QLineEdit::Normal,"", &ok);
       else
          text = QInputDialog::getText(this, tr("Enter sudo-password","Sudo-Passwort eingeben"),
          (tr("sudo-Password:","sudo Passwort")), QLineEdit::Password,"", &ok);
       if (!ok)  //Cancel Programm wird beendet
          kill_end();
       if (ok && !text.isEmpty())
          password= text;
       if (ok && text.isEmpty())
          QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("You must enter a password.\n", "Sie müssen ein Passwort eingeben.\n"));
       } 
       while( password == "");
      }
      daten_write(password,0);
      daten_write("",1);
      //vorsichtshalber Passswortdatei löschen
      befehl = "rm " + userpath + "/.config/qt-fsarchiver/den.nfo.cpt 2>/dev/null";
      if(system (befehl.toLatin1().data()))
          befehl = "";
      QThread::msleep(10 * sleepfaktor);
      befehl = "/usr/bin/ccrypt -e -k " + userpath + "/.local/share/.en.nfo " + userpath + "/.config/qt-fsarchiver/den.nfo";
      if (system (befehl.toLatin1().data()))
          befehl = "";
      password = "xx"; //Damit das Passwort nicht im RAM ausgelesen werden kann
      if (live_flag == 0 && password_ == 0)
         {
       // Passwort prüfen
       attribute ="/temp1 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  3 " + attribute;
       if(system (befehl.toLatin1().data()))
           befehl = "";
       QThread::msleep(10 * sleepfaktor);
       QDir dir2("/temp1");
       if (dir2.exists())
          {
          attribute ="/temp1 2>/dev/null";
          befehl = "/usr/sbin/qt-fsarchiver.sh  8 "  + attribute;
          if(system (befehl.toLatin1().data()))
                befehl = ""; 
          password_ = 1; 
          } 
       else 
          {
          QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("The password is wrong. The program must be terminated. It may take a few seconds to close the window.\n", "Das Passwort ist falsch. Das Programm muss beendet werden. Das Schließen des Fensters kann einige Sekunden dauern.\n"));
          kill_end();   
          return;
         } 
       } 
       found = userpath.indexOf("root");
       if(found > -1)
          { 
          userpath = "/root";
          QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("The program cannot be run as root. The program must be terminated. It may take a few seconds to close the window.\n", "Das Programm kann nicht als root ausgeführt werden. Das Programm muss beendet werden. Das Schließen des Fensters kann einige Sekunden dauern.\n"));
          kill_end();   
          return;
          } 
       //vorsichtshalber Rechte immer neu setzen
       attribute = "chown -R " + user + " " + userpath + "/.config/qt-fsarchiver";
       befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
       if(system (befehl.toLatin1().data()))
         befehl = "";
       attribute = "chmod 777 "  + userpath + "/.config/qt-fsarchiver";
       befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
       if(system (befehl.toLatin1().data()))
         befehl = "";
   QFile file3(userpath + "/.config/qt-fsarchiver/running.txt");
   if (file3.exists())
      {
      if (is_running() == 2) {
         QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Qt-fsarchiver can only be started once. The program must be terminated..\n", "Qt-fsarchiver kann nur einmal gestartet werden. Das Programm muss beendet werden.\n"));
         esc_end(1);
        return;
        }
      }
   QFile file2("/usr/sbin/qt-fsarchiver-terminal");
   if(!file2.exists())
      {
      QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("The program qt-fsarchiver-terminal is not installed. You have to install this program additionally.\n", "Das Programm qt-fsarchiver-terminal ist nicht installiert. Sie müssen dieses  Programm zusätzlich installieren.\n"));
      esc_end(1);
      return;
      }
      //Version von qt-fsarchiver-terminal prüfen
      befehl = "/usr/sbin/qt-fsarchiver-terminal " + userpath + " version";
      if (system (befehl.toLatin1().data()))
         befehl = "";
      QString filename = userpath + "/.config/qt-fsarchiver/version.txt";
      QFile file1(filename);
      if(file1.open(QIODevice::ReadWrite))
         {
          QDataStream in(&file1);
          QString str;
          in >> version;
         }
       file1.close();
       found = version.indexOf(".");
       while (found > -1)
          {
          found = version.indexOf(".");
          if(found > -1)
             version.replace(found, 1, "");
          } 
        found = version.indexOf("-");
        version.replace(found, 1, "");
        int version_  = version.toInt();
        version1 ="0.8.6-3";
       if (!file1.exists() or 8603 > version_)
           {
       QMessageBox::warning(this,tr("Note", "Hinweis"),tr("qt-fsarchiver-terminal must be updated to version: ", "qt-fsarchiver-terminal muss auf die Version aktualisiert werden: ") + version1 + tr(" The program is terminated.", " Das Programm wird beendet"));
    	return;	
          }
       // Prüfen ob qt-fsarchiver.sh geändert wurde. Eventuell wurde eine echo Befehl zum Auslesen des Passwortes eingefügt.
       // Bei Ubuntu, Debian, Mint und Suse ist die erste Zeile #!/bin/bash.
       // Bei Fedora ist die erste Zeile #!/usr/bin/bash. Daher die verschiedenen Ergebnisse.
       QString vergleich = md5sum("/usr/sbin/qt-fsarchiver.sh");
       if(vergleich == "5619409c58962a583f17c93d30e26be9" or vergleich == "9fbdcece8af2796acfdc3284c4bd82b2");
       else
       {
           QMessageBox::warning(this,tr("Note", "Hinweis"),tr("Security warning: A file has been modified. The program is terminated. Please reinstall qt-fsarchiver.", "Sicherheitswarnung: Eine Datei wurde geändert. Das Programm wird beendet. Bitte installieren Sie qt-fsarchiver neu"));
    	return;
        }
   //Vorsichtshalber alle txt Dateien löschen
   date_delete();
   items_kerne_ << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12";
   cmb_kerne->addItems (items_kerne_);
   items_kerne_.clear();
   items_GB << "2" << "4" << "4,7";
   cmb_GB->addItems (items_GB);
   items_GB.clear();
   items_zstd << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" <<  "17" << "18" << "19" << "20" << "21" << "22";
   cmb_zstd->addItems (items_zstd);
   items_zstd.clear();
   items_sleep_.clear();
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
   if (flag1 == 0) 
   {
      QDir dir(userpath + "/.qt-fs-client");
      // Eventuelle Datein in .qt-fs-client löschen, da sonst das Mounten fehlerhaft sein kann
       attribute = "-R -f " + userpath + "/.qt-fs-client";
       befehl = "/usr/sbin/qt-fsarchiver.sh  15 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
       attribute = userpath + "/.qt-fs-client 2>/dev/null" ;
       befehl = "/usr/sbin/qt-fsarchiver.sh  3 " + attribute;
       if(system (befehl.toLatin1().data()))
          befehl = "";
      /* attribute = "chown -R " + user + " " + userpath + "/.qt-fs-client";
       befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
       if (system (befehl.toLatin1().data()))
          befehl = ""; */
    }
   // wegen Suse
   QDir dir3("/media");
   QString media = "/media";
   if (!dir3.exists()){
       attribute = media + " 2>/dev/null" ;
       befehl = "/usr/sbin/qt-fsarchiver.sh  3 " + attribute;
       if(system (befehl.toLatin1().data()))
           befehl = "";
       }
   // beim Abbruch einer Sicherung bleiben eventuell Daten in /tmp/fsa erhalten.
   // Bei ersten Start werden eventuell vorhandene Dateien gelöscht.
   // Beim Öffnen einer weiteren Instanz von qt-fsarchiver, darf /tmp/fsa keinenfalls gelöscht werden.
   // Das System sürzt ab!!
   if (is_running() == 0) {
       attribute = "-r -f /tmp/fsa 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  15 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
   }
   // Ini-Datei auslesen
   QFile file(userpath + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
   QSettings setting("qt-fsarchiver", "qt-fsarchiver");
   file.open(QIODevice::ReadOnly);
   if (file.exists()) {
        setting.beginGroup("Basiseinstellungen");
        sleepfaktor= setting.value("sleep").toInt();
        if (sleepfaktor == 0)
           sleepfaktor = 5;
        int auswertung = setting.value("Kompression").toInt();
        cmb_zip -> setCurrentIndex(auswertung); 
        if (auswertung ==10)
            cmb_zstd->setEnabled(true);
        else
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
        cmb_zstd -> setCurrentIndex(8);
        setting.beginGroup("Basiseinstellungen");
        setting.setValue("showPrg",1); 
        setting.setValue("ssh",1); 
        setting.setValue("sshfs",1); 
        setting.setValue("dummy",2);
        setting.setValue("sleep",4);
        setting.setValue("Kompression",10);
        setting.setValue("zstd",8);
        setting.setValue("Kerne",1);
        setting.setValue("overwrite",1);
        setting.setValue("tip",1);
        setting.endGroup();
        cmb_zstd -> setCurrentIndex(7);
        cmb_zstd->setEnabled(true);
        }
   label_4->setEnabled(false);
   chk_overwrite->setEnabled(true);
   cmb_zip->setEnabled(false);
   cmb_GB->setEnabled(false);
  // chk_Beschreibung->setEnabled(true);
   label->setEnabled(false);
   starteinstellung();
   if(show_part == 0)
       {
       sdx_einlesen();
       format_();
           // Partitionsname, Partitiontyp und Größe einlesen und formatieren für listWidget Ausgabe
           i=0;
           while (part[i][0] != "")
	   {
                partition_ = part[i][0]; // z.B. sda1
		UUID = part[i][3];       // UUID
                partition_typ = part[i][1]; // beispielweise ext4
                pos = partition_typ.indexOf("fat");
                if (pos > -1)
		   partition_typ = "vfat";
                pos = partition_typ.indexOf("ext3");
                pos1 = partition_typ.indexOf("ext4");
                if (pos > -1 || pos1 > -1)
		    partition_typ = "ext";
                partition_ = "/dev/"+ partition_; 
                //Prüfen ob System oder Home Partition
                part_art = mtab_einlesen(i);
                found = 0;
                if (part_art == "system" or part_art == "home" or part_art == "boot" or part_art == "boot/efi")
                   found = 1;
                if (!is_mounted(partition_.toLatin1().data()))
                   { 
                  if (found == 0)
                     {
         		if (partition_typ == "ext" || partition_typ == "btrfs"|| partition_typ == "vfat" || partition_typ ==  "ntfs" || partition_typ ==  "jfs" || partition_typ ==  "xfs")
                   		{
                   	 	befehl = "/usr/sbin/qt-fsarchiver.sh  3 -m 0777 /media/" + part[i][0];
                                if(system (befehl.toLatin1().data()))
                                    befehl = "";
                                befehl = "/usr/sbin/qt-fsarchiver.sh  2 /dev/" + part[i][0] + " /media/" + part[i][0]; 
                         	if(system (befehl.toLatin1().data()))
                                   befehl = "";
                                }
                        }
 		     }
                i++;
             }
         }
        show_part ++;
        partition_ = "" ;
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("showPrg").toInt();
        setting.endGroup();
        if (auswertung ==1 && dialog_auswertung == 0){
        int ret = questionMessage(tr("The file /usr/share/doc/qt-fsarchiver/doc/Readme contains instructions for using the program. Do you still want to see this note? You can change this in the basic settings.", "In der Datei /usr/share/doc/qt-fsarchiver/doc/Liesmich sind Hinweise zur Nutzung des Programms enthalten. Wollen Sie diesen Hinweis weiterhin sehen? Sie können dies in den Basiseinstellungen ändern."));
    		if (ret == 2){
		//Basiseinstellungen ändern
               QThread::msleep(5 * sleepfaktor);
        	QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        	setting.beginGroup("Basiseinstellungen");
        	setting.setValue("showPrg",0);
        	setting.endGroup();
                }
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
     Qt::CheckState state;
     state= chk_hidden->checkState();
     QStringList filters;
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
         }
     } 

void MWindow::starteinstellung()
     {
     Qt::CheckState state;
     state= chk_hidden->checkState();
     QStringList filters;
            label_folder->setText (tr("Backup directory", "Sicherungsverzeichnis"));
           // pushButton_save->setText (tr("Save partition", "Partition sichern"));
            lineEdit_DateiName->setEnabled(true);
            pushButton_restore->setEnabled(false);
            pushButton_save->setEnabled(true);
            label_4->setEnabled(true);
            chk_overwrite->setEnabled(true);
            cmb_zip->setEnabled(true);
            cmb_zstd->setEnabled(true);
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
     QFile file(folder);
     QFile file1(userpath + "/.config/qt-fsarchiver/zahlen.txt");
     QString befehl;
     QString text;
     QString attribute;
     Qt::CheckState state;
     Qt::CheckState state1;
     Qt::CheckState state3;
     int err = 0;
     QString keyText = "";
     QString compress = "";
     int found = 0; 
     int zip;
     int zip_zstd;
     bool ok;
     indicator_reset();
     attribute = "chown -R " + user + " " + userpath + "/.config/qt-fsarchiver";
     befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
     if(system (befehl.toLatin1().data()))
         befehl = "";
     QFile::remove(userpath + "/.config/qt-fsarchiver/zahlen.txt");
     if (file1.exists())
        {
        QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Error. The file ~/config/qt-fsarchiver/zahlen.txt could not be deleted by qt-fsarchiver. The program is terminated. Manually delete the mentioned file and start the program again.\n", "Fehler. Die Datei ~/config/qt-fsarchiver/zahlentext konnte von qt-fsarchiver nicht gelöscht werden. Das Programm wird beendet. Löschen Sie manuell die genannte Datei und starten das Programm erneut.\n"));
        del_mediafolder();
        }
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
        // Überprüfen ob ntfs oder fat Partition, wenn ja Sicherung PBR nicht ermöglichen
        DateiName = lineEdit_DateiName->text();
        if (DateiName == "")
           {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please select the file name of the backup.\n", 
		"Bitte wählen Sie den Dateinamen der Sicherung aus.\n"));
		return 0 ;
           }
        //Überprüfen ob im Dateinamen "/" enthalten ist. Wird durch "-" ersetzt
        found = DateiName.indexOf("/");
        while (found > -1){
          found = DateiName.indexOf("/");
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
         int liveFlag = 0;
         zip = cmb_zip->currentIndex();
        // Werte sammeln und nach file_dialog übergeben, Partition ist eingehängt
         int row = listWidget->currentRow();
       	 beschreibungstext(DateiName + "-" + _Datum + ".fsa", zip, row);
         if (!is_mounted(partition_.toLatin1().data()))
         {
                   part_art = mtab_einlesen(row_1);
                   //Überprüfung on LVM vorhanden und ob gemounted
                   if(part[row][7] == "/" or part[row][7] == "/home")
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
                                 befehl = "/usr/sbin/qt-fsarchiver.sh  4 /media/" + partition_; 
                             else                                 //Live-DVD ohne LVM und Raid
                                 befehl = "/usr/sbin/qt-fsarchiver.sh  4 /dev/" + partition_; 
                             err = system (befehl.toLatin1().data());
                                                                  // Sichern von LVM und Raid, keine Live-DVD
                             if(part[row_1][7] != "")
                                 befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + part[row_1][7]; 
                             err = err + system (befehl.toLatin1().data());
                            } 
                           if (err != 0 && liveFlag == 0)
                                {
				QMessageBox::warning(this,tr("Note", "Hinweis"),
         			tr("The partition", "Die Partition ")   + partition_ + tr("cannot be unmounted. The program is aborted.\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ; 
                                }  
                 	}
                }
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
                                    int len = parameter[indizierung + 1].size();
               				if (len < 6 || len > 64) {
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

                                 parameter[indizierung] = (folder1 + "/" + DateiName + "-" + _Datum + ".fsa");
				// Vorbereitung für psb
                                befehl_pbr = ""; 
				state = chk_pbr->checkState();
				if (state == Qt::Checked)
                                  {
                                  befehl_pbr = "/usr/sbin/qt-fsarchiver.sh  12 if=/dev/" + partition_ + " 'of=" + folder + "/" + DateiName + "-" + _Datum + ".pbr' bs=512 count=1";
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
             			 if (wert == 0 && dialog_auswertung == 0)
                		  {
                		  QMessageBox::warning(this,tr("Note", "Hinweis"),
         			  tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
				  pushButton_save->setEnabled(true);
                                  chk_pbr->setEnabled(true);
                		  return 0;
                		  }
             			}
//qDebug() << "Befehl" << parameter[0] << parameter[1] << parameter[2] << parameter[3] << parameter[4] << parameter[5] << parameter[6] << parameter[7] << parameter[8] << parameter[9] << parameter[10] << indizierung + 2;
                                // Argumente in txt-Datei schreiben
				QString attribute; 
				for ( int i=0; i<15; i++)
  				  {
  				  if (parameter[i] != " ")
     				  attribute = attribute + " " + parameter[i];
  				  }
				  attribute = QString::number(indizierung + 2)  + attribute;
                                save_attribut(attribute);
				pushButton_end->setEnabled(false);  
                                pushButton_save->setEnabled(false);
                                chk_pbr->setEnabled(true); 
                                flag_View = 1;
                              //  werte_reset();
  				//timer->singleShot( 20, this , SLOT(ViewProzent( ))) ;
                                ViewProzent();
                                stopFlag = 0;
                                dialog_auswertung = 1;
                                this->setCursor(Qt::WaitCursor);
  				statusBar()->showMessage(tr("The backup is performed", "Die Sicherung wird durchgeführt"), 15000);
                                befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath;
                                if(system (befehl.toLatin1().data()))
                                   befehl = "";
        		        }
                    }
           return 0;

}

void MWindow::save_attribut(QString attribut)
{
QString dateiname = userpath + "/.config/qt-fsarchiver/attribute.txt";
QFile file(dateiname);
file.open(QIODevice::WriteOnly);
QDataStream out(&file);
out << attribut;
file.close();
}

void MWindow::ViewProzent()
{
QString text;
QString sekunde;
int sekunde_ = 0;
QString minute;
int minute_ = 0;
int anzahl = 0;
int anzahl1 = 0;
int flag = 0;
int prozent = 0;
QString text_integer;
QString dummy;
int dummy1 = 0;
text = datei_auswerten("p");
endeThread = text.toInt();
if((endeThread == 10 && flag_View == 1) or (endeThread == 11 && flag_View == 1))
   thread1Ready();
if((endeThread == 10 && flag_View == 2)or (endeThread == 11 && flag_View == 2))
   thread2Ready();
if(endeThread != 10 && endeThread != 11)
{
  timer->singleShot(1000, this , SLOT(ViewProzent( ))) ;
  elapsedTime();
  this->repaint();
  dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/meldung.txt"); 
  flag = dummy.toInt();
  if (flag_View == 1)  //nur bei save
	{
         if (flag == 0)
         {
          dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/anzahl_file.txt"); 
          anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
          if (anzahl != 0){
  	   text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);
           }
 	}
      if (flag == 1)
 	   {
           dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/anzahl_file.txt"); 
           anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
           text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);

           dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/anzahlfile.txt");
           anzahl1  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
           if (anzahl1 != 0) { 
 	   text_integer = text_integer.setNum(anzahl1);
           AnzahlgesicherteFile ->setText(text_integer);
           }
      }     
      }
 dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/prozent.txt");
 dummy = dummy.left(dummy.size()-1);
 dummy1  = dummy.toInt(); // Prozent
 if (dummy1 > 0){
     prozent = dummy.toInt();
}
 if (dummy_prozent != prozent)
   {
     if(prozent > 0) 
        {
        remainingTime(prozent);
        }
   }
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
 if (prozent != 100 && stopFlag == 0 && prozent > 0) 
     	progressBar->setValue(prozent);
       //  progressBar->setValue(0);
    return;
} 


int MWindow::restorePartition()
{
Qt::CheckState state1;
QFile file(folder);
QFile file1(userpath + "/.config/qt-fsarchiver/zahlen.txt");
QString DateiName("") ;
int err = 0;
QString keyText = "";
QString dev_part;
QString text;
QString befehl;
int cmp = 0;
QString attribute;
  indicator_reset();
  std::string dateiname;
  keyText = lineKey->text();
  state1 = chk_key->checkState();
  attribute = "chown -R " + user + " " + userpath + "/.config/qt-fsarchiver";
  befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
  if(system (befehl.toLatin1().data()))
      befehl = "";
  QFile::remove(userpath + "/.config/qt-fsarchiver/zahlen.txt");
  if (file1.exists())
        {
        QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Error. The file ~/config/qt-fsarchiver/zahlen.txt could not be deleted by qt-fsarchiver. The program is terminated. Manually delete the mentioned file and start the program again.\n", "Fehler. Die Datei ~/config/qt-fsarchiver/zahlentext konnte von qt-fsarchiver nicht gelöscht werden. Das Programm wird beendet. Löschen Sie manuell die genannte Datei und starten das Programm erneut.\n"));
        del_mediafolder();
        return 1;
        }
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
               QString optionkey;
               parameter[0] = "fsarchiver";
       	       parameter[1] = "archinfo";
               if (state1 != Qt::Checked) {
               		parameter[2] = folder1;
                        attribute = parameter[0] + " " + parameter[1] + " " + parameter[2];
  			attribute = "3 " + attribute;
                        save_attribut(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath;
                        if(system (befehl.toLatin1().data()))
                            befehl = "";
                        QThread::msleep(10 * sleepfaktor);
               		optionkey = datei_auswerten("p");
               		dev_part = datei_auswerten("r");
                        QString sys = datei_auswerten("o");
                        if(optionkey == "13"){
                  	  chk_key->setChecked(true);
                          lineKey->setEnabled(true);
                  	  QMessageBox::about(this,tr("Note", "Hinweis"),
         	     		tr("The partition is encrypted. Please enter the key", "Die Partition ist verschlüsselt. Bitte geben Sie den Schlüssel ein\n"));
                   	  return 0;
               		} 
     
        	   }
                       if (state1 == Qt::Checked) {
            		parameter[2] = "-c";
                        parameter[3] = keyText;
                        if (parameter[3].size() < 6 || parameter[3].size() > 64) {
                  		QMessageBox::about(this,tr("Note", "Hinweis"),
         	  		tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  	lineKey->setText ("");
	                return 0 ; 
               	   		}
			parameter[4] = folder1;
                        attribute = parameter[0] + " " + parameter[1] + " " + parameter[2] + " " + parameter[3] + " " + parameter[4];
                        attribute = "5 " + attribute;
                        save_attribut(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath;
                        if(system (befehl.toLatin1().data()))
                           befehl = "";
                        QThread::msleep(10 * sleepfaktor);
                        dev_part = datei_auswerten("r");
                        optionkey = datei_auswerten("p");
                        if(optionkey == "13") {
                           QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                          date_delete();
                           return 0;
                        }
			
                }
            // Hier wird verglichen dev_ = die Partition, die zu sichern ist. dev_part = Originalpartition
            QString label1 = label_read(partition_);  //Bezeichnung der wiederherzustellenden Partition ermitteln
            QString dummy = dev_part.right(dev_part.size() -5); 
            QString label2 = label_read(dummy);      //Bezeichnung der gesicherten Partition ermitteln
            if (dev_part != "/dev/" + partition_){
               cmp = questionMessage(tr("The partition to be recovered  ", "Die wiederherzustellende Partition ") + "/dev/" + partition_ + " " + label1 +
               tr(" does not coincide with the saved  ", " stimmt nicht mit der gesicherten ") + dev_part + " " + label2 + tr("Do you still want to perform the recovery?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
               if (cmp == 2)  //nicht wiederherstellen
                  return 0;
            }
           if (rdBt_restoreFsArchiv->isChecked())
            	{
                extern QString folder_file_;
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
             		if (wert == 0 && dialog_auswertung == 0)
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
        			befehl_pbr = "if="+ filename + " of=/dev/" + partition_; 
		       }
            	  }
           if (!is_mounted(partition_.toLatin1().data())) 
              {
              part_art = mtab_einlesen(row_1);
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
                          befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
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
                 befehl = "/usr/sbin/qt-fsarchiver.sh  4 /dev/" + partition_; // unmounten
 		 if(system (befehl.toLatin1().data()))
                    befehl = "";
                 QThread::msleep(50 * sleepfaktor);
                 befehl = "/usr/sbin/qt-fsarchiver.sh  7 -f /dev/" + partition_; // Partition anlegen
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
               parameter[3] = folder1;
               parameter[4] = "id=0,dest=/dev/" + partition_;
               int indizierung = 5;       
               if (state1 == Qt::Checked) { // Verzeichnis mit Schlüssel gesichert
                 indizierung = 7; 
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
                  save_attribut(attribute);
             //  werte_reset();
               pushButton_restore->setEnabled(false);
               pushButton_end->setEnabled(true); 
               flag_View = 2;
  	      // timer->singleShot( 1000, this , SLOT(ViewProzent( )));
               ViewProzent();
               stopFlag = 0;
               this->setCursor(Qt::WaitCursor);
               befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath;
               if(system (befehl.toLatin1().data()))
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
    partition_ = widget[row];
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
qDebug() << "Bin in zip einlesen";
int zip = cmb_zip->currentIndex();
    if (zip == 10) 
       cmb_zstd->setEnabled(true);
    else
       cmb_zstd->setEnabled(false);
}

void MWindow::folder_einlesen() {
int found = 0;
   QModelIndex index = treeView->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder =  (dirModel->filePath(index));
   folder1 =  (dirModel->filePath(index));
   found=folder1.indexOf(" ");
   while (found > -1)
        {
        found = folder1.indexOf(" ");
        if (found > -1)
              folder1.replace(found, 1, "+"); 
        }
}

void MWindow::folder_expand() {
   QModelIndex index = treeView->currentIndex();
   treeView->expand(index);
}

void MWindow::folder_file() {
   extern QString folder_file_;
   folder_file_ = folder + "/" + DateiName + "-" + _Datum + ".txt";
}

void MWindow::info() {
   QMessageBox::information(
      0, tr("qt-fsarchiver"),
      tr("Backup and restore partitions, directory and MBR.\nversion 0.8.6-5, November 30, 2021",
         "Sichern und Wiederherstellen von Partitionen, Verzeichnissen und MBR Version 0.8.6-5, 30. November 2021"));
      }

int MWindow::is_running(){
      QString running;
      QString befehl;
      QDir dir1(userpath + "/.config/qt-fsarchiver");
      if (dir1.exists()){  //vermeidet Fehlermeldung beim ersten Start
          befehl = "ps --user " + user + " | grep -w qt-fsarchiver 1> " +  userpath + "/.config/qt-fsarchiver/running.txt";
          if(system (befehl.toLatin1().data()))
             befehl = ""; 
      }
      QString filename = userpath + "/.config/qt-fsarchiver/running.txt";
      QFile file(filename);
      int zaehler = 0;
      QTextStream ds(&file);
      file.open(QIODevice::ReadOnly | QIODevice::Text); 
      while (running == ""){
            running = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
       while (!ds.atEnd())
      	   {
           running = ds.readLine();
	   if (running.indexOf("qt-fsarchiver") > 0) 
              zaehler = zaehler + 1;
           } 
           file.close();
           if (zaehler > 0) {
               // qt-fsarchiver läuft bereits in einer Instanz 
               return 2;
           }
           return 0; 
}

int MWindow::testDateiName(std::string endung)
{
  std::string str (folder.toLatin1().data());
  size_t found;
  // different member versions of find in the same order as above:
  found=str.find(endung);
  if (found!=std::string::npos)
     {
        return found;
     }
  else
     {
        return 0;
     } 
}

int MWindow::is_mounted(char* dev_path) {
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


void MWindow::mbr_save () {
int i = 5;
QString device = part[0][3]; 
     i = is_gpt_main(device);
//qDebug() << "dialog i" << i;
     if(i < 2)
     {
        dialog_auswertung = 4;
        DialogMBR *dialog = new DialogMBR;
        dialog->show();
      }
}
void MWindow::mbr_restore () {
int i = 5;
QString device = part[0][3]; 
     i = is_gpt_main(device);
//qDebug() << "dialog i" << i;
     if(i < 2)
      {
         dialog_auswertung = 5;
         DialogMBR *dialog = new DialogMBR;
         dialog->show();
      }
}

void MWindow::dir_save () {
     dialog_auswertung = 4;
     DialogDIR *dialog1 = new DialogDIR;
     dialog1->show();
}
void MWindow::dir_restore () {
      dialog_auswertung = 5;
      DialogDIR *dialog1 = new DialogDIR;
      dialog1->show();
}

void MWindow::clone_save () {
     dialog_auswertung = 7;
     DialogClone *dialog1 = new DialogClone;
     dialog1->show();
}

void MWindow::einstellungen() {
      DialogSetting *dialog2 = new DialogSetting;
      dialog2->show();
}

void MWindow::eingabe_net_save () {
NetEin netein;
      	this->setCursor(Qt::WaitCursor);  
        int i = netein.list_net("1");
        if ( i != 1)
	{
 		dialog_auswertung = 6;
      		NetEin *dialog3 = new NetEin;
      		dialog3->show();
                this->setCursor(Qt::ArrowCursor);  
	}
         this->setCursor(Qt::ArrowCursor);
}

void MWindow::eingabe_net_restore () {
NetEin netein;
      	this->setCursor(Qt::WaitCursor);  
        int i = netein.list_net("1");
        if ( i != 1)
	{
                this->setCursor(Qt::WaitCursor);  
      		dialog_auswertung = 7;
      		NetEin *dialog3 = new NetEin;
      		dialog3->show();
                this->setCursor(Qt::ArrowCursor);
        }
        this->setCursor(Qt::ArrowCursor);
}

void MWindow::format_() {
     extern QString add_part[100];
     if (add_part[0] == "") //verhindert Änderungen durch Aufruf in net.cpp listWidget_auslesen() MWindow window
     {
     QString teilstring, space1, space2, space3, dummy;
     int aa, bb, cc, dd;
     int i = 0;
     int j = 0;
     //zunächst prüfen ob Label Einträge vorhanden sind
         while (part[i][0] != "") {
            dummy =  part[i][6];
            if (!dummy.isEmpty())
                 j++;
              i++;   
             } 
         i = 0; 
         if (j > 0)  //mindestens 1 Label Eintrag vorhanden
           {    
           while (part[i][0] != "") {
             teilstring = part[i][0];
             aa = teilstring.size();
             teilstring = part[i][1];
             bb = teilstring.size();
             teilstring = part[i][2];
             cc = teilstring.size();
             dd = 12 - aa; 
             space1.fill (' ',dd);
             dd = 15 -bb -cc;
             space2.fill (' ',dd);
             dd = 2;
             space3.fill (' ',dd);
             teilstring = part[i][0] + space1 + part[i][1] +space2 + part[i][2] + space3 + part[i][6];
             if (part[i][1] != "" ){
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
           while (part[i][0] != "") {
              teilstring = part[i][0];
              aa = teilstring.size();
              teilstring = part[i][1];
              bb = teilstring.size();
              teilstring = part[i][2];
              cc = teilstring.size();
              dd = 19 - aa; 
              space1.fill (' ',dd);
              teilstring = part[i][0] + space1;
              dd = 21 -bb -cc;
              space2.fill (' ',dd);
              teilstring = part[i][0] + space1 + part[i][1] +space2 + part[i][2];
              if (part[i][1] != "" ){
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

void MWindow::closeEvent(QCloseEvent *event) {
     del_mediafolder();
     event->accept();
}

void MWindow::thread1Ready(){
int part_testen;
QString dummy; 
QString text_integer; 
int err = 0;
int anzahl = 0;
     if (endeThread != 0) {
       dummy = datei_auswerten_1(userpath + "/.config/qt-fsarchiver/anzahlfile.txt");
       anzahl  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
       if (anzahl != 0) { 
          text_integer = text_integer.setNum(anzahl);
           }
       AnzahlgesicherteFile ->setText(text_integer);
       progressBar->setValue(100); 
       SekundeRemaining ->setText("0");
       MinuteRemaining ->setText("0");
       dummy = datei_auswerten("f"); 
       int cnt_regfile  = dummy.toInt();
       QString cnt_regfile_ = QString::number(cnt_regfile);
       dummy = datei_auswerten("g"); 
       int cnt_dir  = dummy.toInt();
       QString cnt_dir_ = QString::number(cnt_dir); 
       dummy = datei_auswerten("h"); 
       int cnt_symlinks  = dummy.toInt();
       QString cnt_symlinks_ = QString::number(cnt_symlinks);
       dummy = datei_auswerten("i"); 
       int cnt_hardlinks  = dummy.toInt(); 
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       cnt_hardlinks = cnt_hardlinks + cnt_symlinks;
       cnt_hardlinks_ = QString::number(cnt_hardlinks);
       dummy = datei_auswerten("j"); 
       int cnt_special  = dummy.toInt();
       QString cnt_special_;
       cnt_special_ = QString::number(cnt_special);
       dummy = datei_auswerten("p"); 
       err = dummy.toInt();
       if (dialog_auswertung == 1 and err == 10 and befehl_pbr == ""){ 
           //Rückmeldung von fsarchiver: Sicherung erfolgreich
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been backed.", " spezielle Daten wurden gesichert."));
	}
        if (dialog_auswertung == 1 and err == 10 and befehl_pbr != ""){ 
           //Rückmeldung von fsarchiver: Sicherung erfolgreich
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
        + cnt_special_ + tr(" specials and the Partition Boot Record have been backed.", " spezielle Daten und der Partition Boot Sektor wurden gesichert."));
	}
        if (dialog_auswertung == 1 and err != 10)
        {
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
       if (flag_end == 1) 
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The backup of the partition was aborted by the user!\n", "Die Sicherung der Partition  wurde vom Benutzer abgebrochen!\n") );
       // Prüfen ob Partitionsart unterstützt wird 
       dummy = datei_auswerten("d");  //Prüfung erforderlich
       part_testen = dummy.toInt();      
       if (part_testen == 110){ 
       QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported.\n", "Der Partitionstyp wird nicht unterstützt.\n" ));
          flag_end = 1;
          } 
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       dummy = datei_auswerten("d");
       part_testen = dummy.toInt(); 
       if (part_testen == 108){
	   QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported. Maybe the partition is encrypted?\n", "Der Partitionstyp wird nicht unterstützt. Vielleicht ist die Partition verschlüsselt?\n" ));
          }
       if (part_testen == 109){
	   QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The backup of the partition was not successful. The file is too large. Use a FAT partition?\n", "Die Sicherung der Partition war nicht erfolgreich. Die Datei ist zu groß. Nutzen Sie eine FAT-Partition?\n" ));
          //verbleibende Text-Datei löschen
          pos=SicherungsFolderFileName.indexOf("fsa");
          if (pos > 0)
        	SicherungsFolderFileName.replace(pos, 3, "txt"); 
          pos=SicherungsFolderFileName.indexOf("+");
          if (pos > 0)
        	SicherungsFolderFileName.replace(pos, 1, " "); 
          QFile file(SicherungsFolderFileName);
          file.remove();
          }
       dummy = datei_auswerten("a");
       int err_regfile = dummy.toInt();    
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten("b");
       int err_dir = dummy.toInt();  
       QString err_dir_ = QString::number(err_dir); 
       dummy = datei_auswerten("c");
       int err_symlinks = dummy.toInt(); 
       dummy = datei_auswerten("e");
       int err_hardlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten("k"); //err_special
       int err_special = dummy.toInt(); 
       QString err_special_ = QString::number(err_special);
       if (part_testen <= 108 && flag_end == 0 ){
       	  QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The backup of the partition was only partially successful.\n", "Die Sicherung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" specials have been backed\n.", " spezielle Daten wurden gesichert\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" special data was not saved correctly.\n."," spezielle Daten wurden nicht korrekt gesichert.\n"));
         //verbleibende Text-Datei löschen
          pos=SicherungsFolderFileName.indexOf("fsa");
          if (pos > 0)
        	SicherungsFolderFileName.replace(pos, 3, "txt"); 
          pos=SicherungsFolderFileName.indexOf("+");
          if (pos > 0)
        	SicherungsFolderFileName.replace(pos, 1, " "); 
          QFile file(SicherungsFolderFileName);
          file.remove();
	  }
        }
       
     }
  this->setCursor(Qt::ArrowCursor);
  pushButton_end->setEnabled(true);
  pushButton_save->setEnabled(true);
  date_delete();
  lineKey->setText ("");
  sekunde_summe = 0;
  minute_elapsed = 0;
  sekunde_elapsed = 0;
  befehl_pbr = "";
}

void MWindow::thread2Ready(){

QString dummy;
int err = 0;
   dummy = datei_auswerten("d"); 
   int meldung  = dummy.toInt();
   int i = 0;
   if (meldung == 105) {
      QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition to be restored is mounted. It must be unmounted first! \n", "Die Partition die wiederhergestellt werden soll, ist eingehängt. Sie muss zunächst ausgehängt werden!\n"));
      endeThread = 0;
       }
   if (endeThread != 0) { 
     pushButton_end->setEnabled(true);
     dummy = datei_auswerten("f"); 
     int cnt_regfile  = dummy.toInt();
     QString cnt_regfile_ = QString::number(cnt_regfile);
     dummy = datei_auswerten("g"); 
     int cnt_dir  = dummy.toInt();
     QString cnt_dir_ = QString::number(cnt_dir); 
     dummy = datei_auswerten("h"); 
     int cnt_symlinks  = dummy.toInt();
     dummy = datei_auswerten("i"); 
     int cnt_hardlinks  = dummy.toInt();
     cnt_hardlinks = cnt_symlinks + dummy.toInt(); 
     QString cnt_hardlinks_ = QString::number(cnt_hardlinks); 
     dummy = datei_auswerten("j"); 
     int cnt_special  = dummy.toInt();
     QString cnt_special_;
     cnt_special_ = QString::number(cnt_special);
     dummy = datei_auswerten("p"); 
     err = dummy.toInt();
     if (err == 10){
       // Ausgabe progressBar durch Timer unterbinden
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       MinuteRemaining ->setText("0");
      //PBR herstellen
      i = 2;
      if (befehl_pbr != "") 
         {
         QString befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + befehl_pbr + " bs=512 count=1"; 
         if(system (befehl.toLatin1().data()))
             befehl = "";
         i = 0;
         }
      if (i!=0 ) {
        stopFlag = 1; 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" special data has been restored.", " spezielle Daten wurden wieder hergestellt."));
        }
      if (i==0) {
       stopFlag = 1; 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links ", " Links ") + cnt_special_ + tr(" special data and the partition boot sector were restored.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt."));
        } 
      }  
     if (flag_end == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The restore of the partition was break by user!\n", "Die Wiederherstellung der Partition  wurde vom Benutzer abgebrochen!\n") );
	meldung = 0;
        }

          // Anzahl nicht korrekt zurückgeschriebene Dateien ausgeben
       dummy = datei_auswerten("e");
       int err_hardlinks = dummy.toInt();
       dummy = datei_auswerten("c");
       int err_symlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten("k"); 
       int err_special = dummy.toInt();
       QString err_special_ = QString::number(err_special);
       dummy = datei_auswerten("a"); 
       int err_regfile = dummy.toInt();
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten("b"); 
       int err_dir = dummy.toInt();
       QString err_dir_ = QString::number(err_dir); 
       err_hardlinks = dummy.toInt();
       err_hardlinks_ = QString::number(err_hardlinks); 
       if (err == 11) {
        if (i!=0 && meldung !=106) {  
          QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" specials has been restored.\n.", " spezielle Daten wurden wiederhergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
               }
       if (i==0 && meldung !=106) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" special data and the partition boot sector were restored.\n.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
                }
        }
     if (meldung == 102) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), tr("You have tried restore a partition. The selected file can only restore directories. Please restart the program.\n", "Sie haben versucht eine Partition wiederherzustellen. Die gewählte Datei kann nur Verzeichnisse wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 103) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben.\n"));
        endeThread = 0;
        lineKey->setText ("");
      }
        if (meldung == 106) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition to be written back to is too small.\n", "Die Partition in die zurückgeschrieben wird ist zu klein.\n"));
        endeThread = 0;
        lineKey->setText ("");
      }
    }
    this->setCursor(Qt::ArrowCursor);
    pushButton_end->setEnabled(true);
    pushButton_restore->setEnabled(true);
    date_delete();
    lineKey->setText ("");
    sekunde_summe = 0;
    minute_elapsed = 0;
    sekunde_elapsed = 0;
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
    // werte_reset();
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
              esc_end(0);  
         break;
     }
}

QString MWindow::beschreibungstext(QString text, int zip, int row)  {
FileDialog filedialog; //Create the main widget; 
float compress_[11];
float compress_zstd[23];
QString part_size_;
QString part_size_compress;
float part_size;
QString Linuxversion;
QString ubuntu_root;
QString ubuntu_home;
QString compress = zip_[zip];
QString kernel;
QString dummy;
QString dummy1;
int pos = 0;
compress_[0] = 0.54;  //lz4
compress_[1] = 0.55;  //lzo
compress_[2] = 0.46;  //gzip fast
compress_[3] = 0.44;  //gzip standard
compress_[4] = 0.42;  //gzip best
compress_[5] = 0.41;  //bzip2 fast
compress_[6] = 0.40;  //bzip2 good
compress_[7] = 0.40; //lzma fast
compress_[8] = 0.38; //lzma medium
compress_[9] = 0.37; //lzma best

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
int zstd = cmb_zip->currentIndex();
int zip_zstd = cmb_zstd->currentIndex() +1;
QString zip_zstd_ = QString::number(zip_zstd);
part[row][4] = sdx3_einlesen(part[row][0],0);
part[row][5] = sdx3_einlesen(part[row][0],1);
     if(zstd == 10)
        compress = compress + " level:" + zip_zstd_;
      dummy = part[row][4];
      dummy1 = dummy.right(2); // Einheiten M(ega) G T 
      dummy = dummy.left(dummy.size() -2); 
// Komma in Punkt ändern
        pos=dummy.indexOf(",");
           if (pos > 0)
        	dummy.replace(pos, 1, "."); 
	part_size = dummy.toFloat();
        if  (zstd == 10)
            part_size = part_size * compress_zstd[zip_zstd];
        else
            part_size = part_size * compress_[zip];
        if(part_size == 0)
           part_size = 1;
        part_size = part_size*100;
        part_size = round(part_size);
        part_size = part_size/100;
        part_size_compress = QString::number(part_size) + " " + dummy1;
        text = tr("Backup file name: ", "Sicherungsdateiname: ") + text + "\n" + 
	tr("Partition  name: ", "Partitionsname: ")  
	+ part[row][0] + "\n" + tr("Partition type: ", "Partitionsart: ") 
       	+ part[row][1] + "\n" + tr("UUID: ") +  part[row][3] + "\n" + tr("Description: ", "Bezeichnung: ") + part[row][6] + "\n" + 
       	tr("Partition size: ", "Partitionsgröße: ") + part[row][2] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + 
       	part[row][4] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + part[row][5]  + "\n" + tr("Compression: ", "Kompression: ") + compress + "\n" + 
       	tr("Approximate image file sizes: ", "ungefähre Sicherungsdateigröße: ") + part_size_compress + "\n" + "\n" + tr("Other notes: ", "weitere Hinweise:");
        ubuntu_root = tr("to be protected/secured partition: / (root system directory) ", "zu sichernde / gesicherte Partition: / (Wurzel-Systemverzeichnis) ");
        row_1 = row;
        part_art = mtab_einlesen(row);
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
	filedialog.werte_uebergeben(text);
        return text;
}

QString MWindow::format(float zahl)
{
QString zahl_;
int found;
         if (zahl <= 999){
            zahl = (int) (zahl * 100/1.024);
            zahl = zahl/100;
            // Punkt in Komma wandeln
            zahl_ = QString::number(zahl,'f',2);
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
            zahl_ = QString::number(zahl,'f',2);
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
            zahl_ = QString::number(zahl,'f',2);
            found=zahl_.indexOf(".");
            if (found > 0)
             	zahl_.replace(found, 1, ","); 
            return zahl_  + tr(" GB");
	 }
return "";  
}


QString MWindow::linux_version()  {

QString befehl;
QString Linuxversion;
int i;
	befehl = "cat /etc/*release 1> " +  userpath + "/.config/qt-fsarchiver/version.txt";
        if(system (befehl.toLatin1().data()))
           befehl = "";
        QString filename = userpath + "/.config/qt-fsarchiver/version.txt";
        QFile file(filename);
        QTextStream ds(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text); 
        while (Linuxversion == ""){
            Linuxversion = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
           Linuxversion = ds.readLine();
           if (Linuxversion.indexOf("PRETTY_NAME") > -1) 
              {  //Debian
               Linuxversion = Linuxversion.right(Linuxversion.size() -13);
               Linuxversion = Linuxversion.left(Linuxversion.size() -1);
               return Linuxversion;
	      }
             for (i=1; i < 4; i++){
           	Linuxversion = ds.readLine(); // Simply Linux
           }
           file.close();
           befehl = "rm " + filename;
           if(system (befehl.toLatin1().data()))
               befehl = "";
           // Ubuntu, Debian  
           if (Linuxversion.indexOf("DISTRIB_DESCRIPTION=")>0)
               Linuxversion=Linuxversion.right(Linuxversion.size()-20);
           return Linuxversion;
}

QString MWindow::kernel_version()  {

QStringList kernel;
QString kernel_;
QString befehl;
	befehl = "uname -a 1> " +  userpath + "/.config/qt-fsarchiver/kernel.txt";
        if(system (befehl.toLatin1().data()))
            befehl = "";
        QString filename = userpath + "/.config/qt-fsarchiver/kernel.txt";
	QFile file(filename);
        QTextStream ds(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text); 
        while (kernel_ == ""){
            kernel_ = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
       //  kernel_ = ds.readLine();
         file.close();
         kernel = kernel_.split(" ");
         if (kernel_.indexOf("Debian") > -1)         
		return kernel[0] + " " + kernel[2] ;
         else
		return kernel[0] + " " + kernel[2] +  " " + kernel[11];
}

QString MWindow::identify_save_part(QString save_partition)
{
int found = 0;
int i = 0;
    while (found != -1){
       found = save_partition.indexOf("/");
       if(found > -1)
         save_partition = save_partition.right(save_partition.size() - found - 1);
       }
       while (part[i][0] != ""){
           found = part[i][0].indexOf(save_partition);
           if(found > -1)
                return part[i][1];
           i++;
           }
return "";
}

//Mountpoint ermitteln
QString MWindow::mtab_einlesen(int zahl)
{
         if (part[zahl][7] == "/")  // sys Partition gefunden
             {
             return "system";
             }
         if (part[zahl][7] == "/home") // home Partition gefunden
             {
             return "home";
             }
return "";
}  

void MWindow::esc_end(int flag)
{
QString befehl = "";
QString attribute;
QString pid_qt_fsarchiver;
QString pid_qt_fsarchiver_terminal;
int ret = 0;
      pid_qt_fsarchiver = pid_ermitteln_("qt-fsarchiver"); 
      pid_qt_fsarchiver_terminal = pid_ermitteln_("qt-fsarchiver-terminal"); 
      if (flag == 0)
          ret = questionMessage(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
      if (ret == 1)
       {
       if (pid_qt_fsarchiver_terminal != "")
        {
        attribute = "kill -15 " + pid_qt_fsarchiver_terminal;  //qt-fsarchiver-terminal abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  
        if(system (befehl.toLatin1().data()))
            befehl = "";    
        attribute = "rm " + SicherungsFolderFileName;
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
        if(system (befehl.toLatin1().data()))
            befehl = "";
        }
     	int pos = SicherungsFolderFileName.indexOf("fsa");
       	SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
       	SicherungsFolderFileName.insert(pos, QString("txt"));
        attribute = "rm " + SicherungsFolderFileName;
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
        if(system (befehl.toLatin1().data()))
            befehl = "";
// pbr-Datei löschen
        pos = SicherungsFolderFileName.indexOf("txt");
        SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
        SicherungsFolderFileName.insert(pos, QString("pbr"));
         attribute = "rm " + SicherungsFolderFileName;
         befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
        if(system (befehl.toLatin1().data()))
            befehl = "";
        attribute = "kill -15 " + pid_qt_fsarchiver;  //qt-fsarchiver-terminal abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  
        if(system (befehl.toLatin1().data()))
            befehl = "";
        close();
   }
}

void MWindow::del_mediafolder()
// Programm beenden
// eingehängte Partitionen aushängen und leere Verzeichnisse in /media löschen.
{
 QString foldername[100];
      QString attribute; 
      QString befehl;
      QString media;
      QString filename = userpath + "/.config/qt-fsarchiver/media.txt";
      QFile file(filename);
      int k = 0;
      int i = 0;
      int size = 0;
      QStringList dev_sdx;
      QString dev_sdx_;
      QString devsdx[100][6];
     // qApp->quit();
      QTextStream ds(&file);
      if(file.open(QIODevice::ReadWrite | QIODevice::Text))
         {
         befehl = "cd /media; ls 1> " +  userpath + "/.config/qt-fsarchiver/media.txt; cd /";
         if(system (befehl.toLatin1().data()))
            befehl = "";
          while (media == ""){
            media = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
        while (!ds.atEnd())
      	    {
            media = ds.readLine();
      	    sdx[i] = media;
            i++;
           }
         }
         file.close();
         for (k=0; k < i; k++)
           {
           dev_sdx_= sdx[k];
           dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
           size = dev_sdx.size();
           media = dev_sdx[size - 1];
           foldername[k] = "/media/" + media; 
           attribute = foldername[k]  + " 2>/dev/null";
            befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
            if(system (befehl.toLatin1().data()))
               befehl = "";
            befehl = "/usr/sbin/qt-fsarchiver.sh  8 " + foldername[k]; //rmdir
            if(system (befehl.toLatin1().data()))
               befehl = "";
           }
           date_delete();
           attribute = "-f " + userpath + "/.qt-fs-client 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
           if(system (befehl.toLatin1().data()))
              befehl = "";
           attribute = "-a -t nfs 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
           if(system (befehl.toLatin1().data()))
              befehl = "";
           attribute = "fusermount -u " + userpath + "/.qt-fs-client 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  //umount
           if(system (befehl.toLatin1().data()))
              befehl = "";
           befehl = "rm " + userpath + "/.config/qt-fsarchiver/den.nfo.cpt 2>/dev/null";
           if(system (befehl.toLatin1().data()))
                befehl = "";
           befehl = "rm " + userpath + "/.local/share/.en.nfo 2>/dev/null";
           if(system (befehl.toLatin1().data()))
             befehl = "";
           qApp->quit();
}

void MWindow::sdx_einlesen()
{
QString text;
QString befehl;
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString dummy;
QString dummy1;
QString filename;
QString filename1;
QString filename2;
QString attribute;
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;
int size = 0;
int n = 0;
int o = 0;
int x = 0;
int y = 0;
int z = 0;
        filename = userpath + "/.config/qt-fsarchiver/disk2.txt";
        QFile file(filename);
        QThread::msleep(200 * sleepfaktor);  
        QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
          {
        attribute = "lsblk --output KNAME,FSTYPE,SIZE,UUID,MOUNTPOINT,LABEL 1> " +  userpath + "/.config/qt-fsarchiver/disk2.txt";
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
        if(system (befehl.toLatin1().data()))
            befehl = "";
        while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
            text = ds.readLine();
            while (!ds.atEnd())
      	    {
            text = ds.readLine();
      	    sdx[i] = text;
            i++;
           }
           }
           file.close();
           j = 0;
           n = j;  //Anzahl der Partitionen

           for (k=0; k < i; k++)
           {
           dummy = sdx[k];
           dev_sdx_= dummy;
           dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
           size = dev_sdx.size();
           if(size >= 5 && dummy.indexOf("squashfs") == -1)
              {
              part[j][0] = dev_sdx[0]; //Partitionsname
              part[j][1] = dev_sdx[1]; //Partitionsart (ext4)
              part[j][2] = dev_sdx[2]; //SIZE
              dummy = part[j][2].right(1);
              part[j][2] = part[j][2].left(part[j][2].size()-1);
              part[j][2] = part[j][2] + " " + dummy + "B";
              part[j][3] = dev_sdx[3]; //UUID
              dummy=dev_sdx[4]; 
              if(dummy.indexOf("/") != -1) //Mountpoint vorhanden
                 {
                  part[j][7] = dev_sdx[4]; //MOUNTPOINT
                  part[j][6] = dev_sdx[5]; //Bezeichnung
                  for(y=6; y<size;y++)     // Wenn Bezeichnung Leersstellen enthält, gemounted
                     {
                     part[j][6] = part[j][6] + " " + dev_sdx[y];
                     }
                  
                  }
               if(dummy.indexOf("/") == -1)  //Mountpoint nicht vorhanden
                  {
                  part[j][6] = dev_sdx[4]; //Bezeichnung
                  for(z=5; z<size;z++)     // Wenn Bezeichnung Leersstellen enthält, nicht gemounted
                     {
                     part[j][6] = part[j][6] + " " + dev_sdx[z];
                     }
                   }
 
              file.close();
              j++;
             }
             x=j+1;
             }
             //Anzahl der Swap ermitteln
             for(j=0; j<k; j++)
               {
               text = part[j][1];
               if (text.indexOf("swap") > -1)
               l++;
               }
             for(m=0; m<l; m++)
             {
             //Suchen an welcher Stelle Swap vorhanden ist
             for(j=0; j<i; j++)
               {
               text = part[j][1];
               if (text.indexOf("swap") > -1)
                  break;
               }
              //Swap aus Array entfernen
              for(j=j; j<i; j++)
                {
                  for(k=0; k< 8; k++)
                  part[j][k] = part[j+1][k];
                }
              }
              int part_zahl = x-l;
              // Prüfen ob Partition doppelt vorhanden ist
               for(j=0; j < part_zahl; j++)
               {
                  for(o=0; o < part_zahl; o++)
                  {
                  if(part[j][0] == part[j+o+1][0] and part[j][0] != "")
                      {
                      // Array kürzen
                      for (n = o;  n < part_zahl -1; n++)
                      {
                       part[j+n+1][0] = part[j+n+2][0];
                           for(k=0; k< 8; k++)
                             part[j+n+1][k] = part[j+n+2][k];
                      }
                      part_zahl--;
                    }
                 }
               }

                //part[k][0]                    Partitionsname
                //part[k][1]                    Partitionsart (ext4)
                //part[k][2]                    Größe der Partition mit Teilung durch 1,024
                //part[k][3]                    UUID
                //part[k][4]                    Belegung der Partition in GB
                //part[k][5]                    Belegung der Partition in %
                //part[k][6]                    Bezeichnung
                //part[k][7]                    Mountpoint
//QMessageBox::about(this,tr("Hinweis"),tr("sdx einlesen\n") + part[k][0] + part[k][7] + part[i][7] + QString::number(i));
}

QString MWindow::sdx3_einlesen(QString part_, int flag)
{
QString text;
QString text1;
QString befehl;
QString dummy;
QStringList dev_sdx;
float part_size;
         QString filename = userpath + "/.config/qt-fsarchiver/disk3.txt";
         QFile file(filename);
         QTextStream ds(&file);
         dummy = "/dev/" + part_;
         if (!is_mounted(dummy.toLatin1().data())) // ist nicht gemounted, somit ist das Ergenis von df nicht korrekt
            {
            befehl = "/usr/sbin/qt-fsarchiver.sh  2 /dev/" + part_ + " /media/" + part_;
            if(system (befehl.toLatin1().data()))
                befehl = "";
            QThread::msleep(5 * sleepfaktor);
            }
         if(file.open(QIODevice::ReadWrite | QIODevice::Text))
          {
         befehl = "df /dev/" + part_ + " 1>" + filename;
         if(system (befehl.toLatin1().data()))
            befehl = "";
         text = "";
                   while (text == ""){
                    text = ds.readLine();
                    QThread::msleep(5 * sleepfaktor);
                 }
            text = ds.readLine();
            dev_sdx = text.split(QRegExp("\\s+"));
           if (flag == 0)
              {
              part_size = dev_sdx[2].toFloat()/1000;
              text1 = format(part_size); //Belegung absolut Größe geteilt durch mehrfaches 1,024 
              }
           if (flag == 1)
              text1 = dev_sdx[4]; //Belegung in %
           }
           file.close();
           return text1;
}

QString MWindow::datei_auswerten(QString buchstabe)
{
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString text;
QString dummy;
QString filename = userpath + "/.config/qt-fsarchiver/zahlen.txt";
QFile file(filename);
QTextStream ds(&file);
         if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
           {
            text = ds.readLine();
            dummy = text.right(1);
            if (dummy == buchstabe)
      	       dev_sdx_ = text;
       	    else
      	    {    
            while (!ds.atEnd())
      	    {
      	    text = ds.readLine();
            dummy = text.right(1);
            if (dummy == buchstabe)
               dev_sdx_ = text;
            }
          } 
       } 
          file.close();
          dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
          return dev_sdx[0];
}

QString MWindow::datei_auswerten_1(QString dateiname)
{
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString text;
QString filename = dateiname;
QFile file(filename);
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream ds(&file);
            text = ds.readLine();
            dev_sdx_ = text;
          }  
          file.close();
          dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
          return dev_sdx[0];
}

QString MWindow::pid_ermitteln_(QString prozess)
{
QString befehl = "";
QString pid_nummer = "";
QStringList pid;
      QString filename = userpath + "/.config/qt-fsarchiver/pid.txt";
      if (userpath == "/root")
         filename = userpath + "/.config/pid.txt"; 
      QFile file(filename);
      QTextStream ds(&file);
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

void MWindow::date_delete()
{
QString befehl;
QString attribute;
     attribute = "chown -R " + user + " " + userpath + "/.config/qt-fsarchiver";
     befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
     if(system (befehl.toLatin1().data()))
         befehl = "";
     QFile::remove(userpath + "/.config/qt-fsarchiver/version.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/disk2.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/disk3.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/running.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/zahlen.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/anzahl_file.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/anzahlfile.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/attribute.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/media.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/meldung.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/prozent.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/pid.txt");
     QFile::remove(userpath + "/.config/qt-fsarchiver/kernel.txt");

}

void MWindow::daten_write(QString password, int i)
{
QString befehl; 
QString filename;

   if(i == 1)
   {
      filename = userpath + "/.local/share/.en.nfo";
      befehl = "rm " + filename + " 2>/dev/null";
      if (system (befehl.toLatin1().data()))
         befehl = "";
      befehl = "md5sum /usr/bin/ccrypt 2>&1 >> " + filename; 
      if (system (befehl.toLatin1().data()))
         befehl = "";
    }
    if ( i == 0)
    {
    filename = userpath + "/.config/qt-fsarchiver/den.nfo"; 
    befehl = "rm " + filename + " 2>/dev/null";
    if (system (befehl.toLatin1().data()))
         befehl = "";
    // }   
QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
       // stream << password << endl;
       stream << password;
    }}
}

QString MWindow::md5sum(QString file_name)
{
QFile file(file_name);
if (file.open(QIODevice::ReadOnly))
{
    QByteArray fileData = file.readAll();
    QByteArray hashData = QCryptographicHash::hash(fileData,QCryptographicHash::Md5); // or QCryptographicHash::Sha1
   // qDebug() << hashData.toHex();  // 0e0c2180dfd784dd84423b00af86e2fc
    return hashData.toHex();
}
  return "";
}

int MWindow::is_gpt_main(QString partition_efi)
{
      QString text;
      QString attribute;
      QString befehl;
      attribute = "gdisk -l " + partition_efi +  " 1>" +  userpath + "/.config/qt-fsarchiver/efi.txt";
      befehl = "/usr/sbin/qt-fsarchiver.sh 13 " + attribute;
      if(system (befehl.toLatin1().data()))
              befehl = "";
      QThread::msleep(10 * sleepfaktor);
      QString filename = userpath + "/.config/qt-fsarchiver/efi.txt";
      QFile file(filename);
      if( file.open(QIODevice::ReadOnly|QIODevice::Text)) { 
	QTextStream ds(&file);
	while (!ds.atEnd()){
              	text = ds.readLine();
		if (text.indexOf("GPT: present") > -1) 
                  return 1;
           }
        }
        if(file.size() == 0)
            {
            QMessageBox::warning(this, tr("Note", "Hinweis"),
      tr("Reading the partition type was faulty. The backup is not possible\n","Die Partitionsart auslesen war fehlerhaft. Die Sicherung ist nicht möglich.\n"));
            return 2;
            }
 	file.close();
  return 0;
}

void MWindow::kill_end()
{ 
QString pid_terminal;
QString befehl;
          pid_terminal = pid_ermitteln_("bash"); 
           // befehl = "kill -15 " + pid_terminal;  //bash abbrechen, Zeit zum ordentlichen Beenden
          befehl = "kill -9 " + pid_terminal;  //bash abbrechen, sofortiges Beenden
          if(system (befehl.toLatin1().data()))
            befehl = "";
          pid_terminal = pid_ermitteln_("qt-fsarchiver-terminal"); 
          // befehl = "kill -15 " + pid_terminal;  //qt-fsarchiver-terminal abbrechen, Zeit zum ordentlichen Beenden
          befehl = "kill -9 " + pid_terminal;  //bash abbrechen, sofortiges Beenden
          if(system (befehl.toLatin1().data()))
            befehl = "";  
          pid_terminal = pid_ermitteln_("qt-fsarchiver"); 
          // befehl = "kill -15 " + pid_terminal;  //qt-fsarchiver abbrechen, Zeit zum ordentlichen Beenden
          befehl = "kill -9 " + pid_terminal;  //bash abbrechen, sofortiges Beenden
          if(system (befehl.toLatin1().data()))
             befehl = "";
} 

QString MWindow::label_read(QString partname)
{
QString befehl;
int i = 0;
QString dummy;
QString dummy1;
       dummy = part[i][0];
       while (dummy != ""){
            dummy = part[i][0];
            i++;
            if (dummy == partname) 
               {
               dummy1= part[i-1][6];
               return dummy1;
               }
            } 
return "";            
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

/*
Auswertung in zahlen.txt
"a" err_regfile
"b" err_dir
"c" err_symlinks part_testen??
"d" part_testen ?? meldung??
"e" err_hardlinks
"f" cnt_regfile bei dir meldung
"g" cnt_dir
"h" cnt_symlinks
"i" cnt_hardlinks
"j" cnt_special
"k" err_special
"l" nicht belegt
"m" nicht belegt
"n" nicht belegt
"o" part oder dir
"p" Inhalt 10 okay 11 schlecht 12 archinfo gut 13 archinfo schlecht
"q" nicht belegt
"r" Name der wiederherzustellende Partition
"s" nicht belegt
"t" nicht belegt

Inhalt Anzahlfile.txt: Summe Anzahl gesicherter Dateien Verzeichnisse Links und Specials
*/

