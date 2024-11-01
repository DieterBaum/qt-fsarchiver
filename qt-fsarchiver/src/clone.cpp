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
#include <QMessageBox> 
#include "clone.h"
#include <string.h>
#include <unistd.h>
#include "mainWindow.h"
#include "filedialog.h"

extern int anzahl_disk;
extern int live_flag;
extern int dialog_auswertung;
int zaehler_2;
QStringList filters_clone;
QString part_clone[100][4];
extern QString part[100][10];
QString clone_part[100][10];
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
extern int sleepfaktor;
QString homepath = QDir::homePath();
QString folder_file_1;
extern QString folder_file_;
int esc_end_flag;
QString bytes_;
int listwidget_exist_read = 0;
int listwidget_clone_read = 0;
float size_folder_float_clone;
float part_size_compress_float_clone;
QString part_size_compress_clone;
QString size_folder_clone;
int live_flag_clone = 0;

DialogClone::DialogClone()
{
        setupUi(this); // this sets up GUI
	connect( bt_save, SIGNAL( clicked() ), this, SLOT(todo()));
        connect( rdbt_clone, SIGNAL( clicked() ), this, SLOT(rdbutton_clone())); 
	connect( rdbt_image_save, SIGNAL( clicked() ), this, SLOT(rdbutton_image_save())); 
        connect( rdbt_image_restore, SIGNAL( clicked() ), this, SLOT(rdbutton_image_restore()));
        connect( rdbt_partition_save, SIGNAL( clicked() ), this, SLOT(rdbutton_partition_image_save()));
        connect( rdbt_partition_restore, SIGNAL( clicked() ), this, SLOT(rdbutton_partition_image_restore()));
        connect( bt_end, SIGNAL( clicked() ), this, SLOT(esc_end()));
        connect( pushButton_folder, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
        connect( pushButton_folder_2, SIGNAL( clicked() ), this, SLOT(folder_expand()));
        connect( pushButton_partition, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        connect( pushButton_partition_2, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        connect( pB1, SIGNAL( clicked() ), this, SLOT(listWidget_exist_auslesen()));
        connect( pB2, SIGNAL( clicked() ), this, SLOT(listWidget_clone_auslesen()));
        connect( pB1_2, SIGNAL( clicked() ), this, SLOT(listWidget_exist_auslesen()));
        connect( pb2_2, SIGNAL( clicked() ), this, SLOT(listWidget_clone_auslesen()));
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
        format_Disk();
        bt_save->setText (tr("Clone Harddrive", "Festplatte klonen"));
        timer_clone = new QTimer(this);
        timer_read_write = new QTimer(this);
       // Erforderlich um Textdatei vor dem ersten Auslesen mit 3 Zeilen zu füllen
        QString befehl = "vmstat 1 2 1> " +  homepath + "/.config/qt5-fsarchiver/disk.txt";
        if(system (befehl.toLatin1()))
           befehl = "";
        chk_zip->setEnabled(false);
        chk_zip->setChecked(true);
        //chk_zip->set| grepHidden(true);
        listWidget->setHidden(true);
        addWidget(); 
        chk_Beschreibung->setEnabled(false);
        chk_Beschreibung->setChecked(true); 
        lbl_hd->setText (tr("Exist harddrive", "Existierende Festplatte"));
        chk_Beschreibung->setEnabled(false);
        esc_end_flag = 0;
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
       befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk.txt 2>/dev/null"; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        filename = homepath + "/.config/qt5-fsarchiver/disk2.txt";
        QFile file(filename);
        QTextStream ds(&file);
             if(file.open(QIODevice::ReadWrite | QIODevice::Text))
               {
               befehl = "lsblk -l 1> " +  homepath + "/.config/qt5-fsarchiver/disk2.txt";
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
        filename1 = homepath + "/.config/qt5-fsarchiver/disk1.txt";
        QFile file1(filename1);
        QTextStream ds1(&file1);
         text = "";
          if(file1.open(QIODevice::ReadWrite | QIODevice::Text))
               {
              befehl = "lsblk -l -b 1> " +  homepath + "/.config/qt5-fsarchiver/disk1.txt";
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
           dev_sdx = dev_sdx_.split(QRegularExpression("\\s+"));
           size = dev_sdx.size();
           if(size >= 5)
              {
              if(dev_sdx[5] == "disk")
                 {
                 part_clone[j][0] = dev_sdx[0]; //Diskname
                 part_clone[j][1] = dev_sdx[3]; //size
                 dummy = part_clone[j][1].right(1);
                 part_clone[j][1] = part_clone[j][1].left(part_clone[j][1].size()-1);
                 part_clone[j][1] = part_clone[j][1] + " " + dummy + "B";
                 _dev_sdx_ = sdx_[k];
                 _dev_sdx = _dev_sdx_.split(QRegularExpression("\\s+"));
                 part_clone_[j] = _dev_sdx[3].toFloat();
                 j++;
                 }
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

void DialogClone::addWidget() {
extern QString add_part[100];
int i = 1;
QString dummy;
QStringList dev_sdx;
QString dev_sdx_;
    while (add_part[i] != "")
    {
	listWidget->addItem (add_part[i]);
	dummy = add_part[i];
        dev_sdx_= dummy;
        dev_sdx = dev_sdx_.split(QRegularExpression("\\s+"));
        part_clone[i][2] = dev_sdx[2]; // size
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
QString befehl;
QString attribute;
int ret = 0;
int zip = 0;
int row = 0;
int found = 0;
int result = 0;
Qt::CheckState state1;
Qt::CheckState state;
chk_Beschreibung->setEnabled(true);
_Datum_clone = Zeit_auslesen_clone();
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
    int part_art_clone = mountpoint(img_partition_clone);
    if (part_art_clone == 1 or part_art_clone == 2){
       ret = questionMessage(tr("There is a root or home partition. Do you want to continue?", "Es ist eine root- oder home Partition vorhanden. Wollen Sie fortfahren?\n"));
       }
       if (ret == 2)
          return 0;
       if (state == Qt::Checked)
          {
          zip = 3; 
          folder_file_ = folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.txt";
          found = folder_clone.indexOf(" ");
 	  if(found > -1)
 	     folder_clone = "'" + folder_clone + "'";
 	  befehl = "dd if=/dev/" + img_partition_clone + " | gzip --best > " + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.fsa";  
 	  thread1.setValues( 0,befehl);
          }
       else
          {
          zip = 0; 
          folder_file_ = folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.txt";
          found = folder_clone.indexOf(" ");
 	  if(found > -1)
 	     folder_clone = "'" + folder_clone + "'";
 	  befehl = "dd if=/dev/" + img_partition_clone + " of=" + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa bs=1M 2>" + homepath + "/.config/qt5-fsarchiver/disk.txt";   
          }
          thread1.setValues( 0,befehl);
          ret = questionMessage(tr("Do you really want to create an image of a partition?  ", " Wollen Sie wirklich ein Abbild einer Partition erstellen? ") ); 
               if (ret == 2)
                 return 0;
              if (ret == 1)
                {
               	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
              	ViewProzent();
              	row = listWidget->currentRow();
              	// Ermittlung freierSpeicherplatz im Sicherungspfad 
              	size_determine_clone("", folder_clone);
              	beschreibungstext_clone(folder_file_, zip, row, size_folder_clone, folder_clone);
              	state1 = chk_Beschreibung->checkState();
	        if (state1 == Qt::Checked)
                  {
                  FileDialog Filedialog;
     	     	  FileDialog *dlg = new FileDialog;
     	     	  dlg->exec();
     	     	  if (dialog_auswertung == 7)
                      {
                      QMessageBox::warning(this, tr("Note", "Hinweis"),
         	      tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
                      bt_end->setEnabled(true);
		      return 0;
                      }
                  }
                result = size_determine_clone(part_size_compress_clone, folder_clone);  
                if(result == 2)  
              	   {
                   QMessageBox::about(this,tr("Note", "Hinweis"),
         	   tr("There is not enough space on the hard disk for the backup. The backup is canceled.", "Auf der Festplatte ist nicht genügend Platz für die Sicherung vorhanden. Die Sicherung wird abgebrochen.\n"));
         	   esc_end1(0);
		   return 0;
               	   }   
                this->setCursor(Qt::WaitCursor);
		if (state == Qt::Checked)
		   {
		   read_write_hd();
		   startThread1(1);
                   }
                else 
                   {
                   startThread1(0);
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
QString befehl;
int pos = 0;
int pos1 = 0;
int found = 0;
QString partition_exist;
QString partition_exist_size;
QString part_name;
QString attribute;
QString filename;
chk_Beschreibung->setEnabled(false);
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
    int part_art_clone = mountpoint(img_partition_clone);
    if (part_art_clone == 1 or part_art_clone == 2){
       QMessageBox::warning(this, tr("Note", "Hinweis"), tr("There is a root or home partition on the hard disk. You must use a live DVD.", "Auf der Festplatte ist eine root- oder home Partition. Sie müssen eine Live-CD benutzen.\n"));
	return 0;
	}
	partition_name  = partition_exist.right(partition_exist.size() -4);
        folder_file_ = folder_clone;
 	filename = folder_clone + ".txt";
 	//Prüfen ob img.fsa oder gz.fsa Datei
 	found = folder_clone.indexOf(" ");
 	  if(found > -1)
 	     folder_clone = "'" + folder_clone + "'";
        if (folder_clone.indexOf("-gz.part.fsa") > -1)
            befehl = "gunzip -c " + folder_clone + " | sudo dd of=/dev/" + img_partition_clone; 
        if (folder_clone.indexOf("-part.fsa") > -1)
            befehl = "dd if=" + folder_clone +  " of=/dev/" +  img_partition_clone + " bs=1M  2>" + homepath + "/.config/qt5-fsarchiver/disk.txt";
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
                this->setCursor(Qt::WaitCursor);
                pos = folder_clone.indexOf("gz.part");
		if (pos > 0)
		   {
                   read_write_hd(); //mit gzip wiederherstellen
		   startThread2(1);
		   }
                else 
                    {
                    //mit dd wiederherstellen 
                    startThread2(0);
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
chk_Beschreibung->setEnabled(false);
lbl_save->setText (tr("already saved", "bereits gesichert"));
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
      if(listwidget_exist_read == 1 or listwidget_clone_read == 0){
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
       befehl = "dd if=" + partition_exist + " of=" + partition_clone + " bs=1M 2>" + homepath + "/.config/qt5-fsarchiver/disk.txt"; 
       
       ret = questionMessage(tr(" Do you want really clone the hard drive? All dates on  ", " Wollen Sie wirklich die Festplatte klonen? Alle Daten auf der Festplatte ")   + partition_clone + tr(" are deleted!", " werden gelöscht!") );
       if (ret == 2)
          return 0;
       thread1.setValues(0,befehl);   
       ViewProzent();
       this->setCursor(Qt::WaitCursor);
       endeThread_clone = 0;
       startThread1(0);
       read_write_hd_1();
       return 0;
}

int DialogClone::do_image()  //Image einer Festplatte erzeugen
{
_Datum_clone = Zeit_auslesen_clone();
QString befehl;
int row;
int ret = 0;
int found = 0;
int result = 0;
QString partition_exist;
QString attribute;
QString dummy;
QString disk_size;
QString partition_exist_size;
Qt::CheckState state;
chk_Beschreibung->setEnabled(false);
      lbl_save->setText (tr("already saved", "bereits gesichert"));
      state = chk_zip->checkState();
      flag_clone = 2;
      row = listWidget_exist->currentRow();
      if (row > -1){
          partition_exist = "/dev/" + part_clone[row][0] ;
          partition_exist_size_int = part_clone_[row]/1000000;
       }
       disk_size = part_clone[row][1];
     if (listwidget_exist_read == 1){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a hard drive.", "Sie müssen eine Festplatte auswählen.\n"));
	return 0;        
	}
    if (folder_clone == "" ){
    	QMessageBox::about(this, tr("Note", "Hinweis"), tr("You must select a folder.", "Sie müssen ein Verzeichnis auswählen.\n"));
	return 0;        
	}
    // Überprüfen, ob System oder Home-Partition auf der Festplatte vorhanden ist
         int part_art_clone = mountpoint_disk(part_clone[row][0]);
         if (part_art_clone == 1 or part_art_clone == 2){
         ret = questionMessage(tr("There is a root or home partition on the hard disk. Do you want to continue?", "Auf der Festplatte ist eine root- oder home Partition. Wollen Sie fortfahren?\n"));
        live_flag_clone = 1;
        }
        if (ret == 2)
          return 0; 
	partition_name  = partition_exist.right(partition_exist.size() -4);
	found = folder_clone.indexOf(" ");
 	if(found > -1)
 	     folder_clone = "'" + folder_clone + "'";
        if (state == Qt::Checked)
           befehl = "dd if=" + partition_exist + " | gzip --best > " + folder_clone +  partition_name + "-" + _Datum_clone + ".gz.fsa";
        else
           befehl = "dd if=" + partition_exist + " of=" + folder_clone +  partition_name + "-" + _Datum_clone + ".img.fsa bs=1M 2>" + homepath + "/.config/qt5-fsarchiver/disk.txt"; 
 	thread1.setValues( 0,befehl);
	ret = questionMessage(tr("Do you really want to create an image of the hard disk?", " Wollen Sie wirklich ein Abbild der Festplatte erstellen? ") );  
              if (ret == 2)
                 return 0;
              if (ret == 1)
                {
                // Hier muss die Größe der festplatte ermittelt werden
                result = size_determine_clone(disk_size, folder_clone);  
                if(result == 2)  
              	   {
                   QMessageBox::about(this,tr("Note", "Hinweis"),
         	   tr("There is not enough space on the hard disk for the backup. The backup is canceled.", "Auf der Festplatte ist nicht genügend Platz für die Sicherung vorhanden. Die Sicherung wird abgebrochen.\n"));
         	   esc_end1(0);
		   return 0;
               	   }  
              	bt_end->setEnabled(false);
            	bt_save->setEnabled(false);
              	ViewProzent();
                this->setCursor(Qt::WaitCursor);
		if (state == Qt::Checked)   //mit gzip schreiben
		    {  
		    read_write_hd();
		    startThread1(1);
		    }
                else 
                    {
                    startThread1(0);  // mit dd schreiben
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
int row = 0;
int pos = 0;
int pos1 = 0;
int found = 0;
QString partition_save;
QString partition_exist;
QString partition_exist_size;
QString attribute;
QString dummy;
QString disk_name;
chk_Beschreibung->setEnabled(false);
      lbl_save->setText (tr("already written back.", "bereits zurückgeschrieben"));
      chk_zip->checkState();
      flag_clone = 4;
      row = listWidget_exist->currentRow();
      row = listWidget_exist->currentRow();
      if (row > -1){
          partition_exist = "/dev/" + part_clone[row][0] ;
          partition_exist_size_int = part_clone_[row]/1000000;
       }
       if (listwidget_exist_read == 1){
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
    if (part_art_clone == 1 or part_art_clone == 2){
       QMessageBox::warning(this, tr("Note", "Hinweis"), tr("There is a root or home partition on the hard disk. You must use a live DVD.", "Auf der Festplatte ist eine root- oder home Partition. Sie müssen eine Live-CD benutzen.\n"));
	return 0;
	}
	partition_name  = partition_exist.right(partition_exist.size() -4);
//Prüfen ob img.fsa oder gz.fsa Datei
        found = folder_clone.indexOf(" ");
 	if(found > -1)
 	     folder_clone = "'" + folder_clone + "'";
        if (folder_clone.indexOf("gz.fsa") > 0)
        	befehl = "gunzip -c " + folder_clone + " | sudo dd of=" + partition_exist; 
        if (folder_clone.indexOf("img.fsa") > 0)
            befehl = "dd if=" + folder_clone +  " of=" + partition_exist + " bs=1M 2>" + homepath + "/.config/qt5-fsarchiver/disk.txt"; 
        int ret = questionMessage(tr("Do you really want to write back an image of the hard disk? ", " Wollen Sie wirklich ein Abbild der Festplatte zurückschreiben? "));
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
                	startThread2(0);
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
        chk_Beschreibung->setChecked(false);
        chk_Beschreibung->setEnabled(false);
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
        chk_Beschreibung->setChecked(false); 
        chk_Beschreibung->setEnabled(false); 
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
        chk_Beschreibung->setChecked(false); 
        chk_Beschreibung->setEnabled(false);   
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
   	chk_Beschreibung->setChecked(true);
   	chk_Beschreibung->setEnabled(true);
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
        chk_Beschreibung->setChecked(false);
        chk_Beschreibung->setEnabled(false);
}

void DialogClone::listWidget_exist_auslesen() {
listwidget_exist_read = listwidget_exist_read + 1;  //Eintrag wurde markiert
}

void DialogClone::listWidget_clone_auslesen() {
listwidget_clone_read = listwidget_clone_read + 1;  //Eintrag wurde markiert
}

void DialogClone::listWidget_auslesen() {
    int row = 0;
    extern QString add_part[100];
    QString size_;
    QStringList partition_kurz;  
    QString widget[100];
    row = listWidget->currentRow() + 1;
    img_partition_clone = add_part[row];
    img_partition_size = add_part[row];
    partition_kurz = img_partition_clone.split(QRegularExpression("\\s+"));;
    img_partition_clone = partition_kurz[0]; // z.B. sda1
    img_partition_clone = img_partition_clone.trimmed();
    img_partition_size = partition_kurz[2];
    img_partition_size = img_partition_size.replace(",","");
    size_ = partition_kurz[3];
    img_partition_size = img_partition_size.trimmed();
    if (size_ == "GB")
       img_partition_size = img_partition_size + "0";
    if (size_ == "TB")
       img_partition_size = img_partition_size + "0000";
}

//Mountpoint ermitteln
int DialogClone::mountpoint(QString partition)
{
   QString text;
   QFile file("/etc/mtab");
   QTextStream ds(&file);
   int pos = 0, pos1 = 0, pos2 = 0;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
        {
        text = ds.readLine();
 	while (!ds.atEnd())
      	   {
	     text = ds.readLine();
	     pos = text.indexOf(" /home"); 
             pos2 = text.indexOf(" / "); 
             if (pos > -1)
                 { // home Partition gefunden
                 pos1 = text.indexOf(partition); 
                 if (pos1 > -1)
      	     		{ 
               		file.close();
               		return 2;
       	    		}
      		 } 
              if (pos2 > -1)
                 { // root Partition gefunden
                 pos1 = text.indexOf(partition); 
                 if (pos1 > -1)
      	     		{ 
               		file.close();
               		return 1;
       	    		}
      		 } 		 
	     } 
	  }
	  file.close();
   	  return 0; 
}

void DialogClone::folder_einlesen() {
   
   QModelIndex index = treeView_clone->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder_clone =  (dirModel->filePath(index));
   
}

int DialogClone::file_check() {
   QFileInfo info(folder_clone); 
   if (!info.isFile() )
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
QString size = "";
int size_1 = 0;
QString letzte_zeile;
QString befehl;
int diff = 0;
QString mb_sec;
QString dummy;
int found = 0;
float dummy1;
        if (endeThread_clone ==0)
	{
	QTimer::singleShot(1000, this, SLOT(ViewProzent()));
                // Prüfen, nach wieviel Sekunden ViewProzent erneut aufgerufen wird
        diff = sekunde_summe_clone - sekunde_summe_clone_1;
	size_clone = read_write_space_sum * sekunde_summe_clone; 
	if(bytes_.toFloat() != 0)
	   size_clone = bytes_.toFloat();
        if (size_clone_dummy > size_clone)
		size_clone=size_clone_dummy; //Verhindert, dass die bereits angezeigten gespeicherten Daten nicht reduziert werden
        size_clone_dummy = size_clone; 
        lbl_hd_size ->setText("MB");
        prozent = size_clone/(partition_exist_size_int)/10;
        prozent = 100 * size_clone/(partition_exist_size_int);
        if (prozent > 100)
            prozent = 100;
        sekunde_summe_clone_1 = sekunde_summe_clone;
        savedBytes->setText("");
        size_1 = (int) size_clone/ 1.074;
        if (size_clone > 10000)
            { 
            size_1 = (int) size_1 / 1000 /1.024;
            lbl_hd_size ->setText("GB");
            }
         if (size_clone > 10000000)
            { 
            size_1 = (int) size_1 / 1000 /1.024;
            lbl_hd_size ->setText("TB");
            }   
        size = QString::number(size_1);
        mb_sec = QString::number(read_write_space_sum, 'f',1);
      //  qDebug() << "prozent size_clone read_write_space_sum sekunde_summe_clone size mb_sec" << prozent <<read_write_space_sum << sekunde_summe_clone<< size << mb_sec;
        if (read_write_space_sum > 0)
        	bytes_sec ->setText(mb_sec);
        if (read_write_space_sec != "")
        	bytes_sec ->setText(read_write_space_sec);
        if (size_clone > 0)
           savedBytes->setText(size);
        // verhindert dass mehr gesicherte Bytes angezeigt werden als Festplattengröße
        dummy1 = partition_exist_size_int;
        dummy1 = dummy1 / 1.074;
        if (size_clone > dummy1)
            {
            if (size_clone > 10000)
               {
               lbl_hd_size ->setText("GB");
               dummy1 = dummy1 / 1000 / 1.024;
               }
            if (size_clone > 10000000)
               {
               lbl_hd_size ->setText("TB");
               dummy1 = dummy1 / 1000 / 1.024;
               }   
            dummy =  QString::number(dummy1); 
            found=dummy.indexOf("."); 
            dummy = dummy.left(found);
            savedBytes->setText(dummy);
            } 
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
					if (minute_ == 0 && sekunde_ == 0)
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
   if( thread1.isRunning() ) return;
   connect( &thread1, SIGNAL(finished()),
            this, SLOT( thread1Ready()));
   thread_run_clone = 1;
   thread1.start();
   bt_end->setEnabled(false);
   bt_save->setEnabled(false);
   // flag=0: Platte klonen, Image ohne zip schreiben
if (flag == 0)
   {
   QThread::msleep(500);
   pid_dd = pid_ermitteln("dd");
   read_write_hd_1(); //Fortschrittsbalken
   }
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
      {
      QThread::msleep(500);
      pid_dd = pid_ermitteln("dd");
      read_write_hd_1(); //Fortschrittsbalken
      }
}

void DialogClone::thread1Ready()  {
QString befehl;
float dummy1;
QString dummy;
int found = 0;
        endeThread_clone = endeThread_clone + 1;
        if (endeThread_clone == 1) {
 	    bt_end->setEnabled(true);
            progressBar->setValue(100);
       	    SekundeRemaining ->setText("0");
            dummy1 = partition_exist_size_int;
            dummy1 = dummy1 / 1.074;
            if (dummy1 > 10000)
               {
               lbl_hd_size ->setText("GB");
               dummy1 = dummy1 / 1000 / 1.024;
               }
             if (dummy1 > 10000000)
               {
               lbl_hd_size ->setText("TB");
               dummy1 = dummy1 / 1000 / 1.024;
               }  
             dummy =  QString::number(dummy1); 
             found=dummy.indexOf("."); 
             dummy = dummy.left(found);
             savedBytes->setText(dummy);
            if (flag_clone==1 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The cloning of the hard disk was successful.", "Das Klonen der Festplatte war erfolgreich.\n"));
            if (flag_clone==2 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was successful.", "Das Sichern des Abbildes der Festplatte war erfolgreich."));
            if (flag_clone==3 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup of the image of the partition was successful.", "Die Sichern des Abbildes der Partition war erfolgreich."));
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
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The backup of the hard disk image was not successful.", "Die Sichern des Abbildes der Festplatte war nicht erfolgreich."));
		}
            if (flag_clone==3 && dialog_auswertung != 0)
                {
                progressBar->setValue(0);
                savedBytes->setText("0");
                this->repaint();
            	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("Saving the image of the partition was not successful.", "Die Sichern des Abbildes der Partition war nicht erfolgreich."));
		}
        }
	thread_run_clone = 0;
	thread1.exit();
        befehl = "rm " +  homepath + "/.config/qt5-fsarchiver/disk.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        SekundeRemaining ->setText("0");
        MinuteRemaining ->setText("0");
        HourRemaining ->setText("0");
        endeThread_clone = 0;
        read_write_space_sum = 0;
        sekunde_summe_clone = 0;
        size_clone_dummy = 0;
        hour_elapsed_clone = 0;
        sekunde_elapsed_clone = 0;
        minute_elapsed_clone = 0;
        this->setCursor(Qt::ArrowCursor);
}

void DialogClone::thread2Ready()  {
float dummy1;
QString dummy;
int found = 0;
	endeThread_clone = endeThread_clone + 1;
        if (endeThread_clone == 1 ) {
	    bt_end->setEnabled(true);
            progressBar->setValue(100);
       	    SekundeRemaining ->setText("0");
            dummy1 = partition_exist_size_int;
            dummy1 = dummy1 / 1.074;
            if (dummy1 > 10000)
               {
               lbl_hd_size ->setText("GB");
               dummy1 = dummy1 / 1000 / 1.024;
               }
             if (dummy1 > 10000000)
               {
               lbl_hd_size ->setText("TB");
               dummy1 = dummy1 / 1000 / 1.024;
               }  
             dummy =  QString::number(dummy1); 
             found=dummy.indexOf("."); 
             dummy = dummy.left(found);
             savedBytes->setText(dummy);
            if (flag_clone==4 && dialog_auswertung == 0)
            	QMessageBox::about(this, tr("Note", "Hinweis"), tr("The hard disk image recovery was successful.", "Die Wiederherstellung des Abbildes der Festplatte war erfolgreich"));
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
        QString befehl = "rm " +  homepath + "/.config/qt5-fsarchiver/disk.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        progressBar->setValue(100);
        if (dialog_auswertung != 0) 
           progressBar->setValue(0);
        SekundeRemaining ->setText("0");
        MinuteRemaining ->setText("0");
        HourRemaining ->setText("0");
        endeThread_clone = 0;
        read_write_space_sum = 0;
        sekunde_summe_clone = 0;
        size_clone_dummy = 0;
        hour_elapsed_clone = 0;
        sekunde_elapsed_clone = 0;
        minute_elapsed_clone = 0;
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
       float remaining_time =(100 * sekunde_summe_clone/prozent)-sekunde_summe_clone ;
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
int ret = 0;
     QWidget::keyPressEvent(event);
     switch( event->key() ) {
         case Qt::Key_Escape:
         if (live_flag_clone == 1)
           ret = questionMessage_critical_clone(tr("Warning: This is a live backup. Do not exit the program. The system could be destroyed. Do you want to quit anyway?", "Warnung: Das ist eine Live-Sicherung. Beenden Sie nicht das Programm. Das System könnte zerstört werden. Wollen Sie trotzdem beenden?"));
         if (live_flag_clone == 0)
            ret = questionMessage_warning_clone(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
         if (ret == 1 )
           {
           esc_end1(1);
           event->accept();
           }   
         if (ret == 2)
           {
           event->ignore();
           return;
           }    
         break;
     }
}

void DialogClone::closeEvent(QCloseEvent *event)
{
int ret = 0;
if (esc_end_flag == 1)
  return;
QString befehl;
      if (live_flag_clone == 1)
           ret = questionMessage_critical_clone(tr("Warning: This is a live backup. Do not exit the program. The system could be destroyed. Do you want to quit anyway?", "Warnung: Das ist eine Live-Sicherung. Beenden Sie nicht das Programm. Das System könnte zerstört werden. Wollen Sie trotzdem beenden?"));
       if (live_flag_clone == 0)
            ret = questionMessage_warning_clone(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
    if (ret == 1 )
       {
       esc_end1(1);
       event->accept();
       }
     if (ret == 2)
       {
       event->ignore();
       return;
       }   
}

void DialogClone::esc_end()
{
esc_end1(0); 
}

void DialogClone::esc_end1(int flag)
{
QString befehl;
int found = 0;
   if (thread_run_clone > 0 && flag == 1)
        {
        pid_2_ermitteln();
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk1.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk2.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";  
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk3.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = ""; 
        // Bei Abbruch fsa und txt Dateien löschen                       
        befehl = "rm "  + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa 2>/dev/null"; 
        QFile file(folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-part.fsa");
        if (file.exists())
            {
	    if(system (befehl.toLatin1().data()))
                 befehl = "";
            found=befehl.indexOf(".fsa");
            if (found > 0)
                 befehl.replace(found, 4, ".txt"); 
            if(system (befehl.toLatin1().data()))
                 befehl = "";     
            }
        befehl = "rm "  + folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.fsa 2>/dev/null"; 
        QFile file1(folder_clone + "/" + img_partition_clone + "-" + _Datum_clone + "-gz.part.fsa");
        if (file1.exists())
            {
	    if(system (befehl.toLatin1().data()))
                 befehl = "";
            found=befehl.indexOf(".fsa");
            if (found > 0)
                 befehl.replace(found, 4, ".txt"); 
            if(system (befehl.toLatin1().data()))
                 befehl = "";     
            }    
        befehl = "kill -15 " + pid_2_dd[0];  //dd abbrechen
        if(system (befehl.toLatin1().data()))
             befehl = "";
        befehl = "kill -15 " + pid_2_dd[1];  //dd abbrechen
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        flag_clone = 0;
        
        }
     if(flag == 0)
        {
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk1.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk2.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = ""; 
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/disk3.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";                             
        }
        esc_end_flag = 1; 
        endeThread_clone = 0;
        read_write_space_sum = 0;
        sekunde_summe_clone = 0;
        size_clone_dummy = 0;
        hour_elapsed_clone = 0;
        sekunde_elapsed_clone = 0;
        minute_elapsed_clone = 0;
        close();       
}

void DialogClone::pid_2_ermitteln()
{
QString befehl;
QString pid_nummer;
QStringList pid;
int i = 0;
int k = 0;
      QString filename = homepath + "/.config/qt5-fsarchiver/pid_2.txt";
      QFile file(filename);
      if (file.exists())
      {
         befehl = "rm " + filename + " 2>/dev/null"; 
         if(system (befehl.toLatin1().data()))
                 befehl = "";
      }  
      befehl = "ps -aux  1> " +  homepath + "/.config/qt5-fsarchiver/pid_2.txt";
      if(system (befehl.toLatin1().data()))
                 befehl = "";
      QThread::msleep(20 * sleepfaktor);           
      if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        QTextStream ds(&file);        
        pid_nummer = ds.readLine();
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
        befehl = "rm " + filename + " 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        pid_nummer = pid_2_dd[0];
        if(pid_nummer != "")
           {
           do
              {
    	      k=pid_nummer.indexOf("  ");
	      if (k > 0)
              pid_nummer.replace("  ", " ");
	      }
	   while  (k >= 0);
	   pid = pid_nummer.split(" ");
           pid_2_dd[0] = pid[1];
           pid_nummer = pid_2_dd[1];
           do
              {
    	      k=pid_nummer.indexOf("  ");
	      if (k > 0)
                 pid_nummer.replace("  ", " ");
	      }
	   while  (k >= 0);
	   pid = pid_nummer.split(" ");
           pid_2_dd[1] = pid[1];
         }  
}

QString DialogClone::pid_ermitteln(QString prozess)
{
QString befehl = "";
QString pid_nummer = "";
QStringList pid;
QString filename = homepath + "/.config/qt5-fsarchiver/pid.txt";
QFile file(filename);
QTextStream ds(&file);
      befehl = "ps -C " + prozess + " 1> " + filename;
      if(system (befehl.toLatin1().data()))
                 befehl = "";
      if(file.size() == 0) 
          return " ";
      QThread::msleep(20 * sleepfaktor);    
      if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        pid_nummer = ds.readLine();
        pid_nummer = ds.readLine();
        file.close();
     }
        befehl = "rm " + filename + " 2>/dev/null"; ;
        if(system (befehl.toLatin1().data()))
                 befehl = "";
      if (pid_nummer != "")
          {
          pid = pid_nummer.split(QRegularExpression("\\s+"));
          pid_nummer = pid[1]; 
          }
        return pid_nummer;
}


void DialogClone::read_write_hd()  // gezipt
{
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
       		QTimer::singleShot(10000, this, SLOT(read_write_hd()));
       read_write_counter = read_write_counter +1;
       if (read_write_counter == 10){
	    read_write_counter = 0;
            read_write_counter_1 = read_write_counter_1 +1;}
        befehl = "vmstat 2 2 1> " +  homepath + "/.config/qt5-fsarchiver/disk.txt";
        if(system (befehl.toLatin1().data()))
                 befehl = "";
        if (sekunde_elapsed_clone < 59)
        	sekunde_elapsed_clone = sekunde_elapsed_clone +1;
        if (sekunde_elapsed_clone < 59)
        	sekunde_elapsed_clone = sekunde_elapsed_clone +1;
        sekunde_summe_clone  = sekunde_summe_clone + 2;
 	QString filename = homepath + "/.config/qt5-fsarchiver/disk.txt";
	QFile file(filename);
	QThread::msleep(20 * sleepfaktor);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
           QTextStream ds(&file);
           teilstring = ds.readLine();
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
                rrw[read_write_counter]= 1.08 * rw_.toInt();}  //1.1 Erfahrungsfaktor
	if (rdbt_image_restore->isChecked() or rdbt_partition_restore->isChecked()){
                rw_ = read_write[10];  // 10=bo 9=bi  Auswertung gelesene Blöcke
          	rrw[read_write_counter]= 1.08 * rw_.toInt();}  //1.1 Erfahrungsfaktor
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
   }
}

void DialogClone::read_write_hd_1()  // nicht gezipt
{
QString befehl;
QStringList bytes;
int pos = 0;
        if (endeThread_clone !=0)
            return;
        while (pid_dd == "") 
            {
            QThread::msleep(1000);
            pid_dd = pid_ermitteln("dd");
            if (pid_dd == "")   
               {
               error = "1";
               return;
               }
            } 
        QTimer::singleShot(10000, this, SLOT(read_write_hd_1()));  //10 sekunden
        // Wird für den Fortschrittsbalken benötigt
        if (pid_dd != "")
           {
           befehl = "kill -USR1 " + pid_dd;
           if(system (befehl.toLatin1().data()))
                 befehl = "";
           } 
	QString filename = homepath + "/.config/qt5-fsarchiver/disk.txt";
	QFile file(filename);
        if(file.size() == 0)
           return;
        QThread::msleep(20 * sleepfaktor);  
        if (file.open(QIODevice::ReadOnly|QIODevice::Text)) 
           {
           QTextStream ds(&file);
           while (!ds.atEnd())
      	     bytes_ = ds.readLine();
      	   }
   	file.close();
   	if (bytes_ != "")
           {
           bytes = bytes_.split(" ") ;
           bytes_ = bytes[0];
           bytes_ =  bytes_.left( bytes_.size() -6);
           read_write_space_sum = (bytes_.toInt()/ sekunde_summe_clone);
           }
        if (bytes_ != ""){
           read_write_space_sec = bytes[7];
           pos = read_write_space_sec.indexOf(".");
       	   read_write_space_sec = read_write_space_sec.left(pos+1);
           }
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
        filename = homepath + "/.config/qt5-fsarchiver/disk2.txt";
        QFile file(filename);
        QTextStream ds(&file);
        QThread::msleep(20 * sleepfaktor);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
            befehl = "lsblk 1> " + filename;
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


void DialogClone::beschreibungstext_clone(QString text, int zip, int row, QString size_folder, QString folder)  
{
FileDialog filedialog; //Create the main widget; 
QString part_size_;
float part_size;
QString Linuxversion;
QString ubuntu_root;
QString ubuntu_home;
QString compress;
QString kernel;
QString dummy;
QString dummy1;
int pos = 0;
int mount = 0;
QString foldertext;
QString foldertext1;
QString zip_zstd_;
      clone_part[row][4] = sdx3_clone_einlesen(part[row][0],0);
      clone_part[row][5] = sdx3_clone_einlesen(part[row][0],1);
      dummy = part[row][2];
      dummy1 = dummy.right(2);
      dummy = dummy.left(dummy.size() -3);
      // Komma in Punkt ändern
      pos=dummy.indexOf(",");
      if (pos > 0)
        dummy.replace(pos, 1, "."); 
      if(zip == 3)
         {
         part_size = dummy.toFloat();
         part_size = part_size * 0.37;
         part_size = part_size*100;
         part_size = round(part_size);
         part_size = part_size/100;
         part_size_compress_clone = QString::number(part_size) + " " + dummy1;
         compress = tr("gzip-standard", "gzip-standard");
         } 
      if(zip == 0)
          {
          compress =  tr("No compression", "keine Kompressiom");
          part_size_compress_clone = part[row][2];
          }
        text = tr("Backup file name: ", "Sicherungsdateiname: ") + text + "\n" + 
	tr("Partition  name: ", "Partitionsname: ")  
	+ part[row][0] + "\n" + tr("Partition type: ", "Partitionsart: ") 
       	+ part[row][1] + "\n" + tr("UUID: ") +  part[row][3] + "\n" + tr("Description: ", "Bezeichnung: ") + part[row][4] + "\n" + 
       	tr("Partition size: ", "Partitionsgröße: ") + part[row][2] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + 
       	clone_part[row][4] + "\n" + tr("Assignment of the partition: ", "Belegung der Partition: ") + clone_part[row][5]  + "\n" + tr("Compression: ", "Kompression: ") + compress + "\n" + 
       	tr("Approximate image file sizes: ", "ungefähre Sicherungsdateigröße: ") + part_size_compress_clone + "\n" ;
        ubuntu_root = tr("to be protected/secured partition: / (root system directory) ", "zu sichernde / gesicherte Partition: / (Wurzel-Systemverzeichnis) ");
        mount = mountpoint(part[row][0]);
       	if (mount == 1){
		Linuxversion = linux_version_clone();
                kernel = kernel_version_clone();
                text = ubuntu_root + "\n" + tr("Operating system: ", "Betriebsystem: ") + Linuxversion + "\n" + tr("Kernel: ") + kernel + " " + "\n" + text + "\n";
	}
	ubuntu_home = tr("to be protected/secured partition: /home", "zu sichernde/gesicherte Partition: /home");
	if (mount == 2){
	   text = ubuntu_home + "\n" + text + "\n";
	}
	foldertext = tr("Path of the backup file: ", "Pfad der Sicherungsdatei: ");
	foldertext1 = tr("Free space on the hard disk to be backed up to: ", "Freier Speicherplatz auf der Festplatte auf die gesichert wird: ");
	if (folder != "")
	     text = text + "" + foldertext + " " + folder + "\n" + foldertext1  +  " " + size_folder + "B";
	text = text + "\n" + "\n" + tr("Other notes: ", "weitere Hinweise:");
	filedialog.werte_uebergeben(text);
 }

QString DialogClone::sdx3_clone_einlesen(QString part_, int flag)
{
QString text;
QString text1;
QString befehl;
QString dummy;
QStringList dev_sdx;
float part_size;
         QString filename = homepath + "/.config/qt5-fsarchiver/disk3.txt";
         QFile file(filename);
         QTextStream ds(&file);
         dummy = "/dev/" + part_;
         if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "df /dev/" + part_ + " 1>" + filename;
           if(system (befehl.toLatin1().data()))
               befehl = "";
           text = "";
           QThread::msleep(5 * sleepfaktor);
           while (text == "")
              text = ds.readLine();
           text = ds.readLine();
           dev_sdx = text.split(QRegularExpression("\\s+"));
           if (flag == 0)
              {
              part_size = dev_sdx[2].toFloat()/1000;
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
	befehl = "uname -a 1> " +  homepath + "/.config/qt5-fsarchiver/kernel.txt";
        if(system (befehl.toLatin1().data()))
            befehl = "";
        QString filename = homepath + "/.config/qt5-fsarchiver/kernel.txt";
	QFile file(filename);
        QTextStream ds(&file);
        QThread::msleep(20 * sleepfaktor);
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
	befehl = "cat /etc/*release 1> " +  homepath + "/.config/qt5-fsarchiver/version.txt";
        if(system (befehl.toLatin1().data()))
           befehl = "";
        QString filename = homepath + "/.config/qt5-fsarchiver/version.txt";
        QFile file(filename);
        QTextStream ds(&file);
        QThread::msleep(20 * sleepfaktor);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        Linuxversion = "xxx"; //damit die erste Zeile ausgewertet wird
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
         befehl = "rm " + filename + " 2>/dev/null"; ;
         if(system (befehl.toLatin1().data()))
               befehl = "";
         return Linuxversion;
}

void DialogClone::folder_expand() {
   QModelIndex index = treeView_clone->currentIndex();
   treeView_clone->expand(index);
}

int DialogClone::size_determine_clone(QString part_size_compress, QString folder)
{
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
      	        size_folder_clone = size[3];
   	      if( size_.isEmpty() )
         	 break;
              size_ = ds.readLine();
       	    } 
   	    file.close();
   	  } 
   	  if (part_size_compress == "")
   	     return 3;
   	  size_folder_ = size_folder_clone.right(1);
   	  part_size_compress_ = part_size_compress.right(2);
   	  part_size_compress_ = part_size_compress_.left(1);
          size_folder_clone = size_folder_clone.left(size_folder_clone.size() -1);
          part_size_compress = part_size_compress.left(part_size_compress.size() -2);
          pos = size_folder_clone.indexOf(",");
          if (pos > 0)
             size_folder_clone.replace(pos, 1, "."); 
          pos = part_size_compress.indexOf(",");
          if (pos > 0)
             part_size_compress.replace(pos, 1, ".");
          size_folder_float_clone = size_folder_clone.toFloat(); 
           
          part_size_compress_float_clone = part_size_compress.toFloat(); 
          if (size_folder_ == "G") 
             size_folder_float_clone = size_folder_float_clone * 1000;  
          if (size_folder_ == "T") 
             size_folder_float_clone = size_folder_float_clone * 1000000; 
          if (part_size_compress_ == "G") 
             part_size_compress_float_clone = part_size_compress_float_clone * 1000;  
          if (part_size_compress_ == "T") 
             part_size_compress_float_clone = part_size_compress_float_clone * 1000000;
          if (size_folder_float_clone  > part_size_compress_float_clone * 1.1) //vorsichtshalber um 20% vergrößern
           	return 1;
          else
                return 2; 
}

int DialogClone::questionMessage_critical_clone(QString frage)
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

int DialogClone::questionMessage_warning_clone(QString frage)
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







