/*
 * qt-fsarchiver: Filesystem Archiver
 * 
* Copyright (C) 2008-2020 Dieter Baum.  All rights reserved.
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

#ifndef FILEDIALOG_H
#define FILEDIALOG_H
#include "ui_filedialog.h"
#include <QMessageBox>

class FileDialog: public QDialog, private Ui::FileDialog {
  Q_OBJECT
  public:
    FileDialog();
    ~FileDialog() {}
    void werte_uebergeben(QString wert);
        
  protected slots:
    void folder_einlesen();
    void file_save();
    void file_read();
    void beenden();
    
  private:

};

#endif // FILEDIALOG_H















