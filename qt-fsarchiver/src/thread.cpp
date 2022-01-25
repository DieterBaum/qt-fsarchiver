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
#include "thread.h"
#include "mainWindow.h"

Thread::Thread() {
   anzahl = 0;
   qdummy = "0";
}

void Thread::setValues( int anzahl_, QString dummy ) {  //Image Festplatte oder Partition mit dd-gzip erstellen oder zurückschreiben
   anzahl = anzahl_;
   qdummy = dummy;
}

void Thread::run() {
extern int dialog_auswertung;
int pos = qdummy.indexOf("/usr/sbin"); 

if (qdummy != "0" && pos > -1) {  //thread Festplatte klonen, Image erstellen midd ohne gzip
	dialog_auswertung = system (qdummy.toLatin1().data()); 
       // qDebug() << "pos = qdummy.indexOf(/usr/sbin);" << pos << dialog_auswertung;
	}
}

 



















