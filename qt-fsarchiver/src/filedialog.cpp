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
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "filedialog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "mainWindow.h"

using namespace std;
extern int dialog_auswertung;
QString wort;

FileDialog::FileDialog()
{
QString filename;
  setupUi(this);
  connect( cmd_save, SIGNAL(clicked()), this, SLOT(folder_einlesen()));
 // connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(reject()));
  connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(close()));
  textEdit->setPlainText(wort);
  
 if (dialog_auswertung ==3)
     {
	cmd_save->setText(tr("Partition restore", "Partition zurückschreiben"));
	file_read();
     }
  
  if (dialog_auswertung ==7)
     {
	cmd_save->setText(tr("Save Harddrive Image", "Festplatten Abbild erstellen"));
	file_save();
     }
if (dialog_auswertung == 8)
     {
        extern QString folder_file_;
   	cmd_save->setText(tr("Write hard disk image back", "Festplatten Abbild zurückschreiben"));
        filename = folder_file_;
        filename = filename + ".txt";
        int found = filename.indexOf("'");
        if (found > -1)
            filename = filename.replace("'", "");
        found = filename.indexOf("'"); 
        if (found > -1)   
            filename = filename.replace("'", ""); 
         //prüfen ob Datei existiert
        if (!filename.isEmpty()) 
           {
      	   QFile file(filename);
           if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
              textEdit->setPlainText(file.readAll());
  	   } 
     } 
} 

void FileDialog::beenden() {
     dialog_auswertung = 0;
     close();
}    

void FileDialog::folder_einlesen() {
        QString folder;
        if (dialog_auswertung ==2){
            cmd_save->setText(tr("Save partition", "Partition sichern")); 
            file_save();
        }
        dialog_auswertung = 1;
  	close();
}

void FileDialog::file_save()
{
        extern QString folder_file_;
      	QString filename = folder_file_;
      	if (filename.isEmpty())
   		return;
	QFile file(filename);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) 
           {
             QMessageBox::about(this,tr("Note", "Hinweis"),
              tr("The notes on the partition were not written to a file.\n", "Die Hinweise zur Partition wurden nicht in eine Datei geschrieben.\n"));
            }
        textEdit->toPlainText().toUtf8();
    	file.write((textEdit->toPlainText()).toUtf8());
  }

void FileDialog::file_read()
{
 QString filename;
 int found = 0;
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        setting.endGroup();
	extern QString folder_file_;
        filename = folder_file_;
        int pos = filename.indexOf("fsa");
        filename = filename.left(pos);
        filename.insert(pos, QString("txt")); 
        found=filename.indexOf("+");
        if (found > 0)
            filename.replace(found, 1, " "); 
        if (dialog_auswertung >=7)
           filename = folder_file_ + ".txt" ;  
        //prüfen ob Datei existiert
        if (!filename.isEmpty()) 
           {
      	   QFile file(filename);
           if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
              textEdit->setPlainText(file.readAll());
  	   }
  }

void FileDialog::werte_uebergeben(QString wert) {
       	wort = wert;
}












