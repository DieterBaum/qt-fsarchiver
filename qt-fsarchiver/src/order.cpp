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
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "order.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "mainWindow.h"
#include <iostream>
 
using namespace std;




extern int dialog_auswertung;
extern int sleepfaktor;
QString widget_list[100];
QString widget_list_[100];
QString order_name_[100];
int size_line= 0;
int row = 0;
QStringList clear;

OrderDialog::OrderDialog()
{
  setupUi(this);
  connect( cmd_del, SIGNAL(clicked()), this, SLOT(del_one()));
  connect( cmd_del_all, SIGNAL(clicked()), this, SLOT(del_all()));
  connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(end_()));
  connect( cmd_listWidget, SIGNAL( clicked() ), this, SLOT(listWidget_auslesen()));
  connect( cmd_clean, SIGNAL( clicked() ), this, SLOT(clean()));
  clear << "2" << "3" << "4" <<  "5" ;
  cmb_anzahl->addItems (clear);
  cmb_anzahl -> setCurrentIndex(1);
  make_order();
  
} 


void OrderDialog:: make_order()
{
QString homepath = QDir::homePath();
QString filename = homepath + "/.config/qt5-fsarchiver/auftrag.db";
QFile file(filename);
QString attribute;
QStringList auftrag;
QString auftrag_; 
int i = 0;
int j = 0;
int found = 0;
QString order_name;
        file.open(QIODevice::ReadOnly);
        QDataStream stream( &file ); // read the data serialized from the file
        stream >> auftrag_ ;
        file.close(); 
        auftrag = auftrag_.split("##");
        size_line = auftrag.size();
        for(i=0; i < size_line - 1; i++) 
               {
               order_name = auftrag[i];
               order_name = order_name.trimmed();
               attribute = auftrag[i+1];
               found = attribute.indexOf("savefs"); 
               if(order_name != "" && found > -1 )
                  {
                    listWidget->addItem ("Save: " + order_name);
                    order_name_[j] = "Save: " + order_name;
                  }  
               if(order_name != "" && found == -1 )
                  {
                    listWidget->addItem ("Restore: " + order_name);
                    order_name_[j] = "Restore: " + order_name; 
                   }  
               widget_list[j]= order_name;
               widget_list_[j]= attribute;
               i++;
               j ++;
               }  
       file.close(); 
   
}

void OrderDialog::listWidget_auslesen() {
       row = listWidget->currentRow();
       if(row == -1) 
           row = 0;
}

void OrderDialog::clean() {
QString homepath = QDir::homePath();
int i = 0;
int j = 0;
int l = 0;
int k = 0;
int n = 0; 
int o= 0; 
int p= 0; 
int r = 0;
int anzahl = 0;
int temp; 
int zahl = 0;
QString temp1;
QString attribute;
QString saved[100][100];
QString saved_[100][100];
QString pfade[100];
QString name[100];
QString name1[100];
int array_time[100][100];
QString dummy;
int place[50];
QString str;
QString befehl;
       zahl = cmb_anzahl->currentIndex()+2;
       while (widget_list_[l] != "")
	   {
	   j = 0;
	   i = 0;
	   dummy = widget_list_[l];
	   // Pfad der Sicherungen ermitteln
           str = dummy;
           while ((j = str.indexOf("/", j)) != -1) {
              if( j >= 0)
                 {
                 place[i]= j;
                 i++;
                 }
            ++j;
            } 
            dummy = dummy.mid(place[0],place[i-3]-place[0]);
            pfade[l] = dummy;
            if( l > 98)
               break;  // Überlauf verhindern
            l++;   
	 }
	 // Array um doppelte Einträge bereinigen
	 for(k=0; k < l; k++)
	    {
	     for(j=0; j < l; j++)
               {
                  for(o=0; o < l; o++)
                  {
                  if(pfade[j] == pfade[j+o+1])
                      {
                      // Array kürzen
                      for (n = o;  n < l -1; n++)
                         pfade[j+n+1]= pfade[j+n+2];
                      l--;
                    }
                 }
               }
             } 
          // l = Anzahl der Aufträge
          // anzahl = anzahl der Sicherungspfade 
          // Anzahl der Pfade ermitteln 
          i = 0; 
          while (pfade[anzahl] != "")
             anzahl ++;
       // Aufträge von allen Sicherungspfaden einlesem       
         l = 0;
	
	for(j=0; j< anzahl; j++) 
	    {  
            QDir directory(pfade[j]);
	    QStringList Filter;
	    Filter << "*.fsa";
	    QStringList flist = directory.entryList(Filter);
	    QStringList::const_iterator test;
	    for(test = flist.constBegin();test!= flist.constEnd(); ++test)
	        {
        	name[r] = (*test).toLatin1().constData();
        	name1[r] = pfade[j] + "/" + (*test).toLatin1().constData();
        	if(r > 98)  //Überlauf verhindern
        	  break;
               	r++;
	        }
	}   
	//  r = Anzahl aller Aufträge   
	//Auftragsnamen: Datumtext entfernen  
	l = 0;
	while (name[l] != "")
	   {
	   j = 0;
	   i = 0;
	   dummy = name[l];
	   // Pfad der Sicherungen ermitteln
           str = dummy;
           while ((j = str.indexOf("-", j)) != -1) {
              if( j >= 0)
                 {
                 place[i]= j;
                 i++;
                 }
            ++j;
            } 
            dummy = dummy.left(place[i-3]);
            name[l] = dummy;
            l++; 
	 } 
         k = 0;
         i=0;
         o = 0;
         //Anzahl der erforderlichen Array ermitteln, füllen und Zeitstempel ermitteln;
            for(j=0; j < l; j++)
                {
                if(name[j] == name[j+1])
                   {
                   o = 1;
                   saved[i][k]= name1[j];
                   dummy = saved[i][k];
                   QFileInfo resourceInfo(dummy);
                   dummy = resourceInfo.lastModified().toString("yyyy-MM-dd");
                   // in Systemzeit umrechnen
                   befehl = "date -d '" + dummy + "' +%s 1> " +  homepath + "/.config/qt5-fsarchiver/zeit.txt";
                   if(system (befehl.toLatin1().data()))
                        befehl = "";
                   QString filename = homepath + "/.config/qt5-fsarchiver/zeit.txt";
                   QFile file(filename);
                   QTextStream ds(&file);
                   file.open(QIODevice::ReadOnly | QIODevice::Text); 
                   QThread::msleep(5 * sleepfaktor);
                   dummy = ds.readLine();
                   file.close();
                   saved[i][k] = saved[i][k] ;
                   saved_[i][k] = name[j];
                   array_time[i][k] = dummy.toInt();
                   k ++;
                   }
                   if(name[j] != name[j+1]) 
                       {
                       k = 0;
                       if (o == 1)
                           {
                           i ++;
                           o ++;
                           }
                       }
                   }
             // i ist Anzahl der Arrays
             for(l=0;l<i;l++) 
               { 
                n = 0;
                while (saved_[l][n] != "") 
                  {
                   n++;
                   }
                // Array nach Zeit sortieren    
                for(o=0;o<n;++o)
                   {
                   for(j=0;j<(n-1);++j)
                   if(array_time[l][j]>array_time[l][j+1])
                       {
                       temp = array_time[l][j];
                       temp1 = saved[l][j];
                       array_time[l][j]=array_time[l][j+1];
                       saved[l][j] = saved[l][j+1];
                       array_time[l][j+1] = temp;
                       saved[l][j+1]= temp1;
                       }
                   }
              
               }
               // i ist Anzahl der Arrays
               str = "";
               for(l=0;l<i;l++) 
                   { 
                   n = 0;     
                   while (saved_[l][n] != "") 
                      {
                      n++;
                      }  
                      for(o = 0; o < n-zahl+1; o++)
                           {
                           name[p]= "rm " + saved[l][o];
                           str = str + saved[l][o] + " \n";
                           p++;
                           }
                      } 
                if(p == 0)  
                   {
                   QMessageBox::about(this, tr("Note", "Hinweis"), tr("There are no backupfiles to delete.", "Es sind keine Sicherungdateien zum löschen vorhanden.\n"));
                   return;
                   }
               int ret = questionMessage(tr("It will delete \n", "Es werden \n")   + str + tr("Do you want to continue?\n", "Sicherungsdateien gelöscht. Wollen Sie fortfahren?\n"));
               if (ret == 1)
                   { 
                   for(o = 0; o < p; o++)
                       {
                       befehl = name[o]; 
                       if(system (befehl.toLatin1().data()))
                           befehl = "";
                       // Text-Dateien müssen auch entfernt werden
                       zahl=befehl.indexOf(".fsa");
                       if (zahl > 0)
        	          befehl.replace(zahl, 4, ".txt");
        	       if(system (befehl.toLatin1().data()))
                          befehl = "";
                 }
              }   
              else
                 return; 
              QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup files were deleted. \n", "Die Sicherungsdateien wurden gelöscht.\n"));    
}

void OrderDialog::del_all() {
QString homepath = QDir::homePath();
QString befehl;
int ret = 0;
       ret = questionMessage(tr("Do you really want to delete all orders?", "Wollen Sie wirklich alle Aufträge löschen?"));
       if (ret == 1)
          { // beenden
          befehl = "rm " + homepath + "/.config/qt5-fsarchiver/auftrag.db";
          if(system (befehl.toLatin1().data()))
               befehl = "";
          cmd_del_all ->setEnabled(true);
          listWidget-> clear();      
        }
       if (ret == 2 )
          return;
}

void OrderDialog::del_one() {
QString homepath = QDir::homePath();
int i = 0;
QString order_name;
QString dateiname = homepath + "/.config/qt5-fsarchiver/auftrag.db";  
QFile file2(dateiname);
QString text; 
       make_order();
       //Anzeige in listWidget
       listWidget-> clear(); 
       order_name = widget_list[row];
       size_line = size_line / 2;
       for (i = row;  i < size_line -1; i++)
           {
           widget_list[i] = widget_list[i+1];
           widget_list_[i] = widget_list_[i+1];
           order_name_[i] = order_name_[i+1];
           }
        for (i = 0;  i < size_line -1; i++)  
            {
            text = text + widget_list[i] + " ## " + widget_list_[i] + " ## "; 
            listWidget->addItem (order_name_[i]);
            }
        if (file2.open(QIODevice::ReadWrite)) 
            {
             QDataStream out(&file2);
             out << text;
             file2.close();
            } 
 }                  
                     
       

int OrderDialog::questionMessage(QString frage)
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

void OrderDialog::end_()
{
dialog_auswertung = 0;
close();
}










