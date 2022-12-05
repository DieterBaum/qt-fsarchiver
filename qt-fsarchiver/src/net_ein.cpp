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
#include "net_ein.h"
#include "net.h"
#include "mainWindow.h"
#include <iostream>

QString widget_net[100]; // Netzwerk
QString comNet;
QString comNet_name;
QString user;
QString dummykey;
extern int dialog_auswertung; 
extern int sleepfaktor;

NetEin::NetEin()
{
QString homepath = QDir::homePath(); 
int i = 0;
setupUi(this);
connect( pushButton_net, SIGNAL( clicked() ), this, SLOT(listWidget_show()));
connect( pushButton_net_2, SIGNAL( clicked() ), this, SLOT(listWidget_show()));
connect( pushButton_go, SIGNAL( clicked() ), this, SLOT(go()));
connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(end()));
connect( chk_password, SIGNAL( clicked() ), this, SLOT(Kennwort()));
// Vorsichtshalver ./qt4-fs-client löschen und neu anlegen, da eventuell nicht leer
   //    rmDir(homepath + "/.qt5-fs-client");
       QString befehl = "mkdir " + homepath + "/.qt5-fs-client 2>/dev/null" ;
       if (system (befehl.toLatin1().data()))
             befehl = "";
// Ini-Datei auslesen
   QFile file(homepath + "/.config/qt5-fsarchiver/qt5-fsarchiver.conf");
   if (file.exists()) {
        QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("Passwort").toInt();
        if (auswertung ==1){
           	txt_key ->setEchoMode(QLineEdit::Normal);
                chk_password->setChecked(true);
        } 
   	else
		txt_key ->setEchoMode(QLineEdit::Password);
        auswertung = setting.value("save").toInt();
        if (auswertung ==1)
           chk_datesave->setChecked(true);      
        setting.endGroup();
   }
    while (widget_net[i] != ""){
    	listWidget_net->addItem (widget_net[i]);
        i++;
        if (i > 99)
            break;   
        }
}

void NetEin::Kennwort()
{
Qt::CheckState state;
state = chk_password->checkState(); 
	if (state != Qt::Checked) {
		txt_key ->setEchoMode(QLineEdit::Password);
        } 
   	else
		txt_key ->setEchoMode(QLineEdit::Normal);
}

int NetEin:: list_net_ssh()
{
QString befehl;
QString homepath = QDir::homePath(); 
QString hostname_;
QStringList adresse_;
QString adresse = ""; 
QString adresse_router;
QString adresse_eigen = "";
QString adresse_eigen_ = "";
int k = 0;
int i = 0;
        // Routeradresse ermitteln
        befehl = "route -n 1> " +  homepath + "/.config/qt5-fsarchiver/smbtree.txt";
        if (system (befehl.toLatin1().data()))
             befehl = "";
        QFile file(homepath + "/.config/qt5-fsarchiver/smbtree.txt");
        QTextStream ds1(&file);
        QThread::msleep(20 * sleepfaktor);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
     	     	adresse = ds1.readLine();
             	adresse = ds1.readLine();
             	adresse = ds1.readLine();
            if (adresse != ""){  //verhindert Absturz wenn weder WLan noch Kabelnetzverbindung vorhanden ist
		do{
    			k=adresse.indexOf("  ");
			if (k > 0)
             	    	   adresse.replace("  ", " ");
	          }
			while  (k >= 0);
	     adresse_ = adresse.split(" ");
             adresse_router = adresse_[1];
           }
	}
        file.close();
        hostname_ = hostname();
        adresse_eigen = IP("localhost");
        i = adresse_eigen.indexOf("name_query");
        if (i > -1)
           adresse_eigen = IP(hostname_);
        adresse_ = adresse_eigen.split(" ");
        adresse_eigen = adresse_[0];
        adresse_eigen_ = adresse_[0];
        k = adresse_eigen.size();
        i = adresse_eigen.indexOf(".",k-2);
        if (i != -1)
            adresse_eigen = adresse_eigen.left(i);
        else {

        i = adresse_eigen.indexOf(".",k-3);
        if (i != -1)
            adresse_eigen = adresse_eigen.left(i); 
        i = adresse_eigen.indexOf(".",k-4);
        if (i != -1)
            adresse_eigen = adresse_eigen.left(i);
       }
        //Zahl zwischen 3. und 4. Punkt ermitteln
        //route -n ermittelt die Routeradresse
        befehl = "nmap -sP " + adresse_eigen + ".0/24 1> " +  homepath + "/.config/qt5-fsarchiver/smbtree.txt";
        if (system (befehl.toLatin1().data()))
             befehl = ""; 
       	QTextStream ds(&file);
       	QThread::msleep(20 * sleepfaktor);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) 
             {
     	     adresse = ds.readLine();
  	     //Ermitteln widget_net Belegung
             i = 0;
             while (widget_net[i] != "")
                i = i +1;
             while (!ds.atEnd())
                {
		adresse = ds.readLine();
                if (adresse.indexOf("Nmap scan report") == 0)
                   {
                   adresse_ = adresse.split(" ");
                   adresse = adresse_[4];
                   // Prüfung ob adresse im Array widget_net schon vorhanden ist
                   if (adresse != adresse_router  &&  adresse != adresse_eigen_)
                        {
			k = Array_pruefen(adresse);
    		        if (k == 2) 
    		           {
         	     	   //listWidget_net->addItem (adresse);
                   	   widget_net[i]= adresse;
                     	   i++;
               		   }
			}
		   }
	         }
	      }
	file.close();
   return 0;
}

int NetEin::list_net()
{
QString homepath = QDir::homePath();
int pos = 0;
int k = 0;
int i = 0;
int j = 0;
int m = 0;
QStringList adresse_;
QString attribute;
QString adresse_eigen;
QString adresse1;
QString adresse2;
QString adresse3;
QString befehl;
QString hostname_;
QString router;
QStringList router_;
QString _adresse[100];
QString dummy;
        QFile file4("/usr/bin/findsmb");
        hostname_ = hostname();
        //Routeradresse finden, damit diese Adresse nicht angezeigt wird.
        befehl = "ip route | grep default 1> " +  homepath + "/.config/qt5-fsarchiver/route.txt";
	if (system (befehl.toLatin1().data()))
            befehl = "";
        QFile file2(homepath + "/.config/qt5-fsarchiver/route.txt");
       	QTextStream ds2(&file2);
        file2.open(QIODevice::ReadOnly | QIODevice::Text);
        router = ds2.readLine();
        if (router == "")
           {
           QMessageBox::warning(this,tr("Note","Hinweis"),
      		tr("There is currently no network computer available.\n","Es ist derzeit kein Netzwerkrechner erreichbar.\n"));
           return 1;
           }
        router_ = router.split(QRegExp("\\s+"));
        router = router_[2];
        file2.close();
        if (!file4.exists())
            {
            QFile file1(homepath + "/.config/qt5-fsarchiver/nmblookup.txt");
            file1.open(QIODevice::ReadWrite | QIODevice::Text);
            QThread::msleep(5 * sleepfaktor);
            befehl = "nmblookup '*' 1> " +  homepath + "/.config/qt5-fsarchiver/nmblookup.txt";
	    if (system (befehl.toLatin1().data()))
                befehl = "";
            QThread::msleep(5 * sleepfaktor);
           // file1.open(QIODevice::ReadOnly | QIODevice::Text);          
            QTextStream ds1(&file1);
            _adresse[k] = ds1.readLine();
            k ++;
            while (!ds1.atEnd()) {
               _adresse[k] = ds1.readLine();
               dummy = _adresse[k]; 
               pos = dummy.indexOf("*<00>");
               dummy = dummy.left(pos-1);
               if(dummy != router)
                 {
                 QThread::msleep(5 * sleepfaktor); 
                 _adresse[m] = dummy;
                 m ++;
                 }
              } 
 	   file1.close();
 	   QFile file3(homepath + "/.config/qt5-fsarchiver/nmblookup.txt");
 	   for (i=0; i<m; i++)
 	      {
 	      befehl = "nmblookup -A " +  _adresse[i] + " 1> " +  homepath + "/.config/qt5-fsarchiver/nmblookup.txt";
 	      if (system (befehl.toLatin1().data()))
                 befehl = "";
              file3.open(QIODevice::ReadOnly | QIODevice::Text);   
              QTextStream ds3(&file3);
              QThread::msleep(5 * sleepfaktor);  
              dummy = ds3.readLine(); // 1. Zeile uninteressant
              while (!ds3.atEnd()) 
                 {
                 dummy = ds3.readLine(); 
                 dummy = dummy.trimmed();
                 pos = dummy.indexOf("<00> -         B <ACTIVE>");
                 if (pos > -1 )
                    { 
                    dummy = dummy.left(pos);
                    dummy = dummy.trimmed();
                    dummy = dummy.toLower(); 
                    if(hostname_ != dummy)
                       {
                       widget_net[j] = _adresse[i] + " " + dummy;
                       j ++;
                       }
                    }     
               } 
               file3.close(); 
             }
             // Dateien entfernen 
             if (file3.exists()){
     		attribute = "~/.config/qt5-fsarchiver/nmblookup.txt";
                befehl = "rm " + attribute; 
		if(system (befehl.toLatin1().data()))
                   befehl = "";
                } 
             } 
          
           if (file4.exists())
            { 
            QFile file1(homepath + "/.config/qt5-fsarchiver/findsmb.txt");
            file1.open(QIODevice::ReadWrite | QIODevice::Text);
            befehl = "findsmb 1> " +  homepath + "/.config/qt5-fsarchiver/findsmb.txt";
	    if (system (befehl.toLatin1().data()))
                befehl = "";
            QTextStream ds1(&file1);
            QString adresse = ds1.readLine();
            // Eigenen Rechner nicht anzeigen
	    QThread::msleep(5 * sleepfaktor);
	    while (!ds1.atEnd()) {
             	adresse = ds1.readLine();
             	adresse = adresse.toLower();
             	pos = adresse.indexOf("["); 
               if ( pos > 0)
                { adresse_ = adresse.split(QRegExp("\\s+"));
                  adresse2 = adresse_[0];
                  adresse3 = adresse_[0];
                  adresse1 = adresse_[1];
                  adresse2 = adresse2 + " " + adresse1;
                  if(hostname_ != adresse1 && router != adresse3)
                     {
                     listWidget_net->addItem(adresse2);
                     widget_net[k]= adresse2;
                     k++;
                     }
                  }              
             } 
	file1.close();
         
        // Dateien entfernen 
  	if (file1.exists()){
     		attribute = "~/.config/qt5-fsarchiver/findsmb.txt";
                befehl = "rm " + attribute; 
		if(system (befehl.toLatin1().data()))
                   befehl = "";
               }
        }
       //Ermitteln widget_net Belegung
        if (widget_net[0] == "" ){
   		QMessageBox::warning(this,tr("Note","Hinweis"),
      		tr("There is currently no network computer available.\n","Es ist derzeit kein Netzwerkrechner erreichbar.\n"));
        return 1;
   }
   return 0;
}


int NetEin::Array_pruefen(QString ip){
int k= 0;
int pos;
int pos1;
QString hostname_;
        hostname_ = hostname();
        pos = widget_net[k].indexOf(ip);
        pos1 = ip.indexOf(hostname_);
        if (pos >= 0)  // Name im Array vorhanden
               return 0;
        if (pos1 >= 0)  // Hostname, Abbruch
               return 0;
        while (widget_net[k] != "") {
            pos = widget_net[k].indexOf(ip);
            pos1 = ip.indexOf(hostname_);
            if (pos >= 0)  // Name im Array vorhanden
               return 0;
            if (pos1 >= 0)  // Hostname, Abbruch
               return 0;
            k++;
            }
        return 2;
}

int NetEin:: setting_save()
{
QString homepath = QDir::homePath();
   QString key;  
   QString befehl;
   QString text;
   QString filename;
   QFile f(filename);
   Qt::CheckState state;
   state = chk_datesave->checkState();
   QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
   setting.beginGroup(comNet_name);
   user = txt_user->text();
   //Neue oder geänderte Daten in setting eingeben
    if (state == Qt::Checked && comNet != "")   
       setting.setValue("Name",user);
   setting.endGroup();
  // Dateien entfernen 
   filename = homepath + "/.config/qt5-fsarchiver/ip.txt";
	if (f.exists()){
     	   befehl = "rm " +filename;
	   if(system (befehl.toLatin1().data()))
              befehl = "";
       }     
       filename = homepath + "/.config/qt5-fsarchiver/smbtree.txt";
       if (f.exists()){
     	   befehl = "rm " + filename;
	   if(system (befehl.toLatin1().data()))
             befehl = "";
       } 
   return 0;
} 


QString NetEin::hostname()
{
QString homepath = QDir::homePath();
QString befehl;
QString text;
        QFile file(homepath + "/.config/qt5-fsarchiver/hostname.txt");
    	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "hostname > " +  homepath + "/.config/qt5-fsarchiver/hostname.txt";
	if(system (befehl.toLatin1().data()))
           befehl = "";
        while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
           }
        file.close();
        befehl = "rm " + homepath + "/.config/qt5-fsarchiver/hostname.txt";
        if (system (befehl.toLatin1().data()))
             befehl = "";
        return text;
return "";
}
        
QString NetEin:: IP(QString adresse)
{
QString befehl;
int pos;
QString homepath = QDir::homePath();
QFile file(homepath + "/.config/qt5-fsarchiver/ip.txt");
QTextStream ds(&file);
QString text;
	befehl = "nmblookup -R " + adresse + " 1> " +  homepath + "/.config/qt5-fsarchiver/ip.txt 2>/dev/null";
	if (system (befehl.toLatin1().data()))
             befehl = "";
        int i = 0;
        // Anzahl Zeilen der Datei /.config/qt5-fsarchiver/ip.txt ermitteln
        // Ausgabe nmblookup manchmal mit einer aber auch mit 2 Zeilen
        QThread::msleep(20 * sleepfaktor);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
     	     do {
                 i = i + 1;
                text = ds.readLine();
	        } while (!ds.atEnd());
              }
             file.close();
        if (i  == 2) // Anzahl 2 Zeilen, nmblookup -T adresse arbeitet korrekt
	  {
          if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
     	     text = ds.readLine();
	     text = ds.readLine();   
              }
             file.close();
          }
          pos = text.indexOf("<");
          text = text.left(pos);
          text = text.toLower();
          return text;
}

void NetEin:: listWidget_show()
{
QString homepath = QDir::homePath();
int row = 1;
QString key_;
QString key;
QString befehl;
QStringList comNet_;
    key = " ";
    row = listWidget_net->currentRow();
    comNet = widget_net[row];
    if (comNet.indexOf(" ") != -1){
    comNet_ = comNet.split(" ");
    comNet = comNet_[0];
    comNet_name = comNet_[1];}
    else
         comNet_name = "";
    // Prüfen ob Daten in setting
   QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
   setting.beginGroup(comNet_name);
   user = setting.value("Name").toString();
   key_ = setting.value("key").toString();
   setting.endGroup();
   //Netzwerk-Daten in Textfeld eintragen
   txt_user ->setText(user);
}

QString NetEin::Namen_holen()
{
  return comNet + " " + comNet_name;
}

QString NetEin::user_holen()
{
  return user;
}

QString NetEin::key_holen()
{
   return dummykey;
}

void NetEin:: end()
{ 
   close();
}

int NetEin:: go()
{ 
extern int dialog_auswertung;
QString homepath = QDir::homePath();
QString key;
QString befehl;
Qt::CheckState state;
state = chk_datesave->checkState();
QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
setting.beginGroup(comNet_name);
     user = txt_user->text();
     key = txt_key->text();
     dummykey = key;
     QThread::msleep(10 * sleepfaktor);
      if (system (befehl.toLatin1().data()))
          befehl = "";
      if (comNet == "" && dialog_auswertung == 6)
       {
       QMessageBox::about(this, tr("Note", "Hinweis"),
      tr("You must select the computer on which the backup data is to be written.\n", "Sie müssen den Rechner auswählen, auf den die Sicherungsdaten geschrieben werden sollen\n"));
      return 1 ;
      }
     if (comNet == "" && dialog_auswertung == 7)
      {
       QMessageBox::about(this, tr("Note", "Hinweis"),
       tr("You must select the computer from which the backup data is to be written back.\n", "Sie müssen den Rechner auswählen, von dem die Sicherungsdaten zurück geschrieben werden sollen\n"));
      return 1 ;
      }
     if (user == "" )
      {
       QMessageBox::about(this, tr("Note","Hinweis"),
      tr("You must enter the user name. Otherwise network computers cannot be accessed.\n", "Sie müssen den Benutzernamen eingeben. Sonst kann nicht auf Netzrechner zugegriffen werden\n"));
      return 1 ;
      }
     if (key == "" ) {
          int ret = questionMessage(tr("Is that correct that you have not entered a key? (NFS does not need a key.", "Ist das richtig, dass Sie keinen Schlüssel eingegeben haben? (NFS benötigt keinen Schlüssel)"));
              if (ret == 2)
              return 1;
      }
     if (state == Qt::Checked )   
       setting.setValue("Name",user);
     if (state != Qt::Checked )   
       setting.setValue("Name","");
     setting.endGroup();
     if (dialog_auswertung == 6)
	save_net();
     if (dialog_auswertung == 7)
	restore_net(); 
     return 0;
}

void NetEin::save_net () {
extern int dialog_auswertung;
	this->setCursor(Qt::WaitCursor);
    	dialog_auswertung = 6;
     	DialogNet *dialog2 = new DialogNet;
     	dialog2->show();
        this->setCursor(Qt::ArrowCursor);
        close();
}
void NetEin::restore_net () {
extern int dialog_auswertung;
        this->setCursor(Qt::WaitCursor);
      	dialog_auswertung = 7;
      	DialogNet *dialog2 = new DialogNet;
        dialog2->show();
        this->setCursor(Qt::ArrowCursor);
        close();
}


int NetEin::questionMessage(QString frage)
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

bool NetEin::rmDir(const QString &dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists())
        return true;
    foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
        if (info.isDir()) {
            if (!rmDir(info.filePath()))
                return false;
        } else {
            if (!dir.remove(info.fileName()))
                return false;
        }
    }
    QDir parentDir(QFileInfo(dirPath).path());
    return parentDir.rmdir(QFileInfo(dirPath).fileName());
}













