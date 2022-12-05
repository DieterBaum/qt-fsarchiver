/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2022 Dieter Baum.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Publicstimmt nicht 
 * License v3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */
#include <string.h>
#include <stdio.h>
#include <QtGui> 
#include <QInputDialog>
#include "net.h"
#include "net_ein.h"
#include "filedialog.h"
#include "mainWindow.h"
#include <iostream>
#include "treeview.h"
#include <unistd.h>
#include "setting.h"

extern "C" {
#include "connect_c_cpp.h"
#include "fsarchiver.h"
}

using namespace std;

extern int dialog_auswertung;
extern QString add_part[100]; 
extern QString parameter[15];
extern QString folder_file_;
extern QString part[100][10];
extern QString user;
extern int flag1;
QString zip_net[11];
QString folder_net;
QString file_net;
QString folder_free;
QString folder_free_[100];
QString partition_net; // z.B 192.168.2.5
QString partition_net_; // z.B sda1
QString UUID_net;
QString partition_typ_net;
QString DateiName_net = "";
QString _Datum_net;
QString part_art_net;
QString user_net;
QString key_net;
QString rechner_IP;
int endeThread_net;
QString SicherungsDateiName_net;
QString SicherungsFolderFileName_net;
int sekunde_elapsed_net;
int minute_elapsed_net;
int sekunde_summe_net;
int dummy_prozent_net;
int flag_View_net; 
int flag_end_net;
int sekunde_tara_net; 
QString pid_net, pid1_net;
QString befehl_pbr_net;
int stopFlag_;
QStringList items_Net;
QStringList items_zstd_net;
QString pfad_back;
QString pfad_forward;
int backFlag;
int cmbFlag = 0;
int listwidgetrow = 0;
QString folder_dir_net;
int zstd_level_net;
extern QString password;
int mountflag = 0;
int show1 = 0;
extern int sleepfaktor;
int nameflag = 0;
int liveFlag_net = 0;
int row_net = 0;
int rootpassword_net = 0;
QString name_txt_file;
bool ok;
int thread_run_net;
extern int fsarchiver_aufruf(int argc, char *anlage0=NULL, char 
*anlage1=NULL, char *anlage2=NULL, char *anlage3=NULL, char 
*anlage4=NULL, char *anlage5=NULL, char *anlage6=NULL, char 
*anlage7=NULL, char *anlage8=NULL, char *anlage9=NULL, char 
*anlage10=NULL, char *anlage11=NULL, char *anlage12=NULL, char 
*anlage13=NULL, char *anlage14=NULL);

DialogNet::DialogNet()
{
QString homepath = QDir::homePath();
QString befehl; 
QStringList items;
QStringList items_kerne_; 
setupUi(this); // this sets up GUI
        folder_net = homepath + "/.qt5-fs-client";
        if ( dialog_auswertung == 6)
        	rdBt_saveFsArchiv->setChecked(true);
        else
		rdBt_restoreFsArchiv->setChecked(true);
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
        dirModel->setRootPath(QDir::rootPath());
        connect( pushButton_zstd_net, SIGNAL( clicked() ), this, SLOT(zip_einlesen_net())); 
        connect( chk_path, SIGNAL( clicked()), this, SLOT(rdButton_auslesen()));
      	connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(end()));
        connect( pushButton_save, SIGNAL( clicked() ), this, SLOT(savePartition()));
   	connect( pushButton_restore, SIGNAL( clicked() ), this, SLOT(restorePartition()));
       	connect( rdBt_saveFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen()));
   	connect( rdBt_restoreFsArchiv, SIGNAL( clicked() ), this, SLOT(rdButton_auslesen())); 
        connect( pushButton_partition, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        connect( pushButton_partition_2, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        connect( pushButton_folder_free, SIGNAL( clicked() ), this, SLOT(listWidget_folder_free_auslesen()));
        connect( pushButton_folder_free_2, SIGNAL( clicked() ), this, SLOT(listWidget_folder_free_auslesen()));
        connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
        connect( bt_net_art, SIGNAL( clicked() ), this, SLOT(cmb_net()));
        connect( bt_treeWiget_2, SIGNAL( clicked() ), this, SLOT(listWidget_tree_auslesen_1()));
        connect( pushButton_partition_2, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
        if (rdBt_saveFsArchiv->isChecked()){
  	    pushButton_restore->setEnabled(false);
            pushButton_save->setEnabled(true);}
        else
            {
  	    pushButton_restore->setEnabled(true);
            pushButton_save->setEnabled(false);}
        timer = new QTimer(this);
        items_Net << "Samba" << "NFS";
       	cmb_Net->addItems (items_Net);
	items_Net.clear();
        items_kerne_ << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" <<  "14" << "15" << "16" << "17" << "18" << "19" << "20";
   	cmb_kerne->addItems (items_kerne_);
   	items_kerne_.clear();
        items_zstd_net << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" <<  "17" << "18" << "19" << "20" << "21" << "22";
        cmb_zstd_net->addItems (items_zstd_net);
        items_zstd_net.clear();
   	zip_net[0]= tr("lz4");
        zip_net[1]= tr("lzo");
   	zip_net[2]= tr("gzip fast");
   	zip_net[3]= tr("gzip standard");
   	zip_net[4]= tr("gzip best");
   	zip_net[5]= tr("bzip2 fast");
   	zip_net[6]= tr("bzip2 good");
   	zip_net[7]= tr("lzma fast");
   	zip_net[8]= tr("lzma medium");
   	zip_net[9]= tr("lzma best");
        zip_net[10]=(tr("zstd","zstd"));
   	items << zip_net[0] << zip_net[1] << zip_net[2] << zip_net[3] <<  zip_net[4];
   	cmb_zip->addItems (items);
   	items.clear();
   	items << zip_net[5] << zip_net[6] << zip_net[7] << zip_net[8] << zip_net[9] << zip_net[10];
   	cmb_zip->addItems (items);
   	items.clear();
        chkkey();
        // Ini-Datei auslesen
   	QFile file1(homepath + "/.config/qt5-fsarchiver/qt5-fsarchiver.conf");
        cmb_Net -> setCurrentIndex(0);
        listWidget ->setHidden(false);
     if (file1.exists()) {
        QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("Kompression").toInt();
        cmb_zip -> setCurrentIndex(auswertung); 
        auswertung = setting.value("Kerne").toInt();
        cmb_kerne -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("Network").toInt();
        cmb_Net -> setCurrentIndex(auswertung-1); //Auswahl setzen
        if (auswertung == 0)
            cmb_Net -> setCurrentIndex(1); //Auswahl setzen
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
        auswertung = setting.value("place").toInt();
        if (auswertung ==1)
           chk_path->setChecked(true); 
        auswertung = setting.value("Passwort").toInt();
        if (auswertung ==1){
           	lineKey ->setEchoMode(QLineEdit::Normal);
        } 
   	else
		lineKey ->setEchoMode(QLineEdit::Password);
        zstd_level_net = setting.value("zstd").toInt();
        cmb_zstd_net -> setCurrentIndex(zstd_level_net-1);
        auswertung = setting.value("Kompression").toInt();
        if (auswertung ==10)
            cmb_zstd_net->setEnabled(true);
        else
            cmb_zstd_net->setEnabled(false); 
        setting.endGroup();
        } 
   else {
        lineKey ->setEchoMode(QLineEdit::Password);
        cmb_Net -> setCurrentIndex(1); //Auswahl setzen
        cmb_kerne -> setCurrentIndex(0);
        chk_Beschreibung->setChecked(true);
        chk_overwrite->setChecked(true); 
        cmb_zip -> setCurrentIndex(2);
        cmb_zstd_net -> setCurrentIndex(7);
        cmb_zstd_net->setEnabled(false);
        }
    
    	label_4->setEnabled(false);
   	chk_overwrite->setEnabled(true);
   	cmb_zip->setEnabled(false);
   	chk_Beschreibung->setEnabled(true);
   	chk_Beschreibung->setChecked(true);
   	rdButton_auslesen();
   	addWidget();
        chk_path ->setEnabled(false);
          
    QFile file(homepath + "/.config/qt5-fsarchiver/qt5-fsarchiver.conf");
    QTextStream ds(&file);
    int a = 0;
    int b = 0;
    int c = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QThread::msleep(5 * sleepfaktor);
    QString text = ds.readLine();
   	  while (!ds.atEnd())
      	  {
          if (text.indexOf("Network=") > -1)
              c = c + 1; 
          if (text.indexOf("ssh=") > -1)
              a = a + 1;
          if (text.indexOf("sshfs=") > -1)
              b = b + 1;
           text = ds.readLine();
          } }
   	file.close();
        QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
        setting.beginGroup("Basiseinstellungen"); 
        if (a ==0)
           setting.setValue("ssh",1);
        if (b ==0)
            setting.setValue("sshfs",1);
        if (c ==0)
            setting.setValue("Network",2);
        setting.endGroup();
        cmbFlag = 1;
        cmb_net();
        dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
} 

void DialogNet::chkkey(){
     Qt::CheckState state;
     state = chk_key->checkState();
     if (state == Qt::Checked)
        lineKey->setEnabled(true);
     else 
	lineKey->setEnabled(false);
}  
void DialogNet::cmb_net(){
if (cmbFlag == 0)
   return;
int net_art = cmb_Net->currentIndex(); //auslesen
if (net_art == -1)
    net_art = 1;
if (net_art == 0){
        Daten_Samba_eintragen();}
if (net_art == 1){
        QString index = QString::number(net_art);
        Daten_NFS_eintragen();
       	}
}

void DialogNet:: end()
{ 
QString homepath = QDir::homePath();
QString befehl;
QString filename;
        befehl = "umount -f" + homepath + "/.qt5-fs-client 2>/dev/null"; //umount samba
	if(system (befehl.toLatin1().data()))
           befehl = "";   
        befehl = "fusermount -u " + homepath + "/.qt5-fs-client 2>/dev/null"; //fusermount
        if(system (befehl.toLatin1().data()))
           befehl = "";
        befehl = "umount -a -t nfs 2>/dev/null";  //umount nfs
        if(system (befehl.toLatin1().data()))
           befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/ip.txt 2>/dev/null";
	if(system (befehl.toLatin1().data()))
              befehl = "";
 	befehl = "rm " + homepath + "/.config/qt5-fsarchiver/smbtree.txt 2>/dev/null";
        if(system (befehl.toLatin1().data()))
              befehl = "";
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/smbclient.txt 2>/dev/null";
        if(system (befehl.toLatin1().data()))
              befehl = "";
	befehl = "rm " + homepath + "/.config/qt5-fsarchiver/folder.txt 2>/dev/null";
        if(system (befehl.toLatin1().data()))
              befehl = "";
        cmbFlag = 0;
        befehl = "umount " + homepath + "/.qt5-fs-client 2>/dev/null"; 
	if(system (befehl.toLatin1().data()))
           befehl = "";
        close(); 
}

void DialogNet:: Daten_NFS_eintragen()
{
	this->setCursor(Qt::WaitCursor);
	NetEin netein;	
	QString rechner;
	QStringList items;
	rechner = netein.Namen_holen();
   	txt_rechner_net ->setText(rechner);
   	//IP-Adresse Netzrechner
   	items = rechner.split(" ");  
   	rechner_IP = items[0];
   	user_net = netein.user_holen();
   	key_net = netein.key_holen();
        //freigegebene Ordner ermitteln
        int i = nfs_search_folder_free(rechner_IP); 
   	if ( i==1){
        	QMessageBox::warning(this,tr("Note", "Hinweis"),
        tr("No released directory was found for the NFS protocol.\n", "Für das NFS Protokoll wurde kein freigegebenes Verzeichnis gefunden.\n"));
	}
    	this->setCursor(Qt::ArrowCursor); 
}

void DialogNet:: Daten_Samba_eintragen()
{
this->setCursor(Qt::WaitCursor);
NetEin netein;	
QString rechner;
QStringList items;
int i = 0;
   rechner = netein.Namen_holen();
   txt_rechner_net ->setText(rechner);
   //IP-Adresse Netzrechner
   items = rechner.split(" ");  
   rechner_IP = items[0];
   user_net = netein.user_holen(); 
   key_net = netein.key_holen();
   //freigegebene Ordner ermitteln
   i = search_folder_free(rechner_IP); 
   if ( i==1){
        QMessageBox::warning(this,tr("Note", "Hinweis"),
        tr("No shared directory was found for Samba.\n", "Für das Samba Protokoll wurde kein freigegebenes Verzeichnis gefunden.\n"));
	}
    this->setCursor(Qt::ArrowCursor); 
   
}

int DialogNet::nfs_search_folder_free(QString rechner_IP)  //NFS freigegebene Verzeichnisse ermitteln
{
QString homepath = QDir::homePath();
QString befehl;
int i = 0;
QString text;
QStringList items;
listWidget_free_folder -> clear();
        QFile file(homepath + "/.config/qt5-fsarchiver/smbclient.txt");
	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
             {
            befehl = "showmount -e " + rechner_IP + " 1> " +  homepath + "/.config/qt5-fsarchiver/smbclient.txt";
	    if(system (befehl.toLatin1().data()))
                befehl = "";
            QThread::msleep(5 * sleepfaktor);    
            while (text == ""){
             text = ds.readLine();
            }
    	  while (!ds.atEnd())
      	{
          text = ds.readLine();
 	  items = text.split(" ");
          folder_free = items[0];
          folder_free = folder_free.trimmed();
          listWidget_free_folder ->addItem (folder_free);
          folder_free_[i] = folder_free;
          i = i + 1;
          } 
   	file.close();
        if ( i==0){
           return 1 ;
        }
     }
    folder_free = "";
    return 0;	
}

int DialogNet::search_folder_free(QString rechner_IP) //Samba freigegebene Verzeichnisse ermitteln
{
QString homepath = QDir::homePath();
QString befehl;
int line = 0;
int i = 0;
int pos = 0;
QString text;
QStringList items;
listWidget_free_folder -> clear();
	// freigegebene Verzeichnisse ermitteln
        QFile file(homepath + "/.config/qt5-fsarchiver/smbclient.txt");
	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
             {
            befehl = "smbclient -N -L" + rechner_IP + " 1> " +  homepath + "/.config/qt5-fsarchiver/smbclient.txt";
	    if(system (befehl.toLatin1().data()))
                 befehl = "";
            QThread::msleep(5 * sleepfaktor);      
            while (text == ""){
              text = ds.readLine();
              }
   	  while (!ds.atEnd())
      	     {
 	       if (text.indexOf("Disk") > -1)  {
                   if (text.indexOf("print$") == -1){
                     pos = text.indexOf("Disk");
                     folder_free = text.left(pos);
                     folder_free = folder_free.trimmed();
                     listWidget_free_folder ->addItem (folder_free);
                     folder_free_[i] = folder_free;
                     i = i + 1;
		               if (i > 99) {
                        file.close();
                        return 1;
                       }
   	       } }
   	       	line++;
            text = ds.readLine();
           }
   	file.close();
        if ( i==0){
           return 1 ;
        }
     }
    folder_free = "";
    return 0;	
}

int DialogNet::savePartition() {
QString homepath = QDir::homePath();
flag1 = 1;
MWindow window;
flag1 = 0;
QFileInfo info(folder_dir_net); 
FileDialog filedialog;
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[10][20];
int k = 0;
int umount = 0;
int len = 0;
QString dummy;
QString attribute;
     QString befehl;
     QString text;
     Qt::CheckState state;
     Qt::CheckState state1;
     Qt::CheckState state3;
     int err = 0;
     QString keyText = "";
     int zip;
     indicator_reset();
     int net_art = cmb_Net->currentIndex();
     int found = 0;
     char * part_;
     QString compress = "";
     if (rdBt_saveFsArchiv->isChecked())
        {
     	if (folder_free == "")
           {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please, select a folder.\n", "Bitte wählen Sie einen Ordner aus.\n"));
		return 0 ;
           }
        if (partition_net_ == "")
           {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please, select the partition to be saved.\n", "Bitte wählen Sie die zu sichernde Partition aus.\n"));
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
        DateiName_net = lineEdit_DateiName->text();
        if (DateiName_net == "")
           {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please, select the filename of the backup.\n", "Bitte wählen Sie den Dateinamen der Sicherung aus.\n"));
		return 0 ;
           }
        //Überprüfen ob im Dateinamen "/" enthalten ist. Wird durch "-" ersetzt
        while (found > -1){
          found = DateiName_net.indexOf("/");
          if (found > -1)
             	DateiName_net.replace(found, 1, "-"); 
        }
        found = DateiName_net.indexOf(" ");
        //Überprüfen ob im Dateinamen "" enthalten ist. Wird durch "-" ersetzt
        while (found > -1){
          found = DateiName_net.indexOf(" ");
          if (found > -1)
             	DateiName_net.replace(found, 1, "-"); 
        }
        while (found > -1){
          found = DateiName_net.indexOf("+");
          if (found > -1)
             	DateiName_net.replace(found, 1, "-"); 
        }
       this->setCursor(Qt::WaitCursor);
       QString zeichen = "'";
       if (net_art == 0){  //Samba
           QString befehl = "mount -t cifs -o username=" + user_net + ",password=" + key_net + ",uid=0,gid=0 //" + rechner_IP + "/'" + folder_free + "' " + homepath + "/.qt5-fs-client";
        k = system (befehl.toLatin1().data());
	}
       if (net_art == 1){ //NFS
           QString befehl = "mount " + rechner_IP + ":" + folder_free +  " " + homepath + "/.qt5-fs-client" ;
           k = system (befehl.toLatin1().data()); 
	} 
	QThread::msleep(50 * sleepfaktor);
        this->setCursor(Qt::ArrowCursor); 
        if (k != 0)
             {
   	     QMessageBox::warning(this, tr("Note", "Hinweis"),
      	     tr("The network computer ",  "Der Netzwerkrechner ") + rechner_IP + tr(" could not be integrated. The program is aborted\n", " konnte nicht eingebunden werden. Das Programm wird abgebrochen\n"));
      	     return 1;
             }
         _Datum_net = Zeit_auslesen_net();
         state = chk_Beschreibung->checkState();
         zip = cmb_zip->currentIndex();
         if (zip == -1)
            zip = 3;
         int zip_zstd_net  = cmb_zstd_net->currentIndex() + 1;   
         if (zip == 10) 
             zip = zip + zip_zstd_net;   
         int liveFlag = 0;
         int row;
         char  dev_[50] = "/dev/";
         QString dummy;
         // Werte sammeln und nach file_dialog übergeben, Partition ist eingehängt
         row = listWidget->currentRow();
         dialog_auswertung = 6;
        //Überprüfung ob gemounted
         part_ = partition_net_.toLatin1().data();
         strcat (dev_ , part_);  // String zusammenfügen: dev_  = dev_ + part_
         dummy = partition_net_;
 	 // Werte sammeln und nach file_dialog übergeben, Partition ist eingehängt
         row = listWidget->currentRow();
         text = window.beschreibungstext("/dev/" + partition_net_, DateiName_net + "-" + _Datum_net + ".fsa", zip, row);
         filedialog.werte_uebergeben(text);
         partition_net = dummy;
         if (!window.is_mounted(partition_net_.toLatin1().data())) 
            {
		   UUID_net = window.UUID_auslesen(listwidgetrow);
                   liveFlag_net = 0;
		   part_art_net = window.mtab_einlesen("/dev/" + partition_net_);
		   if(part_art_net == "")
		      umount = 1;
		   //Überprüfung on LVM vorhanden
                   if(part[row][7] == "/" or part[row][7] == "/home")
                      liveFlag = 1;
                   if(liveFlag_net == 1)
                      liveFlag = 1;
                   liveFlag_net = 0; 
                   //Überprüfung ob System oder Home Partition
                   int ret = 1; 
                   if (part_art_net == "system")
                	{
                	ret = questionMessage_net(tr("The system partition to be saved is mounted. Do you want to do a live backup?", "Die zu sichernde Systempartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
                        if (ret == 2)
                           return 0;
                        if (ret == 1)
                           liveFlag = 1;
                	}
                  if (part_art_net == "home")
                	{
                	ret = questionMessage_net(tr("The home partition to be saved is mounted. Do you want to do a live backup?", "Die zu sichernde Homepartition ist eingehängt. Wollen Sie eine Live-Sicherung durchführen?"));
                        if (ret == 2)
                           return 0;
                        if (ret == 1)
                           liveFlag = 1;
                	}
                   if (part_art_net != "system" || part_art_net != "home")
                	{
                	   if (liveFlag == 0)
                               {
                               if(partition_net_.indexOf("dm-") > -1)   //Live-DVD mit LVM und Raid
                                    befehl = "umount /media/" + partition_net_;
                               else
                                    befehl = "umount /dev/" + partition_net_;
                               err = system (befehl.toLatin1().data());
                               if(part[listwidgetrow][7] != "")
                                    befehl = "umount" + part[listwidgetrow][7]; 
                               err = err + system (befehl.toLatin1().data());   
                               }
                           if (err != 0 && liveFlag == 0 && umount == 0)
                                {
				QMessageBox::warning(this, tr("Note", "Hinweis"),
         			tr("The partition ", "Die Partition ")   + partition_net_ + 
				tr("cannot be unmounted. The program is aborted.\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ; 
                                } 
                                umount = 0; 
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
                                if (zip < 10)
                                {
                                compress = QString::number(zip);
                                compress = "-z" + compress;
                                parameter[2] = compress;
                                }
                                if (zip == 10)
                                   {
                                   compress = "-Z" + QString::number(zstd_level_net);   
                                   parameter[2] = compress;
                                }
                         int kerne = cmb_kerne->currentIndex()+1;
                         QString index = QString::number(kerne);
                         if (index == "0")
                             index = "1";
                         indizierung = 4;
         		 if (state == Qt::Checked) //Überschreiben ja
                         parameter[3] = "-j" + index;
                              {
                                    parameter[4] = "-o";
                                    indizierung = 5;
				    }	
				    if (state1 == Qt::Checked)   //Schlüssel ja
                                    {
                                    //Wiederholung der Eingabe und prüfen auf Übereinstimmung
                                    if(rootpassword_net == 1)
                                       text = QInputDialog::getText(this, tr("Enter password again","Passwort nochmals eingeben"),
                                       (tr("Password:","Passwort")), QLineEdit::Normal,"", &ok);
                                    else
                                       text = QInputDialog::getText(this, tr("Enter password again","Passwort nochmals eingeben"),
                                       (tr("Password:","Passwort")), QLineEdit::Password,"", &ok);
                               //     if (!ok)  //Cancel Programm wird beendet
                               //          window.kill_end();
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
				    if (net_art == 1) //NFS -x hinzufügen
				       {
                                      parameter[indizierung] = "-x";
                                      indizierung = indizierung + 1;
                                      }
				    if (state3 == Qt::Checked)   //Archiv splitten 
                                     {
                                      parameter[indizierung] = "-s4400";
                                      indizierung = indizierung + 1;
                                      }
                                  if (liveFlag == 1)
                                      {
                                      parameter[indizierung] = "-A";
                                      parameter[indizierung + 1] = "-a";
                                      indizierung = indizierung + 2; 
                                      }
				  QFile file_suse(".snapshots");
                                  if (file_suse.exists())
                                    {
                                    parameter[indizierung] = "--exclude=./snapshots";
                                    indizierung = indizierung + 1;
                                    }
         		           // Windows Auslagerungsdatei pagefile.sys von der Sicherung immer ausschließen
                                  parameter[indizierung] = "--exclude=pagefile.sys";
                                  indizierung = indizierung + 1;
                                  // Vorbereitung für pbr
				 QString befehl = ("dd if=/dev/" + partition_net_ + " of=" + folder_net + "/" + DateiName_net + "-" + _Datum_net + ".pbr" + " bs=512 count=1");
				state = chk_pbr->checkState();
				if (state == Qt::Checked)
                                   {
				   if(system (befehl.toLatin1().data()))
                                        befehl = "";
                                    }
                                parameter[indizierung] = (folder_net + "/" + DateiName_net + "-" + _Datum_net + ".fsa");
                                name_txt_file = DateiName_net + "-" + _Datum_net + ".fsa";
                                parameter[indizierung + 1] = ("/dev/" + partition_net_);
                                QFile f(parameter[indizierung]);
                                if  (parameter[4] != "-o" && (f.exists())){
				       QMessageBox::about(this, tr("Note", "Hinweis"),
         	  			  tr("The partition file ", "Die Partitionsdatei ")   + parameter[indizierung] + tr("already exists. The backup is not performed\n", " ist bereits vorhanden. Die Sicherung wird nicht durchgeführt\n"));
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
                		      QMessageBox::warning(this, tr("Note", "Hinweis"),
         			      tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
				      pushButton_save->setEnabled(true);
                                      return 0;
                		      }
                	         }
                	        thread1.setValues(indizierung + 2,"0"); 
                	        pushButton_end->setEnabled(false);  
                                pushButton_save->setEnabled(false);
                                flag_View_net = 1;
                                ViewProzent();
                                stopFlag_ = 0;
                                this->setCursor(Qt::WaitCursor);
                                startThread1(); // fsarchiver wird im Thread ausgeführt
                                    
        		  }
                       }
    return 0;
}  

int DialogNet::restorePartition() {
QString homepath = QDir::homePath();
flag1 = 1;
MWindow window;
flag1 = 0;
Qt::CheckState state1;
QFileInfo info(folder_dir_net); 
QFile file(file_net);
QString DateiName("") ;
int err = 0;
QString keyText = "";
int pos= 0;
int pos1 = 0;
int cmp = 0;
QString str = ""; 
QString str1 = "";
QString befehl;
QString attribute;
QString text;
QString dummy;
QString sys;
QString optionkey;
char dev_[50] = "/dev/";
char * part_;
char * dev_part;
int umount = 0;
        state1 = chk_key->checkState();
	indicator_reset();
	//int net_art = cmb_Net->currentIndex();
       	if (rdBt_restoreFsArchiv->isChecked())
        {
          keyText = lineKey->text();
          if (state1 == Qt::Checked && keyText.isEmpty())  
              {
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("No decryption key was specified.\n", "Es wurde kein Schlüssel für die Entschlüsselung angegeben.\n"));
		return 1 ;
               }
           if (file_net == "")
           {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please, select the filename of the backup.\n", "Bitte wählen Sie den Dateinamen der Sicherung aus.\n"));
                return 0;
           }
          if (partition_net_ == "")
           {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select the partition you want to write back.\n", "Bitte wählen Sie die zurück zu schreibende Partition aus.\n"));
		return 0 ;
           }
            if (rdBt_restoreFsArchiv->isChecked())
           	{
                 pos = testDateiName(".fsa"); 
                 pos1= testDateiName("part.fsa");
         		if (pos > 0 && pos1 >0)
         	   {
           	   QMessageBox::about(this, tr("Note", "Hinweis"),
         	   tr("You have selected an incorrect recovery file.\nThe file extension must be .fsa.", "Sie haben eine falsche Wiederherstellungsdatei ausgesucht ausgesucht \nDie Dateiendung muss .fsa sein"));
                    return 0;
         	   }
         	}
          this->setCursor(Qt::WaitCursor);  
          this->setCursor(Qt::ArrowCursor);
		// Archinfo einholen um Originalpartition einzulesen und Verschlüsselung überprüfen.
                // das zurücksichern Partition oder Verzeichnis
               // Annahme zunächst kein Schlüssel
               parameter[0] = "fsarchiver";
       	       parameter[1] = "archinfo";
	       if (state1 != Qt::Checked) 
	          {
               	  parameter[2] = file_net;
           	fsarchiver_aufruf(3,parameter[0].toLatin1().data(),parameter[1].toLatin1().data(),parameter[2].toLatin1().data(),parameter[3].toLatin1().data());
               	  optionkey = meldungen_holen(1);
               	   dev_part = meldungen_holen(2);
                  if (werte_holen(4) == 103){
                  	chk_key->setChecked(true);
                        lineKey->setEnabled(true);
                  	QMessageBox::about(this, tr("Note", "Hinweis"),
         	     	tr("The partition is encrypted. Please enter the key\n", "Die Partition ist verschlüsselt. Bitte geben Sie den Schlüssel ein\n"));
                   	return 0;
               	   } 
        	}
        	if (state1 == Qt::Checked) {
            		parameter[2] = "-c";
                        parameter[3] = keyText;
                        if (parameter[3].size() < 6 || parameter[3].size() > 64) {
                  		QMessageBox::about(this, tr("Note", "Hinweis"),
         	  		tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  		return 0 ; 
               	   		}
			parameter[4] = file_net;
                        int retour =  fsarchiver_aufruf(5,parameter[0].toLatin1().data(),parameter[1].toLatin1().data(),parameter[2].toLatin1().data(),parameter[3].toLatin1().data(),parameter[4].toLatin1().data (),parameter[5].toLatin1().data());
                        if ( werte_holen(4) == 103 && retour != 0){
                          QMessageBox::about(this, tr("Note","Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                           return 0;
                        }
			optionkey = meldungen_holen(1);
               		dev_part = meldungen_holen(2);
                }
                //Überprüfen, ob in die Originalpartition zurückgeschrieben werden soll
                part_ = partition_net_.toLatin1().data();
	        strcat (dev_ , part_);  // String zusammenfügen: dev_  = dev_ + part_
                // Hier wird verglichen dev_ = die Partition, die zu sichern ist. dev_part = Originalpartition
                cmp = strcmp (dev_, dev_part);
                QString str, str1;
	        str = dev_part;
                str1 = dev_;
                if (cmp != 0)
                   {
                   // char in QString wandeln
                   QString str, str1;
	           str = dev_part;
                   str1 = dev_;
                   cmp = window.questionMessage(tr("The partition to be recovered ", "Die wiederherzustellende Partition ") + str1 + 
                   tr(" does not match the backed up partition.", " stimmt nicht mit der gesicherten ") + str + tr("Do you still want to perform the restore?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
                   if (cmp == 2)  //nicht wiederherstellen
                     return 0;
                   }
           if (rdBt_restoreFsArchiv->isChecked())
            	{
                folder_file_ = file_net;
               // folder_file();	
		QString filename = folder_file_;
                pos = filename.indexOf("fsa");
        	filename = filename.left(pos);
        	filename.insert(pos, QString("txt"));
                QFile f(filename);
                // Prüfen ob text-Datei vorhanden 
		if (f.exists())
                    {
           	    extern int dialog_auswertung;
                    dialog_auswertung = 3;
              	    FileDialog Filedialog;
     	       	    FileDialog *dlg = new FileDialog;
     	     	    // dlg->show(); nicht modal
             	    int wert = dlg->exec();
               		if (wert == 0 && dialog_auswertung == 3)
                	   {
                	   QMessageBox::warning(this, tr("Note", "Hinweis"),
         		   tr("The write back was aborted by the user.\n", "Das Zurückschreiben wurde vom Benutzer abgebrochen\n"));
                            pushButton_restore->setEnabled(false);
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
 			cmp = questionMessage(tr("There is a file with the contents of the partition boot sector present. Do you want to perform the restoration of the PBR?", "Es ist eine Datei mit dem Inhalt des Partition Boot Sektors vorhanden. Wollen Sie die Wiederherstellung des PBR durchführen?"));
    			if (cmp == 1)  // wiederherstellen
        			befehl_pbr_net = "dd if="+ filename + " of=/dev/" + partition_net_ + " bs=512 count=1";
		         }
        	}
        	  if (!window.is_mounted(partition_net_.toLatin1().data()))
                    {
                       UUID_net = window.UUID_auslesen(listwidgetrow);
                       part_art_net = window.mtab_einlesen("/dev/" + partition_net_);
                       if(part_art_net == "")
                           umount = 1;
                       //Überprüfung ob System oder Home Partition 
                       if (part_art_net == "system")
                	    {
                           QMessageBox::warning(this, tr("Note", "Hinweis"),
         			tr("The system partition to be restored is mounted and cannot be written back. Please use a live DVD.\n", "Die wiederherzustellende Systempartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
				return 0;
		            } 
                        if (part_art_net == "home")
                	    {
                            QMessageBox::warning(this, tr("Note", "Hinweis"),
         			tr("The home partition to be restored is mounted and cannot be written back. Please use a live DVD.\n", "Die wiederherzustellende Homepartition ist eingehängt und kann nicht zurückgeschrieben werden. Benutzen Sie bitte eine Live-CD\n"));
			    return 0; 
                  	    }
                        if (part_art_net != "system"|| part_art_net != "home")
                	    {
                            if(partition_net_.indexOf("/dm-") > -1)
                                attribute = "/media/" + partition_net_  + " 2>/dev/null";  //LVM, Raid
                            else
                                 attribute = "/dev/" + partition_net_  + " 2>/dev/null";    //nicht LVM, Raid
                            char umountpoint[100] = "umount ";
                            strcat (umountpoint,dev_); 
                            err = system (umountpoint);  
                            befehl = "umount /media/" + partition_net_;
                            err = system (befehl.toLatin1().data()); 
                            if (err != 0 && umount == 0)
                                {
                                befehl = "umount /media/" + partition_net_;      
                                if(system (befehl.toLatin1().data()))
                                befehl = "";
				QMessageBox::about(this, tr("Note", "Hinweis"),
         			tr("The partition", "Die Partition ")   + partition_net_ + 
         			tr("can not be unmounted. The program is terminated\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ; 
                                }
                             umount = 0;     
                          }
                       }    
                          
           if (rdBt_restoreFsArchiv->isChecked())
              {
              if (partition_typ_net == "btrfs")
                 {
                 QThread::msleep(20 * sleepfaktor);
                 befehl = "umount /dev/" + partition_net_; // unmounten
 		 if(system (befehl.toLatin1().data()))
                     befehl = "";
                 befehl = "mkfs.btrfs -f /dev/" + partition_net_; // Partition anlegen
 		 if(system (befehl.toLatin1().data()))
                    befehl = "";
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
               parameter[3] = file_net;
               parameter[4] = "id=0,dest=/dev/" + partition_net_;
               thread2.setValues(5,"0");
               if (state1 == Qt::Checked) 
                  { // Verzeichnis mit Schlüssel gesichert
                  parameter[3] = "-c";
                  parameter[4] = keyText;
                  int len = parameter[4].size();
               	  if (len < 6 || len > 64) 
               	       {
                  	QMessageBox::about(this, tr("Note", "Hinweis"),
         	  	tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  	return 0 ; 
               	        }
                   parameter[5] = file_net;
                   parameter[6] = "id=0,dest=/dev/" + partition_net_;
                   thread2.setValues(7,"0");
                   }
               pushButton_restore->setEnabled(false);
               pushButton_end->setEnabled(true); 
               flag_View_net = 2;
  	       ViewProzent();
               stopFlag_ = 0;
               this->setCursor(Qt::WaitCursor);
               this->setCursor(Qt::WaitCursor);
               startThread2(); // fsarchiver wird im Thread ausgeführt
               }
     }
   return 0;
}

void DialogNet::addWidget() {
int i = 1;
    while (add_part[i] != "")
    {
	listWidget->addItem (add_part[i]);
        i++ ;
     }
}

void DialogNet::starteinstellung(){
            QStringList filters;
            pushButton_save->setText (tr("Save partition", "Partition sichern"));
            lineEdit_DateiName->setEnabled(true);
            chk_pbr->setEnabled(true);
            pushButton_restore->setEnabled(false);
            pushButton_save->setEnabled(true);
            label_4->setEnabled(true);
            chk_overwrite->setEnabled(true);
            cmb_zip->setEnabled(true);
            chk_Beschreibung->setEnabled(true);
            AnzahlsaveFile->setEnabled(true);
            AnzahlgesicherteFile->setEnabled(true);
            chk_key->setText (tr("Encrypt\nbackup. key:", "Sicherung\nverschlüsseln. Schlüssel:"));
            chk_split->setEnabled(true);
            chk_pbr->setEnabled(true); 
            restore_file_name_txt ->setEnabled(false); 
            label_folder->setEnabled(false);
            filters << "*.*";
            dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
   	    dirModel->setNameFilters(filters); 
            }

void DialogNet::rdButton_auslesen()
     {
     QStringList filters; 
     if (rdBt_saveFsArchiv->isChecked())
        {
	starteinstellung();
        }
     if (rdBt_restoreFsArchiv->isChecked())
        {
		pushButton_save->setText (tr("Write back partition", "Partition zurückschreiben"));
                pushButton_restore->setEnabled(true);
                pushButton_save->setEnabled(false);
                lineEdit_DateiName->setEnabled(false);
                label_4->setEnabled(false);
                chk_overwrite->setEnabled(false);
                cmb_zip->setEnabled(false);
                chk_Beschreibung->setEnabled(false);
                AnzahlsaveFile->setEnabled(false);
                AnzahlgesicherteFile->setEnabled(false);
                chk_key->setText (tr("Decrypt\nbackup. key:", "Sicherung\nentschlüsseln. Schlüssel"));
                chk_split->setEnabled(false);
		chk_pbr->setEnabled(false);
                filters << "*.fsa";
                dirModel->setFilter(QDir::AllDirs  | QDir::NoDotAndDotDot);
   		dirModel->setNameFilters(filters);  
         }
     } 

QString DialogNet::Zeit_auslesen(){
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
    _Datum_net = Datum_akt.setNum(Tag) + "-" ; 
    _Datum_net = _Datum_net + Datum_akt.setNum(Monat) + "-" ;
    _Datum_net = _Datum_net + Datum_akt.setNum(Jahr) ;
    return _Datum_net;
}

void DialogNet::listWidget_auslesen() {
    QStringList partition_kurz;
    QString dummy;
    listwidgetrow = listWidget->currentRow();
    partition_net_ = add_part[listwidgetrow + 1];
    int pos = partition_net_.indexOf("btrfs");
    if (pos > 0)
       partition_typ_net = "btrfs";
    partition_kurz = partition_net_.split(QRegExp("\\s+"));
    partition_net_ = partition_kurz[0];
    dummy = partition_kurz[1];
    if (dummy == "ntfs" || dummy == "vfat")
        chk_pbr->setEnabled(false);
    else 
       chk_pbr->setEnabled(true);
}

int DialogNet::listWidget_folder_free_auslesen() {
QString homepath = QDir::homePath();
QString befehl;
QString attribute;
QString dummy;
int k = 0;
int pos = 0;
int net_art = cmb_Net->currentIndex();
    TreeviewRead treeviewread;
   // cmb_net();
    int row;
    this->setCursor(Qt::WaitCursor); 
    restore_file_name_txt ->setText("");
    row = listWidget_free_folder->currentRow();
    row_net = row;
    if (row > -1)
    	folder_free = folder_free_[row];
   // folder_free eventuell falsch 
    if (rdBt_restoreFsArchiv->isChecked() && net_art == 0) //Samba
       {
       //Verzeichnis mounten
       this->setCursor(Qt::WaitCursor);
       befehl = "umount " + homepath + "/.qt5-fs-client 2>/dev/null";  //umount
       k = system (befehl.toLatin1().data()); 
       QThread::msleep(50 * sleepfaktor); 
       befehl = "mount -t cifs -o username=" + user_net + ",password=" + key_net + ",uid=0,gid=0 //" + rechner_IP + "/'" + folder_free + "' " + homepath + "/.qt5-fs-client" ;
       k = system (befehl.toLatin1().data());
       QThread::msleep(50 * sleepfaktor);
       }
    if (rdBt_restoreFsArchiv->isChecked() && net_art == 1) //NFS
       {
       //Verzeichnis mounten
       this->setCursor(Qt::WaitCursor);
       if (row > -1)
    	   folder_free = folder_free_[row];
       befehl = "mount " + rechner_IP + ":" + folder_free + " " + homepath + "/.qt5-fs-client" ;
       k = system (befehl.toLatin1().data());
       }
       QThread::msleep(50 * sleepfaktor);
       this->setCursor(Qt::ArrowCursor);  
    if (k != 0){
   	QMessageBox::warning(this, tr("Note", "Hinweis"),
      	tr("The network computer ",  "Der Netzwerkrechner ") + rechner_IP + tr(" cannot be embedded. The program is aborted.\n", " konnte nicht eingebunden werden. Das Programm wird abgebrochen\n"));
      	return 1;
        }
    if (rdBt_restoreFsArchiv->isChecked()){
        TreeviewRead *dialog1 = new TreeviewRead;
        dialog1->exec();
        file_net = treeviewread.folder_treeview_holen(); 
        dummy = file_net;
        pos = dummy.indexOf("qt5-fs-client");
        dummy = dummy.right(dummy.size() -pos -22); 
        restore_file_name_txt ->setText(dummy);
        if (file_net != "")
	    pushButton_restore->setEnabled(true);
        }
        this->setCursor(Qt::ArrowCursor); 
        return 0;
}
void DialogNet::folder_file() {
QString homepath = QDir::homePath();
   folder_file_ = homepath + "/.qt5-fs-client/" + DateiName_net + "-" + _Datum_net + ".txt";
}

void DialogNet::closeEvent(QCloseEvent *event) {
   event->accept();
}

void DialogNet::startThread1() {
   if( thread1.isRunning() ) return;
   connect( &thread1, SIGNAL(finished()),this, SLOT(thread1Ready()));
   thread_run_net = 1;
   thread1.start();
}

void DialogNet::startThread2() {
   if( thread2.isRunning() ) return;
   connect( &thread2, SIGNAL(finished()),this, SLOT(thread2Ready()));
   thread_run_net = 2;
   thread2.start();
}

void DialogNet::startThread3() {
   if( thread3.isRunning() ) return;
   connect( &thread3, SIGNAL(finished()),this, SLOT(folder_text_einlesen()));
   thread_run_net = 1;
   thread3.start();
}

void DialogNet::thread1Ready()  {
   QString homepath = QDir::homePath();
   endeThread_net = endeThread_net + 1;
   extern int dialog_auswertung;
   this->setCursor(Qt::ArrowCursor);
   QString befehl;
   if (endeThread_net == 1) {
       pushButton_end->setEnabled(true);
       pushButton_save->setEnabled(true);
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       int anzahl  = werte_holen(2);
       QString text_integer = QString::number(anzahl);
       AnzahlgesicherteFile ->setText(text_integer);
       int cnt_regfile = werte_holen(6);
       QString cnt_regfile_ = QString::number(cnt_regfile);
       int cnt_dir = werte_holen(7);
       QString cnt_dir_ = QString::number(cnt_dir); 
       int cnt_hardlinks = werte_holen(8);
       cnt_hardlinks = cnt_hardlinks + werte_holen(9);
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       int cnt_special = werte_holen(10);
       QString cnt_special_ = QString::number(cnt_special); 
       int err = werte_holen(17);
       if (dialog_auswertung == 0 and err == 10){ 
       // Ausgabe progressBar durch Timer unterbinden
       stopFlag_ = 1; 
       if (befehl_pbr_net == "")
          {
       QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been backed up.", " spezielle Daten wurden gesichert."));
          } 
          if (befehl_pbr_net != "") 
          {
           QMessageBox::about(this, tr("Note", "Hinweis"), 
           tr("The partition was successfully backed up.\n", "Die Partition wurde erfolgreich gesichert.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") 
        + cnt_special_ + tr(" specials and the Partition Boot Record have been backed.", " spezielle Daten und der Partition Boot Sektor wurden gesichert."));
          }
     }
     if (dialog_auswertung == 0 and err != 10){ 
       pushButton_save->setEnabled(false);
       //Beschreibungsdate löschen
     	QString filename = SicherungsDateiName_net;
        int pos = filename.indexOf("fsa");
       	filename = filename.left(pos);
       	filename.insert(pos, QString("txt"));
        QFile f(filename);
        // Prüfen ob text-Datei vorhanden 
        if (f.exists())
            befehl = "rm "  + filename;
        if(system (befehl.toLatin1().data()))
            befehl = "";
        if (flag_end_net == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The backup of the partition was aborted by the user!\n", "Die Sicherung der Partition/des Verzeichnisses wurde vom Benutzer abgebrochen!\n") );
         pushButton_save->setEnabled(true);
	}
        // Prüfen ob Partitionsart unterstützt wird      
       int part_testen = werte_holen(3);
       if (part_testen == 110){ 
       QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported.\n", "Der Partitionstyp wird nicht unterstützt\n" ));
       flag_end_net = 1;
          } 
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       part_testen = werte_holen(4);
       if (part_testen == 108 && flag_end_net == 0){
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
       if (part_testen != 108 && flag_end_net == 0){
       QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The backup of the partition was only partially successful.\n", "Die Sicherung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been backed\n.", " spezielle Daten wurden gesichert\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ + tr(" specials were not properly backed\n."," spezielle Daten wurden nicht korrekt gesichert.\n"));
	  }
        }
       
     }
  int net_art = cmb_Net->currentIndex();   
  if (net_art == 0) //Samba
       befehl = "umount -f " + homepath + "/.qt5-fs-client 2>/dev/null";
  if (net_art == 1) //NFS
      // befehl = "/etc/init.d/nfs-kernel-server restart";
         befehl = "umount -a -t nfs 2>/dev/null";
  if(system (befehl.toLatin1().data()))
     befehl = "";
  thread_run_net = 0;
  thread1.exit();
}

void DialogNet::thread2Ready() 
   {
   QString homepath = QDir::homePath();
   QString befehl;
   endeThread_net = endeThread_net + 1;
   this->setCursor(Qt::ArrowCursor);
   int meldung = werte_holen(4);
   int i = 0;
   if (meldung == 105) {
      QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The partition to be restored is mounted. It must be unmounted first!\n", "Die Partition die wiederhergestellt werden soll, ist eingehängt. Sie muss zunächst ausgehängt werden!\n"));
      endeThread_net = 0;
       }
   if (endeThread_net == 1) { 
     pushButton_end->setEnabled(true);
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
       stopFlag_ = 1; 
       pushButton_restore->setEnabled(true);
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       //PBR nicht herstellen
       i = 2;
	if (befehl_pbr_net != "") 
    	i = system (befehl_pbr_net.toLatin1().data());
	if (i!=0 ) { 
       		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition/das Verzeichnis wurde erfolgreich wieder hergestellt.\n") + 		cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been restored.", " spezielle Daten wurden wieder hergestellt."));
        }
        //PBR herstellen
	if (i==0) { 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links ", " Links ") + cnt_special_ + tr(" specials and the Partition Boot Record have been restored.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt."));
        } 
        }
       if (flag_end_net == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The restore of the partition was aborted by the user!\n", "Die Wiederherstellung der Partition wurde vom Benutzer abgebrochen!\n") );
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
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been restored\n.", " spezielle Daten wurden wiederhergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
               }
      if (i==0) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials and the Partition Boot Record have been restored\n.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt\n.") + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
                }
             }
     if (meldung == 102) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
        tr(" You have tried to restore a partition. The selected file can only recover directories. Please restart the program.\n", "Sie haben versucht eine Partition wiederherzustellen. Die gewählte Datei kann nur Verzeichnisse wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 103) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben. \n"));
        endeThread_net = 0;
        lineKey->setText ("");
      }
      if (meldung == 104) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
        tr("You have tried to restore a directory. The selected file can only recover partitions. Please restart the program.\n", "Sie haben versucht ein Verzeichnis wiederherzustellen. Die gewählte Datei kann nur Partitionen wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
    }
    int net_art = cmb_Net->currentIndex();
    if (net_art == 0) //Samba
       befehl = "umount -f " + homepath + "/.qt5-fs-client 2>/dev/null";
    if (net_art == 1) //NFS
      //befehl = "/etc/init.d/nfs-kernel-server restart";
       befehl = "umount -a -t nfs 2>/dev/null";
    if(system (befehl.toLatin1().data()))
        befehl = "";
    thread_run_net = 0;
    thread2.exit();
}

void DialogNet::elapsedTime()
 {
    sekunde_elapsed_net = sekunde_elapsed_net + 1; 
    sekunde_summe_net = sekunde_summe_net + 1; 
    if (sekunde_elapsed_net == 60) {
        sekunde_elapsed_net = 0 ;
        minute_elapsed_net = minute_elapsed_net + 1;
       }
    QString sekunde_ = QString::number(sekunde_elapsed_net);
    SekundeElapsed ->setText(sekunde_);
    QString minute_ = QString::number(minute_elapsed_net);
    MinuteElapsed ->setText(minute_);
}

void DialogNet::remainingTime(int prozent)
 {
    if (prozent <= 1) 
       sekunde_tara_net = sekunde_summe_net ;
    int sekunde_netto = sekunde_summe_net - sekunde_tara_net;

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

void DialogNet::indicator_reset() {
     // Anzeige zurücksetzen für neuen Aufruf fsarchiver
     progressBar->setValue(0);
     AnzahlgesicherteFile ->setText(0);
     AnzahlsaveFile ->setText(0); 
     SekundeRemaining ->setText(" ");
     MinuteRemaining ->setText(" ");
     SekundeElapsed ->setText("0");
     MinuteElapsed ->setText("0");
     sekunde_summe_net = 0;
     minute_elapsed_net = 0;
     endeThread_net = 0;
     sekunde_elapsed_net = 0;
     minute_elapsed_net = 0;
}

int DialogNet::testDateiName(string endung)
{
  std::string str (file_net.toLatin1().data());
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

void DialogNet::ViewProzent()
{
int prozent = 0;
QString sekunde;
int sekunde_ = 0;
QString minute;
int minute_ = 0;
int meldung = 0;
int anzahl = 0;
int anzahl1 = 0;
QString text_integer;

if (endeThread_net !=1)
{
 timer->singleShot( 1000, this , SLOT(ViewProzent( )) ) ;
  elapsedTime();
  this->repaint();
  meldung = werte_holen(4);
  if (meldung >= 100) // Thread Abschluss mit Fehler
   		return;
if (flag_View_net == 1)
	{
 	anzahl  = werte_holen(2);
 	text_integer = text_integer.setNum(anzahl);
 	AnzahlsaveFile ->setText(text_integer);
 	anzahl1  = werte_holen(3);
 	text_integer = text_integer.setNum(anzahl1);
 	AnzahlgesicherteFile ->setText(text_integer);
	}
 prozent = werte_holen(1);
 if (dummy_prozent_net != prozent)
     remainingTime(prozent);
 else {
        if (prozent > 5)
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
 dummy_prozent_net = prozent;
 }
// bei mehrmaligem Aufruf von fsarchiver wird am Anfang der Sicherung kurzfristig 100 % angezeigt, was falsch ist
 if (prozent != 100 && stopFlag_ == 0)  
  	progressBar->setValue(prozent);
 return;
} 


void DialogNet::keyPressEvent(QKeyEvent *event) {
     QWidget::keyPressEvent(event);
     switch( event->key() ) {
         case Qt::Key_Escape:
              	esc_end(); 
         break;
     }
}

int DialogNet::questionMessage(QString frage)
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

void DialogNet::esc_end()
{
MWindow window;
QString befehl;
QString pid_qt_fsarchiver;
   //    pid_qt_fsarchiver = window.pid_ermitteln_("qt5-fsarchiver"); 

      int ret = questionMessage(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
      if (ret == 1)
        {
	befehl = "rm " + SicherungsFolderFileName_net;
        if(system (befehl.toLatin1().data()))
           befehl = "";
        int pos = SicherungsFolderFileName_net.indexOf("fsa");  //fsa-Datei löschen
       	SicherungsFolderFileName_net = SicherungsFolderFileName_net.left(pos);
       	SicherungsFolderFileName_net.insert(pos, QString("txt"));
        befehl = "rm "  + SicherungsFolderFileName_net;  //txt-Datei löschen
        if(system (befehl.toLatin1().data()))
           befehl = "";
        // pbr-Datei löschen
        pos = SicherungsFolderFileName_net.indexOf("txt");
        SicherungsFolderFileName_net = SicherungsFolderFileName_net.left(pos);
        SicherungsFolderFileName_net.insert(pos, QString("pbr"));
        befehl = "rm " + SicherungsFolderFileName_net;
        if(system (befehl.toLatin1().data()))
           befehl = "";
        befehl = "kill -15 " + pid_qt_fsarchiver;  //qt5-fsarchiver abbrechen  
        if(system (befehl.toLatin1().data()))
           befehl = "";   
        close();
	}
}

void DialogNet::folder_text_einlesen()
{
QString homepath = QDir::homePath();	
QStringList folder;
QString folder_[500];
int found = 0;
QString befehl;
QStringList filters;
QString filename = homepath + "/.config/qt5-fsarchiver/folder.txt";
QFile file1(filename);
QTextStream ds(&file1);
QString folder_teilen;
int jj= 0;
        if (rdBt_saveFsArchiv->isChecked()){ //Verzeichnisse auswerten
      	    if( file1.open(QIODevice::ReadOnly|QIODevice::Text)) 
      	    {
        	while (!ds.atEnd())
        	{
        	folder_teilen= ds.readLine();
        	  do{
    		    found=folder_teilen.indexOf("  ");
	     	    if (found > 0)
             	    	folder_teilen.replace("  ", " ");
		     }
		while  (found >= 0);
            folder = folder_teilen.split(" ") ;
            folder_[jj] = folder[folder.size()-1];
            jj = jj + 1;
 	    } 
 	}      
 	file1.close();
        }
        if (rdBt_restoreFsArchiv->isChecked()){ //Verzeichnisse und Dateien auswerten
      	    if( file1.open(QIODevice::ReadOnly|QIODevice::Text)) 
      	       {
                folder_teilen= ds.readLine();
                QThread::msleep(5 * sleepfaktor);
        	while (!ds.atEnd())
        	{
        	folder_teilen= ds.readLine();
                   if (folder_teilen.left(1) == "d" || folder_teilen.right(4) == ".fsa")  //nochmals prüfen
                      { 
		      do{
    			found=folder_teilen.indexOf("  ");
			if (found > 0)
             	    	   folder_teilen.replace("  ", " ");
		        }
			while  (found >= 0);
                      folder = folder_teilen.split(" ") ;
                      folder_[jj] = folder[folder.size()-1];
                      jj = jj + 1;
                      }
 	         } 
 	}      
 	file1.close();
        }
 	befehl = "rm " + homepath + "/.config/qt5-fsarchiver/folder.txt";
 	//system (befehl.toLatin1().data()); 
}

void DialogNet::zip_einlesen_net() {
int zip = cmb_zip->currentIndex();
    if (zip == 10) 
       cmb_zstd_net->setEnabled(true);
    else
       cmb_zstd_net->setEnabled(false);
}

void DialogNet::save_attribut_net(QString attribut)
{
QString homepath = QDir::homePath();
QString dateiname = homepath + "/.config/qt5-fsarchiver/attribute.txt";
QFile file(dateiname);
file.open(QIODevice::WriteOnly);
QDataStream out(&file);
out << attribut;
file.close();
}

int DialogNet::questionMessage_net(QString frage)
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

QString DialogNet::Zeit_auslesen_net(){
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
    _Datum_net = Datum_akt.setNum(Tag) + "-" ; 
    _Datum_net = _Datum_net + Datum_akt.setNum(Monat) + "-" ;
    _Datum_net = _Datum_net + Datum_akt.setNum(Jahr) ;
    return _Datum_net;
}

//Mountpoint ermitteln
QString DialogNet::mtab_einlesen_net(int zahl)
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
 











