
/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2018 Dieter Baum.  All rights reserved.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QFileSystemModel> 

#include <string.h>
#include "ui_fsarchiverMain.h"
#include "thread.h"

#include <QDialog>
#include <QMap>

class MWindow : public QMainWindow,
                private Ui::MainWindow {
    Q_OBJECT

public:
   MWindow();
   ~MWindow() {}
   int is_running();
   QString Zeit_auslesen();
   QString mtab_einlesen(int zahl);
   QString identify_save_part(QString save_partition);
   QString beschreibungstext(QString text, int zip, int row);
   int is_mounted (char* dev_path);
   int questionMessage(QString frage); 
   QString UUID_auslesen(int row);
   void save_attribut(QString attribut);
   void date_delete();
              
public slots: 
   void folder_einlesen();
   void folder_expand();
   void save_button();
   QString pid_ermitteln_(QString prozess);
   void del_mediafolder();
   void kill_end();
      
protected slots:
   void esc_end(int flag);
   void ViewProzent();
   int testDateiName(std::string endung);
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
   void format_();
   QString format(float zahl);
   void closeEvent(QCloseEvent* event);
   void elapsedTime();
   void remainingTime(int prozent);
   void indicator_reset();
   void keyPressEvent(QKeyEvent *event);
   void restore_button();
   void eingabe_net_save();
   void eingabe_net_restore();
   void chkkey();
   void chkhidden();
   void chkGB();
   QString kernel_version();
   QString linux_version();
   void clone_save();
   void zip_einlesen();
   void sdx_einlesen();
   QString datei_auswerten(QString buchstabe);
   QString datei_auswerten_1(QString dateiname);
   QString sdx3_einlesen(QString part, int flag);
   void daten_write(QString password, int i);
   QString md5sum(QString file_name);
   int is_gpt_main(QString partition_efi);
   QString label_read(QString partname);
   void zip_setting_einlesen();
     
private:
    QFileSystemModel *dirModel;
    QItemSelectionModel *selModel;
    Thread thread1;
    Thread thread2;
    QTimer *timer;  
    
    
private slots:    
   void thread1Ready();
   void thread2Ready();
     
};
#endif












