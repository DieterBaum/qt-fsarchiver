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

#include <QtGui> 
#include "setting.h"

extern int dialog_auswertung;
QStringList items_kerne;
QStringList items_zip;
QStringList items_language; 
QStringList items_network;
QStringList items_zstd_setting;
QStringList items_sleep;

DialogSetting::DialogSetting()
{
        setupUi(this); // this sets up GUI
	connect( cmd_save, SIGNAL( clicked() ), this, SLOT( setting_save())); 
        connect( cmd_zstd, SIGNAL( clicked() ), this, SLOT( zip_setting_einlesen())); 
        connect( cmd_cancel, SIGNAL( clicked() ), this, SLOT(close()));
        items_language.clear();
        items_language << tr("German", "Deutsch") << tr("English", "Englisch") << tr("Russian", "Russisch") << tr("Spanish", "Spanisch") << tr("Italian", "Italienisch") << tr("Chinese", "Chinesisch");
        items_language << tr("Dutch", "Niederländisch") << tr("Japanese", "Japanisch") <<  tr("French", "Französisch")<<  tr("Arabic", "Arabisch") <<tr("Catalan", "Katalanisch") << tr("Czech", "Tschechisch")<< tr("Danish", "Dänisch");
        items_language  << tr("Greek", "Griechisch") << tr("Estonian", "Estnisch") << tr("Finnish", "Finnisch") <<  tr("Hebrew","Hebräisch")  <<  tr("Hindi", "Hindi") <<tr("Hungarian", "Ungarisch") << tr("Armenian", "Armenisch") << tr("Indonesian", "Indonesisch");
        items_language << tr("Latvian", "Lettisch") << tr("Lithuanian", "Litauisch") << tr("Korean", "Koreanisch") << tr("Norwegian", "Norwegisch") <<  tr("Polish", "Polnisch") << tr("Portuguese", "Portugisisch") <<tr("Persian", "Persisch")<< tr("Romanian", "Rumänisch");
        items_language << tr("Slovak", "Slowakisch") << tr("Serbian", "Serbisch") << tr("Swedish", "Schwedisch") <<  tr("Thai", "Thailändisch") <<tr("Turkish", "Türkisch") << tr("Ukrainian", "Ukrainisch") << tr("Urdu", "Urdu") << tr("Vietnamese", "Vietnamesich");
        cmb_language->addItems (items_language);
        items_zstd_setting << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20" << "21" << "22";
        cmb_zstd->addItems (items_zstd_setting);
        items_kerne << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
        cmb_Kerne->addItems (items_kerne);
   	items_kerne.clear();
        items_sleep << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19" << "20";
        cmb_sleep->addItems (items_sleep);
        items_sleep.clear();
        items_zip << tr("lz4", "lz4") << tr("lzo", "lzo") << tr("gzip fast","gzip fast") << tr("gzip standard","gzip standard") << tr("gzip best","gzip best") <<  tr("bzip2 fast","bzip2 fast");
   	cmb_zip->addItems (items_zip);
   	items_zip.clear();
   	items_zip << tr("bzip2 good", "bzip2 good") << tr("lzma fast","lzma fast") << tr("lzma medium","lzma medium") << tr("lzma best","lzma best") << tr("zstd","zstd");
   	cmb_zip->addItems (items_zip);
   	items_zip.clear();
        items_network << tr("Samba") << tr("NFS");
   	cmb_network->addItems (items_network);
   	items_network.clear();
        QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
        setting.beginGroup("Basiseinstellungen");
        int auswertung = setting.value("Sprache").toInt(); 
        cmb_language -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("zstd").toInt();
        if (auswertung !=0) 
            cmb_zstd -> setCurrentIndex(auswertung-1); 
        else
            cmb_zstd -> setCurrentIndex(7);
        auswertung = setting.value("dummy").toInt();
        if (auswertung ==2){
           chk_ssh ->setEnabled(false);
           chk_sshfs ->setEnabled(false); 
        } 
        auswertung = setting.value("Kompression").toInt();
        if (auswertung !=0)
             cmb_zip -> setCurrentIndex(auswertung);
        else 
            cmb_zip -> setCurrentIndex(10);
        auswertung = setting.value("sleep").toInt();
        if (auswertung !=0)
             cmb_sleep -> setCurrentIndex(auswertung);
        else 
            cmb_sleep -> setCurrentIndex(4);
        auswertung = setting.value("Kerne").toInt();
        cmb_Kerne -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("Network").toInt();
        cmb_network -> setCurrentIndex(auswertung-1); 
        auswertung = setting.value("overwrite").toInt();
        if (auswertung ==1)
           chk_file->setChecked(true); 
        auswertung = setting.value("tip").toInt();
        if (auswertung ==1)
           chk_tip->setChecked(true);  
        auswertung = setting.value("key").toInt();
        if (auswertung ==1)
           chk_key->setChecked(true); 
        auswertung = setting.value("place").toInt();
        if (auswertung ==1)
           chk_folder->setChecked(true); 
        auswertung = setting.value("split").toInt();
        if (auswertung ==1)
           chk_split->setChecked(true); 
        auswertung = setting.value("Passwort").toInt();
        if (auswertung ==1)
           chk_password->setChecked(true);
        auswertung = setting.value("save").toInt();
        if (auswertung ==1)
           chk_datesave->setChecked(true);
        auswertung = setting.value("pbr").toInt();
        if (auswertung ==1)
           chk_pbr->setChecked(true);
        auswertung = setting.value("ssh").toInt();
        if (auswertung ==1)
           chk_ssh->setChecked(true);
        auswertung = setting.value("sshfs").toInt();
        if (auswertung ==1)
           chk_sshfs->setChecked(true);
        auswertung = setting.value("showPrg").toInt();
        if (auswertung ==1)
           chk_prg->setChecked(true);
        auswertung = setting.value("hidden").toInt();
	if (auswertung ==1)
           chk_hidden->setChecked(true);
        setting.endGroup();
        zip_setting_einlesen();
}        

void DialogSetting:: setting_save()
{
     QSettings setting("qt5-fsarchiver", "qt5-fsarchiver");
     setting.beginGroup("Basiseinstellungen");
     setting.setValue("Sprache",cmb_language->currentIndex()+1);
     int zip = cmb_zip->currentIndex();
     if (cmb_Kerne->currentIndex() > -1)
     	setting.setValue("Kerne",cmb_Kerne->currentText());
     else
        setting.setValue("Kerne","1");
     if (cmb_zstd->currentIndex() > -1)
     	setting.setValue("zstd",cmb_zstd->currentIndex()+1);
     else
        setting.setValue("zstd","1");
     if (cmb_sleep->currentIndex() > -1)
     	setting.setValue("sleep",cmb_sleep->currentIndex());
     else
        setting.setValue("sleep","4");
     setting.setValue("Kompression",zip);
     int net = cmb_network->currentIndex()+1;
     setting.setValue("Network",net);
     if (chk_file->checkState()) 
            setting.setValue("overwrite",1);
     else
            setting.setValue("overwrite",0);
     if (chk_tip->checkState())
            setting.setValue("tip",1);
     else
            setting.setValue("tip",0);
     if (chk_key->checkState()) 
            setting.setValue("key",1);
     else
            setting.setValue("key",0);
     if (chk_folder->checkState()) 
            setting.setValue("place",1);
     else
            setting.setValue("place",0);
     if (chk_split->checkState()) 
            setting.setValue("split",1);
     else
            setting.setValue("split",0);
     if (chk_password->checkState()) 
            setting.setValue("Passwort",1);
     else
            setting.setValue("Passwort",0);
     if (chk_datesave->checkState()) 
            setting.setValue("save",1);
     else
            setting.setValue("save",0);
     if (chk_pbr->checkState()) 
            setting.setValue("pbr",1);
     else
            setting.setValue("pbr",0);
     if (chk_ssh->checkState()) 
            setting.setValue("ssh",1);
     else
            setting.setValue("ssh",0);
     if (chk_sshfs->checkState()) 
            setting.setValue("sshfs",1);
     else
            setting.setValue("sshfs",0);
     if (chk_prg->checkState()) 
            setting.setValue("showPrg",1);
     else 
            setting.setValue("showPrg",0);
     if (chk_hidden->checkState()) 
            setting.setValue("hidden",1);
     else
            setting.setValue("hidden",0);	
     setting.endGroup();
     QMessageBox::about(this,tr("Note", "Hinweis"),
         tr("The settings have been saved. If the language setting is changed, the program must be restarted.","Die Einstellungen wurden gespeichert. Bei geänderter Spracheinstellung muss das Programm neu gestartet werden.\n"));
}

void DialogSetting::zip_setting_einlesen() {
int zip = cmb_zip->currentIndex();
    if (zip == 10) {
       cmb_zstd->setEnabled(true);
       label_5->setEnabled(true);
       }
    else
       {
       cmb_zstd->setEnabled(false);
       label_5->setEnabled(false);
       }
}









