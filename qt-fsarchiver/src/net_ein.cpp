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

int NetEin:: list_net(QString flag)
{
int pos = 0;
int k = 0;
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
        //Routeradresse finden, damit diese Adresse nicht angezeigt wird.
        befehl = "ip route | grep default 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/route.txt";
	if (system (befehl.toLatin1().data()))
            befehl = "";
        QFile file2(userpath_net_ein + "/.config/qt-fsarchiver/route.txt");
       	QTextStream ds2(&file2);
        file2.open(QIODevice::ReadOnly | QIODevice::Text);
        router = ds2.readLine();
        router_ = router.split(QRegExp("\\s+"));
        router = router_[2];
        file2.close();
        QFile file1(userpath_net_ein + "/.config/qt-fsarchiver/findsmb.txt");
        file1.open(QIODevice::ReadOnly | QIODevice::Text); 
        befehl = "findsmb 1> " +  userpath_net_ein + "/.config/qt-fsarchiver/findsmb.txt";
	if (system (befehl.toLatin1().data()))
            befehl = "";
        QTextStream ds1(&file1);
        QString adresse = ds1.readLine();
        file1.open(QIODevice::ReadOnly | QIODevice::Text); 
        // Eigenen Rechner nicht anzeigen
	hostname_ = hostname();
	QThread::msleep(5 * sleepfaktor);
   	     while (!ds1.atEnd()) {
             	adresse = ds1.readLine();
             	adresse = adresse.toLower();
             	//qDebug() << "adresse" << adresse;
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
     		attribute = "~/.config/qt-fsarchiver/findsmb.txt";
                befehl = "/usr/sbin/qt-fsarchiver.sh  15 " + attribute; 
		if(system (befehl.toLatin1().data()))
                   befehl = "";
               
       } 
        //Ermitteln widget_net Belegung
        if (widget_net[0] == "" && flag == "1"){
   		QMessageBox::warning(this,tr("Note","Hinweis"),
      		tr("There is currently no network computer available.\n","Es ist derzeit kein Netzwerkrechner erreichbar.\n"));
        return 1;
   }
   
   return 0;
}

void NetEin:: setting_save(QString user_net_ein)
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
     setting_save(user_net_ein);     
     if (dialog_auswertung == 6 )
     {
	save_net();
     }
     if (dialog_auswertung == 7)
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




















