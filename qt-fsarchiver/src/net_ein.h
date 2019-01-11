/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2019 Dieter Baum.  All rights reserved.
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

#ifndef NET_Ein_H
#define NET_Ein_H
#include <QtGui>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDialog>
#include "ui_net_ein.h"



using namespace std;

class NetEin : public QDialog, private Ui::Eingabe_Net
{
	Q_OBJECT

public:
	NetEin(QWidget *parent = 0);
        int list_net(QString flag);
        int list_net_ssh(QString flag);
        QString Namen_holen(); 
	QString user_holen(); 
	QString key_holen(); 

public slots:
        
        
protected slots:
        void save_net ();
   	void restore_net ();
        QString hostname();
        QString IP(QString adresse);
        void listWidget_show();
        QString crypt(QString key);
        QString decrypt(QString key_);
        int setting_save();
        void Kennwort();
        int Array_pruefen(QString ip);
        int questionMessage(QString frage);

private:
	QFileSystemModel *dirModel;
	
private slots:
	int end();
        int go();
};

#endif












