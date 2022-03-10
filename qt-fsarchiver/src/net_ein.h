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

#ifndef NET_Ein_H
#define NET_Ein_H
#include <QtGui>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDialog>
#include "ui_net_ein.h"

class NetEin : public QDialog, private Ui::Eingabe_Net
{
	Q_OBJECT

public:
	NetEin();
        ~NetEin() {}
        int list_net(QString flag);
        QString Namen_holen(); 
	QString user_holen(); 
	QString key_holen(); 

public slots:
        
        
protected slots:
        void save_net ();
   	void restore_net ();
        QString hostname();
        void listWidget_show();
        void setting_save(QString user_net_ein);  
        void Kennwort();
        int questionMessage(QString frage);

private:
	QFileSystemModel *dirModel;
	
private slots:
	int end();
        int go();
};

#endif


















