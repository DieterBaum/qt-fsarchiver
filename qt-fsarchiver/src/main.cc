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

#define HAVE_QT5 (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

#ifdef HAVE_GETOPT_H
  #include <getopt.h>
#endif

#ifdef HAVE_SYS_PARAM_H
  #include <sys/param.h>
#endif
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "mainWindow.h"
#include <iostream>
#include <fstream>

#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include "qt_probe.h"
#include "setting.h"
#include <locale.h>
#include <gettext.h>

using namespace std;
// experement mit uid: uid_t my_uid, my_euid, my_gid, my_egid; 

FILE * g_fDebug; // debug file
QString folder_file_;
int dialog_auswertung;
int btrfs_flag;
int show_flag = 0;
QString parameter[15];
QString add_part[100];
QString partition1[100][5];
QString part[100][10];
QString anlage;
QString password;
//QString user;
int sleepfaktor = 5;
int flag1 = 0;
int password_ = 0;
QString list_;

int main(int argc, char *argv[])
{
list_ = argv[1];
   /* Set locale via LC_LL.  */
   setlocale (LC_ALL, "");
   bindtextdomain ("" ,"qt-fsarchiver");
   textdomain ("qt-fsarchiver");
   QApplication app(argc, argv);
   QString language_;
   QString language[100];
   language[0] = "de_DE";
   language[1] = "en_EN";
   language[2] = "ru_RU";
   language[3] = "es_ES";
   language[4] = "it_IT";
   language[5] = "ch_CH";
   language[6] = "nl_NL";
   language[7] = "jp_JP";
   language[8] = "fr_FR";
   language[9] = "ar_AR";
   language[10] = "ca_CA";
   language[11] = "cs_CS";
   language[12] = "da_DA";
   language[13] = "el_EL";
   language[14] = "et_ET";
   language[15] = "fi_FI";
   language[16] = "he_HE";
   language[17] = "hi_HI";
   language[18] = "hu_HU";
   language[19] = "hy_HY";
   language[20] = "id_ID";
   language[21] = "lt_LT";
   language[22] = "lv_LV";
   language[23] = "ko_KO";
   language[24] = "no_NO";
   language[25] = "pl_PL";
   language[26] = "pt_PT";
   language[27] = "fa_FA";
   language[28] = "ro_RO";
   language[29] = "sl_SL";
   language[30] = "sr_SR";
   language[31] = "sv_SV";
   language[32] = "th_TH";
   language[33] = "tr_TR";
   language[34] = "uk_UK";
   language[35] = "ur_UR";
   language[36] = "vi_VI";
           
   QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
   setting.beginGroup("Basiseinstellungen");
   int auswertung = setting.value("Sprache").toInt();
   if (auswertung > 0) 
   	language_ = "qt-fsarchiver_" + language[auswertung -1];
   setting.endGroup();
/* ---install translation file for application strings---
   ursprünglicher Code, Ausführung nur in Deutsch  
   QString translatorFileName = QLatin1String("qt_");
   translatorFileName += QLocale::system().name();
   QTranslator *translator = new QTranslator(&app);
   if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);*/
//   internationale Sprachauswahl
    QString sLocPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
     QTranslator *translator = new QTranslator(0);
     if (auswertung == 0)
         translator->load(QString("qt-fsarchiver_"+QLocale::system().name()), sLocPath);
     if (auswertung != 0) 
         translator->load(language_, sLocPath);
     app.installTranslator(translator);
//     QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); 
     QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); 
//     QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); 
       
   MWindow window;
   if (window.Root_Auswertung() != 10)
      {
      if(list_ == "")
         {
   	 window.show();
   	 return app.exec();
   	 }
      if(list_ != "")
         return 0;	 
      }
      else
   	return 0;	
 //  qDebug() << window.Root_Auswertung();
 }
  














