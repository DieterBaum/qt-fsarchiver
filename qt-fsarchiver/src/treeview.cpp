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

#include <QtGui> 
#include "treeview.h"

QString folder_treeview;
extern QString user;
QString userpath_treeview;
QString homepath_treeview = QDir::homePath();

TreeviewRead::TreeviewRead()
{
QStringList filters;
        userpath_treeview = homepath_treeview; 
        setupUi(this); 
	connect( cmd_save, SIGNAL( clicked() ), this, SLOT(folder_einlesen_beenden())); 
        connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(close()));
        connect( pushButton_treeview, SIGNAL( clicked() ), this, SLOT(folder_einlesen()));
        connect( pushButton_treeview_2, SIGNAL( clicked() ), this, SLOT(folder_expand()));
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
   	treeView->setModel(dirModel);
        filters << "*.fsa";
       	dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters); 
   	treeView->setSelectionModel(selModel);
	QModelIndex cwdIndex = dirModel->index(userpath_treeview +"/.qt-fs-client");
        dirModel->setRootPath(userpath_treeview +"/.qt-fs-client");
        treeView->setRootIndex(cwdIndex);
	treeView->setEnabled(true);
        connect(treeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &TreeviewRead::folder_einlesen);
        
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

void TreeviewRead::folder_expand() {
   QModelIndex index = treeView->currentIndex();
   treeView->expand(index);
}


















