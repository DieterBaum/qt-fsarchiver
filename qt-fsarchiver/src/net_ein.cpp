/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2020 Dieter Baum.  All rights reserved.
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
#include "net_ein.h"
#include "net.h"
#include "mainWindow.h"
#include <iostream>
#include <string>

QString widget_net[100]; // Netzwerk
QString comNet;
QString comNet_name;
QString user_net_ein;
QString dummykey;
extern QString password;
extern int dialog_auswertung; 
extern QString user;
extern int sleepfaktor;
QString userpath_net_ein;
QString homepath_net_ein = QDir::homePath();

NetEin::NetEin()
{
int i = 0;
QString attribute;
QString befehl;
setupUi(this);
connect( pushButton_net, SIGNAL( clicked() ), this, SLOT(listWidget_show()));
connect( pushButton_net_2, SIGNAL( clicked() ), this, SLOT(listWidget_show()));
connect( pushButton_go, SIGNAL( clicked() ), this, SLOT(go()));
connect( pushButton_end, SIGNAL( clicked() ), this, SLOT(end()));
connect( chk_password, SIGNAL( clicked() ), this, SLOT(Kennwort()));
       userpath_net_ein = homepath_net_ein; 
// Vorsichtshalver ./qt-fs-client löschen und neu anlegen, da eventuell nicht leer
       attribute =  userpath_net_ein + "/.qt-fs-client  2>/dev/null"; 
       befehl = "/usr/sbin/qt-fsarchiver.sh  8 " + attribute; 
       if(system (befehl.toLatin1().data()))
         attribute = "";
       attribute  = attribute;
       befehl = "/usr/sbin/qt-fsarchiver.sh  3 " + attribute;
       if (system (befehl.toLatin1().data()))
        attribute = "";
    /*   //vorsichtshalber Rechte immer neu setzen
       attribute = "a+rwx " + userpath_net_ein + "/.qt-fs-client 2>/dev/null";
       befehl = "/usr/sbin/qt-fsarchiver.sh  16 " + attribute;
       x = system (befehl.toLatin1().data());*/
// Ini-Datei auslesen
   QFile file(userpath_net_ein + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
   if (file.exists()) {
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
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
QString attribute;
QString hostname_;
QStringList adresse_;
QString adresse = ""; 
QString adresse_router;
QString adresse_eigen = "";
QString adresse_eigen_ = "";
int k = 0;
int i = 0;
        // Routeradresse ermitteln
        QFile file(userpath_net_ein + "/.config/qt-fsarchiver/smbtree.txt");
        QTextStream ds1(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "route -n 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/smbtree.txt";
        if(system (befehl.toLatin1().data()))
            befehl = ""; 
        while (adresse == ""){
            adresse = ds1.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
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
        QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           attribute = "-sP " + adresse_eigen + ".0/24 1>" +  userpath_net_ein + "/.config/qt-fsarchiver/smbtree.txt";
           befehl = "/usr/sbin/qt-fsarchiver.sh  18 " + attribute;
           if(system (befehl.toLatin1().data()))
              befehl = "";
           {
            while (adresse == "")
            adresse = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
 	     adresse = ds.readLine();
  	     //Ermitteln widget_net Belegung
             i = 0;
             while (widget_net[i] != ""){
	            i = i +1;}
             while (!ds.atEnd()) {
		adresse = ds.readLine();
                if (adresse.indexOf("Nmap scan report") == 0){
                   adresse_ = adresse.split(" ");
                   adresse = adresse_[4];
                  // Prüfung ob adresse im Array widget_net schon vorhanden ist
                  if (adresse != adresse_router  &&  adresse != adresse_eigen_){
			k = Array_pruefen(adresse);
    		if (k == 2) {
         	     		//listWidget_net->addItem (adresse);
                   		widget_net[i]= adresse;
                     		i++;
               		 }
			}}
	}
        }
	file.close();
   return 0;
}

int NetEin:: list_net(QString flag)
{
int pos = 0;
int i = 0;
int j;
QStringList adresse_;
QString attribute;
QString adresse_eigen;
QString adresse2;
QString befehl;
QString hostname_;
 	hostname_ = hostname();
      // Eigenen Rechner nicht anzeigen
        adresse_eigen = IP("localhost");
        i = adresse_eigen.indexOf("name_query");
        if (i > -1)
           adresse_eigen = IP(hostname_);
        adresse_ = adresse_eigen.split(" ");
        adresse_eigen = adresse_[0];
 //smbtree: zuverlässige und schnelle Linux-Rechner Suche. Windows-Rechner werden aber nicht erkannt
// -N verhindert die sudo-Abfrage
        QFile file(userpath_net_ein + "/.config/qt-fsarchiver/smbtree.txt");
    	QTextStream ds(&file);
        QString text = ds.readLine();
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "smbtree -N 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/smbtree.txt";
	  if (system (befehl.toLatin1().data()))
              befehl = "";
           if (file.size() != 0) 
           {  
           while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
	     while (!ds.atEnd()) {
             	text = ds.readLine();
               // text = text.toLower(); 
                pos = text.indexOf("IPC$ ");
                if (pos > -1){
                text = text.left(pos-1);
                text = text.trimmed();
                j = text.size();
		     text = text.right(j-2);
                     text = text.toLower();
                     text = IP(text); // IP ermitteln
                     adresse_ = text.split(" ");
                     adresse2 = adresse_[0]; 
                  if (adresse2 != adresse_eigen){ // Eigenen Rechner nicht anzeigen
                      widget_net[i]= text;
                      i++;}
                   if (i > 99)
                      break;
             }
            } 
           } 
        }
	file.close();
//Auswertung findsmb Windows-Rechner werden erkannt
        befehl = "findsmb 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/findsmb.txt";
	if (system (befehl.toLatin1().data()))
            befehl = "";
        QFile file1(userpath_net_ein + "/.config/qt-fsarchiver/findsmb.txt");
    	QTextStream ds1(&file1);
        QString adresse = ds1.readLine();
        QString adresse1; 
        int k;
        // Eigenen Rechner nicht anzeigen
	hostname_ = hostname();
        adresse_eigen = IP("localhost");
        i = adresse_eigen.indexOf("name_query");
        if (i > -1)
           adresse_eigen = IP(hostname_);
        adresse_ = adresse_eigen.split(" ");
        adresse_eigen = adresse_[0];
        file1.open(QIODevice::ReadOnly | QIODevice::Text); 
        while (adresse == ""){
            adresse = ds1.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
            for (k = 0; k < 5; k++){
               	adresse = ds1.readLine();
             }
   	     while (!ds1.atEnd()) {
             	adresse = ds1.readLine();
                adresse = adresse.toLower();
                k = adresse.size();
                if (k > 0)
                { //findsmb findet die IP-Adresse nicht
                   adresse_ = adresse.split(" ");
                   j = adresse_[0].size();
		   adresse2 = adresse_[0];
		   adresse = adresse.right(k-j);
                   adresse = adresse.trimmed();
                   adresse_ = adresse.split(" ");
                   adresse = adresse_[0];
                   pos = adresse.indexOf("+");
                   if (pos == -1)
                   {
                      adresse = IP(adresse);
		      // Prüfung ob adresse im Array widget_net schon vorhanden ist
                      k = 0;
                      if (adresse2 != adresse_eigen) // Eigenen Rechner nicht anzeigen
                	k = Array_pruefen(adresse2);
                      if (k == 2) {
         	        listWidget_net->addItem(adresse);
                        widget_net[i]= adresse;
                        i++;
                    }
                }
               }
             } 
	file1.close();
        // Dateien entfernen 
  	if (file1.exists()){
     		attribute = "~/.config/qt-fsarchiver/findsmb.txt";
                befehl = "/usr/sbin/qt-fsarchiver.sh  15 " + attribute; 
		if(system (befehl.toLatin1().data()))
                   befehl = "";
               
       } 
        list_net_ssh();
        //Ermitteln widget_net Belegung
        if (widget_net[0] == "" && flag == "1"){
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

int NetEin:: setting_save(QString user_net_ein)
{
   QString befehl;
   QString filename;
   QFile f(filename);
   QString attribute;
   Qt::CheckState state;
   state = chk_datesave->checkState();
   QSettings setting("qt-fsarchiver", "qt-fsarchiver");
   setting.beginGroup(comNet_name);
   //Neue oder geänderte Daten in setting eingeben
    if (state == Qt::Checked && comNet != "")   
       setting.setValue("Name",user_net_ein);
    setting.endGroup();
  // Dateien entfernen 
  filename = "~/.config/qt-fsarchiver/ip.txt";
	if (f.exists()){
     		attribute = filename;
                befehl = "/usr/sbin/qt-fsarchiver.sh  8 " + attribute; 
		if(system (befehl.toLatin1().data()))
                  befehl = "";
       }     
       filename = "~/.config/qt-fsarchiver/smbtree.txt";
       if (f.exists()){
     		attribute = filename;
                befehl = "/usr/sbin/qt-fsarchiver.sh  8 " + attribute; 
		if(system (befehl.toLatin1().data()))
                   befehl = "";
       } 
   return 0;
} 


QString NetEin::hostname()
{
QString befehl;
QString text;
        QFile file(userpath_net_ein + "/.config/qt-fsarchiver/hostname.txt");
    	QTextStream ds(&file);
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
           {
           befehl = "hostname > " +  userpath_net_ein + "/.config/qt-fsarchiver/hostname.txt";
	if(system (befehl.toLatin1().data()))
           befehl = "";
        while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
           }
        file.close();
        befehl = "rm " + userpath_net_ein + "/.config/qt-fsarchiver/hostname.txt";
        if (system (befehl.toLatin1().data()))
             befehl = "";
        return text;
return "";
}
        
QString NetEin:: IP(QString adresse)
{
QString befehl;
int pos;
QFile file(userpath_net_ein + "/.config/qt-fsarchiver/ip.txt");
QTextStream ds(&file);
QString text;
        // IP-Adresse auslesen
        int i = 0;
        // Anzahl Zeilen der Datei /.config/qt-fsarchiver/ip.txt ermitteln
        // Ausgabe nmblookup manchmal mit einer aber auch mit 2 Zeilen
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) 
           {
            befehl = "nmblookup -R " + adresse + " 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/ip.txt 2>/dev/null";
	   if (system (befehl.toLatin1().data())) 
              befehl = "";
     	     do {
                 i = i + 1;
                text = ds.readLine();
	         } 
             while (!ds.atEnd());
              }
             file.close();
        if (i  == 2) // Anzahl 2 Zeilen, nmblookup -T adresse arbeitet korrekt
	  {
        file.open(QIODevice::ReadOnly | QIODevice::Text); 
        while (text == ""){
            text = ds.readLine();
            QThread::msleep(5 * sleepfaktor);
            }
            text = ds.readLine();   
            file.close();
          }
          pos = text.indexOf("<");
          text = text.left(pos);
          text = text.toLower();
          return text;
}

void NetEin:: listWidget_show()
{
int row = 1;
QString key_;
QString key;
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
   QSettings setting("qt-fsarchiver", "qt-fsarchiver");
   setting.beginGroup(comNet_name);
   user_net_ein = setting.value("Name").toString();
   key_ = setting.value("key").toString();
   setting.endGroup();
   txt_user ->setText(user_net_ein);
}

QString NetEin::Namen_holen()
{
  return comNet + " " + comNet_name;
}

QString NetEin::key_holen()
{
    return dummykey;
}

QString NetEin::user_holen()
{
  return user_net_ein;
}

int NetEin:: end()
{ 
   close();
return 0;
}

int NetEin:: go()
{ 
QString key;
Qt::CheckState state;
state = chk_datesave->checkState();
QSettings setting("qt-fsarchiver", "qt-fsarchiver");
setting.beginGroup(comNet_name);
     user_net_ein = txt_user->text();
     key = txt_key->text();
     dummykey = key;
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
     if (user_net_ein == "" )
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
       setting.setValue("Name",user_net_ein);
     else
       setting.setValue("Name","");
     setting.endGroup();
     int i = setting_save(user_net_ein);     
     if (dialog_auswertung == 6 && i == 0)
     {
	save_net();
     }
     if (dialog_auswertung == 7 && i == 0)
	restore_net(); 
     return 0;
}

void NetEin::save_net () {
	this->setCursor(Qt::WaitCursor);
    	dialog_auswertung = 6;
     	DialogNet *dialog2 = new DialogNet;
     	dialog2->show();
        this->setCursor(Qt::ArrowCursor);
        close();
}
void NetEin::restore_net () {
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
















