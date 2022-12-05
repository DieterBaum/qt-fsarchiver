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

#include <QtGui> 
#include "treeview.h"

QString folder_treeview;

TreeviewRead::TreeviewRead(QWidget *parent)
{
QStringList filters;
QString homepath = QDir::homePath();
        setupUi(this); 
	connect( cmd_save, SIGNAL( clicked() ), this, SLOT(folder_einlesen_beenden())); 
        connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(close()));
        connect( pushButton_treeview, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));

        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
   	treeView->setModel(dirModel);
        filters << "*.fsa";
   	dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters); 
   	treeView->setSelectionModel(selModel);
	QModelIndex cwdIndex = dirModel->index(homepath +"/.qt5-fs-client");
        dirModel->setRootPath(homepath +"/.qt5-fs-client");
        treeView->setRootIndex(cwdIndex);
	treeView->setEnabled(true);
}        

void TreeviewRead::folder_einlesen() {
   QModelIndex index = treeView->currentIndex();
   QModelIndexList indexes = selModel->selectedIndexes();
   folder_treeview =  (dirModel->filePath(index));
}

QString TreeviewRead::folder_treeview_holen()
{
  return folder_treeview;
}

void TreeviewRead::folder_einlesen_beenden() {
     close();
}















