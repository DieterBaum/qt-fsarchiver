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
#include "thread.h"
#include "mainWindow.h"
extern "C" {
#include "connect_c_cpp.h"
}

Thread::Thread() {
   anzahl = 0;
   qdummy = "0";
}

void Thread::setValues( int anzahl_, QString dummy ) {
   anzahl = anzahl_;
   qdummy = dummy;
}

void Thread::run() {
  extern int dialog_auswertung;
  extern QString parameter[15];
  QString befehl;
if(anzahl == 100)  
  {
  befehl = qdummy;
  if(system (befehl.toLatin1().data()))
      befehl = "";
  }
if (qdummy == "0") {
  //Zurücksetzen der bekannten oder unbekannten Fehlermeldung
  werte_uebergeben(1,4);
//  qDebug() << "fsarchiver aufruf in thread.cpp" << anzahl << parameter[0] << parameter[1] << parameter[2] << parameter[3] << parameter[4] << parameter[5] << parameter[6] << parameter[7] << parameter[8];
  dialog_auswertung = fsarchiver_aufruf(anzahl,parameter[0].toLatin1().data(),parameter[1].toLatin1().data(),parameter[2].toLatin1().data(),parameter[3].toLatin1().data(),parameter[4].toLatin1().data (),parameter[5].toLatin1().data(),parameter[6].toLatin1().data(),parameter[7].toLatin1().data(),parameter[8].toLatin1().data(),parameter[9].toLatin1().data(),parameter[10].toLatin1().data(),parameter[11].toLatin1().data(),parameter[12].toLatin1().data(),parameter[13].toLatin1().data(),parameter[14].toLatin1().data());

   if (dialog_auswertung != 0){
     //verhindert das Blockieren des Programmes Abfrage in der while Schleife in dir.cpp und mainwindow.cpp
     float endeThread = werte_holen(4);
     // Wenn vom Programm bereits eine Fehlermeldung zurückgeschrieben wurde, wird die Fehlermeldungnummer nicht durch 100 ersetzt.
     if (endeThread ==0)
     	werte_uebergeben(100,4);
    }
 }
int pos = qdummy.indexOf("dd"); 
if (qdummy != "0" && pos > -1) {  //thread Festplatte klonen, Image erstellen
	dialog_auswertung = system (qdummy.toLatin1().data()); 
	}
}

 














