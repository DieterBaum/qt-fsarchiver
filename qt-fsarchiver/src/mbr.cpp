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

#include <QtGui> 
#include "mbr.h"
#include <string.h>

extern int dialog_auswertung;

QString folder_;
QString Ubuntuversion;
int sektor_byte;
int sektor_byte_1;
QString Sektor_byte;
QString Sektor_byte_1;
qint64 size_;
int efiflag;
QString disk_name[1000];
QStringList items_disk;
extern int sleepfaktor;

DialogMBR::DialogMBR()
{
QStringList filters;
	setupUi(this); // this sets up GUI
        connect( bt_end, SIGNAL( clicked() ), this, SLOT(close()));
        connect( bt_save, SIGNAL( clicked() ), this, SLOT(mbr()));
        connect( bt_dummy, SIGNAL( clicked() ), this, SLOT(disk_art()));
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
   	treeView->setModel(dirModel);
   	treeView->setSelectionModel(selModel);
   	QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
        dirModel->setRootPath(QDir::rootPath());
   	treeView->setRootIndex(cwdIndex);
   	connect(treeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &DialogMBR::folder_einlesen);
        connect( bt_folder, SIGNAL( clicked() ), this, SLOT(folder_expand()));
        disk_exist();
        if (dialog_auswertung == 4){
            bt_save->setText (tr("MBR/GPT save", "MBR/GPT sichern"));
            dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot);
   	    dirModel->setNameFilters(filters); 
            } 
        if (dialog_auswertung == 5){
            bt_save->setText (tr("MBR/GPT restore", "MBR/GPT zurückschreiben"));  
	    filters << "*_gpt_*" << "*_mbr_*" ;
   	    dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	    dirModel->setNameFilters(filters);  
            }
        disk_art();
}

void DialogMBR::disk_exist()
{
//vorhandene disk ermitteln
QString befehl;
QString homepath = QDir::homePath();
int i = 0;
int j = 0;
int k = 0;
int size = 0;
QString filename = homepath + "/.config/qt5-fsarchiver/disk.txt";
QFile file(filename);
QStringList disk;
QString disk_;
        i = system (befehl.toLatin1().data());
        QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "lsblk -l 1> " + homepath + "/.config/qt5-fsarchiver/disk.txt";
           if(system (befehl.toLatin1().data()))
              befehl = "";
           while (disk_ == ""){
            disk_ = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
            while (!ds.atEnd())
      	    {
            disk_ = ds.readLine();
      	    if (disk_.indexOf("loop") == -1 )
      	      {
      	      disk_name[i] = disk_;
      	      i++;
      	      }
           }
           file.close();
           }
           j = 0;
           for (k=0; k < i; k++)
           {
            disk = disk_name[k].split(QRegularExpression("\\s+"));
            size = disk.size();
           if(size >= 5)
             {
             if(disk[5] == "disk")
               {
               disk_name[j] = disk[0]; //Diskname
               j++;
               }
             } 
           }
           disk_name[j] = "";
 //Anzahl Festplatten ermitteln 
          j = 0;
         while (disk_name[j]!= "")
            {
            j++;
            }
//Combobox füllen
           items_disk.clear();
           for(i=0;i<j;i++) 
              items_disk <<  disk_name[i];
            cmb_disk->addItems(items_disk); 
            items_disk.clear();
   
}

void DialogMBR::disk_art()
{
    int i = cmb_disk->currentIndex();
    QString partition = disk_name[i];
    int efi = is_gpt("/dev/" + partition);
    cmb_mbr->setEnabled(false);
    if (efi == 0 &&  dialog_auswertung == 5)
	     cmb_mbr->setEnabled(true);
}

int DialogMBR::mbr()
{
QString befehl;
int i;
int success = 0;
int pos = 0;
int pos2 = 0;
QString partition;
QString homepath = QDir::homePath();
QModelIndex index = treeView->currentIndex();
QModelIndexList indexes = selModel->selectedIndexes();
    //Ubuntu Version einlesen, nur wenn Systempartition
    Ubuntuversion_auslesen();
    i = cmb_disk->currentIndex();
    partition = disk_name[i];
    efiflag = is_gpt("/dev/" + partition);
    folder_ =  (dirModel->filePath(index));
    pos = folder_.indexOf("_mbr_");
    pos2 = folder_.indexOf("_gpt_");
    if (efiflag == 0 && (pos == -1) && (dialog_auswertung == 5)){
          QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You must select an MBR backup file.\n","Sie müssen eine MBR Sicherungsdatei auswählen.\n"));
      return 1 ;
     }
    if (efiflag == 1 && (pos2 == -1) && (dialog_auswertung == 5))
      {
       QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You must select a GPT backup file.\n","Sie müssen eine GPT Sicherungsdatei auswählen.\n"));
      return 1 ;
      } 
    if (efiflag == 0){
        success = sektor_auslesen();
        if (success == 1)
           return 1;
    } 
    if (efiflag == 1 &&  (dialog_auswertung == 5))
	     cmb_mbr->setEnabled(false);
    if (efiflag == 0 &&  (dialog_auswertung == 5))
	     cmb_mbr->setEnabled(true);
    if (dialog_auswertung == 4)	
       {
	i = folder_einlesen();
        if (i ==0) {
                QFile file(folder_);
             
             if (efiflag == 0)   
                befehl = ("dd if=/dev/" + partition + " of='" + folder_ + "'/" + Ubuntuversion + "_mbr_" + partition + " bs=" + Sektor_byte + " " + "count=1");
             if (efiflag == 1)
                befehl = ("sgdisk -b '" + folder_ + "'/" + Ubuntuversion + "_gpt_" + partition + " /dev/" + partition);
             this->setCursor(Qt::WaitCursor); 
                i = system (befehl.toLatin1().data());
             this->setCursor(Qt::ArrowCursor);
   		if (i == 0 && efiflag == 0)
      			QMessageBox::about(this,tr("Note", "Hinweis"), tr("The MBR was successfully saved.\n", "MBR wurde erfolgreich gesichert.\n"));
        	if (i != 0 && efiflag == 0)
      			QMessageBox::about(this, tr("Note", "Hinweis"), tr("The MBR was not saved. If the backup path \n", "MBR wurde nicht gesichert.\n"));
                if (i == 0 && efiflag == 1)
      			QMessageBox::about(this,tr("Note", "Hinweis"), tr("GPT was successfully saved.\n", "GPT wurde erfolgreich gesichert.\n"));
        	if (i != 0 && efiflag == 1)
      			QMessageBox::about(this, tr("Note", "Hinweis"), tr("GPT was not saved. If the backup path \n", "GPT wurde nicht gesichert.\n"));
      		
                }
       }

 if (dialog_auswertung == 5 && efiflag == 1)
	{
	   i = folder_einlesen();
           if (i ==1)
	       return 0; 
	   int auswertung = questionMessage(tr("Caution: Do you really want to write back the GUID partition table?\n", "Vorsicht: Wollen Sie wirklich die GUID Partitionstabelle zurückschreiben?\n")); 
            if  (auswertung == 2) 
                return 1;
         if (i ==0) {
             this->setCursor(Qt::WaitCursor);	
	      if (cmb_mbr->currentIndex() == 0) {
              befehl = ("sgdisk -l '" + folder_ + "' /dev/" + partition);
              i = system (befehl.toLatin1().data());
              this->setCursor(Qt::ArrowCursor); 
   	      if (i == 0)
      		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The GUID partition table was successfully restored.\n", "Die GUID Partitionstabelle wurde erfolgreich wieder hergestellt.\n"));
              else
      		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The GUID partition table was not restored.\n", "Die GUID Partitionstabelle wurde nicht wieder hergestellt.\n"));
              }
 	      }
	}

     if (dialog_auswertung == 5 && cmb_mbr->currentIndex() != 3 && efiflag == 0)	
       {
        i = folder_einlesen();
        if (i ==1)
	   return 0;
 	if (efiflag == 0)
	{
          int auswertung = questionMessage(tr("Caution: Do you really want to write the MBR back completely or partially?\n", "Vorsicht: Wollen Sie wirklich den MBR komplett beziehungsweise teilweise zurückschreiben?\n")); 
            if  (auswertung == 2) 
                return 1; 
           if (i ==0) {
        	this->setCursor(Qt::WaitCursor);
	   if (cmb_mbr->currentIndex() == 0) {
              befehl = ("dd if='"+ folder_ + "' of=/dev/" + partition + " bs=1 count=446");
              i = system (befehl.toLatin1().data());
              this->setCursor(Qt::ArrowCursor);  
   	      if (i == 0)
      		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The bootloader area was successfully restored.\n", "Der Bootloaderbereich wurde erfolgreich wieder hergestellt.\n"));
              else
      		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The boot loader area was not restored.\n", "Der Bootloaderbereich wurde nicht wieder hergestellt.\n"));
              }
              if (cmb_mbr->currentIndex() == 2) {
		   //Partitionstabelle extrahieren                   
                   befehl = ("dd if='"+ folder_ + "' of=" + homepath + "/.mbr.txt  bs=1 skip=446 count=66");
                   i = system (befehl.toLatin1().data());
                   //Partitionstabelle wiederherstellen 
                   befehl = ("dd if=" + homepath + "/.mbr.txt of=/dev/" + partition + " bs=1 seek=446 count=66");
                   i = i + system (befehl.toLatin1().data());  	
                   //Datei löschen
                   befehl = "rm " + homepath + "/.mbr.txt";
                   if(system (befehl.toLatin1().data()))
                      befehl = "";
                   this->setCursor(Qt::ArrowCursor);    
   	           if (i == 0)
      			QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition table was successfully restored.", "Die Partitionstabelle wurde erfolgreich wieder hergestellt.\n"));
                   else
      			QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition table was not restored.\n", "Die Partitionstabelle wurde nicht wieder hergestellt.\n"));
               }
               if (cmb_mbr->currentIndex() == 1) {
                 // MBR und Pasrtitionstabelle wieder herstellen
                 befehl = ("dd if='"+ folder_ + "' of=/dev/" + partition + " bs=1 count=512");
                 i = system (befehl.toLatin1().data());
               this->setCursor(Qt::ArrowCursor); 
   	       if (i == 0) 
      		   QMessageBox::about(this, tr("Note","Hinweis"), tr("The MBR was successfully restored.\n", "Der MBR wurde erfolgreich wieder hergestellt.\n"));
                else
      		  QMessageBox::about(this, tr("Note", "Hinweis"), tr("The MBR is not restored.\n", "Der MBR wurde nicht wieder hergestellt.\n"));
               }
                 
          }
       }
    }
    if (dialog_auswertung == 5 && cmb_mbr->currentIndex() == 3)	
       {
        i = folder_einlesen();
        if (i ==1)
	   return 0;
        int auswertung = questionMessage(tr("Caution: Do you really want to write back the hidden area?\n", "Vorsicht: Wollen Sie wirklich den verborgenen Bereich zurückschreiben? \n")); 
            if  (auswertung == 2) 
                return 1; 
            //i = folder_einlesen();
            this->setCursor(Qt::WaitCursor);
            if (i ==0) {
		   //verborgenen Bereich extrahieren                   
                   befehl = ("dd if='"+ folder_ + "' of=" + homepath + "/.mbr.txt  bs=1 skip=512 count=" + Sektor_byte_1);
                   i = system (befehl.toLatin1().data());
                   //verborgenen Bereich wiederherstellen 	
                   befehl = ("dd if=" + homepath + "/.mbr.txt of=/dev/" + partition + " bs=1 seek=512 count=" + Sektor_byte_1);
                   i = i + system (befehl.toLatin1().data());  	
                   //Datei löschen
                   befehl = "rm " + homepath + "/.mbr.txt";
                   i = system (befehl.toLatin1().data());
                   this->setCursor(Qt::ArrowCursor);       
      	        if (i == 0) 
      		   QMessageBox::about(this, tr("Note", "Hinweis"), tr("The hidden area was successfully restored.\n", "Der verborgene Bereich wurde erfolgreich wieder hergestellt.\n"));
                else
      		  QMessageBox::about(this, tr("Note", "Hinweis"), tr("The hidden area was not restored.\n", "Der verborgene Bereich wurde nicht wieder hergestellt.\n"));
        }
    }
    return 0;
}

int  DialogMBR::sektor_auslesen() {
QString Dateiname;
QString befehl;
QString text;
QString partition;
QString homepath = QDir::homePath();
int sektor_ = 0;
int i = 0;
int j = 0;
QString dummy[10];
QStringList hidden_size;
QString hidden_size_;
        i = cmb_disk->currentIndex();
        partition = disk_name[i];
        efiflag = is_gpt("/dev/" + partition);
        // fdisk -lu , mit diesem Befehl Startsektor von sda1 ermitteln.
        // derzeit für Ubuntu:  Startsektor sda1 = 63*512 = 32256 
	// Sektornummer in Datei abspeichern
        Dateiname = homepath + "/.config/qt5-fsarchiver/sektornummer.txt";
        befehl = "fdisk -lu | grep " + partition + "1 > " + homepath + "/.config/qt5-fsarchiver/sektornummer.txt";
        i = system (befehl.toLatin1().data());
        QFile file(Dateiname);
        QFileInfo info(Dateiname); 
        size_ = info.size();  //Wenn Dateigröße = 0 ist verhindert diese Abfrage einen Abstaurz
        if (size_ == 0){
           QMessageBox::about(this, tr("Note", "Hinweis"), tr("Error. The partition table cannot be read. The partition table cannot be read out. The program is aborted.", "Fehler. Die Partitionstabelle kann nicht ausgelesen werden. Das Programm wird abgebrochen.\n")); 
           return 1;
        }
        //Datei auslesen
        if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QTextStream ds(&file);
            hidden_size_ = ds.readLine();
            hidden_size =  hidden_size_.split(" ");
            file.close();
            for (i=0; i < 100; i++){
                if (hidden_size[i] != "") 
                   {
                   dummy[j] = hidden_size[i];
                   j = j + 1; 
                   }
                if (j == 3)
                   break;
            }
            if (dummy[1] == "*")  //Festplatte hat Bootsektor
               sektor_ = dummy[2].toInt();
            else 
               sektor_ = dummy[1].toInt(); //Festplatte hat keinen Bootsektor
            }
      if(system (befehl.toLatin1().data()))
            befehl = ""; 
       if (sektor_ < 2 && efiflag == 0) {
	    QMessageBox::about(this, tr("Note", "Hinweis"), tr("The end of hidden area of the 1st Partition could not be read. Only 512 bytes are saved.", "Das Ende des verborgenen Bereiches der 1. Partition konnte nicht ausgelesen werden. Es werden nur 512 Bytes gesichert.\n"));
            sektor_ = 2;
	}
        sektor_byte = sektor_  * 512;
        Sektor_byte =  QString::number(sektor_byte);
        sektor_byte_1 = (sektor_ -1) * 512 ;
        Sektor_byte_1=  QString::number(sektor_byte_1);
        return 0;  
}

void DialogMBR::Ubuntuversion_auslesen() {
QString Dateiname;
QString partition;
QString befehl;
QStringList Ubuntu_;
int i = 0;
        i = cmb_disk->currentIndex();
        partition = disk_name[i];
        partition = "/dev/"+ partition;
        //Prüfen ob System Partition
        if (mtab_einlesen(partition.toLatin1().data()) == "system") {
             	Dateiname = "/etc/issue";     
        	QFile file(Dateiname);
        	//Datei auslesen
        	if( file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            		QTextStream ds(&file);
            		Ubuntuversion = ds.readLine();
            		Ubuntu_ = Ubuntuversion.split(" ");
            		Ubuntuversion = Ubuntu_[1];
            		file.close();
                }
         }
         else
		Ubuntuversion = "";
   
}

int DialogMBR::folder_einlesen() {
   QString partition;
   QString Festplatte;
   int ret = 1; 
   int pos = 0;
   int i = 0;
   QModelIndex index = treeView->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder_.append  (dirModel->filePath(index));
   folder_ =  (dirModel->filePath(index));
   if (dialog_auswertung == 5)
	Festplatte = folder_.right(3);
   QFileInfo info(folder_); 
   size_ = info.size(); 
   if (folder_ == "" && (dialog_auswertung == 4))
      {
       QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You must select a directory", "Sie müssen ein Verzeichnis auswählen\n"));
      return 1 ;
      }
   if (info.isFile() && (dialog_auswertung == 4))
      {
      QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You have selected a file. You must select a directory.\n", "Sie haben eine Datei ausgewählt. Sie müssen ein Verzeichnis auswählen\n"));
      return 1 ;
      }
    if (folder_ == "" && (dialog_auswertung == 5))
      {
       QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You must choose the MBR/GPT file\n","Sie müssen die MBR/GPT Sicherungsdatei auswählen.\n"));
      return 1 ;
      }
    if (info.isDir() && (dialog_auswertung == 5))
      {
      QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You have selected a directory. You must select an MBR/GPT backup file.\n", "Sie haben ein Verzeichnis ausgewählt. Sie müssen die MBR/GPT Sicherungsdatei auswählen\n"));
      return 1 ;
       }
    i = cmb_disk->currentIndex();
    partition = disk_name[i];
    if (dialog_auswertung == 5 )
       pos = folder_.indexOf("_" + partition);
    if (pos == -1  && dialog_auswertung == 5){
      //Partitionen stimmen nicht überein
      QString text = tr("You may have selected the wrong hard disk. The hard disk to be restored is ", "Sie haben eventuell eine falsche Festplatte ausgewählt. Die wiederherzustellende Festplatte ist ") + partition + tr(", but the backed up hard drive is ", ",  die gesicherte Festplatte ist aber ") +  Festplatte + tr(" Do you want to continue?", " Wollen Sie fortfahren?");
        ret = questionMessage(text);
        if (ret == 2)
            return 1;
        }
    QString sA = QString::number(size_);
    if (efiflag == 0)
    {
    QString text = tr("You may have selected an incorrect file. The hidden area to be restored has a size of ", "Sie haben eventuell eine falsche Datei ausgewählt. Der wiederherzustellende verborgene Bereich hat eine Größe von") +  sA + 
    tr(" bytes. The hidden area of the disk ", " Byte. Der verborgene Bereich von der Festplatte ") + partition + tr(" has a size of ", " hat eine Größe von ") + Sektor_byte + tr(" bytes. Do you want to continue?", " Byte. Wollen Sie fortfahren?");
    if (size_ != sektor_byte && dialog_auswertung == 5 && cmb_mbr->currentIndex() == 3) {
        ret = questionMessage(text);
        if (ret == 2)
            return 1;
        if (ret == 1)
           return 0;
       }
    }
    return 0;
}

int DialogMBR::questionMessage(QString frage)
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

string DialogMBR::mtab_einlesen(string partition_if_home)
{
   QString text;
   QFile file("/etc/mtab");
   QTextStream ds(&file);
   string text_str;
   int pos;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     text = ds.readLine();
     text_str = text.toLatin1().data();
     pos = text_str.find(partition_if_home); 
     if (pos > -1)  // Partitionsname gefunden
        return "system";
     file.close();
     }
  return "";
}

int DialogMBR::is_gpt(QString partition_efi)
{
      QString homepath = QDir::homePath();
      QString text;
      QString befehl = "gdisk -l " + partition_efi +  " 1> " +  homepath + "/.config/qt5-fsarchiver/efi.txt";
      //QString befehl = "sgdisk -p " + partition_efi +  " 1> " +  homepath + "/.config/qt5-fsarchiver/efi.txt";
      if(system (befehl.toLatin1().data()))
            befehl = "";
      QString filename = homepath + "/.config/qt5-fsarchiver/efi.txt";
      QFile file(filename);
      if( file.open(QIODevice::ReadOnly|QIODevice::Text)) { 
	QTextStream ds(&file);
        while (!ds.atEnd()){
           	text = ds.readLine();
		if (text.indexOf("GPT: present") > -1) 
                   return 1;
               // if( text.isEmpty() )
         	// break;
           }
 } 

   	file.close();
  return 0;
}

void DialogMBR::folder_expand() {
   QModelIndex index = treeView->currentIndex();
   treeView->expand(index);
}









