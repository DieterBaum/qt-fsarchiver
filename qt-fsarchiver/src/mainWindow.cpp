/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2018 Dieter Baum.  All rights reserved.
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
#include <mntent.h>
#include <QtGui>
#include <QInputDialog>
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


using namespace std;

QString Datum_akt("");
QString partition_;
QString UUID;
string partition_str;
QString folder;
QString _Datum;
QString DateiName("") ;
extern int dialog_auswertung;
extern QString parameter[15];
QString part[100][10];
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

MWindow::MWindow()
{
   questionLabel = new QLabel;
   QStringList dummy;
   QStringList partition_kurz;
   QString partition1_;
   QStringList items; 
   int pos = 0, pos1 = 0;
   int i = 0;
   int j = 0;
   int k = 0;
   QString befehl;
   QString homepath = QDir::homePath();
   QString rootpath = QDir::rootPath();
   QString attribute;
   setupUi(this);
   rdBt_saveFsArchiv->setChecked(Qt::Checked);
   dirModel = new QFileSystemModel;
   selModel = new QItemSelectionModel(dirModel);
   treeView->setModel(dirModel);
   treeView->setSelectionModel(selModel);
   treeView->setEnabled(true);
   QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
   dirModel->setRootPath(QDir::rootPath());
   treeView->setRootIndex(cwdIndex);
   groupBox->setFlat (true);
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
   connect( pushButton_folder, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
   connect( rdBt_saveFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( rdBt_restoreFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
   connect( chk_hidden, SIGNAL( clicked() ), this, SLOT(chkhidden()));
   connect( chk_split, SIGNAL( clicked() ), this, SLOT(chkGB()));
   //Benutzername ermitteln
   user = homepath.right(homepath.size() -6);
   userpath = "/home/" + user;
   // Zeitgeber für Berechnung remainingTime
   timer = new QTimer(this);
   bool ok;
   if (is_running() == 2) {
      QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Qt-fsarchiver can only be started once. The program must be terminated..\n", "Qt-fsarchiver kann nur einmal gestartet werden. Das Programm muss beendet werden.\n"));
      esc_end(1);
      return;

   }
   if (password == "")
     {
     QString text = QInputDialog::getText(this, tr("Enter sudo-password","Sudo-Passwort eingeben"),
       (tr("sudo-Password:","sudo Passwort")), QLineEdit::Password,"", &ok);
     if (ok && !text.isEmpty())
       password= text;
     }
QFile file2("/usr/sbin/qt-fsarchiver-terminal");
   if (!file2.exists())
      {
      QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("The program qt-fsarchiver-terminal is not installed. You have to install this program additionally.\n", "Das Programm qt-fsarchiver-terminal ist nicht installiert. Sie müssen dieses  Programm zusätzlich installieren.\n"));
      esc_end(1);
      return;
      }
   if (password == "")
   {
   QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("You must enter a password. You must exit the program and restart.\n", "Sie müssen ein Passwort eingeben. Sie müssen das Programm beenden und neu starten.\n"));
   return;
   }
   //Vorsichtshalber alle txt Dateien löschen
   befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 5 " + userpath + "/.config/qt-fsarchiver *.txt 2>/dev/null";
   system (befehl.toLatin1().data());
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
   QDir dir1(userpath + "/.config/qt-fsarchiver");
   if (!dir1.exists()){
       attribute = userpath + "/.config/qt-fsarchiver 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 3 " + attribute;
       system (befehl.toLatin1().data());
       }
   //vorsichtshalber Rechte immer neu setzen
       attribute = "chown -R " + user + " " + userpath + "/.config/qt-fsarchiver";
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;
       system (befehl.toLatin1().data());
   QDir dir(userpath + "/.qt-fs-client");
   if (!dir.exists()){
       attribute = userpath + "/.qt-fs-client 2>/dev/null" ;
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 3 " + attribute;
       system (befehl.toLatin1().data());
       }
   if(dialog_auswertung == 0)
       {
       attribute = "chown -R " + user + " " + userpath + "/.qt-fs-client";
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;
       system (befehl.toLatin1().data());
       }
   if(dialog_auswertung == 0)
       {
       attribute = "chown -R " + user + " " + userpath + "/.qt-fs-client";
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;
       system (befehl.toLatin1().data());
       }
   // wegen Suse
   QDir dir3("/media");
   QString media = "/media";
   if (!dir3.exists()){
       attribute = media + " 2>/dev/null" ;
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 3 " + attribute;
       system (befehl.toLatin1().data());
       }
   // beim Abbruch einer Sicherung bleiben eventuell Daten in /tmp/fsa erhalten.
   // Bei ersten Start werden eventuell vorhandene Dateien gelöscht.
   // Beim Öffnen einer weiteren Instanz von qt-fsarchiver, darf /tmp/fsa keinenfalls gelöscht werden.
   // Das System sürzt ab!!
   if (is_running() == 0) {
       attribute = "-r -f /tmp/fsa 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 15 " + attribute; 
       system (befehl.toLatin1().data());
   }
   // Ini-Datei auslesen
   QFile file(userpath + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
   QSettings setting("qt-fsarchiver", "qt-fsarchiver");
   if (file.exists()) {
        setting.beginGroup("Basiseinstellungen");
        sleepfaktor= setting.value("sleep").toInt();
        if (sleepfaktor == 0)
           sleepfaktor = 5;
        int auswertung = setting.value("Kompression").toInt();
        cmb_zip -> setCurrentIndex(auswertung); 
        auswertung = setting.value("Kerne").toInt();
        cmb_kerne -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("overwrite").toInt();
        if (auswertung ==1)
           chk_overwrite->setChecked(Qt::Checked); 
        auswertung = setting.value("pbr").toInt();
        if (auswertung ==1)
           chk_pbr->setChecked(Qt::Checked); 
        auswertung = setting.value("tip").toInt();
        if (auswertung ==1)
           chk_Beschreibung->setChecked(Qt::Checked);  
        auswertung = setting.value("key").toInt();
        if (auswertung ==1)
           chk_key->setChecked(Qt::Checked); 
	auswertung = setting.value("hidden").toInt();
        if (auswertung ==1)
           chk_hidden->setChecked(Qt::Checked);
        auswertung = setting.value("Passwort").toInt(); 
        if (auswertung ==1)
           	lineKey ->setEchoMode(QLineEdit::Normal);
        else
		     lineKey ->setEchoMode(QLineEdit::Password);
        auswertung = setting.value("sleep").toInt();
        zstd_level = setting.value("zstd").toInt();
        cmb_zstd -> setCurrentIndex(zstd_level-1);
        auswertung = setting.value("Kompression").toInt();
        if (auswertung ==10)
            cmb_zstd->setEnabled(true);
        else
            cmb_zstd->setEnabled(false); 
        setting.endGroup();
        } 
   else {
        lineKey ->setEchoMode(QLineEdit::Password);
        cmb_kerne -> setCurrentIndex(0);
        chk_Beschreibung->setChecked(Qt::Checked);
        chk_overwrite->setChecked(Qt::Checked); 
        cmb_zip -> setCurrentIndex(2);
        setting.beginGroup("Basiseinstellungen");
        setting.setValue("showPrg",1); 
        setting.setValue("ssh",1); 
        setting.setValue("sshfs",1); 
        setting.setValue("dummy",2);
        setting.endGroup();
        cmb_zstd -> setCurrentIndex(7);
        cmb_zstd->setEnabled(false);
        }
   label_4->setEnabled(false);
   chk_overwrite->setEnabled(true);
   cmb_zip->setEnabled(false);
   cmb_GB->setEnabled(false);
   chk_Beschreibung->setEnabled(true);
   chk_Beschreibung->setChecked(Qt::Checked);
   label->setEnabled(false);
   starteinstellung();
   if(show_part == 0)
       {
       sdx_einlesen();
       sdx1_einlesen();
       format_();
           // Partitionsname, Partitiontyp und Größe einlesen und formatieren für listWidget Ausgabe
           j = 2 ;
           i=0;
           while (part[i][0] != "")
	   {
                j = widget[i+1].length();
                partition_ = part[i][0]; // z.B. sda1
		UUID = part[i][3];       // UUID
                partition_typ = part[i][1]; // beispielweise ext4
                // part[i][2] Partitionsgröße
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
                   if (part_art !="system" || part_art != "home")
                     {
			if (partition_typ == "ext" || partition_typ == "btrfs"|| partition_typ == "vfat" || partition_typ ==  "ntfs" || partition_typ ==  "jfs" || partition_typ ==  "xfs")
                   		{
                   	 	befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 3 -m 0777 /media/" + part[i][0];
                                system (befehl.toLatin1().data());
                         	befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 2 /dev/" + part[i][0] + " /media/" + part[i][0]; 
			 	system (befehl.toLatin1().data());
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
     rdBt_saveFsArchiv->setChecked(Qt::Checked);
     rdButton_auslesen();
}

void MWindow::restore_button(){
     rdBt_restoreFsArchiv->setChecked(Qt::Checked);
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
     QString befehl;
     Qt::CheckState state;
     Qt::CheckState state1;
     Qt::CheckState state3;
     int err = 0;
     QString keyText = "";
     QString compress = "";
     int found = 0; 
     int zip;
     int zip_zstd;
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
       	 beschreibungstext("/dev/" + partition_, DateiName + "-" + _Datum + ".fsa", zip, row);
         if (!is_mounted(partition_.toLatin1().data()))
         {
	   part_art = mtab_einlesen("/dev/" + partition_);
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
                             befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 /dev/" + partition_; 
                             err = system (befehl.toLatin1().data());
                            } 
                           if (err != 0 && liveFlag == 0)
                                {
				QMessageBox::about(this,tr("Note", "Hinweis"),
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

                                 parameter[indizierung] = (folder + "/" + DateiName + "-" + _Datum + ".fsa");
				// Vorbereitung für psb
                                befehl_pbr = ""; 
				state = chk_pbr->checkState();
				if (state == Qt::Checked)
                                  {
                                  befehl_pbr = "/usr/sbin/qt-fsarchiver.sh " + password + " 12 " + "if=/dev/" + partition_ + " of=" + folder + "/" + DateiName + "-" + _Datum + ".pbr bs=512 count=1";
				  system (befehl_pbr.toLatin1().data());
                                  }
                                  SicherungsFolderFileName = parameter[indizierung];
                                  parameter[indizierung + 1] = ("/dev/" + partition_);
                                  QFile f(parameter[indizierung]);
                                  if  (parameter[4] != "-o" && (f.exists())){
				       QMessageBox::about(this, tr("Note", "Hinweis"), 
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
                		  QMessageBox::about(this,tr("Note", "Hinweis"),
         			  tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
				  pushButton_save->setEnabled(true);
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
                                flag_View = 1;
                              //  werte_reset();
  				//timer->singleShot( 20, this , SLOT(ViewProzent( ))) ;
                                ViewProzent();
                                stopFlag = 0;
                                this->setCursor(Qt::WaitCursor);
  				statusBar()->showMessage(tr("The backup is performed", "Die Sicherung wird durchgeführt"), 15000);
                                befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 1 " + userpath;
                                system (befehl.toLatin1().data());
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
QString dummy1;
text = datei_auswerten("p");
endeThread = text.toInt();
if (endeThread == 10 && flag_View == 1 or endeThread == 11 && flag_View == 1)
   thread1Ready();
if (endeThread == 10 && flag_View == 2 or endeThread == 11 && flag_View == 2)
   thread2Ready();
if (endeThread != 10 && endeThread != 11)
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
Qt::CheckState state;
Qt::CheckState state1;
QFile file(folder);
QString DateiName("") ;
int err;
QString keyText = "";
QString dev_part;
QString text;
QString befehl;
int cmp = 0;
QString attribute;


  indicator_reset();
  if (rdBt_restoreFsArchiv->isChecked())
      string dateiname;
      int pos;
      int pos1;
      keyText = lineKey->text();
      state1 = chk_key->checkState();
      {
          if (state1 == Qt::Checked && keyText.isEmpty())  
              {
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("No decryption key was specified.", "Es wurde kein Schlüssel für die Entschlüsselung angegeben.\n"));
		return 1 ;
               }
           if (folder == "")
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
                        pos = testDateiName(".fsa"); 
                        pos1= testDateiName("part.fsa");
         		if (pos > 0 && pos1 >0)
         			   {
           			   QMessageBox::about(this, tr("Note", "Hinweis"),
         			   tr("You have selected an incorrect recovery file. \nThe file extension must be .fsa.", "Sie haben eine falsche Wiederherstellungsdatei ausgesucht. \nDie Dateiendung muss .fsa sein"));
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
               state = chk_Beschreibung->checkState();
            // Archinfo einholen um Originalpartition einzulesen und um Verschlüsselung zu überprüfen
            // Annahme zunächst kein Schlüssel
               QString optionkey;
               parameter[0] = "fsarchiver";
       	       parameter[1] = "archinfo";
               if (state1 != Qt::Checked) {
               		parameter[2] = folder;
                        attribute = parameter[0] + " " + parameter[1] + " " + parameter[2];
  			attribute = "3 " + attribute;
                        save_attribut(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 1 " + userpath;
                        system (befehl.toLatin1().data());
                        QThread::msleep(10 * sleepfaktor);
               		optionkey = datei_auswerten("p");
               		dev_part = datei_auswerten("r");
                        QString sys = datei_auswerten("o");
                        if(optionkey == "13"){
                  	  chk_key->setChecked(Qt::Checked);
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
			parameter[4] = folder;
                        attribute = parameter[0] + " " + parameter[1] + " " + parameter[2] + " " + parameter[3] + " " + parameter[4];
                        attribute = "5 " + attribute;
                        save_attribut(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 1 " + userpath;
                        system (befehl.toLatin1().data());
                        QThread::msleep(10 * sleepfaktor);
                        dev_part = datei_auswerten("r");
                        optionkey = datei_auswerten("p");
                        if(optionkey == "13") {
                           QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                           befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 5 " + userpath + "/.config/qt-fsarchiver *.txt 2>/dev/null"; 
                           system (befehl.toLatin1().data());
                           return 0;
                        }
			
                }
            // Hier wird verglichen dev_ = die Partition, die zu sichern ist. dev_part = Originalpartition
            if (dev_part != "/dev/" + partition_){
               cmp = questionMessage(tr("The partition to be recovered  ", "Die wiederherzustellende Partition ") + "/dev/" + partition_ + 
               tr(" does not coincide with the saved  ", " stimmt nicht mit der gesicherten ") + dev_part + tr("Do you still want to perform the recovery?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
               if (cmp == 2)  //nicht wiederherstellen
                  return 0;
            }
           if (rdBt_restoreFsArchiv->isChecked())
            	{
                extern QString folder_file_;
                folder_file();	
		QString filename = folder_file_;
                pos = filename.indexOf("fsa");
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
        			befehl_pbr = "if="+ filename + " of=/dev/" + partition_; 
		       }
            	  }
           // std::string stdString(dummy.toStdString());
          // const char * xxx = stdString.c_str();  //QString zu const char wandeln
          // char * dev_ = strdup(xxx);             //const char zu char[50] wandeln
	  if (!is_mounted(partition_.toLatin1().data())) 
              {
              part_art = mtab_einlesen("/dev/" + partition_);
              //Überprüfung ob System oder Home Partition 
                   if (part_art == "system")
                	{
                        QMessageBox::about(this,tr("Note", "Hinweis"),
         			tr("The system partition to be recovered is mounted and cannot be written back. Please use a Live-CD.", "Die wiederherzustellende Systempartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return 0;
				      } 
                        
                   if (part_art == "home")
                	{
                        QMessageBox::about(this,tr("Note", "Hinweis"),
         			tr("The home partition to be restored is mounted and cannot be written back. Please use a live CD.","Die wiederherzustellende Homepartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return 0; 
                        
                	}
                   if (part_art != "system"|| part_art != "home")
                	{
                          attribute = "/dev/" + partition_  + " 2>/dev/null";
                          befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 " + attribute;  //umount
                          err = system (befehl.toLatin1().data()); 
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
                 befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 /dev/" + partition_; // unmounten
 		 system (befehl.toLatin1().data());
                 QThread::msleep(500 * sleepfaktor);
                 befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 7 -f /dev/" + partition_; // Partition anlegen
 		 system (befehl.toLatin1().data());
                 QThread::msleep(500 * sleepfaktor);
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
               befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 1 " + userpath;
               system (befehl.toLatin1().data());
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
   extern QString folder_file_;
   folder_file_ = folder + "/" + DateiName + "-" + _Datum + ".txt";
}

void MWindow::info() {
   QMessageBox::information(
      0, tr("qt-fsarchiver"),
      tr("Backup and restore partitions, directory and MBR.\nversion 0.8.5-2, November 12, 2018",
         "Sichern und Wiederherstellen von Partitionen, Verzeichnissen und MBR Version 0.8.5-2, 12.November 2018"));
      }

int MWindow::is_running(){
      QString running;
      QString befehl;
      QDir dir1(userpath + "/.config/qt-fsarchiver");
      if (dir1.exists()){  //vermeidet Fehlermeldung beim ersten Start
          befehl = "ps --user " + user + " | grep -w qt-fsarchiver 1> " +  userpath + "/.config/qt-fsarchiver/running.txt";
          system (befehl.toLatin1().data());
      }
      QString filename = userpath + "/.config/qt-fsarchiver/running.txt";
      QFile file(filename);
      int zaehler = 0;
      int i = 0;
      if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           for (i=1; i < 5; i++){
           	running = ds.readLine();
		if (running.indexOf("qt-fsarchiver") > 0) 
                   zaehler = zaehler + 1;
           } }
           file.close();
           befehl = "rm " + filename + " 2>/dev/null";
           system (befehl.toLatin1().data());
           if (zaehler > 1) {
               // qt-fsarchiver läuft bereits in einer Instanz 
               return 2;
           }
           return 0; 
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
 	int is_mounted = 0;
 
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
}


void MWindow::mbr_save () {
     dialog_auswertung = 4;
     DialogMBR *dialog = new DialogMBR;
     dialog->show();
}
void MWindow::mbr_restore () {
      dialog_auswertung = 5;
      DialogMBR *dialog = new DialogMBR;
      dialog->show();
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
     QString teilstring, space1, space2;
     int aa, bb, cc, dd;
     int i = 0;
         while (part[i][0] != "") {
           teilstring = part[i][0];
           aa = teilstring.size();
           teilstring = part[i][1];
           bb = teilstring.size();
           teilstring = part[i][2];
           cc = teilstring.size();
           dd = 18 - aa; 
           space1.fill (' ',dd);
           teilstring = part[i][0] + space1;
           dd = 20 -bb -cc;
           space2.fill (' ',dd);
           teilstring = part[i][0] + space1 + part[i][1] +space2 + part[i][2];
           if (part[i][1] != "" ){
              widget[i] = teilstring;
              add_part[i] = teilstring;
              listWidget->addItem (teilstring);
              }
          i++;
         }
    } 
}

void MWindow::closeEvent(QCloseEvent *event) {
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
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
        + cnt_special_ + tr(" specials have been backed.", " spezielle Daten wurden gesichert."));
        progressBar->setValue(100);     
	}
        if (dialog_auswertung == 1 and err == 10 and befehl_pbr != ""){ 
           //Rückmeldung von fsarchiver: Sicherung erfolgreich
           // Ausgabe progressBar durch Timer unterbinden
           stopFlag = 1; 
           QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
        + cnt_special_ + tr(" specials and the Partition Boot Record have been backed.", " spezielle Daten und der Partition Boot Sektor wurden gesichert."));
        progressBar->setValue(100);     
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
          system (befehl.toLatin1().data());
          }
       if (flag_end == 1) 
        QMessageBox::about(this, tr("Note", "Hinweis"),
         tr("The backup of the partition was aborted by the user!\n", "Die Sicherung der Partition  wurde vom Benutzer abgebrochen!\n") );
       // Prüfen ob Partitionsart unterstützt wird 
       dummy = datei_auswerten("d");  //Prüfung erforderlich
       part_testen = dummy.toInt();      
       if (part_testen == 110){ 
       QMessageBox::about(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported.\n", "Der Partitionstyp wird nicht unterstützt.\n" ));
          flag_end = 1;
          } 
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       dummy = datei_auswerten("d");
       part_testen = dummy.toInt(); 
       if (part_testen == 108){
	   QMessageBox::about(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported. Maybe the partition is encrypted?\n", "Der Partitionstyp wird nicht unterstützt. Vielleicht ist die Partition verschlüsselt?\n" ));
          }
       if (part_testen == 109){
	   QMessageBox::about(this, tr("Note", "Hinweis"),
          tr("The backup of the partition was not successful. The file is too large. Use a FAT partition?\n", "Die Sicherung der Partition war nicht erfolgreich. Die Datei ist zu groß. Nutzen Sie eine FAT-Partition?\n" ));
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
       	  QMessageBox::about(this, tr("Note", "Hinweis"), 
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
      endeThread == 0;
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
         QString befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 12 " + befehl_pbr + " bs=512 count=1"; 
         system (befehl.toLatin1().data());
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
        QMessageBox::about(this, tr("Note", "Hinweis"),
         tr("The restore of the partition was break by user!\n", "Die Wiederherstellung der Partition  wurde vom Benutzer abgebrochen!\n") );
	meldung == 0;
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
        if (i!=0) {  
          QMessageBox::about(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n")
         + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
         + cnt_special_ + tr(" specials has been restored.\n.", " spezielle Daten wurden wiederhergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
               }
       if (i==0) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), 
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
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have tried restore a partition. The selected file can only restore directories. Please restart the program.\n", "Sie haben versucht eine Partition wiederherzustellen. Die gewählte Datei kann nur Verzeichnisse wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 103) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben.\n"));
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

QString MWindow::beschreibungstext(QString partitiontext, QString text, int zip, int row)  {
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
if  (zstd == 10)
        compress = compress + " level:" + zip_zstd_;
        SicherungsDateiName = text;
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
}


QString MWindow::linux_version()  {

QString befehl;
QString Linuxversion;
int i;
	befehl = "cat /etc/*release 1> " +  userpath + "/.config/qt-fsarchiver/version.txt";
        system (befehl.toLatin1().data());
QString filename = userpath + "/.config/qt-fsarchiver/version.txt";
QFile file(filename);
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
           system (befehl.toLatin1().data());
           if (Linuxversion.indexOf("DISTRIB_DESCRIPTION=") > 0); 
               // Ubuntu, Debian       
               Linuxversion = Linuxversion.right(Linuxversion.size() -20);
           return Linuxversion;
}

QString MWindow::kernel_version()  {

QStringList kernel;
QString kernel_;
QString befehl;
	befehl = "uname -a 1> " +  userpath + "/.config/qt-fsarchiver/kernel.txt";
        system (befehl.toLatin1().data());
        QString filename = userpath + "/.config/qt-fsarchiver/kernel.txt";
	QFile file(filename);
        if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           kernel_ = ds.readLine();
           file.close();
           kernel = kernel_.split(" ");
         }
         befehl = "rm " + filename;
         system (befehl.toLatin1().data());
         if (kernel_.indexOf("Debian") > -1)         
		return kernel[0] + " " + kernel[2] ;
         else
		return kernel[0] + " " + kernel[2] +  " " + kernel[11];
}

QString MWindow::identify_save_part(QString save_partition)
{
   
   QString filename = userpath + "/.config/qt-fsarchiver/mtab.txt";
   QString text;
   QStringList items;
   QString save_part;
   QFile file(filename);
   QTextStream ds(&file);
   int line = 0;
   QString befehl;
   befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 11 /etc/mtab " + userpath + "/.config/qt-fsarchiver/mtab.txt";
   system (befehl.toLatin1().data());
   QThread::msleep(10 * sleepfaktor);
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
   QString filename = userpath + "/.config/qt-fsarchiver/mtab.txt";
   QString text;
   QStringList items;
   QString mount_dir;
   QFile file(filename);
   QTextStream ds(&file);
   int line = 0;
   QString befehl;
   befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 11 /etc/mtab " + userpath + "/.config/qt-fsarchiver/mtab.txt";
   system (befehl.toLatin1().data());
   QThread::msleep(10 * sleepfaktor);
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     text = ds.readLine();
   	while (!ds.atEnd())
      	{
	      if (text.indexOf(UUID) > -1 )  // Partitionsname gefunden, Debian 7
      	    { 
	      items = text.split(" ");  //Einhängepunkt ermitteln
    	      mount_dir = items[1];
              if (text.indexOf(" /home") > -1) 
      	            return "home ";
                 if (text.indexOf(" / ") > -1) 
      	           return "system";
      	    }
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
        attribute = "kill -15 " + pid_qt_fsarchiver_terminal;  //qt-fsarchiver-terminal abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;  
        system (befehl.toLatin1().data());
        attribute = "rm " + SicherungsFolderFileName;
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute; 
        system (befehl.toLatin1().data());
     	int pos = SicherungsFolderFileName.indexOf("fsa");
       	SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
       	SicherungsFolderFileName.insert(pos, QString("txt"));
        attribute = "rm " + SicherungsFolderFileName;
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute; 
        system (befehl.toLatin1().data());
// pbr-Datei löschen
        pos = SicherungsFolderFileName.indexOf("txt");
        SicherungsFolderFileName = SicherungsFolderFileName.left(pos);
        SicherungsFolderFileName.insert(pos, QString("pbr"));
         attribute = "rm " + SicherungsFolderFileName;
         befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute; 
        system (befehl.toLatin1().data());
        attribute = "kill -15 " + pid_qt_fsarchiver;  //qt-fsarchiver-terminal abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;  
        system (befehl.toLatin1().data());
        close();
   }
}

void MWindow::del_mediafolder()
// Programm beenden
// eingehängte Partitionen aushängen und leere Verzeichnisse in /media löschen.
{
      QString foldername[100];
      QString attribute;
      QString befehl = "cd /media; ls 1> " +  userpath + "/.config/qt-fsarchiver/media.txt; cd /";
      system (befehl.toLatin1().data());
      QString media;
      QString filename = userpath + "/.config/qt-fsarchiver/media.txt";
      QFile file(filename);
      int zaehler = 0;
      qApp->quit();
      if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           while (!ds.atEnd()){
           	media = ds.readLine();
                if (media.indexOf("sd") > -1 or media.indexOf("nvme") > -1){
                   foldername[zaehler] = "/media/" + media;
                     attribute = foldername[zaehler]  + " 2>/dev/null";
                     befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 " + attribute;  //umount
                     system (befehl.toLatin1().data());
                     befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 8 " + foldername[zaehler]; //rmdir
                     system (befehl.toLatin1().data());
                     zaehler = zaehler + 1;
           }}}
           file.close();
           befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 5 " + userpath + "/.config/qt-fsarchiver *.txt 2>/dev/null"; 
           system (befehl.toLatin1().data());
           attribute = "-f " + userpath + "/.qt-fs-client 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 " + attribute;  //umount
           system (befehl.toLatin1().data());
           attribute = "-a -t nfs 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 4 " + attribute;  //umount
           system (befehl.toLatin1().data());
           attribute = "fusermount -u " + userpath + "/.qt-fs-client 2>/dev/null";
           befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;  //umount
           system (befehl.toLatin1().data());
           qApp->quit();
}

void MWindow::sdx_einlesen()
{
QString text;
QString befehl;
QString filename;
QString dummy;
QString attribute;
QStringList part_sdx;
QString part_sdx_;
QString partsdx[100][6];
int i = 0;
     	attribute = "blkid -o export 1> " +  userpath + "/.config/qt-fsarchiver/disk.txt";
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;
        system (befehl.toLatin1().data());
        filename = userpath + "/.config/qt-fsarchiver/disk.txt";
        QFile file(filename);
	QTextStream ds(&file); 
        QThread::msleep(300 * sleepfaktor);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            text = ds.readLine();
   	    while (!ds.atEnd())
      	    { 
            if (text.indexOf("DEVNAME=/dev/sd") > -1 && (text.indexOf("PTTYPE") == -1) or text.indexOf("DEVNAME=/dev/nvme0") > -1 &&  (text.indexOf("PTTYPE") == -1))
               { 
      	       dummy = text; 
               part[i][0] = dummy.right(dummy.size() -13); //Partitionsname
               }
             if (text.indexOf("UUID=") > -1 && (text.indexOf("PTTYPE") == -1) && text.indexOf("UUID_SUB") == -1)
               { 
      	      dummy = text;
      	      if (part[i][0]!= "")
      	         { 
                  part[i][3] = dummy.right(dummy.size() -5); //UUID
                  }
    
              } 
              if (text.indexOf("TYPE") > -1 && (text.indexOf("PTTYPE") == -1))
               { 
                    dummy = text;
                    if (part[i][0]!= "")
      	             { 
                     part[i][1] = dummy.right(dummy.size() -5); //Partitionstyp
                     i++;
                     }
 
                 } 
              if (text.indexOf("swap") > -1)
                  i--;  //Swap Partition aus Array entfernen
              text = ds.readLine();
      	} 
   	file.close();
        } 
        sdx2_einlesen (); 
}

void MWindow::sdx2_einlesen ()
{

QString text;
QString befehl;
QString attribute;
QString dummy;
QStringList part_sdx;
QString part_sdx_;
QString partsdx[100][6];
QString filename;
int i = 0;
int j = 0;
int k = 0;
float dummy1;
     	attribute = "blkid 1> " +  userpath + "/.config/qt-fsarchiver/disk1.txt";
        befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 13 " + attribute;
        system (befehl.toLatin1().data());
        filename = userpath + "/.config/qt-fsarchiver/disk1.txt";
        QFile file(filename);
	QTextStream ds(&file); 
        QThread::msleep(300 * sleepfaktor);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            text = ds.readLine();
   	      while (!ds.atEnd())
      	    { 
          if (text.indexOf("/dev/sd") > -1 or text.indexOf("/dev/nvme0") > -1 &&  (text.indexOf("PTUUID") == -1))
      	      {
      	      sdx[i] = text;
      	      i++;
      	      }
              text = ds.readLine();
              }
      	  } 
   	  file.close();
          sdx[i] = text;

          for (k=0; k < i +1 ; k++){
           dummy = sdx[k];
           part_sdx_= dummy;
           part_sdx = part_sdx_.split(QRegExp("\\s+"));
           dummy = part_sdx[0]; 

           dummy = dummy.right(dummy.size() -5); 
           partsdx[k][0] = dummy.left(dummy.size() -1); //Partitionsname
           dummy = part_sdx[1];

           if (dummy.indexOf("LABEL") > -1) {
               dummy= dummy.right(dummy.size() -7);
               partsdx[k][1]= dummy.left(dummy.size() -1); //Bezeichnung
           }
           else
               partsdx[k][1]= "";
           } 
           //Bezeichnung nach  nach part[i-1][j] übertragen 
           for (k=0; k < i+1; k++){
              for (j=0; j < i+ 1; j++){
                if (part[k][0] == partsdx[j][0])
                {
                //part[k][0]                Partitionsname
                //part[k][1]                Partitionsart (ext4)
                //part[k][2]                Größe der Partition
                //part[k][3]                UUID
                //part[k][4]                Belegung der Partition in GB
                //part[k][5]                Belegung der Partition in %
                part[k][6] = partsdx[j][1];  //Bezeichnung
                }
              }       
          } 
}

void MWindow::sdx1_einlesen()
{
QString text;
QString befehl;
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString dummy;
float part_size;
int i = 0;
int j = 0;
int k = 0;
int pos = 0;
          QString filename = userpath + "/.config/qt-fsarchiver/disk2.txt";
          befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 11 /proc/partitions " + filename;
          system (befehl.toLatin1().data());
       	     QFile file(filename);
	     QTextStream ds(&file);
         QThread::msleep(10 * sleepfaktor);       
         if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            text = ds.readLine();
            while (!ds.atEnd())
      	    {
      	    if (text.indexOf(" sd") > -1 or text.indexOf(" nvme0") > -1)
      	      {
      	      sdx[i] = text;
      	      i++;
      	      }
           text = ds.readLine();
           }
           file.close();
           sdx[i] = text;
           }
           for (k=0; k < i + 1 ; k++){
           dummy = sdx[k];
           dev_sdx_= dummy;
           dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
           devsdx[k][0] = dev_sdx[4]; //Partitionsname
           devsdx[k][1]= dev_sdx[3]; //Partitionsgröße
           dummy = dev_sdx[3];
           part_size = dev_sdx[3].toFloat();
           }
           //Partitionsgröße nach part[i-1][j] übertragen
          for (k=0; k < i+1; k++){
              for (j=0; j < i+ 1; j++){
                  if (part[k][0] == devsdx[j][0])
                {
                //part[k][0]                    Partitionsname
                //part[k][1]                    Partitionsart (ext4)
                part_size = devsdx[j][1].toFloat();
                part_size = part_size/1000;
                part[k][7] = part_size;        //Partitionsgröße ohne Teilung durch 1,024
                dummy = format(part_size);
                part[k][2] = dummy;            //Größe der Partition mit Teilung durch 1,024
                //part[k][3]                   UUID
                //part[k][4] = devsdx[j][2];  //Belegung der Partition in GB
                //part[k][5] = devsdx[j][3];  //Belegung der Partition in %
                //part[k][6]                  Bezeichnung
                }
              }      
          }
}

QString MWindow::sdx3_einlesen(QString part, int flag)
{

QString text;
QString text1;
QString befehl;
QStringList dev_sdx;
float part_size;
         QString filename = userpath + "/.config/qt-fsarchiver/disk3.txt";
         befehl = "df /dev/" + part + " 1>" + filename;
         system (befehl.toLatin1().data());
       	     QFile file(filename);
	     QTextStream ds(&file);
         QThread::msleep(50 * sleepfaktor);       
         if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            text = ds.readLine();
            text = ds.readLine();
            dev_sdx = text.split(QRegExp("\\s+"));
           if (flag == 0)
              {
              part_size = dev_sdx[2].toFloat()/1000;
              text1 = format(part_size); //Belegung absolut Größe geteilt durch mehrfaches 1,024 
              }
           if (flag == 1)
              text1 = dev_sdx[4]; //Belegung in %
           file.close();
           return text1;
           }
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
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream ds(&file);
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
int i = 0;
int k = 0;
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

      befehl = "ps -C " + prozess + " 1> " +  userpath + "/.config/qt-fsarchiver/pid.txt";
      system (befehl.toLatin1().data());
    QString filename = userpath + "/.config/qt-fsarchiver/pid.txt";
	QFile file(filename);
    if(file.size() == 0) 
       return " ";
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
        pid_nummer = ds.readLine();
        pid_nummer = ds.readLine();
        file.close();
     }
        befehl = "rm " + filename;
        system (befehl.toLatin1().data());
      if (pid_nummer != "")
        {
          pid = pid_nummer.split(" ") ;
          pid_nummer = pid[0]; // 5-stellig
          if (pid_nummer == "")
             pid_nummer = pid[1];// 4-stellig
         }
        return pid_nummer;
}

void MWindow::date_delete()
{
QString befehl;
int i = 0;
QString date_delete_[10];
     	date_delete_[0]= "zahlen.txt";
	date_delete_[1]= "anzahlfile.txt";
	date_delete_[2]= "anzahl_file.txt";
	date_delete_[3]= "attribute.txt";
	date_delete_[4]= "meldung.txt";
	date_delete_[5]= "prozent.txt";
        date_delete_[6]= "mtab.txt";
     for(i=0; i<7; i++)
     {
     befehl = "/usr/sbin/qt-fsarchiver.sh " + password + " 5 " + userpath + "/.config/qt-fsarchiver " + date_delete_[i] + " 2>/dev/null"; 
     system (befehl.toLatin1().data());
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
