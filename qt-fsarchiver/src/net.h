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

#ifndef NET_H
#define NET_H
#include <QtGui>
#include <QFileSystemModel> 
#include <QMessageBox>
#include "ui_net.h"
#include "thread.h"

class DialogNet : public QDialog, private Ui::Dialog_Net
{
	Q_OBJECT

public:
	DialogNet();
        ~DialogNet() {}
        
public slots:
        
protected slots:
   	int restorePartition();
   	int savePartition();
        void closeEvent(QCloseEvent* event);
        void elapsedTime();
   	void remainingTime(int prozent);
        void indicator_reset();
        int testDateiName(std::string endung);
        void Daten_Samba_eintragen();
        void Daten_NFS_eintragen();
        void ViewProzent();
        void keyPressEvent(QKeyEvent *event);
        int questionMessage(QString frage);
        void esc_end();
        void cmb_net();
        void zip_einlesen_net();
        void save_attribut_net(QString attribut);
        int questionMessage_net(QString frage);
        QString mtab_einlesen_net(int zahl);
        void folder_text_einlesen();
        void startThread1();
        void startThread2();
        void startThread3();
                       
private:
        Thread thread1;
        Thread thread2;
        Thread thread3;
        QTimer *timer; 
        QIcon folderIcon;
        QIcon fileIcon;	
        QFileSystemModel *dirModel;
        QItemSelectionModel *selModel;	
	
private slots:
        int search_folder_free(QString rechner);
        int nfs_search_folder_free(QString rechner);		
	void end();
        void chkkey();
	void addWidget();
        void starteinstellung();
        void rdButton_auslesen();
        QString Zeit_auslesen();
        void listWidget_auslesen();
        int listWidget_folder_free_auslesen();    
        void folder_file();
        void thread1Ready();
        void thread2Ready();
        QString Zeit_auslesen_net();
};

#endif





















