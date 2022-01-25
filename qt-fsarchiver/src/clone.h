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

#ifndef CLONE_H
#define CLONE_H
#include <QtGui>
#include <QFileSystemModel> 

#include <string.h>
#include "ui_clone_dialog.h"
#include <qthread.h>

#include "thread.h"

class DialogClone : public QWidget, private Ui::clone_dialog
{
	Q_OBJECT

public:
	DialogClone();
        ~DialogClone() {}

protected slots:
   	void closeEvent(QCloseEvent* event);
        QString Zeit_auslesen_clone();

public slots:
	int do_clone();
        int do_image();
        int restore_image();
        void folder_einlesen();
        int file_check();
        void ViewProzent();
	int questionMessage(QString frage);
        void rdbutton_clone();
        void rdbutton_image_save();
        void rdbutton_image_restore();
        void format_Disk();
        void todo();
        void remainingTime(int prozent);
	void elapsedTime();
	QString  pid_ermitteln(QString prozess);
        void pid_2_ermitteln();
        void esc_end();
        void read_write_hd();
	void read_write_hd_1();
	void keyPressEvent(QKeyEvent *event) ;
        int do_image_partition();
        int restore_image_partition(); 
        void rdbutton_partition_image_save();
        void rdbutton_partition_image_restore();
        void addWidget();
        void listWidget_auslesen();
        void folder_expand();
        int testen_1(QString filename, QString partition, int flag);
        int testen(QString filename);
        void beschreibungstext_clone(QString text, int zip, int row);
        QString sdx3_clone_einlesen(QString part_, int flag, int row);
        QString format_clone(float zahl);
        QString kernel_version_clone();  
        QString linux_version_clone();
    
private:
    QFileSystemModel *dirModel;
    QItemSelectionModel *selModel;
    QLabel *questionLabel;
    int mountpoint(int zahl);
    int mountpoint_disk(QString partition);
    Thread thread1;
    Thread thread2;
    QTimer *timer_clone; 
    QTimer *timer_read_write; 
    

private slots: 
   void startThread1(int flag);
   void thread1Ready();
   void startThread2(int flag);
   void thread2Ready();
};
#endif


















