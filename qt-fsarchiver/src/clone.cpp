/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2022 Dieter Baum.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#include <QtGui> 
#include <QMessageBox> 
#include "clone.h"
#include <string.h>
#include <unistd.h>
#include "mainWindow.h"
#include "filedialog.h"

extern int dialog_auswertung;
extern int anzahl_disk;
extern QString folder_file_;
int zaehler_2;
QStringList filters_clone;
QString part_clone[100][4];
extern QString part[100][10];
float part_clone_[100];
QString folder_clone;
int endeThread_clone;
int flag_clone;
int thread_run_clone;
int sekunde_elapsed_clone;
int minute_elapsed_clone;
int hour_elapsed_clone;
float sekunde_summe_clone = 0;
float sekunde_summe_clone_1 = 0;
QString pid_dd = "";
QString pid_2_dd[5];
QString partition_name;
int read_write_counter = 0;
int read_write_counter_1 = 1;
int rrw[10];
float read_write_space_sum = 0;
QString read_write_space_sum_;
float read_write_space_summe = 0;
float partition_exist_size_int;
float partition_exist_size_int_[100];
int dummy_prozent_clone;
float size_clone;
float size_clone_dummy;
QString read_write_space_sec;
QString img_partition_clone;
QString img_partition_size;
QString img_partition_full_size;
QString error;
extern QString password;
long anzahl_bytes_;
QString _Datum_clone;
extern QString user;
QString userpath_clone;
int mountpoint1;
extern int sleepfaktor;
QString homepath_clone = QDir::homePath();

DialogClone::DialogClone()
{
	setupUi(this); // this sets up GUI
	connect( bt_save, SIGNAL( clicked() ), this, SLOT( todo() ) );
        connect( rdbt_clone, SIGNAL( clicked() ), this, SLOT(rdbutton_clone() ) ); 
	connect( rdbt_image_save, SIGNAL( clicked() ), this, SLOT(rdbutton_image_save() ) ); 
        connect( rdbt_image_restore, SIGNAL( clicked() ), this, SLOT(rdbutton_image_restore() ) ); 
        connect( rdbt_partition_save, SIGNAL( clicked() ), this, SLOT(rdbutton_partition_image_save() ) ); 
        connect( rdbt_partition_restore, SIGNAL( clicked() ), this, SLOT(rdbutton_partition_image_restore() ) ); 
        //connect( pushButton_break, SIGNAL( clicked() ), this, SLOT(esc_end()));
        connect( bt_end, SIGNAL( clicked() ), this, SLOT(close()));
        connect( pushButton_folder, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
        connect( pushButton_folder_2, SIGNAL( clicked() ), this, SLOT(folder_expand()));
        connect( pushButton_partition, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        connect( pushButton_partition_2, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
   	treeView_clone->setModel(dirModel);
   	treeView_clone->setSelectionModel(selModel);
   	QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
        dirModel->setRootPath(QDir::rootPath());
   	treeView_clone->setRootIndex(cwdIndex);
        rdbt_clone->setChecked(true);
        connect(treeView_clone->selectionModel(), &QItemSelectionModel::currentChanged, this, &DialogClone::folder_einlesen);
        treeView_clone->setEnabled(false);
        userpath_clone = homepath_clone; 
       	format_Disk();
        bt_save->setText (tr("Clone Harddrive", "Festplatte klonen"));
        timer_clone = new QTimer(this);
        timer_read_write = new QTimer(this);
       // Erforderlich um Textdatei vor dem ersten Auslesen mit 3 Zeilen zu füllen
        QString befehl = "vmstat 1 2 1> " +  userpath_clone + "/.config/qt-fsarchiver/disk.txt";
        if(system (befehl.toLatin1()))
           befehl = "";
        chk_zip->setEnabled(false);
        chk_zip->setChecked(true);
        //chk_zip->set| grepHidden(true);
        listWidget->setHidden(true);
        addWidget(); 
        chk_Beschreibung->setChecked(true);  
 }

void DialogClone::format_Disk() {
QString befehl;
int  i = 0, j=0, k = 0;
QString attribute;
QString dummy;
QString dummy1;
int size = 0;
QString space1;
QString space2;
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QStringList _dev_sdx;
QString _dev_sdx_;
QString _devsdx[100][6];
QString text;
QString sdx[50];
QString sdx_[50];
QString filename;
QString filename1;
QString teilstring;
int aa, bb, dd;
//Zunächst disk.txt löschen
        attribute = userpath_clone + "/.config/qt-fsarchiver/disk.txt";
        befehl = "/usr/sbin/qt-fsarchiver.sh  23 " + attribute;
       if(system (befehl.toLatin1().data()))
           befehl = "";
        filename = userpath_clone + "/.config/qt-fsarchiver/disk2.txt";
        QFile file(filename);
            QTextStream ds(&file);
             if(file.open(QIODevice::ReadWrite | QIODevice::Text))
               {
                attribute = "lsblk -l 1> " +  userpath_clone + "/.config/qt-fsarchiver/disk2.txt";
               befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
              if(system (befehl.toLatin1().data()))
                  befehl = "";
            while (text == ""){
               text = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
            while (!ds.atEnd())
      	    {
            text = ds.readLine();
            if (text.indexOf("disk") > -1 )
       	      {
      	      sdx[i] = text;
      	     i++;
      	      }
            }
           file.close();
           }
           i = 0;
        filename1 = userpath_clone + "/.config/qt-fsarchiver/disk1.txt";
        QFile file1(filename1);
        QTextStream ds1(&file1);
         text = "";
          if(file1.open(QIODevice::ReadWrite | QIODevice::Text))
               {
              attribute = "lsblk -l -b 1> " +  userpath_clone + "/.config/qt-fsarchiver/disk1.txt";
              befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
             if(system (befehl.toLatin1().data()))
                 befehl = "";
         while (text == ""){
            text = ds1.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
            while (!ds1.atEnd())
      	    {
            text = ds1.readLine();
            if (text.indexOf("disk") > -1 )
       	      {
      	      sdx_[i] = text;

      	      i++;
      	      }
            }
           file.close();
           }
           j = 0;
           for (k=0; k < i; k++)
           {
           dummy = sdx[k];
           dev_sdx_= dummy;
           dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
           size = dev_sdx.size();
           if(dev_sdx[5] == "disk" && size >= 5)
             {
              part_clone[j][0] = dev_sdx[0]; //Diskname
              part_clone[j][1] = dev_sdx[3]; //size
              dummy = part_clone[j][1].right(1);
              part_clone[j][1] = part_clone[j][1].left(part_clone[j][1].size()-1);
              part_clone[j][1] = part_clone[j][1] + " " + dummy + "B";
              _dev_sdx_ = sdx_[k];
              _dev_sdx = _dev_sdx_.split(QRegExp("\\s+"));
              part_clone_[j] = _dev_sdx[3].toFloat();
              j++;
             }
             }
          i = 0;     
         while (part_clone[i][0] != "") {
           teilstring = part_clone[i][0];
           aa = teilstring.size();
           teilstring = part_clone[i][1];
           bb = teilstring.size();
           dd = 9 - aa; 
           space1.fill (' ',dd);
           teilstring = part_clone[i][0] + space1;
           dd = 11 -bb;
           space2.fill (' ',dd);
           teilstring = part_clone[i][0] + space1 + part_clone[i][1];
           if (part_clone[i][1] != "" ){
              listWidget_clone->addItem (teilstring);
              listWidget_exist->addItem (teilstring);
              }
          i++;
         }
}

//QMessageBox::about(this, "Hinweis", "disk ermitteln\n" + QString::number(part_clone_[j]) );
void DialogClone::addWidget() {
extern QString add_part[100];
int i = 0;
QString dummy;
QStringList dev_sdx;
QString dev_sdx_;
    while (add_part[i] != "")
    {
	listWidget->addItem (add_part[i]);
        dummy = add_part[i];
        dev_sdx_= dummy;
        dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
        part_clone[i][0] = dev_sdx[0]; // sda1
        part_clone[i][1] = dev_sdx[1]; // ext4
        part_clone[i][2] = dev_sdx[2]; // size
        part_clone[i][3] = dev_sdx[3]; // GB
        part_clone[i][4] = dev_sdx[4]; // Bezeichnung
        i++ ;
     }
}

void DialogClone::todo(){
	if (rdbt_clone->isChecked())
	   do_clone();
	if (rdbt_image_save->isChecked()) 
            do_image();
 	if (rdbt_image_restore->isChecked())
           restore_image();
        if (rdbt_partition_save->isChecked()) 
            do_image_partition();
        if (rdbt_partition_restore->isChecked())
            restore_image_partition();
 }

int DialogClone::do_image_partition()  //Image einer Partition erstellen
{
dialog_auswertung = 7;
QString befehl;
QString attribute;
int ret = 0;
int success = 0;
int row;
int zip;
chk_Beschreibung->setEnabled(true);   
QString _Datum_clone = Zeit_auslesen_clone();
      success = testen_1(folder_clone, img_partition_clone, 0);
      if (success ==1)
         {
               QMessageBox::warning(this,tr("Note", "Hinweis"),tr("The folder cannot be read or written to. If the path ", "Der Ordner kann nicht gelesen oder beschrieben werden. Enthält der Pfad ") + folder_clone + tr(" contains a special character?\n", " ein Sonderzeichen?\n"));
          return 1;
         }
Qt::CheckState state;
Qt::CheckState state1;
      lbl_save->setText (tr("already saved", "bereits gesichert"));
      state = chk_zip->checkState();
      flag_clone =3;
      if (img_partition_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a partition.", "Sie müssen eine Partition auswählen.\n"));
	return 0;        
	}
      if (folder_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a folder.", "Sie müssen ein Verzeichnis auswählen.\n"));
	return 0;        
	}
     partition_exist_size_int = img_partition_size.toInt();
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
    int part_art_clone = mountpoint(mountpoint1);
    if (part_art_clone == 1){
       ret = questionMessage(tr("There is a root or home partition. Do you want to continue?", "Es ist eine root- oder home Partition vorhanden. Wollen Sie fortfahren?\n"));
       }
       if (ret == 2)
          return 0;
       if (state == Qt::Checked)
          {
	  attribute = "if=/dev/" + img_partition_clone + " | gzip --best >" + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.fsa";
          befehl = "/usr/sbin/qt-fsarchiver.sh  21 " + attribute;
          zip = 3; 
          folder_file_ = folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.fsa.txt";
          }
       else
          {
          attribute = "if=/dev/" + img_partition_clone + " of=" + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa bs=1M 2>" + userpath_clone + "/.config/qt-fsarchiver/disk.txt"; 
          befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute;
          zip = 0; 
          folder_file_ = folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa.txt";
          }
        thread1.setValues( 0,befehl);
	ret = questionMessage(tr("Do you really want to create an image of a partition?  ", " Wollen Sie wirklich ein Abbild einer Partition erstellen? ") );  
              if (ret == 2)
                 return 0;
              if (ret == 1){
               	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
              	ViewProzent();
               row = listWidget->currentRow();
               beschreibungstext_clone(folder_file_, zip, row);
               state1 = chk_Beschreibung->checkState();
	       if (state1 == Qt::Checked)
               	  {
		  FileDialog Filedialog;
     	     	  FileDialog *dlg = new FileDialog;
     	     	 dlg->exec();
          	  if (dialog_auswertung == 0)
                      {
                      QMessageBox::warning(this, tr("Note", "Hinweis"),
         	      tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
                      bt_end->setEnabled(true);
		      return 0;
                      }
                   }
                this->setCursor(Qt::WaitCursor);
		if (state == Qt::Checked){
			read_write_hd();
			startThread1(1);
                   }
                else 
                {
                         if(system (befehl.toLatin1().data()))
                            befehl = "";
                         read_write_hd_1();
                         if (error == "1")
                            {
                            QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was not successful.", "Das Sichern des Abbildes der Festplatte war nicht erfolgreich.\n"));
                            bt_end->setEnabled(true);
                            bt_save->setEnabled(true);
                            this->setCursor(Qt::ArrowCursor);
                            return 0;
                            }
                      }
                }
    return 0;
}

int DialogClone::restore_image_partition()  //Image einer Partition wiederherstellen
{
dialog_auswertung = 8;
QString befehl;
int pos;
int pos1 = 0;
QString partition_exist;
QString partition_exist_size;
QString part_name;
QString attribute; 
int success = 0;
QString filename;
chk_Beschreibung->setEnabled(false);
      success = testen_1(folder_clone, img_partition_clone, 1);
      if (success ==1)
         {
               QMessageBox::warning(this,tr("Note", "Hinweis"),tr("The folder cannot be read or written to. If the path ", "Der Ordner kann nicht gelesen oder beschrieben werden. Enthält der Pfad ") + folder_clone + tr(" contains a special character?\n", " ein Sonderzeichen?\n"));
          return 1;
         }
      lbl_save->setText (tr("already restored", "bereits zurückgeschrieben"));
      chk_zip->checkState();
      flag_clone = 5;
      partition_exist_size_int = img_partition_size.toInt();
     if (img_partition_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a partition.", "Sie müssen eine Partitiom auswählen.\n"));
	return 0;        
	}
     if (folder_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a part.fsa file or an part.fsa.gz file.", "Sie müssen eine part.fsa- oder eine part.fsa.gz-Datei auswählen.\n"));
	return 0;        
	}
     if (file_check() == 1)
        return 0;
     // Prüfen, ob gesicherte und wiederherzustellende Partition übereinstimmt.
        part_name = folder_clone;
        while (pos > -1)
          {
          pos = part_name.indexOf("/");
          if(pos > -1)
          {
             part_name.replace(pos, 1, "+");
             if (pos != -1)
               pos1 = pos;
           }
          } 
          part_name = part_name.right(part_name.size() - pos1 - 1);  
          pos = part_name.indexOf("-"); 
          part_name = part_name.left(pos); 
          pos = folder_clone.indexOf(img_partition_clone);
        if (pos == -1)
         if (folder_clone.indexOf(img_partition_clone) == -1)
            pos = questionMessage(tr("Partition to restore ", "Die wiederherzustellende Partition ") + part_name + 
               tr(" does not match the backed up partition.", " stimmt nicht mit der gesicherten ") + img_partition_clone + tr(" Do you want to continue restore?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
               if (pos == 2)  //nicht wiederherstellen
                  return 0;
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
    int part_art_clone = mountpoint(mountpoint1);
    if (part_art_clone == 1){
       QMessageBox::warning(this, tr("Note", "Hinweis"), tr("There is a root or home partition on the hard disk. You must use a live DVD.", "Auf der Festplatte ist eine root- oder home Partition. Sie müssen eine Live-CD benutzen.\n"));
	return 0;
	}
//Prüfen ob img.fsa oder gz.fsa Datei
        if (folder_clone.indexOf("-gz.part.fsa") > -1)
           {
            attribute = "-c " + folder_clone + "|sudo dd of=/dev/" + img_partition_clone;
            befehl = "/usr/sbin/qt-fsarchiver.sh  14 " + attribute;
            }
        if (folder_clone.indexOf("-part.fsa") > -1)
            {
            attribute = "if=" + folder_clone +  " of=/dev/" +  img_partition_clone + " bs=1M 2>" + userpath_clone + "/.config/qt-fsarchiver/disk.txt";
            befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute;
            }
        folder_file_ = folder_clone;
 	filename = folder_clone + ".txt";
        QFile f(filename);
                // Prüfen ob text-Datei vorhanden 
		if (f.exists())
                         {
           		dialog_auswertung = 8;
              		FileDialog Filedialog;
     	       		FileDialog *dlg = new FileDialog;
     	     		dlg->exec();
             		if (dialog_auswertung == 0)
                	   {
                	   QMessageBox::warning(this, tr("Note", "Hinweis"),
         		   tr("The write back was aborted by the user.\n", "Das Zurückschreiben wurde vom Benutzer abgebrochen\n"));
                            bt_end->setEnabled(true);
                            return 0;
                	   }
                       }
            int ret = questionMessage(tr("Do you really want to write back an image of a partition? ", " Wollen Sie wirklich ein Abbild einer Partition zurückschreiben? ") );  
              if (ret == 2)
                 return 0;
              if (ret == 1){
               	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
                thread2.setValues( 0,befehl);
                ViewProzent();
                //text = window.beschreibungstext(DateiName_net + "-" + _Datum_net + ".fsa", zip, row);
                this->setCursor(Qt::WaitCursor);
                pos = folder_clone.indexOf("gz.part");
		if (pos > 0){
                      read_write_hd(); //mit gzip wiederherstellen
		      startThread2(1);
			}
                else 
                    {
                	if(system (befehl.toLatin1().data()))
                           befehl = "";
                        read_write_hd_1(); //mit dd wiederherstellen 
                    }
    	}
    return 0;
}

int DialogClone::do_clone()  //Festplatte klonen
{
QString befehl;
int row = 0;
int ret = 0;
QString partition_exist;
QString partition_exist_size;
QString partition_clone;
QString partition_clone_size;
float partition_clone_size_int = 0;
QString attribute;
QString dummy;
int part_art_clone;
int part_art_clone1;
lbl_save->setText (tr("already saved", "bereits gesichert"));
chk_Beschreibung->setEnabled(false);
      flag_clone =1;
      row = listWidget_exist->currentRow();
      if (row > -1){
            partition_exist = "/dev/" + part_clone[row][0];
            partition_exist_size_int = part_clone_[row]/1000000;
            dummy = part_clone[row][0];
       }
      row = listWidget_clone->currentRow();
      if(row > -1){
         partition_clone = "/dev/" + part_clone[row][0];
         partition_clone_size_int = part_clone_[row]/1000000;
         }
     if(partition_exist == "" or partition_clone == ""){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a hard drive.", "Sie müssen eine Festplatte auswählen.\n"));
	return 0;        
	}
    // Überprüfen, ob Festplatte groß genug ist
    if(partition_clone_size_int < partition_exist_size_int){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The selected hard drive is too small.", "Die gewählte Festplatte ist zu klein.\n"));
	return 0;
	}
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
       part_art_clone = mountpoint_disk(dummy);
       part_art_clone1 = mountpoint_disk(part_clone[row][0]);
       part_art_clone = part_art_clone + part_art_clone1;
       if (part_art_clone > 0){
         ret = questionMessage(tr("There is a root or home partition on the hard disk. Do you want to continue?", "Auf der Festplatte ist eine root- oder home Partition. Wollen Sie fortfahren.\n"));
       }
       if (ret == 2)
          return 0; 

       attribute = "if=" + partition_exist + " of=" + partition_clone + " bs=1M 2>" + userpath_clone + "/.config/qt-fsarchiver/disk.txt";
       befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute;
       thread1.setValues(0,befehl);
       ret = questionMessage(tr(" Do you want really clone the hard drive? All dates on  ", " Wollen Sie wirklich die Festplatte klonen? Alle Daten auf der Festplatte ")   + partition_clone + tr(" are deleted!", " werden gelöscht!") );
              if (ret == 2)
                 return 0;
              ViewProzent();
              this->setCursor(Qt::WaitCursor);
              endeThread_clone = 0;
             if(system (befehl.toLatin1().data()))
                befehl = "";
             read_write_hd_1();
             return 0;
}


int DialogClone::do_image()  //Image einer Festplatte erzeugen
{
QString _Datum_clone = Zeit_auslesen_clone();
QString befehl;
int row;
int ret = 0;
QString partition_exist;
QString attribute;
QString dummy;
QString partition_exist_size;
Qt::CheckState state;
chk_Beschreibung->setEnabled(false);
int success = 0;
      lbl_save->setText (tr("already saved", "bereits gesichert"));
      state = chk_zip->checkState();
      flag_clone = 2;
      row = listWidget_exist->currentRow();
      if (row > -1){
          partition_exist = "/dev/" + part_clone[row][0] ;
          partition_exist_size_int = part_clone_[row]/1000000;
       }
      success = testen_1(folder_clone,partition_exist, 2);
      if (success ==1)
         {
               QMessageBox::warning(this,tr("Note", "Hinweis"),tr("The folder cannot be read or written to. If the path ", "Der Ordner kann nicht gelesen oder beschrieben werden. Enthält der Pfad ") + folder_clone + tr(" contains a special character?\n", " ein Sonderzeichen?\n"));
          return 1;
         }
    if (partition_exist == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a partition.", "Sie müssen eine Partition auswählen.\n"));
	return 0;        
	}
    if (folder_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a folder.", "Sie müssen ein Verzeichnis auswählen.\n"));
	return 0;        
	}
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
         int part_art_clone = mountpoint_disk(part_clone[row][0]);
         if (part_art_clone == 1){
         ret = questionMessage(tr("There is a root or home partition on the hard disk. Do you want to continue?", "Auf der Festplatte ist eine root- oder home Partition. Wollen Sie fortfahren?\n"));
        }
        if (ret == 2)
          return 0; 
	partition_name  = partition_exist.right(partition_exist.size() -4);
        if (state == Qt::Checked)
          {
          attribute = "if=" + partition_exist + " | gzip --best > " + folder_clone +  partition_name + "-" + _Datum_clone + ".gz.fsa";
          befehl = "/usr/sbin/qt-fsarchiver.sh  21 " + attribute; 
          }
       else
          {
	   attribute = "if=" + partition_exist + " of=" + folder_clone +  partition_name + "-" + _Datum_clone + ".img.fsa bs=1M 2>" + userpath_clone + "/.config/qt-fsarchiver/disk.txt";
           befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute; 
          }
 	thread1.setValues( 0,befehl);
	ret = questionMessage(tr("Do you really want to create an image of the hard disk?", " Wollen Sie wirklich ein Abbild der Festplatte erstellen? ") );  
              if (ret == 2)
                 return 0;
              if (ret == 1){
               	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
              	ViewProzent();
                this->setCursor(Qt::WaitCursor);
		if (state == Qt::Checked){
			read_write_hd();
			startThread1(1);}   // mit gzip schreiben
                else
                {
                	if(system (befehl.toLatin1().data()))
                          befehl = "";
                        read_write_hd_1();  // mit dd schreiben
                        if (error == "1")
                            {
                            QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was not successful.", "Das Sichern des Abbildes der Festplatte war nicht erfolgreich.\n"));
                            bt_end->setEnabled(true);
                            bt_save->setEnabled(true);
                            this->setCursor(Qt::ArrowCursor);
                            return 0;
                            }
                    }
                }
    return 0;
}


int DialogClone::restore_image()  //Image einer Festplatte wiederherstellen
{
QString befehl;
int row;
int pos;
int pos1 = 0;
QString partition_save;
QString partition_exist;
QString partition_exist_size;
QString attribute;
QString dummy;
QString disk_name;
chk_Beschreibung->setEnabled(false);
int success = 0;
      lbl_save->setText (tr("already written back.", "bereits zurückgeschrieben"));
      chk_zip->checkState();
      flag_clone = 4;
      row = listWidget_exist->currentRow();
      row = listWidget_exist->currentRow();
      if (row > -1){
          partition_exist = "/dev/" + part_clone[row][0] ;
          partition_exist_size_int = part_clone_[row]/1000000;
       }
       success = testen_1(folder_clone, partition_exist, 3);
      if (success ==1)
         {
               QMessageBox::warning(this,tr("Note", "Hinweis"),tr("The folder cannot be read or written to. If the path ", "Der Ordner kann nicht gelesen oder beschrieben werden. Enthält der Pfad ") + folder_clone + tr(" contains a special character?\n", " ein Sonderzeichen?\n"));
          return 1;
         }
       if (partition_exist == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a hard drive.", "Sie müssen eine Festplatte auswählen.\n"));
	return 0;        
	}
     if (folder_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a gz.fsa file or an img.fsa file.", "Sie müssen eine gz.fsa- oder eine img.fsa-Datei auswählen.\n"));
	return 0;        
	}
     if (file_check() == 1)
        return 0;
// Prüfen, ob gesicherte und wiederherzustellende Partition übereinstimmt.
// Festplatte aus folder_clone extrahieren
         pos = folder_clone.indexOf(".gz.fsa");
         if (pos > -1)
             disk_name = folder_clone.mid(pos-14,3);
         pos = folder_clone.indexOf(".img.fsa");
         if (pos > -1)
             disk_name = folder_clone.mid(pos-14,3);
         disk_name = partition_exist.right(partition_exist.size() -5);
         partition_save = folder_clone;;
         while (pos > -1)
          {
          pos = partition_save.indexOf("/");
          if(pos > -1)
          {
             partition_save.replace(pos, 1, "+");
             if (pos != -1)
               pos1 = pos;
           }
          } 
          partition_save = partition_save.right(partition_save.size() -pos1 - 1);  
          pos = partition_save.indexOf("-"); 
          partition_save = partition_save.left(pos);  
        if (folder_clone.indexOf(disk_name) == -1)
            pos = questionMessage(tr("The disk to be recovered ", "Die wiederherzustellende Festplatte ") + disk_name + 
               tr(" does not coincide with the saved ", " stimmt nicht mit der gesicherten ") + partition_save + tr(" Do you want to continue restore?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
               if (pos == 2)  //nicht wiederherstellen
                  return 0;
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
    int part_art_clone = mountpoint_disk(part_clone[row][0]);
    if (part_art_clone == 1){
       QMessageBox::warning(this, tr("Note", "Hinweis"), tr("There is a root or home partition on the hard disk. You must use a live DVD.", "Auf der Festplatte ist eine root- oder home Partition. Sie müssen eine Live-CD benutzen.\n"));
	return 0;
	}
	partition_name  = partition_exist.right(partition_exist.size() -4);
//Prüfen ob img.fsa oder gz.fsa Datei
        if (folder_clone.indexOf("gz.fsa") > 0)
             {
        	attribute = "-c " + folder_clone + "|sudo dd of=" + partition_exist; 
                befehl = "/usr/sbin/qt-fsarchiver.sh  14 " + attribute;
            }
        if (folder_clone.indexOf("img.fsa") > 0)
            {
            attribute = "if=" + folder_clone +  " of=" + partition_exist + " bs=1M 2>" + userpath_clone + "/.config/qt-fsarchiver/disk.txt"; 
            befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute;
            }
            int ret = questionMessage(tr("Do you really want to write back an image of the hard disk? ", " Wollen Sie wirklich ein Abbild der Festplatte zurückschreiben? "));
              if (ret == 2)
                 return 0;
              if (ret == 1){
               	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
                thread2.setValues( 0,befehl);
                ViewProzent();
                this->setCursor(Qt::WaitCursor);
                pos = folder_clone.indexOf("gz.fsa");
		if (pos > 0){
                      read_write_hd();
		      startThread2(1);
			}
                else 
                	{
                	if(system (befehl.toLatin1().data()))
                            befehl = "";
                        read_write_hd_1();
                       }
     	}
    return 0;
}

int DialogClone::questionMessage(QString frage)
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

void DialogClone::rdbutton_clone(){
	treeView_clone->setEnabled(false);
	bt_save->setText (tr("Clone Harddrive", "Festplatte klonen"));
        treeView_clone->setEnabled(false);
        //chk_zip->setHidden(true);
        chk_zip->setEnabled(false);
        listWidget->setHidden(true); 
        label_3->setHidden(false);
        lbl_hd->setText (tr("Exist harddrive", "Existierende Festplatte"));
        listWidget_exist->setHidden(false);
        listWidget_clone->setEnabled(true); 
        commandLinkButton_2->setEnabled(true); 
        commandLinkButton->setEnabled(true); 
        commandLinkButton_3->setEnabled(true); 
        commandLinkButton_4->setEnabled(true); 
        commandLinkButton_5->setEnabled(true); 
}

void DialogClone::rdbutton_image_save(){
	treeView_clone->setEnabled(true);
        bt_save->setText (tr("Save Harddrive Image", "Festplatten Abbild erstellen"));
        dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters_clone); 
        listWidget_exist->setHidden(false); 
        chk_zip->setEnabled(true);
        lbl_hd->setText (tr("Exist harddrive", "Existierende Festplatte"));
        label_3->setHidden(false);
        listWidget->setHidden(true);
        listWidget_clone->setEnabled(false); 
        commandLinkButton_2->setEnabled(false);
        commandLinkButton->setEnabled(false);
        commandLinkButton_3->setEnabled(false); 
        commandLinkButton_4->setEnabled(false); 
        commandLinkButton_5->setEnabled(false);   
}

void DialogClone::rdbutton_image_restore(){
	treeView_clone->setEnabled(true);
        bt_save->setText (tr("Write hard disk image back", "Festplatten Abbild zurückschreiben"));
        filters_clone << "*gz.fsa" << "*img.fsa" ;
   	dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters_clone); 
        listWidget_exist->setHidden(false); 
        chk_zip->setEnabled(false);
        lbl_hd->setText (tr("Exist harddrive", "Existierende Festplatte"));
        label_3->setHidden(false); 
        listWidget->setHidden(true);
        listWidget_clone->setEnabled(false); 
        commandLinkButton_2->setEnabled(false); 
        commandLinkButton->setEnabled(false);
        commandLinkButton_3->setEnabled(false); 
        commandLinkButton_4->setEnabled(false); 
        commandLinkButton_5->setEnabled(false);    
}

void DialogClone::rdbutton_partition_image_save(){
        treeView_clone->setEnabled(true);
        listWidget->setEnabled(true);
        listWidget_exist->setHidden(true); 
        label_3->setHidden(true); 
        lbl_hd->setText (tr("Save Partition Image", "Image einer Partition erstellen"));
        chk_zip->setEnabled(true);
        bt_save->setText (tr("Save Partition Image", "Partition Abbild erstellen"));
        listWidget->setHidden(false);
        dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters_clone); 
}

void DialogClone::rdbutton_partition_image_restore(){
        treeView_clone->setEnabled(true);
        listWidget->setEnabled(true);
        listWidget_exist->setHidden(true); 
        label_3->setHidden(true);  
        lbl_hd->setText (tr("Writing back the image of a partition", "Image einer Partition zurückschreiben"));
        chk_zip->setEnabled(false);
        bt_save->setText (tr("Writing back the image of a partition", "Partition Abbild zurückschreiben"));
        filters_clone << "*-part.fsa" << "*-gz.part.fsa" ;
   	dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters_clone); 
        listWidget->setHidden(false);
}

void DialogClone::listWidget_auslesen(){
QString befehl;
QString attribute;
QString text;
QString sdx[100];
QStringList dev_sdx;
long j = 0;
int row = 0;

QString filename = userpath_clone + "/.config/qt-fsarchiver/disk.txt";
QFile file(filename);
QTextStream ds(&file);
    row = listWidget->currentRow();
    mountpoint1 = row;
    img_partition_clone = part[row][0]; // z.B. sda1
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
          {
          attribute = "lsblk /dev/" + img_partition_clone + " -l -b 1> " +  filename;
          befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
         if(system (befehl.toLatin1().data()))
              befehl = "";
          while (text == "")
            {
             text = ds.readLine();
             QThread::msleep(5 * sleepfaktor);
            }
        text = ds.readLine();
         }
    file.close(); 
    dev_sdx = text.split(QRegExp("\\s+"));
    partition_exist_size_int = dev_sdx[3].toFloat()/1000000/1.024; //bei MB
    img_partition_size = QString::number(j);
           if (partition_exist_size_int >= 1000) //GB
               partition_exist_size_int = partition_exist_size_int /1.024;
           if (partition_exist_size_int >= 1000000)
               partition_exist_size_int = partition_exist_size_int /1.024;
           img_partition_size = QString::number(partition_exist_size_int);
}


//Mountpoint ermitteln
int DialogClone::mountpoint(int zahl)
{
        if (part[zahl][7] == "/")  // sys Partition gefunden
             {
             return 1;
             }
         if (part[zahl][7] == "/home") // home Partition gefunden
             {
             return 1;
             }
return 0;
}  


int DialogClone::mountpoint_disk(QString partition)
{
QString attribute;
QString befehl;
QString text;
QString filename;
int found = 0;
int found2 = 0;
QString dummy;
        filename = userpath_clone + "/.config/qt-fsarchiver/disk2.txt";
        QFile file(filename);
        QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
            attribute = "lsblk 1> " + filename;
            befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
            if(system (befehl.toLatin1().data()))
               befehl = "";
            while (text == "")
              {
               text = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
            while (!ds.atEnd())
      	    {
               text = ds.readLine();
               found = text.indexOf(partition);
               if (found > -1)
                  {
                  dummy = text.right(1); 
                  found2 = dummy.indexOf("/"); 
                  if(found2 == 0)
                     return 1; 
                  }
            }
        }
        return 0;
}   	 

void DialogClone::folder_einlesen() {
   QModelIndex index = treeView_clone->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder_clone =  (dirModel->filePath(index));
   int found = folder_clone.indexOf(" ");
      if (found > -1)
         folder_clone= "'" + folder_clone + "'"; 

}

int DialogClone::file_check() {
int found = 0;
QFileInfo info(folder_clone); 
    found=folder_clone.indexOf(" ");
    //Überprüfung bei vorhandener Leerstelle nicht möglich
    if (found == -1 and !info.isFile())
        {
        QMessageBox::about(this, tr("Note", "Hinweis"),
        tr("You have selected a directory. You must select a gz.fsa file.\n", "Sie haben ein Verzeichnis ausgewählt. Sie müssen eine gz.fsa Datei auswählen\n"));
        return 1 ;
        }
   return 0;
}


void DialogClone::ViewProzent()
{
int prozent = 0 ;
QString sekunde;
int sekunde_ = 0;
QString minute;
int minute_ = 0;
QString hour;
int hour_ = 0;
QString text_integer;
QString size;
int size_1 = 0;
QString letzte_zeile;
QString befehl;
int diff = 0;
QString mb_sec;
QString dummy;
float dummy1;
     if (endeThread_clone ==0)
     {
       QTimer::singleShot(1000, this, SLOT(ViewProzent()));
                // Prüfen, nach wieviel Sekunden ViewProzent erneut aufgerufen wird
       diff = sekunde_summe_clone - sekunde_summe_clone_1;
       sekunde_summe_clone_1 = sekunde_summe_clone;
       if (read_write_space_sec == "")  //Anzeige von read_write_hd gzip()
       { 
	size_clone = read_write_space_sum * sekunde_summe_clone; 
        if (size_clone_dummy > size_clone)
		size_clone=size_clone_dummy; //Verhindert, dass die bereits angezeigten gespeicherten Daten nicht reduziert werden
        size_clone_dummy = size_clone; 
        lbl_hd_size ->setText("MB");
        prozent = size_clone/(partition_exist_size_int)/10;
	prozent = 100 * size_clone/(partition_exist_size_int);
        if (prozent > 100)
            prozent = 100;
        savedBytes->setText("");
        size_1 = (int) size_clone;
        if (size_clone > 10000) 
            { 
            size_1 = size_1 / 1000;
            lbl_hd_size ->setText("GB");
            }
        size = QString::number(size_1);
        mb_sec = QString::number(read_write_space_sum, 'f',1);
        if (read_write_space_sum > 0)
        	bytes_sec ->setText(mb_sec);
        if (size_clone > 0) 
        	savedBytes->setText(size);
         // verhindert dass mehr gesicherte Bytes angezeigt werden als Festplattengröße
        if (size_clone > partition_exist_size_int)
            {
            dummy1 = partition_exist_size_int/1000;
            savedBytes->setText(QString::number(dummy1));
            }
        }
        if (read_write_space_sec != "")  //Anzeige von read_write_hd_1 dd()
        {
            bytes_sec ->setText(read_write_space_sec);
            savedBytes->setText(read_write_space_sum_);
            lbl_hd_size ->setText("MB");
            if (read_write_space_sum > 10000)
               {
               lbl_hd_size ->setText("GB");
               dummy = read_write_space_sum_.left(read_write_space_sum_.size() -3);
               savedBytes->setText(dummy);
               }
            if (read_write_space_sum > 10000000)
               {
               lbl_hd_size ->setText("TB");
               dummy = read_write_space_sum_.left(read_write_space_sum_.size() -6);
               savedBytes->setText(dummy);
               } 
               prozent = 100 *read_write_space_sum/(partition_exist_size_int);
            if (prozent > 100)
               prozent = 100;
            if (read_write_space_sum > partition_exist_size_int)
               savedBytes->setText(QString::number(partition_exist_size_int));
        } 
        this->repaint();
        elapsedTime();
       	progressBar->setValue(prozent);
        if (dummy_prozent_clone != prozent)
     		remainingTime(prozent);
 	else {
        	if (prozent >= 1)
       		{
        	// Sekunden nach unten zählen
        	sekunde = SekundeRemaining->text();
        	sekunde_ = sekunde.toInt();
        	minute = MinuteRemaining->text();
        	minute_ = minute.toInt();
                hour = HourRemaining->text();
        	hour_ = hour.toInt();
        		if (sekunde_ > 0)
        		{
            		sekunde_ = sekunde_ - diff;
                                if (sekunde_ < 0) 
                                    sekunde_ = 0; 
            			if (sekunde_ == 0) 
            			{
					if (minute_ > 0)
                			{		
					minute_ = minute_ - 1;
                			minute = QString::number(minute_); 
        				MinuteRemaining ->setText(minute);
                       			sekunde_ = 59;
                			}
					if (minute_ == 0 && sekunde == 0)
                			{		
					hour_ = hour_ - 1;
                			hour = QString::number(hour_); 
        				HourRemaining ->setText(hour);
                       			minute_ = 59;
                			}
	    			}
        }		
        sekunde = QString::number(sekunde_); 
        SekundeRemaining ->setText(sekunde);
	    } 
    } 
 dummy_prozent_clone = prozent;
        }
} 


void DialogClone::startThread1(int flag) {
QString befehl;
   if( thread1.isRunning())
      return;
   connect( &thread1, SIGNAL(finished()),
            this, SLOT( thread1Ready()));
   thread_run_clone = 1;
   thread1.start();
   bt_end->setEnabled(false);
   bt_save->setEnabled(false);
   // flag=0: Platte klonen, Image ohne zip schreiben
if (flag == 0)
   read_write_hd_1(); //Fortschrittsbalken
}

void DialogClone::startThread2(int flag) {
   if( thread2.isRunning() ) return;
   connect( &thread2, SIGNAL(finished()),
            this, SLOT( thread2Ready()));
   thread_run_clone = 2;
   thread2.start();
   bt_end->setEnabled(false);
   bt_save->setEnabled(false);
   // flag = 0: ungezipptes Image zurückschreiben
   if (flag == 0)
      read_write_hd_1(); //Fortschrittsbalken anzeigen
}

void DialogClone::closeEvent(QCloseEvent *event) {
   thread1.wait();
   thread2.wait();
   event->accept();
}

void DialogClone::thread1Ready()  {
QString befehl;
QString dummy;
float dummy1;
	endeThread_clone = endeThread_clone + 1;
        if (endeThread_clone > 0) {
 	    bt_end->setEnabled(true);
            progressBar->setValue(100);
       	    SekundeRemaining ->setText("0");
            MinuteRemaining ->setText("0");
            HourRemaining ->setText("0");
            dummy1= partition_exist_size_int;
            lbl_hd_size ->setText("MB");
            savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
            if (dummy1 > 1000)
               {
                partition_exist_size_int = partition_exist_size_int / 1000; 
                lbl_hd_size ->setText("GB");
                savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
               }
            if (dummy1 > 1000000)
               {
               partition_exist_size_int = partition_exist_size_int / 1000000;
               lbl_hd_size ->setText("TB");
               savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
               } 
            if (flag_clone==1 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The cloning of the hard disk was successful.", "Das Klonen der Festplatte war erfolgreich.\n"));
            if (flag_clone==2 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was successful.", "Das Sichern des Abbildes der Festplatte war erfolgreich.\n"));
            if (flag_clone==3 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup of the image of the partition was successful.", "Das Sichern des Abbildes der Partition war erfolgreich.\n"));
            if (flag_clone==1 && dialog_auswertung != 0){
            	progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The cloning of the hard disk was not successful.", "Das Klonen der Festplatte war nicht erfolgreich.\n"));
            }
            if (flag_clone==2 && dialog_auswertung != 0)
                {
                progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was not successful.", "Das Sichern des Abbildes der Festplatte war nicht erfolgreich.\n"));
		}
            if (flag_clone==3 && dialog_auswertung != 0)
                {
                progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("Saving the image of the partition was not successful.", "Das Sichern des Abbildes der Partition war nicht erfolgreich.\n"));
		}
        }
	thread_run_clone = 0;
	thread1.exit();
        befehl = "/usr/sbin/qt-fsarchiver.sh  5 " + userpath_clone + "/.config/qt-fsarchiver *.txt 2>/dev/null";
        if(system (befehl.toLatin1().data()))
           befehl = "";
        sekunde_summe_clone = 0;
        minute_elapsed_clone = 0;
        hour_elapsed_clone = 0;
        this->setCursor(Qt::ArrowCursor);
}

void DialogClone::thread2Ready()  {
QString befehl;
QString dummy;
float dummy1;
        extern int dialog_auswertung;
	endeThread_clone = endeThread_clone + 1;
        if (endeThread_clone > 0) {
	           bt_end->setEnabled(true);
            //bt_save->setEnabled(true);
      	    progressBar->setValue(100);
       	    SekundeRemaining ->setText("0");
            MinuteRemaining ->setText("0");
            HourRemaining ->setText("0");
            dummy1= partition_exist_size_int;
            partition_exist_size_int = partition_exist_size_int; 
            lbl_hd_size ->setText("MB");
            savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
            if (dummy1 > 1000)
               {
                partition_exist_size_int = partition_exist_size_int / 1000; 
                lbl_hd_size ->setText("GB");
                savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
               }
            if (dummy1 > 1000000)
               {
               partition_exist_size_int = partition_exist_size_int / 1000000;
               lbl_hd_size ->setText("TB");
               savedBytes->setText(QString::number(partition_exist_size_int,'f',2));
               } 
            if (flag_clone==4 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The hard disk image recovery was successful.", "Die Wiederherstellung des Abbildes der Festplatte war erfolgreich."));
            if (flag_clone==5 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The recovery of the partition image was successful.", "Die Wiederherstellung des Abbildes der Partition war erfolgreich."));
            if (flag_clone==4 && dialog_auswertung != 0){
                progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("Hard disk image recovery was not successful.", "Die Wiederherstellung des Abbildes der Festplatte war nicht erfolgreich."));
                }
            if (flag_clone==5 && dialog_auswertung != 0){
                progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The recovery of the partition image was not successful.", "Die Wiederherstellung des Abbildes der Partition war nicht erfolgreich."));
                }
	}
        thread_run_clone = 0; 
        thread2.exit();	
        befehl = "/usr/sbin/qt-fsarchiver.sh  5 " + userpath_clone + "/.config/qt-fsarchiver *.txt 2>/dev/null";
        if(system (befehl.toLatin1().data()))
            befehl = "";
        progressBar->setValue(100);
        if (dialog_auswertung != 0) 
           progressBar->setValue(0);
        
        sekunde_summe_clone = 0;
        minute_elapsed_clone = 0;
        hour_elapsed_clone = 0;
        this->setCursor(Qt::ArrowCursor);
 }


void DialogClone::elapsedTime()
 {
    sekunde_elapsed_clone = sekunde_elapsed_clone + 1; 
    sekunde_summe_clone  = sekunde_summe_clone + 1; 
    if (sekunde_elapsed_clone == 60) {
        sekunde_elapsed_clone = 0 ;
        minute_elapsed_clone = minute_elapsed_clone + 1;
       }
    if (minute_elapsed_clone == 60) {
        minute_elapsed_clone = 0 ;
        hour_elapsed_clone = hour_elapsed_clone + 1;
       }
    QString sekunde_ = QString::number(sekunde_elapsed_clone);
    SekundeElapsed ->setText(sekunde_);
    QString minute_ = QString::number(minute_elapsed_clone);
    MinuteElapsed ->setText(minute_);
    QString hour_ = QString::number(hour_elapsed_clone);
    HourElapsed ->setText(hour_);
}

void DialogClone::remainingTime(int prozent)
 {
    if (prozent >= 1) {
       float remaining_time =(100 * sekunde_summe_clone/prozent)-sekunde_summe_clone;
       int dummy = (int)remaining_time;
       int hour_remaining = (int)(remaining_time/3600);
       QString hour_ = QString::number(hour_remaining);
       HourRemaining ->setText(hour_);
       int min_remaining = (dummy % 3600)/60;
       QString minute_ = QString::number(min_remaining);
       MinuteRemaining ->setText(minute_);
       int sek_remaining = (dummy % 60);
       QString sekunde_ = QString::number(sek_remaining);
       SekundeRemaining ->setText(sekunde_);
    }
}

void DialogClone::keyPressEvent(QKeyEvent *event) {
     QWidget::keyPressEvent(event);
     switch( event->key() ) {
         case Qt::Key_Escape:
              	esc_end(); 
         break;
     }
}

void DialogClone::esc_end()
{
QString befehl;
QString attribute;

   pid_2_ermitteln();
   int ret = questionMessage(tr("Do you want really break clone, save or restore an image from the partition?", "Wollen Sie wirklich das Klonen der Festplatte, die Erstellung oder die Wiederherstellung eines Images der Festplatte beenden?"));
      if (ret == 1)
        {
        attribute = "kill -15 " + pid_2_dd[0];;  //dd abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  
        if(system (befehl.toLatin1().data()))
           befehl = "";
        attribute = "kill -15 " + pid_2_dd[1];;  //dd abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  
        if(system (befehl.toLatin1().data()))
            befehl = "";
        attribute = "rm " + folder_clone +  partition_name + ".gz.fsa 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        attribute = "rm " + folder_clone +  partition_name + ".img.fsa 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        attribute = "rm " + folder_clone +  partition_name + ".gz.part.fsa 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
    	close();
        }
}

void DialogClone::pid_2_ermitteln()
{
QString befehl;
QString pid_nummer;
QStringList pid;
int i = 0;
int k = 0;

      QString filename = userpath_clone + "/.config/qt-fsarchiver/pid_2.txt";
      QFile file(filename);
      if (file.exists())
      {
         befehl = "rm " + filename;
         if(system (befehl.toLatin1().data()))
             befehl = "";
      }  
      QTextStream ds(&file);
      if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
            befehl = "ps -aux  1> " +  userpath_clone + "/.config/qt-fsarchiver/pid_2.txt";
            if(system (befehl.toLatin1().data()))
                befehl = "";
            while (pid_nummer == "")
              {
               pid_nummer = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
      	    while (!ds.atEnd())
      	    {
            pid_nummer = ds.readLine();
 	    if (pid_nummer.indexOf("dd if=") >= 0)  // dd Prozess gefunden
               {
      	       pid_2_dd[i] = pid_nummer;
               i = i +1;
               }
   	       if(pid_nummer.isEmpty() )
         	 break;
         }
   	file.close();
     }
        befehl = "rm " + filename;
        if(system (befehl.toLatin1().data()))
           befehl = "";
        pid_nummer = pid_2_dd[0];
        do{
    	   k=pid_nummer.indexOf("  ");
	   if (k > 0)
              pid_nummer.replace("  ", " ");
	   }
	while  (k >= 0);
	     pid = pid_nummer.split(" ");
             pid_2_dd[0] = pid[1];
        pid_nummer = pid_2_dd[1];
        do{
    	   k=pid_nummer.indexOf("  ");
	   if (k > 0)
              pid_nummer.replace("  ", " ");
	   }
	while  (k >= 0);
	     pid = pid_nummer.split(" ");
             pid_2_dd[1] = pid[1];
}


QString DialogClone::pid_ermitteln(QString prozess)
{
QString befehl = "";
QString pid_nummer = "";
QStringList pid;
QString filename_1 = folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa";
QString filename = userpath_clone + "/.config/qt-fsarchiver/pid.txt";
QFile file(filename);
QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "ps -C " + prozess + " 1> " + filename;
           if(system (befehl.toLatin1().data()))
              befehl = "";

            while (pid_nummer == "")
              {
               pid_nummer = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
        pid_nummer = ds.readLine();
        }
        file.close();
        if (pid_nummer != "")
        {
           pid_nummer = pid_nummer.trimmed(); 
           pid = pid_nummer.split(" ");
           pid_nummer = pid[0]; 
        }
        return pid_nummer;
}


void DialogClone::read_write_hd(){
//verarbeite qzip
QString teilstring = "";
QString befehl = "";
QString harddrive;
int  i = 0;
QStringList read_write;
QString rw_;
QString rw_1;
int read_write_space = 0;
int found = 0;

       
       if (endeThread_clone !=0)
            return;
       read_write_space= 0;
       if (partition_exist_size_int < 20000 )
       		QTimer::singleShot(3000, this, SLOT(read_write_hd()));
       if (partition_exist_size_int > 20000 )
       		QTimer::singleShot(9950, this, SLOT(read_write_hd()));
       read_write_counter = read_write_counter +1;
       if (read_write_counter == 10){
	    read_write_counter = 0;
            read_write_counter_1 = read_write_counter_1 +1;}
        if (sekunde_elapsed_clone < 59)
        	sekunde_elapsed_clone = sekunde_elapsed_clone +1;
        if (sekunde_elapsed_clone < 59)
        	sekunde_elapsed_clone = sekunde_elapsed_clone +1;
        sekunde_summe_clone  = sekunde_summe_clone + 2;
 	QString filename = userpath_clone + "/.config/qt-fsarchiver/disk.txt";
	QFile file(filename);
        QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
            befehl = "vmstat 2 2 1> " +  userpath_clone + "/.config/qt-fsarchiver/disk.txt";
            if(system (befehl.toLatin1().data()))
               befehl = "";
            while (teilstring == "")
              {
               teilstring = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
   	   teilstring = ds.readLine();
           teilstring = ds.readLine();
           teilstring = ds.readLine();
        }
        file.close();
      	do{
    		found=teilstring.indexOf("  ");
		if (found > 0){
             	    teilstring.replace("  ", " ");

		}
	}
	while  (found >= 0);
        read_write = teilstring.split(" ") ;

        if (rdbt_image_save->isChecked() or rdbt_partition_save->isChecked()){
        	rw_ = read_write[9];  // 10=bo 9=bi Auswertung geschriebene Blöcke
                rrw[read_write_counter]= 0.98 * rw_.toInt();}  //1.1 Erfahrungsfaktor
	if (rdbt_image_restore->isChecked() or rdbt_partition_restore->isChecked()){
                rw_ = read_write[10];  // 10=bo 9=bi  Auswertung gelesene Blöcke
          	rrw[read_write_counter]= 0.98 * rw_.toInt();}  //1.1 Erfahrungsfaktor
         if (read_write_counter == 9) {
         //Summe bzw Schnitt bilden der ersten 10 ermittelten Werte
         for (i=0; i< 10; i++){
             read_write_space = read_write_space + rrw[i];
             }
             read_write_space = read_write_space / 10000.0;
             read_write_space_summe = read_write_space_summe + read_write_space;
             // Durchschnitte errechnen write/read bytes je Sekunde
             read_write_space_sum = read_write_space_summe /read_write_counter_1;
             read_write_space = 0;
       lbl_B_sec ->setText("MB/sec");
   }
}

void DialogClone::read_write_hd_1() // mit dd kopieren
{
// mit dd ungezipt verarbeiten
QString befehl;
QString bytes_;
QStringList bytes;
int size = 0;
QString attribute;
QString filename = userpath_clone + "/.config/qt-fsarchiver/disk.txt";
	if (endeThread_clone !=0)
            return;
        while (pid_dd.size() < 4)
            { 
            pid_dd = pid_ermitteln("dd"); 
            size = pid_dd.size();
            //dd startet nicht da beispielsweise ein Umlaut in dem Sicherungsverzeichnis vorhanden ist.
            // dd kann mit Umlauten nicht arbeiten
            if (size == 0)   
               {
               error = "1";
               return;
               }
            }
        QTimer::singleShot(9800, this, SLOT(read_write_hd_1()));  //10 sekunden
        // Wird für den Fortschrittsbalken benötigt
        if (pid_dd != "")
        {
        attribute = "kill -USR1 " + pid_dd ;
        befehl = "/usr/sbin/qt-fsarchiver.sh  10 " + attribute; 
        if(system (befehl.toLatin1().data()))
           befehl = "";
        } 
	QFile file(filename);
        if(file.size() == 0)
           return;
        anzahl_bytes_ = file.size();
        QTextStream ds(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text); 
            while (bytes_ == "")
              {
               bytes_ = ds.readLine();
               QThread::msleep(5 * sleepfaktor);
               }
          while (!ds.atEnd())
      	     bytes_ = ds.readLine();
    	file.close();
        if (bytes_ != ""){
           pid_dd = pid_ermitteln("dd");
           bytes = bytes_.split(" ");
           bytes_ = bytes[0];
           if(pid_dd == 0)
              {
              endeThread_clone = 1;
              dialog_auswertung = 0;
              if (flag_clone == 3 or flag_clone == 2 or flag_clone == 1)
                 thread1Ready();
              if (flag_clone == 5 or flag_clone == 4)
                 thread2Ready();
              }
           size = bytes_.size();
           if(size > 7)
           {
           read_write_space_sum_ =  bytes_.left(bytes_.size() -6);
           read_write_space_sum = read_write_space_sum_.toFloat();
           read_write_space_sum = qRound(read_write_space_sum);
           read_write_space_sum_ = QString::number(read_write_space_sum);
           read_write_space_sec = bytes[9];
           lbl_B_sec ->setText(bytes[10]);
           }
        }
}

QString DialogClone::Zeit_auslesen_clone(){
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
    _Datum_clone = Datum_akt.setNum(Tag) + "-" ; 
    _Datum_clone = _Datum_clone + Datum_akt.setNum(Monat) + "-" ;
    _Datum_clone = _Datum_clone + Datum_akt.setNum(Jahr) ;
    return _Datum_clone;
}

void DialogClone::folder_expand() {
   QModelIndex index = treeView_clone->currentIndex();
   treeView_clone->expand(index);
}

int DialogClone::testen(QString filename) {
    QThread::msleep(10 * sleepfaktor);
    QFile file(filename);
    if (file.exists()) {
      //qDebug() << "Datei vorhanden" << filename;
      return 0;
    }
    else
    {
    // qDebug() << "Datei nicht vorhanden" << filename;
      return 1;
    }
}

int DialogClone::testen_1(QString filename, QString partition, int flag) {
QString attribute;
QString befehl;
QString folder_;
int i = 0;
int j[10];
int k = 0;
int found = 0;
       if (flag == 1 or flag == 3)
          {
          folder_ = filename;
          found = folder_.indexOf("/");
          while (found > -1)
             {
             found = folder_.indexOf("/");
             if(found > -1)
                {
                j[i] = found;
                i++;
                folder_.replace(found, 1, "+");
                }
              }
          k = filename.size() - j[i-1];
          filename = filename.left(filename.size() - k); 
          }
       attribute = "if=/dev/" + partition + " of=" + filename + "/test bs=512 count=1";
       if (flag == 2 or flag == 3)
          attribute = "if=/" + partition + " of=" + filename + "/test bs=512 count=1";
       befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + attribute;
       if(system (befehl.toLatin1().data()))
              befehl = "";
      i = testen(filename + "/test");
      attribute = "rm " + filename + "/test";
      befehl = "/usr/sbin/qt-fsarchiver.sh 10 " + attribute;
      if(system (befehl.toLatin1().data()))
          befehl = "";
      return i;
}

void DialogClone::beschreibungstext_clone(QString text, int zip, int row)  {
FileDialog filedialog; //Create the main widget; 

QString part_size_;
QString part_size_compress;
float part_size;
QString Linuxversion;
QString ubuntu_root;
QString ubuntu_home;
QString compress;
QString kernel;
QString dummy;
QString dummy1;
int pos = 0;
QString zip_zstd_;
      part[row][4] = sdx3_clone_einlesen(part[row][0],0, row);
      part[row][5] = sdx3_clone_einlesen(part[row][0],1, row);
      dummy = part_clone[row][2];
      // Komma in Punkt ändern
        pos=dummy.indexOf(",");
           if (pos > 0)
        	dummy.replace(pos, 1, "."); 
      if(zip == 3)
         {
         part_size = dummy.toFloat();
         part_size = part_size * 0.44;
         part_size = part_size*100;
         part_size = round(part_size);
         part_size = part_size/100;
         part_size_compress = QString::number(part_size) + " " + part_clone[row][3];
         compress = tr("gzip-standard", "gzip-standard");
         } 
      if(zip == 0)
          {
          compress =  tr("No compression", "keine Kompressiom");
          part_size_compress = part_clone[row][2] + " " + part_clone[row][3]; 
          }
        text = tr("Backup file name: ", "Sicherungsdateiname: ") + text + "\n" + 
	tr("Partition  name: ", "Partitionsname: ")  
	+ part[row][0] + "\n" + tr("Partition type: ", "Partitionsart: ") 
       	+ part[row][1] + "\n" + tr("UUID: ") +  part[row][3] + "\n" + tr("Description: ", "Bezeichnung: ") + part[row][6] + "\n" + 
       	tr("Partition size: ", "Partitionsgröße: ") + part[row][2] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + 
       	part[row][4] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + part[row][5]  + "\n" + tr("Compression: ", "Kompression: ") + compress + "\n" + 
       	tr("Approximate image file sizes: ", "ungefähre Sicherungsdateigröße: ") + part_size_compress + "\n" + "\n" + tr("Other notes: ", "weitere Hinweise:");
        ubuntu_root = tr("to be protected/secured partition: / (root system directory) ", "zu sichernde / gesicherte Partition: / (Wurzel-Systemverzeichnis) ");
       // int part_art_clone = mountpoint_disk(part_clone[row][0]);
	if (part[row][7] == "/"){
		Linuxversion = linux_version_clone();
                kernel = kernel_version_clone();
                text = ubuntu_root + "\n" + tr("Operating system: ", "Betriebsystem: ") + Linuxversion + "\n" + tr("Kernel: ") + kernel + " " + "\n" + text + "\n";
	}
	ubuntu_home = tr("to be protected/secured partition: /home", "zu sichernde/gesicherte Partition: /home");
	if (part[row][7] == "/home"){
	   text = ubuntu_home + "\n" + text + "\n";
	}
	filedialog.werte_uebergeben(text);
        
}

QString DialogClone::sdx3_clone_einlesen(QString part_, int flag, int row)
{
QString text;
QString text1;
QString befehl;
QString dummy;
QStringList dev_sdx;
float part_size;
         QString filename = userpath_clone + "/.config/qt-fsarchiver/disk3.txt";
         QFile file(filename);
         QTextStream ds(&file);
         dummy = "/dev/" + part_;
         if (part[row][7] == "") // ist nicht gemounted, somit ist das Ergenis von df nicht korrekt
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
              text1 = part_size;
              text1 = format_clone(part_size); //Belegung absolut Größe geteilt durch mehrfaches 1,024 
              }
           if (flag == 1)
              text1 = dev_sdx[4]; //Belegung in %
           }
           file.close();
           return text1;
}

QString DialogClone::format_clone(float zahl)
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

QString DialogClone::kernel_version_clone()  {
QStringList kernel;
QString kernel_;
QString befehl;
	befehl = "uname -a 1> " +  userpath_clone + "/.config/qt-fsarchiver/kernel.txt";
        if(system (befehl.toLatin1().data()))
            befehl = "";
        QString filename = userpath_clone + "/.config/qt-fsarchiver/kernel.txt";
	QFile file(filename);
        QTextStream ds(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text); 
        while (kernel_ == ""){
            kernel_ = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
         file.close();
         kernel = kernel_.split(" ");
         if (kernel_.indexOf("Debian") > -1)         
		return kernel[0] + " " + kernel[2] ;
         else
		return kernel[0] + " " + kernel[2] +  " " + kernel[11];
}

QString DialogClone::linux_version_clone()  {
QString befehl;
QString Linuxversion;
QString text;
	befehl = "cat /etc/*release 1> " +  userpath_clone + "/.config/qt-fsarchiver/version.txt";
        if(system (befehl.toLatin1().data()))
           befehl = "";
        QString filename = userpath_clone + "/.config/qt-fsarchiver/version.txt";
        QFile file(filename);
        QTextStream ds(&file);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        Linuxversion = "xxx"; //damit die erste Zeile ausgewerted wird
                   while (Linuxversion != ""){
                    Linuxversion = ds.readLine();
                    if (Linuxversion.indexOf("PRETTY_NAME") > -1) 
                        {  //Debian
                        Linuxversion = Linuxversion.right(Linuxversion.size() -13);
                        Linuxversion = Linuxversion.left(Linuxversion.size() -1);
                        break;
                        }
                    if (Linuxversion.indexOf("DISTRIB_DESCRIPTION=")>0)
                        {
                        Linuxversion=Linuxversion.right(Linuxversion.size()-20);
                        break;
                        }
                   QThread::msleep(5 * sleepfaktor);
                 }
         file.close();
         befehl = "rm " + filename;
         if(system (befehl.toLatin1().data()))
               befehl = "";
         return Linuxversion;
  
}



