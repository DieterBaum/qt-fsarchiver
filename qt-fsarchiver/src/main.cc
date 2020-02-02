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

#define HAVE_QT5 (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "mainWindow.h"
#include "setting.h"
#include <locale.h>
#include <gettext.h>

QString folder_file_;
int dialog_auswertung;
QString parameter[15];
QString add_part[100];
QString part[100][10];
QString anlage;
QString password;
QString user;
int sleepfaktor = 5;
int flag1 = 0;
int password_ = 0;
//QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

int main(int argc, char **argv)
{
//QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    if (argc < 1)
    {   fprintf(stderr, "No arguments provided, cannot continue\n");
        return -1;
    }
    anlage = argv[1];
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
   language[15] = "fn_FN";
   language[16] = "he_HE";
   language[17] = "hi_HI";
   language[18] = "hu_HU";
   language[19] = "hy_HY";
   language[20] = "id_ID";
   language[21] = "lv_LV";
   language[22] = "lt_LT";
   language[23] = "ko_KO";
   language[24] = "no_NO";
   language[25] = "pl_PL";
   language[26] = "pt_PT";
   language[27] = "fa_FA";
   language[28] = "fa_FA";
   language[29] = "ro_RO";
   language[30] = "sl_SL";
   language[31] = "sr_SR";
   language[32] = "sv_SV";
   language[33] = "th_TH";
   language[34] = "tr_TR";
   language[35] = "uk_UK";
   language[36] = "ur_UR";
   language[37] = "vi_VI";
           
   QSettings setting("qt-fsarchiver", "qt-fsarchiver");
   setting.beginGroup("Basiseinstellungen");
   int auswertung = setting.value("Sprache").toInt();
   if (auswertung > 0) 
      language_ = "qt-fsarchiver_" + language[auswertung -1];
   setting.endGroup();
  // internationale Sprachauswahl
    QString sLocPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QTranslator *translator = new QTranslator(0);
    if (auswertung == 0)
        translator->load(QString("qt-fsarchiver_"+ QLocale::system().name()), sLocPath);
    if (auswertung != 0) 
       translator->load(language_, sLocPath);
     app.installTranslator(translator);
     QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); 
     MWindow window;
     window.show();
     return app.exec();
 }
  















