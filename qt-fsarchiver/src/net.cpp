/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2020 Dieter Baum.  All rights reserved.
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

using namespace std;

extern int dialog_auswertung;
extern QString add_part[100]; 
extern QString parameter[15];
extern QString folder_file_;
extern QString part[100][10];
extern QString user;
extern int flag1;
//QString folder_file_1;
QString zip_net[11];
QString folder_net;
QString file_net;
QString folder_free;
QString folder_free_[100];
QString partition_net; // z.B 192.168.2.5
QString partition_net_; // z.B sda1
QString UUID_net;
QString partition_typ_net;
QString DateiName_net("") ;
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
QString userpath_net;
extern int sleepfaktor;
int nameflag = 0;
int liveFlag_net = 0;
int row_net = 0;
int rootpassword_net = 0;
QString name_txt_file;
QString homepath_net = QDir::homePath();
bool ok;

DialogNet::DialogNet()
{
QString befehl; 
QStringList items;
QStringList items_kerne_; 
setupUi(this); // this sets up GUI
        userpath_net = homepath_net; 
        folder_net = userpath_net + "/.qt-fs-client";
        if ( dialog_auswertung == 6)
        	rdBt_saveFsArchiv->setChecked(true);
        else
		rdBt_restoreFsArchiv->setChecked(true);
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
      //  QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
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
        //connect( pushButton_break, SIGNAL( clicked() ), this, SLOT(esc_end()));
        connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
        connect( bt_net_art, SIGNAL( clicked() ), this, SLOT(cmb_net()));
        connect( bt_toParent, SIGNAL( clicked() ), this, SLOT(button_toParent()));
        connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem *, int)), this, SLOT(listWidget_tree_auslesen(QTreeWidgetItem *, int)));
        connect(treeWidget, SIGNAL(doubleClicked(QTreeWidgetItem *, int)), this, SLOT(listWidget_tree_auslesen(QTreeWidgetItem *, int)));
        connect( bt_treeWiget, SIGNAL( clicked() ), this, SLOT(treeWidget_auslesen()));
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
        items_Net << "Samba" << "SSH" << "NFS";
        //items_Net << "Samba" << "NFS";
	cmb_Net->addItems (items_Net);
	items_Net.clear();
        items_kerne_ << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12";
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
   	QFile file1(userpath_net + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
        cmb_Net -> setCurrentIndex(0);
        treeWidget->setHidden(true);
        listWidget ->setHidden(false);
     if (file1.exists()) {
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
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
          
    QFile file(userpath_net + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
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
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
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
       // dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);
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
        listWidget_free_folder->setHidden(false);
        treeWidget->setHidden(true);
	bt_toParent ->setHidden(true);
        Daten_Samba_eintragen();}
if (net_art == 1){
        listWidget_free_folder->setHidden(true);
        treeWidget->setHidden(false);
	bt_toParent ->setHidden(false);
	QString index = QString::number(net_art);
        Daten_SSH_eintragen();}
if (net_art == 2){
        listWidget_free_folder->setHidden(false);
        treeWidget->setHidden(true);
	bt_toParent ->setHidden(true);
	QString index = QString::number(net_art);
        Daten_NFS_eintragen();
       	}
}

void DialogNet:: end()
{ 
QString befehl;
QString filename;
QString attribute;
        attribute = "-f" + userpath_net + "/.qt-fs-client 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute; //umount samba
	if(system (befehl.toLatin1().data()))
           befehl = "";   
        attribute = "-u " + userpath_net + "/.qt-fs-client 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  17 " + attribute; //fusermount 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        attribute = "-a -t nfs 2>/dev/null";
        befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount nfs
       if(system (befehl.toLatin1().data()))
           befehl = "";
       cmbFlag = 0;
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

void DialogNet:: Daten_SSH_eintragen()
{

	this->setCursor(Qt::WaitCursor);
        bt_toParent->setEnabled(true);
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
        // Ordner ermitteln
        listWidget_tree_eintragen(rechner_IP, key_net, user_net, "/", 0);
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

int DialogNet::nfs_search_folder_free(QString rechner_IP){
QString befehl;
int i = 0;
QString text;
QStringList items;
listWidget_free_folder -> clear();
	// freigegebene Verzeichnisse ermitteln
        QFile file(userpath_net + "/.config/qt-fsarchiver/smbclient.txt");
	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
             {
            befehl = "showmount -e " + rechner_IP + " 1> " +  userpath_net + "/.config/qt-fsarchiver/smbclient.txt";
	    if(system (befehl.toLatin1().data()))
                befehl = "";
            while (text == ""){
             text = ds.readLine();
             QThread::msleep(5 * sleepfaktor);
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

int DialogNet::search_folder_free(QString rechner_IP){
QString befehl;
int line = 0;
int i = 0;
int pos = 0;
QString text;
QStringList items;
listWidget_free_folder -> clear();
	// freigegebene Verzeichnisse ermitteln
    	
        QFile file(userpath_net + "/.config/qt-fsarchiver/smbclient.txt");
	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
             {
            befehl = "smbclient -N -L" + rechner_IP + " 1> " +  userpath_net + "/.config/qt-fsarchiver/smbclient.txt";
	    if(system (befehl.toLatin1().data()))
                 befehl = ""; 
            while (text == ""){
             text = ds.readLine();
             QThread::msleep(5 * sleepfaktor);
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

QString DialogNet::hostname()
{
// eigenen Hostname einlesen
QString filename = userpath_net + "/.config/qt-fsarchiver/hostname.txt";
QFile file(filename);
QString befehl;
    	QTextStream ds(&file);
        QString text; 
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
             {
             befehl = "/usr/sbin/qt-fsarchiver.sh  11 /etc/hostname " + filename;
       if(system (befehl.toLatin1().data()))
           befehl = "";
        while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            } 
         }
        file.close();
     text = text.toLower();
     return text;
}

int DialogNet::savePartition() {
flag1 = 1;
MWindow window;
flag1 = 0;
//folder_dir_net.append  (dirModel->filePath(index));
//folder_dir_net =  (dirModel->filePath(index));
QFileInfo info(folder_dir_net); 
FileDialog filedialog;
QFile file(folder_net);
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[10][20];
int k = 0;
QString dummy;
QString attribute;
QFile file1(userpath_net + "/.config/qt-fsarchiver/zahlen.txt");
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
     int stop = 0;
     QString compress = "";
     attribute = "chown -R " + user + " " + userpath_net + "/.config/qt-fsarchiver";
     befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
     if(system (befehl.toLatin1().data()))
         befehl = "";
     QFile::remove(userpath_net + "/.config/qt-fsarchiver/zahlen.txt");  
     if (file1.exists())
        {
        QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Error. The file ~/config/qt-fsarchiver/zahlen.txt could not be deleted by qt-fsarchiver. The program is terminated. Manually delete the mentioned file and start the program again.\n", "Fehler. Die Datei ~/config/qt-fsarchiver/zahlentext konnte von qt-fsarchiver nicht gelöscht werden. Das Programm wird beendet. Löschen Sie manuell die genannte Datei und starten das Programm erneut.\n"));
        window.del_mediafolder();
        return 1;
        }
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
        if (file.open(QIODevice::ReadOnly))
        	  {
                QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("You have selected a file. You must select a directory\n", "Sie haben eine Datei ausgewählt. Sie müssen ein Verzeichnis auswählen\n"));
		file.close();
		return 0 ;
 	        }
       this->setCursor(Qt::WaitCursor);
       QString zeichen = "'";
       if (net_art == 1) //SSH
           stop = folder_free_mounten();
       if (stop == 256){
           return 1;}
       if (net_art == 0){  //Samba
         attribute = "-t cifs -o username=" + user_net + ",password=" + key_net + ",uid=0,gid=0 //" + rechner_IP + "/'" + folder_free + "' " + userpath_net + "/.qt-fs-client";
         befehl = "/usr/sbin/qt-fsarchiver.sh  19 " + attribute; 
         k = system (befehl.toLatin1().data());
       	}
       if (net_art == 2){ //NFS
           attribute = rechner_IP + ":" + folder_free +  " " + userpath_net + "/.qt-fs-client" ; //mounten
           befehl = "/usr/sbin/qt-fsarchiver.sh  2 " + attribute; 
           k = system (befehl.toLatin1().data());
	} 
        QThread::msleep(50 * sleepfaktor);
        this->setCursor(Qt::ArrowCursor); 
        if (k != 0){
   	QMessageBox::warning(this, tr("Note", "Hinweis"),
      	tr("The network computer ",  "Der Netzwerkrechner ") + rechner_IP + tr(" could not be integrated. The program is aborted\n", " konnte nicht eingebunden werden. Das Programm wird abgebrochen\n"));
        return 1;}
         _Datum_net = Zeit_auslesen_net();
         state = chk_Beschreibung->checkState();
         zip = cmb_zip->currentIndex();
         if (zip == -1)
            zip = 3;
         int liveFlag = 0;
         int row;
         // Werte sammeln und nach file_dialog übergeben, Partition ist eingehängt
         row = listWidget->currentRow();
         text = window.beschreibungstext(DateiName_net + "-" + _Datum_net + ".fsa", zip, row);
         filedialog.werte_uebergeben(text);
         //Überprüfung ob gemounted
         if (!window.is_mounted(partition_net_.toLatin1().data())) 
            {
		   UUID_net = window.UUID_auslesen(listwidgetrow);
                   liveFlag_net = 0;
		   part_art_net = mtab_einlesen_net(row);
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
                                    befehl = "/usr/sbin/qt-fsarchiver.sh  4 /media/" + partition_net_;
                               else
                                    befehl = "/usr/sbin/qt-fsarchiver.sh  4 /dev/" + partition_net_;
                               err = system (befehl.toLatin1().data());
                               if(part[listwidgetrow][7] != "")
                                    befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + part[listwidgetrow][7]; 
                               err = err + system (befehl.toLatin1().data());   
                               }
                           if (err != 0 && liveFlag == 0)
                                {
				QMessageBox::warning(this, tr("Note", "Hinweis"),
         			tr("The partition ", "Die Partition ")   + partition_net_ + 
				tr("cannot be unmounted. The program is aborted.\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
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
                                    if (!ok)  //Cancel Programm wird beendet
                                         window.kill_end();
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
                                  // Vorbereitung für psb
				 QString befehl_pbr_net = "/usr/sbin/qt-fsarchiver.sh  12 if=/dev/" + partition_net_ + " of=" + folder_net + "/" + DateiName_net + "-" + _Datum_net + ".pbr bs=512 count=1";
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
             			 if (wert == 0 && dialog_auswertung == 0)
                		      {
                		      QMessageBox::warning(this, tr("Note", "Hinweis"),
         			      tr("The backup was aborted by the user\n", "Die Sicherung wurde vom Benutzer abgebrochen\n"));
				      pushButton_save->setEnabled(true);
                                      return 0;
                		      }
                	         }
				//txt-Datei von /.config/qt-fsarchiver in die gemeountete Partition kopieren
                                attribute = folder_file_ + " " + userpath_net + "/.qt-fs-client/" +  DateiName_net + "-" + _Datum_net + ".txt";
                                befehl = "/usr/sbin/qt-fsarchiver.sh  11 " + attribute;  //Datei kopieren
                              if(system (befehl.toLatin1().data()))
                                    befehl = "";
                               QString attribute; 
			       for ( int i=0; i<15; i++)
  				  {
  				  if (parameter[i] != " ")
     				  attribute = attribute + " " + parameter[i];
  				  }
				attribute = QString::number(indizierung + 2)  + attribute;
                                save_attribut_net(attribute);
				pushButton_end->setEnabled(false);  
                                pushButton_save->setEnabled(false); 
                                flag_View_net = 1;
                                ViewProzent();
                                stopFlag_ = 0;
                                this->setCursor(Qt::WaitCursor);
  				befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_net;
                               if(system (befehl.toLatin1().data()))
                                    befehl = "";
        		        }
                       }
                               return 0;
}  

int DialogNet::restorePartition() {
flag1 = 1;
MWindow window;
flag1 = 0;
Qt::CheckState state1;
//folder_dir_net.append  (dirModel->filePath(index));
//folder_dir_net =  (dirModel->filePath(index));
QFileInfo info(folder_dir_net); 
QFile file(file_net);
QString DateiName("") ;
int err = 0;
QString keyText = "";
QString dev_part;
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
QFile file1(userpath_net + "/.config/qt-fsarchiver/zahlen.txt");
        state1 = chk_key->checkState();
	indicator_reset();
	befehl = "/usr/sbin/qt-fsarchiver.sh  5 " + userpath_net + "/.config/qt-fsarchiver/zahlen.txt 2>/dev/null"; 
        if(system (befehl.toLatin1().data()))
               befehl = "";
        if (file1.exists())
        {
        QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Error. The file ~/config/qt-fsarchiver/zahlen.txt could not be deleted by qt-fsarchiver. The program is terminated. Manually delete the mentioned file and start the program again.\n", "Fehler. Die Datei ~/config/qt-fsarchiver/zahlentext konnte von qt-fsarchiver nicht gelöscht werden. Das Programm wird beendet. Löschen Sie manuell die genannte Datei und starten das Programm erneut.\n"));
        window.del_mediafolder();
        return 1;
        }
        int net_art = cmb_Net->currentIndex();
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
          if (net_art == 1) //SSH
              folder_free_mounten();
          this->setCursor(Qt::WaitCursor);  
          this->setCursor(Qt::ArrowCursor);
		// Archinfo einholen um Originalpartition einzulesen und Verschlüsselung überprüfen.
                // das zurücksichern Partition oder Verzeichnis
               // Annahme zunächst kein Schlüssel
               parameter[0] = "fsarchiver";
       	       parameter[1] = "archinfo";
		if (state1 != Qt::Checked) {
               		parameter[2] = file_net;
               		attribute = parameter[0] + " " + parameter[1] + " " + parameter[2];
  			attribute = "3 " + attribute;
                        save_attribut_net(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_net;
                       if(system (befehl.toLatin1().data()))
                           befehl = "";
                        QThread::msleep(10 * sleepfaktor);
                        optionkey = datei_auswerten_net("s");
                        QThread::msleep(10 * sleepfaktor);
                        if(optionkey == "112") {    
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
                                lineKey->setText ("");
                  		return 0 ; 
               	   		}
			parameter[4] = file_net;
                        attribute = parameter[0] + " " + parameter[1] + " " + parameter[2] + " " + parameter[3] + " " + parameter[4];
                        attribute = "5 " + attribute;
                        save_attribut_net(attribute);
                        befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_net;
                       if(system (befehl.toLatin1().data()))
                            befehl = "";
                        QThread::msleep(10 * sleepfaktor);
                        optionkey = datei_auswerten_net("s");
                        QThread::msleep(10 * sleepfaktor);
                        if (optionkey == "112"){
                            QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                           befehl = "/usr/sbin/qt-fsarchiver.sh  5 " + userpath_net + "/.config/qt-fsarchiver *.txt 2>/dev/null"; 
                         if(system (befehl.toLatin1().data()))
                              befehl = "";
                          return 0;
                        }
                }
                //Überprüfen, ob in die Originalpartition zurückgeschrieben werden soll
                while (dev_part == ""){
                QThread::msleep(10 * sleepfaktor);
                dev_part = datei_auswerten_net("r");
                }
                if (dev_part != "/dev/" + partition_net_){
                   cmp = questionMessage_net(tr("The partition to be recovered ", "Die wiederherzustellende Partition ") +  "/dev/" + partition_net_ + tr(" does not match the backed up partition.", " stimmt nicht mit der gesicherten ") + dev_part + tr("Do you still want to perform the restore?", " überein. Wollen Sie trotzdem die Wiederherstellung durchführen?"));
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
           		dialog_auswertung = 3;
              		FileDialog Filedialog;
     	       		FileDialog *dlg = new FileDialog;
     	     		// dlg->show(); nicht modal
             		int wert = dlg->exec();
             		if (wert == 0 && dialog_auswertung == 0)
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
        			befehl_pbr_net = "if="+ filename + " of=/dev/" + partition_net_ + " bs=512 count=1";
		         }
                        }
                     if (!window.is_mounted(partition_net_.toLatin1().data()))
                       {
                       UUID_net = window.UUID_auslesen(listwidgetrow);

                      part_art_net = mtab_einlesen_net(listwidgetrow);
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
                   if (part_art_net != "system" && part_art_net != "home")
                	{
                       if(partition_net_.indexOf("/dm-") > -1)
                             attribute = "/media/" + partition_net_  + " 2>/dev/null";  //LVM, Raid
                       else
                             attribute = "/dev/" + partition_net_  + " 2>/dev/null";    //nicht LVM, Raid
                       befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
                       err = system (befehl.toLatin1().data()); 
                       if (err != 0)
                                {
				QMessageBox::about(this, tr("Note", "Hinweis"),
         			tr("The partition", "Die Partition ")   + partition_net_ + 
         			tr("can not be unmounted. The program is terminated\n", " kann nicht ausgehängt werden. Das Programm wird abgebrochen\n"));
                                return 0 ; 
                                }  
                          }
                                
                 } 
   	if (rdBt_restoreFsArchiv->isChecked())
              {
if (partition_typ_net == "btrfs"){
                 QThread::msleep(20 * sleepfaktor);
                 befehl = "/usr/sbin/qt-fsarchiver.sh  4 /dev/" + partition_net_; // unmounten
 		if(system (befehl.toLatin1().data()))
                     befehl = "";
                 befehl = "/usr/sbin/qt-fsarchiver.sh  7 -f /dev/" + partition_net_; // Partition anlegen
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
               int indizierung = 4;
               if (state1 == Qt::Checked) { // Verzeichnis mit Schlüssel gesichert
                    parameter[3] = "-c";
                 parameter[4] = keyText;
                 int len = parameter[4].size();
               	    if (len < 6 || len > 64) {
                  	QMessageBox::about(this, tr("Note", "Hinweis"),
         	  	tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  	return 0 ; 
               	   }
                 parameter[5] = file_net;
                 indizierung = 5;
                 parameter[6] = "id=0,dest=/dev/" + partition_net_;
                 indizierung = 6;
                 }
                attribute = " ";
                for ( int i=0; i<15; i++)
  		  {
  		  if (parameter[i] != "")
                    {
     		    attribute = attribute + " " + parameter[i];
                    }
  		  }
                  attribute = QString::number(indizierung + 1)  + attribute;
		 // attribute = QString::number(j - 2)  + attribute;
                  save_attribut_net(attribute);
               pushButton_restore->setEnabled(false);
               pushButton_end->setEnabled(true); 
               flag_View_net = 2;
  	       ViewProzent();
               stopFlag_ = 0;
               this->setCursor(Qt::WaitCursor);
               befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_net;
              if(system (befehl.toLatin1().data()))
                   befehl = "";
               }
     }
   return 0;
}

void DialogNet::addWidget() {
int i = 0;
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
    partition_net_ = add_part[listwidgetrow];
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
QString befehl;
QString attribute;
QString dummy;
int k = 0;
int pos = 0;
int ret = 0;
int net_art = cmb_Net->currentIndex();
    TreeviewRead treeviewread;
    int row;
    this->setCursor(Qt::WaitCursor); 
    restore_file_name_txt ->setText("");
    row = listWidget_free_folder->currentRow();
    row_net = row;
    if (row > -1)
    	folder_free = folder_free_[row];
    int found=folder_free.indexOf(" ");
    if (found > -1 && rdBt_saveFsArchiv->isChecked())
           {
           ret = questionMessage(tr("There is a blank space in the name of the backup/restore directory. It is safer to use a directory without a space. If you still want to continue?", "In dem Verzeichnisnamen ist eine Leerstelle vorhanden. Es ist sicherer ein Verzeichnis ohne Leerstelle zu verwenden. Wollen Sie dennoch fortfahren?"));
           if (ret == 2)
              {
              this->setCursor(Qt::ArrowCursor); 
              close();;
              return 1;
              }
           }
           
         
     if (rdBt_restoreFsArchiv->isChecked() && net_art == 0) //Samba
       {
       //Verzeichnis mounten
       this->setCursor(Qt::WaitCursor);
       attribute = userpath_net + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
       k = system (befehl.toLatin1().data()); 
       QThread::msleep(10 * sleepfaktor); 
       attribute = "-t cifs -o username=" + user_net + ",password=" + key_net + ",uid=0,gid=0 //" + rechner_IP + "/'" + folder_free + "' " + userpath_net + "/.qt-fs-client";
       befehl = "/usr/sbin/qt-fsarchiver.sh  19 " + attribute;
       k = system (befehl.toLatin1().data());
       QThread::msleep(50 * sleepfaktor);
       }
    if (rdBt_restoreFsArchiv->isChecked() && net_art == 2) //NFS
       {
       //Verzeichnis mounten
       this->setCursor(Qt::WaitCursor);
       attribute = rechner_IP + ":" + folder_free + " " + userpath_net + "/.qt-fs-client" ;
       befehl = "/usr/sbin/qt-fsarchiver.sh  2 " + attribute;
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
        pos = dummy.indexOf("qt-fs-client");
        dummy = dummy.right(dummy.size() -pos - 13); 
        restore_file_name_txt ->setText(dummy);
        if (file_net != "")
	    pushButton_restore->setEnabled(true);
        }
        this->setCursor(Qt::ArrowCursor); 
        return 0;
}
void DialogNet::folder_file() {
   folder_file_ = userpath_net + "/.config/qt-fsarchiver/" + DateiName_net + "-" + _Datum_net + ".txt";
}

void DialogNet::closeEvent(QCloseEvent *event) {
   event->accept();
}

void DialogNet::thread1Ready()  {
int anzahl = 0;
QString dummy; 
QString text_integer;
QString befehl;
QString attribute;
int part_testen;
int err = 0;
int success = 0;
int net_art = cmb_Net->currentIndex();  
   this->setCursor(Qt::ArrowCursor);
   if (endeThread_net !=0) {
     if (net_art == 1) //SSH
       {
       //befehl = "/etc/init.d/ssh restart";
       attribute = "-u " + userpath_net + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  17 " + attribute;  //fuserufusermount -umount
       }
     if (net_art == 0) //Samba
       {
       attribute = "-f " + userpath_net + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
       }
     if (net_art == 2) //NFS
     {
      // befehl = "/etc/init.d/nfs-kernel-server restart";
         attribute = "-a -t nfs 2>/dev/null";
         befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
     }
     if(system (befehl.toLatin1().data()))
           befehl = "";
        // wurde nicht erfolgreich gemeounted wurde in die Datei .qt-fs-client gesichert.
        // in diesem Fall verbleibt nach dem entmounten die gesicherten Datein in dem Ordner .qt-fs-client
        // Es wird geprüft ob die fsa-Datei vorhanden ist oder nicht
      QThread::msleep(25 * sleepfaktor);
      QString filename = userpath_net + "/.qt-fs-client/" + name_txt_file;
      QFile file(filename);
      if (file.exists())
           {
           success = 1;
           befehl = "/usr/sbin/qt-fsarchiver.sh  10 rm " + filename + " 2>/dev/null"; 
           if(system (befehl.toLatin1().data()))
               befehl = "";
           filename = filename.left(filename.size()-3) + "txt";
           befehl = "/usr/sbin/qt-fsarchiver.sh  10 rm " + filename + " 2>/dev/null"; 
           if(system (befehl.toLatin1().data()))
              befehl = "";
           } 
      // die Dateien fsa umd txt müssen gelöscht werden
       dummy = datei_auswerten_net("p"); 
       err = dummy.toInt();
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/anzahlfile.txt");
       anzahl  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
       if (anzahl != 0) { 
          text_integer = text_integer.setNum(anzahl);
           }
       AnzahlgesicherteFile ->setText(text_integer);
       dummy = datei_auswerten_net("b"); 
       anzahl  = dummy.toInt();
       text_integer = QString::number(anzahl);
      // AnzahlgesicherteFile ->setText(text_integer);
       dummy = datei_auswerten_net("f"); 
       int cnt_regfile  = dummy.toInt();
       QString cnt_regfile_ = QString::number(cnt_regfile);
       dummy = datei_auswerten_net("g"); 
       int cnt_dir  = dummy.toInt();
       QString cnt_dir_ = QString::number(cnt_dir); 
       dummy = datei_auswerten_net("h"); 
       int cnt_symlinks  = dummy.toInt();
       QString cnt_symlinks_ = QString::number(cnt_symlinks);
       dummy = datei_auswerten_net("i"); 
       int cnt_hardlinks  = dummy.toInt(); 
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       cnt_hardlinks = cnt_hardlinks + cnt_symlinks;
       cnt_hardlinks_ = QString::number(cnt_hardlinks);
       dummy = datei_auswerten_net("j"); 
       int cnt_special  = dummy.toInt();
       QString cnt_special_;
       cnt_special_ = QString::number(cnt_special);
       if (err == 10 && success == 0){ 
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
     else {
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
         tr("The backup of the partition was aborted by the user!\n", "Die Sicherung der Partition wurde vom Benutzer abgebrochen!\n") );
        }
        // Prüfen ob Partitionsart unterstützt wird      
       dummy = datei_auswerten_net("c");
       part_testen = dummy.toInt();
       if (part_testen == 110){ 
       QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported.\n", "Der Partitionstyp wird nicht unterstützt\n" ));
       flag_end_net = 1;
          } 
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       dummy = datei_auswerten_net("d");
       part_testen = dummy.toInt(); 
       if (part_testen == 108 && flag_end_net == 0){
	    QMessageBox::warning(this, tr("Note", "Hinweis"),
          tr("The partition type is not supported. Maybe the partition is encrypted?\n", "Der Partitionstyp wird nicht unterstützt. Vielleicht ist die Partition verschlüsselt?\n" ));
          }
       dummy = datei_auswerten_net("a");
       int err_regfile = dummy.toInt();    
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten_net("b");
       int err_dir = dummy.toInt();  
       QString err_dir_ = QString::number(err_dir); 
       dummy = datei_auswerten_net("c");
       int err_symlinks = dummy.toInt(); 
       dummy = datei_auswerten_net("e");
       int err_hardlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten_net("k"); //err_special
       int err_special = dummy.toInt();
       QString err_special_ = QString::number(err_special);  
       if ((part_testen != 108 && flag_end_net == 0) or success ==1){
          if (success == 1)
             {
             err_regfile_ = cnt_regfile_ ;
             err_dir_ = cnt_dir_;
             err_hardlinks_ = cnt_hardlinks_;
             err_special_ = cnt_special_;
             cnt_regfile_ = "0";
             cnt_dir_ = "0";
             cnt_hardlinks_ = "0";
             cnt_special_ = "0";
             }
       QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The backup of the partition was only partially successful.\n", "Die Sicherung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials have been backed\n.", " spezielle Daten wurden gesichert\n.")  + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories, ", " Verzeichnisse, ") + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ + tr(" special data was not saved correctly.\n."," spezielle Daten wurden nicht korrekt gesichert.\n"));
	  }
        }
     }
  lineKey->setText ("");
  pushButton_end->setEnabled(true);
  date_delete_net();
  mountflag = 0;
  sekunde_summe_net = 0;
  minute_elapsed_net = 0;
  sekunde_elapsed_net = 0;
}

void DialogNet::thread2Ready()  {
   QString befehl;
   QString attribute;
   QString dummy;
   this->setCursor(Qt::ArrowCursor);
   dummy = datei_auswerten_net("d"); 
   int meldung  = dummy.toInt();
   int i = 0;
   int err = 0;
   if (meldung == 105) {
      QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The partition to be restored is mounted. It must be unmounted first!\n", "Die Partition die wiederhergestellt werden soll, ist eingehängt. Sie muss zunächst ausgehängt werden!\n"));
      endeThread_net = 0;
       }
   if (endeThread_net != 0) { 
     dummy = datei_auswerten_net("f"); 
     int cnt_regfile  = dummy.toInt();
     QString cnt_regfile_ = QString::number(cnt_regfile);
     dummy = datei_auswerten_net("g"); 
     int cnt_dir  = dummy.toInt();
     QString cnt_dir_ = QString::number(cnt_dir); 
     dummy = datei_auswerten_net("h"); 
     int cnt_symlinks  = dummy.toInt();
     dummy = datei_auswerten_net("i"); 
     int cnt_hardlinks  = dummy.toInt();
     cnt_hardlinks = cnt_symlinks + dummy.toInt(); 
     QString cnt_hardlinks_ = QString::number(cnt_hardlinks); 
     dummy = datei_auswerten_net("j"); 
     int cnt_special  = dummy.toInt();
     QString cnt_special_;
     cnt_special_ = QString::number(cnt_special);
     dummy = datei_auswerten_net("p"); 
     err = dummy.toInt();
       //Rückmeldung von fsarchiver: Zurückschreiben erfolgreich
       if (err == 10){
       // Ausgabe progressBar durch Timer unterbinden
       stopFlag_ = 1; 
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       //Abfrage PBR herstellen ja nein
       i = 2;
	if (befehl_pbr_net != "") 
         {
         QString befehl = "/usr/sbin/qt-fsarchiver.sh  12 " + befehl_pbr_net ; 
        if(system (befehl.toLatin1().data()))
           befehl = "";
         i = 0;
         }
        //PBR nicht herstellen
	if (i!=0 ) { 
       		QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" specials has been restored.", " spezielle Daten wurden wieder hergestellt."));
        }
        //PBR herstellen
	if (i==0) { 
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The partition was successfully restored.\n", "Die Partition wurde erfolgreich wieder hergestellt.\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links ", " Links ") + cnt_special_ + tr(" special data and the partition boot sector were restored.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt."));
        } 
        }
       if (flag_end_net == 1) {
        QMessageBox::warning(this, tr("Note", "Hinweis"),
         tr("The restore of the partition was aborted by the user!\n", "Die Wiederherstellung der Partition wurde vom Benutzer abgebrochen!\n") );
	meldung = 0;
        }
     if (err != 10) {
          // Anzahl nicht korrekt zurückgeschriebene Dateien ausgeben
       dummy = datei_auswerten_net("e");
       int err_hardlinks = dummy.toInt();
       dummy = datei_auswerten_net("c");
       int err_symlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten_net("k"); 
       int err_special = dummy.toInt();
       QString err_special_ = QString::number(err_special);
       dummy = datei_auswerten_net("a"); 
       int err_regfile = dummy.toInt();
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten_net("b"); 
       int err_dir = dummy.toInt();
       QString err_dir_ = QString::number(err_dir); 
       err_hardlinks = dummy.toInt();
       err_hardlinks_ = QString::number(err_hardlinks); 
       if (i!=0) {  
       QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" special data has been restored.\n.", " spezielle Daten wurden wiederhergestellt\n.")
         + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") 
         + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ 
         + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
               }
      if (i==0) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
       	  tr("The restore of the partition was only partially successful.\n", "Die Wiederherstellung der Partition war nur teilweise erfolgreich\n") + cnt_regfile_ + tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") 
         + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" special data and the partition boot sector were restored.\n.", " spezielle Daten und der Partition Boot Sektor wurden wieder hergestellt\n.") + err_regfile_ + tr(" files, ", " Dateien, ")   + err_dir_ + tr(" directories and ", " Verzeichnisse und ") + err_hardlinks_ + tr(" links and ", " Links und ") + err_special_ + tr(" specials were not properly restored\n."," spezielle Daten wurden nicht korrekt wiederhergestellt.\n"));
                }
             }
     if (meldung == 102) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
        tr(" You have tried to restore a partition. The selected file can only recover directories. Please restart the program.\n", "Sie haben versucht eine Partition wiederherzustellen. Die gewählte Datei kann nur Verzeichnisse wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 104) { 
        QMessageBox::warning(this, tr("Note", "Hinweis"), 
        tr("You have tried to restore a directory. The selected file can only recover partitions. Please restart the program.\n", "Sie haben versucht ein Verzeichnis wiederherzustellen. Die gewählte Datei kann nur Partitionen wiederherstellen. Bitte starten Sie das Programm neu.\n"));
      }
     if (meldung == 103) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben. \n"));
        endeThread_net = 0;
        lineKey->setText ("");
      }
    }
    int net_art = cmb_Net->currentIndex();
    if (net_art == 1) //SSH
       {
       //befehl = "/etc/init.d/ssh restart";
       attribute = "-u " + userpath_net + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  17 " + attribute;  //fuserumount
       }
    if (net_art == 0) //Samba
       {
       attribute = "-f " + userpath_net + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
       }
    if (net_art == 2) //NFS
       {
      //befehl = "/etc/init.d/nfs-kernel-server restart";
       attribute = "-a -t nfs 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  4 " + attribute;  //umount
       }
    this->setCursor(Qt::ArrowCursor);
   if(system (befehl.toLatin1().data()))
           befehl = "";
    lineKey->setText ("");
    pushButton_end->setEnabled(true);
    date_delete_net();
    mountflag = 0;
    sekunde_summe_net = 0;
    minute_elapsed_net = 0;
    sekunde_elapsed_net = 0;
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
QString text;
int sekunde_ = 0;
QString minute;
int minute_ = 0;
int anzahl = 0;
int anzahl1 = 0;
QString text_integer;
QString dummy;
int dummy1 = 0;
int flag = 0;
text = datei_auswerten_net("p");
endeThread_net = text.toInt();  //10 korrekt beendet 11 fehlerhaft
if ((endeThread_net == 10 && flag_View_net == 1) || (endeThread_net == 11 && flag_View_net == 1)) //backup
   thread1Ready();
if ((endeThread_net == 10 && flag_View_net == 2) || (endeThread_net == 11 && flag_View_net == 2)) //restore
   thread2Ready();
if (endeThread_net != 10 && endeThread_net != 11)
{
 timer->singleShot( 1000, this , SLOT(ViewProzent( )) ) ;
// timer->singleShot( 100, this , SLOT(ViewProzent( )) ) ;
  elapsedTime();
  this->repaint();
  dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/meldung.txt"); 
  flag = dummy.toInt();
if (flag_View_net == 1)  //nur bei save
	{
         if (flag == 0)
         {
          dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/anzahl_file.txt"); 
          anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
          if (anzahl != 0){
  	   text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);
           }
 	}
      if (flag == 1)
 	   {
           dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/anzahl_file.txt"); 
           anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
           text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);

           dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/anzahlfile.txt");
           anzahl1  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
           if (anzahl1 != 0) { 
 	   text_integer = text_integer.setNum(anzahl1);
           AnzahlgesicherteFile ->setText(text_integer);
           }
      }     
      }
 dummy = datei_auswerten_1_net(userpath_net + "/.config/qt-fsarchiver/prozent.txt");
 dummy = dummy.left(dummy.size()-1);
 dummy1  = dummy.toInt(); // Prozent
 if (dummy1 > 0){
     prozent = dummy.toInt();
}
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
QString attribute;
QString pid_qt_fsarchiver;
QString pid_qt_fsarchiver_terminal;
      pid_qt_fsarchiver = window.pid_ermitteln_("qt-fsarchiver"); 
      pid_qt_fsarchiver_terminal = window.pid_ermitteln_("qt-fsarchiver-terminal");  
      int ret = questionMessage(tr("Do you really want to stop backing up or restoring the partition?", "Wollen Sie wirklich die Sicherung oder Wiederherstellung der Partition beenden?"));
      if (ret == 1)
        {
	attribute = "kill -15 " + pid_qt_fsarchiver_terminal;  //qt-fsarchiver-terminal abbrechen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;  
        if(system (befehl.toLatin1().data()))
           befehl = "";
        attribute = "rm " + SicherungsFolderFileName_net;	
	befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
        if(system (befehl.toLatin1().data()))
           befehl = "";
        int pos = SicherungsFolderFileName_net.indexOf("fsa");  //fsa-Datei löschen
       	SicherungsFolderFileName_net = SicherungsFolderFileName_net.left(pos);
       	SicherungsFolderFileName_net.insert(pos, QString("txt"));
        attribute = "rm "  + SicherungsFolderFileName_net;  //txt-Datei löschen
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute; 
       if(system (befehl.toLatin1().data()))
           befehl = "";
        // pbr-Datei löschen
        pos = SicherungsFolderFileName_net.indexOf("txt");
        SicherungsFolderFileName_net = SicherungsFolderFileName_net.left(pos);
        SicherungsFolderFileName_net.insert(pos, QString("pbr"));
        attribute = "rm " + SicherungsFolderFileName_net;
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

void DialogNet::addItems(const QString &name) {
   QTreeWidgetItem *root1 = new QTreeWidgetItem(treeWidget);
   root1->setText(0, name);  //zuständig für die Anzeige des Foldernamens
   if (name.right(4)== ".fsa")
      root1->setIcon(0, fileIcon );// zuständig für das Filesymbol
   else
      root1->setIcon(0, folderIcon );// zuständig für das Foldersymbol
   QList<QTreeWidgetItem *> items;
 // QTreeWidgetItem *tItem=new QTreeWidgetItem(root1); // zuständig für den Pfeil vor dem Namen
   treeWidget->addTopLevelItems(items);
}


void DialogNet::listWidget_tree_auslesen(QTreeWidgetItem *item, int)
{
NetEin netein;	
QString rechner;
	QString name = item->text(0);
	rechner = netein.Namen_holen();
   	user_net = netein.user_holen(); 
   	key_net = netein.key_holen();
        listWidget_tree_eintragen(rechner_IP, key_net, user_net, "/" + name, 0);
}

void DialogNet::listWidget_tree_auslesen_1()
{
NetEin netein;	
QString rechner;
QString name = " ";
       if(nameflag == 0)
          {QTreeWidgetItem *current = treeWidget->currentItem();
          name = current->text(0);}
       rechner = netein.Namen_holen();
       user_net = netein.user_holen(); 
       key_net = netein.key_holen();
       folder_free = pfad_forward + "/" + name;
       // Prüfen ob 2 Flash vorhanden sind
        if (folder_free.indexOf ("/", 1) == 1)
		folder_free.replace(1,1,"");
        if (rdBt_restoreFsArchiv->isChecked()){
            file_net = userpath_net + "/.qt-fs-client/" + name;
            int pos = file_net.indexOf(".fsa");
            if (pos > 1)
            	restore_file_name_txt ->setText(name);}
}

void DialogNet::treeWidget_auslesen()
{
	QTreeWidgetItem *current = treeWidget->currentItem();
	QString currentFile = current->text(0);
        restore_file_name_txt ->setText("");
	//Verzeichnis, in dem gesichert oder zurückgeschrieben wird
        //Name folder_free wurde aus dem Code Samba-Sicherung übernommen
        folder_free = pfad_forward + "/" + currentFile;
        // Prüfen ob 2 Flash vorhanden sind
        if (folder_free.indexOf ("/", 1) == 1)
		folder_free.replace(1,1,"");
        if (rdBt_restoreFsArchiv->isChecked()){
            file_net = userpath_net + "/.qt-fs-client/" + currentFile;
            int pos = file_net.indexOf(".fsa");
            if (pos > 1)
            	restore_file_name_txt ->setText(currentFile);}
}

int DialogNet::folder_free_mounten(){  //ssh mounten
QString befehl;
QString attribute;
int i = 0;
        if(mountflag == 1)
            return 0;
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("sshfs").toInt();
        setting.endGroup();
        if (auswertung ==1){
             int ret = questionMessage(tr("If you have not set up SSH authentication, you must now enter the password in the terminal. Do you still want to see this message? You can change this in the basic settings.", "Wenn Sie keine SSH-Authentifizierung eingerichtet haben, müssen Sie nun das Passwort in dem Terminal eingeben. Wollen Sie diesen Hinweis weiterhin sehen? Sie können dies in den Basiseinstellungen ändern"));
             if (ret == 2){
		//Basiseinstellungen ändern
        	QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        	setting.beginGroup("Basiseinstellungen");
        	setting.setValue("sshfs",0);
        	setting.endGroup();
                }
        }
        if (folder_free != "" && rdBt_saveFsArchiv->isChecked() )
		befehl = "sudo sshfs -o nonempty " + user_net+ "@" + rechner_IP + ":" + folder_free + " " +  userpath_net + "/.qt-fs-client";
        if (folder_free != "" && rdBt_restoreFsArchiv->isChecked() )
		befehl = "sudo sshfs " + user_net+ "@" + rechner_IP + ":" + pfad_forward + " " + userpath_net + "/.qt-fs-client";
        i = system (befehl.toLatin1().data());
        if ( i==1){
            QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The SSH server is not reachable. Try again or with another network protocol.\n", "Der SSH-Server ist nicht erreichbar. Versuchen Sie es nochmals oder mit einem anderen Netzwerkprotokoll.\n"));
        return 1;
        }
        if (i == 0)
           mountflag = 1; //Beim erfolgreichen mounten wird das erneute mounten verhindert
return 0;
}


void DialogNet::listWidget_tree_eintragen(QString rechner, QString pass, QString user, QString pfad, int flag)
{ 
QStringList filters;
QString befehl;
int ret_;
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("ssh").toInt();
        setting.endGroup();
        if (auswertung ==1 && show1 == 0){
        int ret_ = questionMessage(tr("If you have not yet successfully accessed the computer (server) via ssh, you must now do the following: 1.In the opened terminal, you must confirm the RSA key fingerprint with yes. 2.enter the password for the access to the server and 3.leave the server with the command exit. Do you now want to enter the RSA key fingerprint?\n", "Wenn Sie noch nicht erfolgreich per ssh auf den Rechner(Server) zugegriffen haben, müssen Sie nun folgendes tun: 1.In dem geöffneten Terminal müssen Sie den RSA key fingerprint mit yes bestätigen. 2.Geben Sie das Passwort für den Zugriff auf den Server ein  und 3.verlassen Sie den Server mit dem Befehl exit. Wollen Sie nun den RSA key fingerprint eingeben?\n")); 
        if (ret_ == 1)
           {
           befehl = "ssh " + user_net + "@" +  rechner_IP;
	   ret_ = system (befehl.toLatin1().data());
           }
         }
        //Basiseinstellungen ändern
        //QSettings setting("qt-fsarchiver", "qt-fsarchiver");
         if (auswertung == 1  && show1 == 0){
            int ret = questionMessage(tr("Do you still want to see this message? You can change this in the basic settings.", "Wollen Sie diesen Hinweis weiterhin sehen? Sie können dies in den Basiseinstellungen ändern."));
            if (ret == 2){ 
              setting.beginGroup("Basiseinstellungen");
              setting.setValue("dummy",0);
              auswertung = setting.value("ssh").toInt();
              setting.setValue("ssh",0);
              setting.endGroup();
             }
         }
        show1 = 1;
        if (pfad != "/")
        	bt_toParent->setEnabled(true); 
        if (pfad == "/")
                bt_toParent->setEnabled(false); 
        if (flag==0){
               // pfad_back = pfad_forward;
                backFlag = 1;
		pfad_forward = pfad_forward + pfad;
                pfad_back = pfad_forward;
		if (pfad_forward.indexOf ("/", 1) == 1)
			pfad_forward.replace(1,1,"");
	}
	QString filename = userpath_net + "/.config/qt-fsarchiver/folder.txt";
	listWidget_base(); 
        ret_ = 0;
//nur Verzeichnisse anzeigen
	if (flag==0 && rdBt_saveFsArchiv->isChecked())
		    befehl = "sshpass -p " + pass + " ssh " + user+ "@" + rechner + " ls -l " + pfad_forward + " | grep '^d'  1>" + filename;
	if (flag==1 && rdBt_saveFsArchiv->isChecked())
		    befehl = "sshpass -p " + pass + " ssh " + user+ "@" + rechner + " ls -l " + pfad_back + " | grep '^d'  1>" + filename;
        if (flag==0 && rdBt_restoreFsArchiv->isChecked())
		    befehl = "sshpass -p " + pass + " ssh " + user+ "@" + rechner + " ls -l " + pfad_forward + " 1>" + filename;
	if (flag==1 && rdBt_restoreFsArchiv->isChecked())
		     befehl = "sshpass -p " + pass + " ssh " + user+ "@" + rechner + " ls -l " + pfad_back + " 1>" + filename;
	ret_ = system (befehl.toLatin1().data());
        if ( ret_ != 0) {
	QMessageBox::warning(this, tr("Note", "Hinweis"), tr("The SSH server is not reachable. Try again or with another network protocol.\n", "Der SSH-Server ist nicht erreichbar. Versuchen Sie es nochmals oder mit einem anderen Netzwerkprotokoll.\n"));
        return ;
	}
	QStringList folder;
	QString folder_[500];
	int found = 0;
	int i = 0;
QFile file1(filename);
QTextStream ds(&file1);
QString folder_teilen;
int jj= 0;
        if (rdBt_saveFsArchiv->isChecked()){ //Verzeichnisse auswerten
      	    if( file1.open(QIODevice::ReadOnly|QIODevice::Text)) {
        	while (!ds.atEnd())
        	{
        	folder_teilen= ds.readLine();
			do{
    			found=folder_teilen.indexOf("  ");
				if (found > 0){
             	    			folder_teilen.replace("  ", " ");
			}
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
      	    if( file1.open(QIODevice::ReadOnly|QIODevice::Text)) {
                folder_teilen= ds.readLine();
                QThread::msleep(5 * sleepfaktor);
        	while (!ds.atEnd())
        	{
        	folder_teilen= ds.readLine();
                   if (folder_teilen.left(1) == "d" || folder_teilen.right(4) == ".fsa")  //nochmals prüfen
                   {
			do{
    			found=folder_teilen.indexOf("  ");
				if (found > 0){
             	    			folder_teilen.replace("  ", " ");
			                      }
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
 	befehl = "rm " + userpath_net + "/.config/qt-fsarchiver/folder.txt";
 	//system (befehl.toLatin1().data()); 
 	nameflag = 1;
 	treeWidget->clear();
        nameflag = 0;
        QDir dir2(QString("%1").arg(""));
   	dir2.setNameFilters(filters);
   	QStringList dirList2 = dir2.entryList(QDir::Files);
 	for ( i = 0; i < jj; ++i){
    		dir2.setNameFilters(filters);
    		dirList2 = dir2.entryList(QDir::Files);
    		addItems(folder_[i]);
   	}
}
void DialogNet::button_toParent()
{
int found = 1;
int found1;
        //Rücksprungpfad ermitteln
        // vorhandenen / am Ende entfernen
        pfad_back = pfad_back.left(pfad_back.lastIndexOf('/'));
        if (backFlag == 0){
	     do{
		found1 = found;	
		found = pfad_back.indexOf ("/", found);
        	found = found +1;
   	        }
	     while  (found != 0);
             pfad_back = pfad_back.left(found1);
	}
        if (pfad_back.isEmpty()) 
                pfad_back ="/";
        if (pfad_back != "/")
        	bt_toParent->setEnabled(true); 
        if (pfad_back == "/")
                bt_toParent->setEnabled(false); 
        pfad_forward = pfad_back;
        backFlag = 0;
        listWidget_tree_eintragen(rechner_IP, key_net, user_net, pfad_back, 1);
}

void DialogNet::listWidget_base()
{
  	treeWidget->setColumnCount(1);
 	QStringList sList;
 	sList << tr("Name");
 	treeWidget->setHeaderLabels( sList );
	folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),QIcon::Normal, QIcon::Off);
        fileIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon),QIcon::Normal, QIcon::On);
	QList<QTreeWidgetItem *> items1;
	treeWidget->addTopLevelItems( items1 );
        treeWidget->setRootIsDecorated(false);  // Pfeil wird nicht angezeigt
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
QString dateiname = userpath_net + "/.config/qt-fsarchiver/attribute.txt";
QFile file(dateiname);
file.open(QIODevice::WriteOnly);
QDataStream out(&file);
out << attribut;
file.close();
}

QString DialogNet::datei_auswerten_net(QString buchstabe)
{
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString text;
QString dummy;
QString filename = userpath_net + "/.config/qt-fsarchiver/zahlen.txt";
QFile file(filename);
         if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QThread::msleep(5 * sleepfaktor);
            QTextStream ds(&file);
            while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
            dummy = text.right(1);
            if (dummy == buchstabe)
               {
      	       dev_sdx_ = text;
               }
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

QString DialogNet::datei_auswerten_1_net(QString dateiname)
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

void DialogNet::date_delete_net()
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
     befehl = "/usr/sbin/qt-fsarchiver.sh  5 " + userpath_net + "/.config/qt-fsarchiver " + date_delete_[i] + " 2>/dev/null"; 
    if(system (befehl.toLatin1().data()))
        befehl = "";
     }
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
 




