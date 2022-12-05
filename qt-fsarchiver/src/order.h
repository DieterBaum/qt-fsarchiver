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

#ifndef ORDER_H
#define ORDER_H  
#include "ui_order.h"
#include <QMessageBox>

class OrderDialog: public QDialog, private Ui::order_dialog {
  Q_OBJECT
  public:
    OrderDialog();
    ~OrderDialog() {}

private slots:	
   void make_order();
   void del_all();
   void del_one();
   int questionMessage(QString frage);
   void listWidget_auslesen();
   void clean();
   void end_();
};

#endif // OrderDialog_H






















