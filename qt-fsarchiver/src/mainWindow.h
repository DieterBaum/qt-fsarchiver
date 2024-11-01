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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QFileSystemModel> 

#include <string.h>
#include "ui_fsarchiverMain.h"
#include "thread.h"

#include <QDialog>
#include <QMap>

using namespace std;



class MWindow : public QMainWindow,
                private Ui::MainWindow {
    Q_OBJECT

public:
   MWindow();
   ~MWindow() {}
   //int show_flag = 0; Zugriff auf eine Variable von beispielsweise net.cpp
   int Root_Auswertung();
   QString Zeit_auslesen();
   QString mtab_einlesen(QString partition_if_home);
   QString identify_save_part(QString save_partition);
   QString beschreibungstext(QString partitiontext, QString text, int zip, int row, QString size_folder, QString folder);
   int is_mounted (char* dev_path);
   int questionMessage(QString frage); 
   int questionMessage_critical(QString frage);
   int questionMessage_warning(QString frage);
   QString UUID_auslesen(int row);
        
public slots: 
   void folder_einlesen();
   void save_button();
                    
protected slots:
   void esc_end();
   void ViewProzent();
   int testDateiName(string endung);
   int savePartition();
   int restorePartition();
   void info();
   void einstellungen();
   void listWidget_auslesen();
   void rdButton_auslesen();
   void mbr_save ();
   void mbr_restore ();
   void dir_save ();
   void dir_restore ();
   void folder_file();
   void starteinstellung();
   void format();
   void closeEvent(QCloseEvent* event);
   void elapsedTime();
   void remainingTime(int prozent);
   void indicator_reset();
   void keyPressEvent(QKeyEvent *event);
   void restore_button();
   void chkkey();
   void chkhidden();
   void chkGB();
   QString kernel_version();
   QString linux_version();
   QString mountpoint(QString uuid);
   QString format(float zahl);
   int pid_ermitteln();
   void del_mediafolder();
   void clone_save();
   void make_order(); 
   void order_edit(); 
   void save_restorePartiiton_list();
   void save_attribut(QString attribut, int zahl);
   void listWidget2_auslesen();
   void kill_end();
   QString pid_ermitteln_(QString prozess);
   void zip_setting_einlesen();
   void zip_einlesen();
   void make_direct();
   int size_determine(QString part_size_compress, QString folder);
   int question_end();
    
private:
    QFileSystemModel *dirModel;
    QItemSelectionModel *selModel;
    QLabel *questionLabel;
    Thread thread1;
    Thread thread2;
    QTimer *timer;  
    
    
private slots:    
   void startThread1();
   void thread1Ready();
   void startThread2();
   void thread2Ready();
     
};
#endif














