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

#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QtGui>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDialog>
#include "ui_treeview.h"

class TreeviewRead : public QDialog, private Ui::treeview_dialog
{
	Q_OBJECT

public:
	TreeviewRead();
         ~TreeviewRead() {}
         QString folder_treeview_holen();
       
private:
	QFileSystemModel *dirModel;
    	QItemSelectionModel *selModel;       
	
private slots:	
        void folder_einlesen();
        void folder_einlesen_beenden();
        void folder_expand();
};

#endif


















