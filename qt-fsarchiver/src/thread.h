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


#ifndef THREAD_H
#define THREAD_H
#include <qthread.h>

class Thread : public QThread {
   Q_OBJECT
public:
   Thread();
   void setValues( int anzahl_, QString dummy);
   //int progressbar();
protected:
   void run();
private:
   int anzahl;
   QString qdummy; 
};
#endif














