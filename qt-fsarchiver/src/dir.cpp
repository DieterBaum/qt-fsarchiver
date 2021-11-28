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
#include "dir.h"
#include "mainWindow.h"
#include <unistd.h>
extern "C" {
}

extern int dialog_auswertung;
extern int anzahl_disk;
extern QString parameter[15];
extern QString password;
extern QString user;
QString folder_dir;
QString folder_path;
QString dummy;
Qt::CheckState state;
QStringList items;
int endeThread_;
int dir_sekunde_elapsed;
int dir_minute_elapsed;
int dir_sekunde_summe;
QStringList items_dir_kerne;
int dummy_prozent_dir;
int prozent_ = 0;
int flag_View_dir;
int sekunde_tara_dir ;
int thread_run_dir;
int flag_end_dir;
extern int fsarchiver_aufruf(int argc, char *anlage0=NULL, char 
*anlage1=NULL, char *anlage2=NULL, char *anlage3=NULL, char 
*anlage4=NULL, char *anlage5=NULL, char *anlage6=NULL, char 
*anlage7=NULL, char *anlage8=NULL, char *anlage9=NULL, char 
*anlage10=NULL, char *anlage11=NULL, char *anlage12=NULL, char 
*anlage13=NULL, char *anlage14=NULL);
QStringList filters;
QStringList items_zstd_dir;
QString zip_dir_[11];
int zstd_level_dir;
extern QString user;
QString userpath_dir;
extern int sleepfaktor;
QString homepath_dir = QDir::homePath();

DialogDIR::DialogDIR()
{
        setupUi(this); // this sets up GUI
	connect( bt_save, SIGNAL( clicked() ), this, SLOT( folder_dir_path_einlesen())); 
        connect( chk_path, SIGNAL( clicked() ), this, SLOT( treeview_show() ) );
        connect( bt_end, SIGNAL( clicked() ), this, SLOT(close()));
        connect( chk_key, SIGNAL( clicked() ), this, SLOT(chkkey()));
        //connect( pushButton_break, SIGNAL( clicked() ), this, SLOT( esc_end() ) ); 
        connect( chk_hidden, SIGNAL( clicked() ), this, SLOT(chkhidden()));
        connect( pushButton_zstd_dir, SIGNAL( clicked() ), this, SLOT(zip_einlesen_dir()));
        connect( bt_dir, SIGNAL( clicked() ), this, SLOT(folder_expand_dir()));
        connect( bt_path, SIGNAL( clicked() ), this, SLOT(folder_expand_path()));
        timer = new QTimer(this);
        dirModel = new QFileSystemModel;
   	selModel = new QItemSelectionModel(dirModel);
        dirModel1 = new QFileSystemModel;
   	selModel1 = new QItemSelectionModel(dirModel1);
   	QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
        dirModel->setRootPath(QDir::rootPath());
        treeView_dir->setModel(dirModel);
   	treeView_dir->setSelectionModel(selModel);
   	treeView_dir->setRootIndex(cwdIndex);
	QModelIndex cwdIndex1 = dirModel1->index(QDir::rootPath());
        dirModel1->setRootPath(QDir::rootPath());
        treeView_path->setModel(dirModel1);
   	treeView_path->setSelectionModel(selModel1);
   	treeView_path->setRootIndex(cwdIndex1);
        items_zstd_dir << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" <<  "17" << "18" << "19" << "20" << "21" << "22";
        cmb_zstd_dir->addItems (items_zstd_dir);
        items_zstd_dir.clear();
        items_dir_kerne << "1" << "2" << "3" << "4" <<  "5" << "6" << "7" << "8" ;
   	cmb_kerne->addItems (items_dir_kerne);
   	items_dir_kerne.clear();
        zip_dir_[0]=(tr("lz4", "lz4"));
        zip_dir_[1]=(tr("lzo", "lzo"));
        zip_dir_[2]=(tr("gzip fast","gzip fast"));
        zip_dir_[3]=(tr("gzip standard","gzip standard"));
        zip_dir_[4]=(tr("gzip best","gzip best"));
        zip_dir_[5]=(tr("bzip2 fast","bzip2 fast"));
        zip_dir_[6]=(tr("bzip2 good"," bzip2 good"));
        zip_dir_[7]=(tr("lzma fast","lzma fast"));
        zip_dir_[8]=(tr("lzma medium","lzma medium"));
        zip_dir_[9]=(tr("lzma best","lzma best"));
        zip_dir_[10]=(tr("zstd","zstd"));
        items << zip_dir_[0] << zip_dir_[1] << zip_dir_[2] << zip_dir_[3] <<  zip_dir_[4];
        cmb_zip->addItems (items);
        items.clear();
        items << zip_dir_[5] << zip_dir_[6] << zip_dir_[7] << zip_dir_[8] << zip_dir_[9] << zip_dir_[10];
        cmb_zip->addItems (items);
        items.clear();
        userpath_dir = homepath_dir;
        // Ini-Datei auslesen
        QFile file(userpath_dir + "/.config/qt-fsarchiver/qt-fsarchiver.conf");
        QSettings setting("qt-fsarchiver", "qt-fsarchiver");
        if (file.exists()) 
        {
           setting.beginGroup("Basiseinstellungen");
           int auswertung = setting.value("Kompression").toInt();
           sleepfaktor= setting.value("sleep").toInt();
           if (sleepfaktor == 0)
               sleepfaktor = 5;
           cmb_zip -> setCurrentIndex(auswertung);
           if (auswertung ==10)
              cmb_zstd_dir->setEnabled(true);
           else
              cmb_zstd_dir->setEnabled(false);  
           auswertung = setting.value("Kerne").toInt();
           cmb_kerne -> setCurrentIndex(auswertung-1); 
           auswertung = setting.value("overwrite").toInt();
           auswertung = setting.value("place").toInt();
           if (auswertung ==1)
              chk_path->setChecked(true);
           if (auswertung ==1)
              chk_overwrite->setChecked(true); 
           auswertung = setting.value("pbr").toInt();
           if (auswertung ==1)
              chk_key->setChecked(true); 
	   auswertung = setting.value("hidden").toInt();
           if (auswertung ==1)
              chk_hidden->setChecked(true);
           auswertung = setting.value("Passwort").toInt(); 
           if (auswertung ==1)
              lineKey ->setEchoMode(QLineEdit::Normal);
           else
	       lineKey ->setEchoMode(QLineEdit::Password);
           zstd_level_dir = setting.value("zstd").toInt();
           cmb_zstd_dir -> setCurrentIndex(zstd_level_dir-1);
           auswertung = setting.value("Kompression").toInt();
           if (auswertung ==10)
               cmb_zstd_dir->setEnabled(true);
           else
               cmb_zstd_dir->setEnabled(false);
           setting.endGroup(); 
        } 
        else { 
                cmb_kerne -> setCurrentIndex(0);
        	chk_path->setChecked(true);
        	chk_overwrite->setChecked(true); 
        	cmb_zip -> setCurrentIndex(2);
                cmb_zstd_dir -> setCurrentIndex(9);
                cmb_zstd_dir->setEnabled(false);
        	} 
        chkkey();
        state = chk_key->checkState();
        if (state == Qt::Checked)
           lineKey->setEnabled(true);
        state = chk_path->checkState();
        if (dialog_auswertung == 4){
            chk_key->setText (tr("Encrypt\nbackup. key:", "Sicherung\nverschlüsseln. Schlüssel:"));
            bt_save->setText (tr("Backup directory", "Verzeichnis sichern"));
            label->setText (tr("Directory to backup", "zu sicherndes Verzeichnis"));
            label_2->setText (tr("Location (path) of the backup", "Ort (Pfad) der Sicherung")); 
            chk_path->setEnabled(false);
            chk_overwrite->setEnabled(true);
            cmb_zip->setEnabled(true);
            label_4->setEnabled(true);
            label_5->setEnabled(true);
            AnzahlsaveFile->setEnabled(true);
            AnzahlgesicherteFile->setEnabled(true);
            filters << "*.fsa*";
   	    } 
        if (dialog_auswertung == 5){
            chk_key->setText (tr("Decrypt\nbackup. key:", "Sicherung\nentschlüsseln. Schlüssel:"));
            bt_save->setText (tr("Write directory back", "Verzeichnis zurückschreiben"));  
	    label_2->setText (tr("Backup file to write back", "zurück zu schreibende Sicherungsdatei"));
            label->setText (tr("Location (path) of the restore", "Ort (Pfad) der Wiederherstellung")); 
            state = chk_path->checkState();
            if (state == Qt::Checked)
                 treeView_path->setEnabled(false);
            chk_overwrite->setEnabled(false);
            cmb_zip->setEnabled(false);
            label_4->setEnabled(false);
            label_5->setEnabled(false);
            AnzahlsaveFile->setEnabled(false);
            AnzahlgesicherteFile->setEnabled(false);
            filters << "*.fsa";
            }
            chkhidden();
 }

void DialogDIR::chkkey(){
     Qt::CheckState state;
     state = chk_key->checkState();
     if (state == Qt::Checked)
         lineKey->setEnabled(true);
     else 
        lineKey->setEnabled(false);
}

int DialogDIR::folder_dir_path_einlesen() {
MWindow window;
int pos = 0;
QString befehl = "";
int zip ;
QString compress = "";
QString keyText = "";
Qt::CheckState state1;
QString optionkey;
QString attribute;
QFile file1(userpath_dir + "/.config/qt-fsarchiver/zahlen.txt");
int found = 0;
     attribute = "chown -R " + user + " " + userpath_dir + "/.config/qt-fsarchiver";
     befehl = "/usr/sbin/qt-fsarchiver.sh  13 " + attribute;
     if(system (befehl.toLatin1().data()))
         befehl = "";
     attribute = "";
     QFile::remove(userpath_dir + "/.config/qt-fsarchiver/zahlen.txt");  
if (file1.exists())
        {
        QMessageBox::warning(this,tr("Note", "Hinweis"),
         	tr("Error. The file ~/config/qt-fsarchiver/zahlen.txt could not be deleted by qt-fsarchiver. The program is terminated. Manually delete the mentioned file and start the program again.\n", "Fehler. Die Datei ~/config/qt-fsarchiver/zahlentext konnte von qt-fsarchiver nicht gelöscht werden. Das Programm wird beendet. Löschen Sie manuell die genannte Datei und starten das Programm erneut.\n"));
        window.del_mediafolder();
        return 1;
        }
   	QModelIndex index = treeView_dir->currentIndex();
   	folder_dir.append  (dirModel->filePath(index));
   	folder_dir =  (dirModel->filePath(index));
        while (found > -1){
          found = folder_dir.indexOf(" ");
          if (found > -1)
            folder_dir.replace(found, 1, "+"); 
          }
        QModelIndex index1 = treeView_path->currentIndex();
   	folder_path.append  (dirModel1->filePath(index1));
   	folder_path =  (dirModel1->filePath(index1));
        found = 0;
        while (found > -1){
          found = folder_path.indexOf(" ");
          if (found > -1)
            folder_path.replace(found, 1, "+"); 
          }
        QFileInfo info(folder_path); 
        keyText = lineKey->text();
        state = chk_overwrite->checkState();
        state1 = chk_key->checkState();
        int indizierung;         
        //Verzeichnis sichern
        if (dialog_auswertung == 4){
           if (state1 == Qt::Checked && keyText.isEmpty())
              {
                QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("No encryption key was specified.\n", "Es wurde kein Schlüssel für die Verschlüsselung angegeben.\n"));
		return 1 ;
               }
           if (folder_path == "")
             {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select the directory in which the directory or file to be backed up is to be written.\n", "Bitte wählen Sie das Verzeichnis aus, in das das zu sichernde Verzeichnis bzw die zu sichernde Datei geschrieben werden soll.\n"));
		return 1 ;
             }
   	   if (folder_dir == "")
             {
          	QMessageBox::about(this,tr("Note","Hinweis"),
         	tr("Please select the directory or file to be backed up.\n", "Bitte wählen Sie das zu sichernde Verzeichnis bzw. die zu sichernde Datei aus.\n"));
		return 1 ;
             }
   	  if (info.isFile() && (dialog_auswertung == 4))
            {
      		QMessageBox::about(this, tr("Note", "Hinweis"),
      		tr("You have selected a file. You must select a directory\n", "Sie haben eine Datei ausgewählt. Sie müssen ein Verzeichnis auswählen\n"));
      		return 1 ;
            }
        parameter[0] = "fsarchiver";
       	parameter[1] = "savedir"; 
        zip = cmb_zip->currentIndex();
        zstd_level_dir = cmb_zstd_dir->currentIndex() +1;
                                if (zip < 10)
                                {
                                compress = QString::number(zip);
                                compress = "-z" + compress;
                                parameter[2] = compress;
                                if (zip == -1)
                                   parameter[2] = "-z3";
                                else
                                parameter[2] = compress; 
                                }
                                if (zip == 10)
                                   {
                                   compress = "-Z" + QString::number(zstd_level_dir);
                                   parameter[2] = compress;
                                }
        int kerne = cmb_kerne->currentIndex()+1;
        QString index = QString::number(kerne);
        if (index == "0")
           index = "1";
        parameter[3] = "-j" + index;
      	indizierung = 4;
        if (state == Qt::Checked) //Überschreiben ja
             {
             parameter[4] = "-o";
             indizierung = 5;
	     }	
        if (state1 == Qt::Checked)   //Schlüssel ja
              {     
              parameter[indizierung] = "-c";
	      parameter[indizierung + 1] = keyText;  
              int len = parameter[indizierung + 1].size();
              if (len < 6 || len > 64) {
                  QMessageBox::about(this,tr("Note", "Hinweis"),
         	  	tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                  	return 0 ; 
               	   }
               indizierung = indizierung + 2;  
	      }
        dummy = folder_path;
      	while (pos != -1)
      	{
      		pos = dummy.indexOf("/");
      		dummy.replace(pos,1,"-"); 
      		}
      	dummy.replace(0,1,"/"); 
        parameter[indizierung] = folder_dir + dummy + ".fsa";
        parameter[indizierung+1] = folder_path;
        QFile f(parameter[indizierung]);
        if  (parameter[4] != "-o" && (f.exists())){
            QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("The partition file ", "Die Partitionsdatei ")   + parameter[6] 
	+ tr("already exists. The backup is not performed\n", " ist bereits vorhanden. Die Sicherung wird nicht durchgeführt\n"));
                return 0 ; 
            }
            for ( int i=0; i<15; i++)
  		{
  		 if (parameter[i] != " ")
     		 attribute = attribute + " " + parameter[i];
  		 }
		 attribute = QString::number(indizierung + 2)  + attribute;
                 save_attribut_dir(attribute);
qDebug() << "attribute" << attribute;
            indicator_reset();
         //   werte_reset();
            bt_save->setEnabled(false);
            bt_end->setEnabled(false);
            flag_View_dir = 1;
            ViewProzent();
            befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_dir;
          if(system (befehl.toLatin1().data()))
               befehl = "";
            return 0;
            }

      //Verzeichnis zurückschreiben
      if (dialog_auswertung == 5){
      state = chk_path->checkState();
           if (state1 == Qt::Checked && keyText.isEmpty())  
              {
                QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("No decryption key was specified..\n", "Es wurde kein Schlüssel für die Entschlüsselung angegeben.\n"));
		return 1 ;
               }
           
           if (folder_path == ""  && state != Qt::Checked)
             {
          	QMessageBox::about(this, tr("Note", "Hinweis"),
         	tr("Please select the directory in which the saved directory is to be written back.\n", "Bitte wählen Sie das Verzeichnis aus, in das das das gesicherte Verzeichnis zurück geschrieben werden soll.\n"));
		return 1 ;
             }
   	   if (folder_dir == "")
             {
          	QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("Please select the existing backup file.\n", "Bitte wählen Sie die vorhandene Sicherungsdatei aus.\n"));
		return 1 ;
             }
   	  if (info.isDir() && (dialog_auswertung == 4))
            {
      		QMessageBox::about(this, tr("Note", "Hinweis"),
      		tr("You have selected a directory. You must select a backup file with the file extension .fsa.\n", "Sie haben ein Verzeichnis ausgewählt. Sie müssen eine Sicherungsdatei mit der Dateiendung .fsa auswählen\n"));
      		return 1 ;
            }
          pos = folder_dir.indexOf("fsa");
          if (pos == -1)
         	{
                QMessageBox::about(this,tr("Note", "Hinweis"),
         	tr("You have selected an incorrect recovery file.\nThe file extension must be .fsa.", "Sie haben eine falsche Wiederherstellungsdatei ausgesucht\nDie Dateiendung muss .fsa sein"));
                return 1;
         	}
        // prüfen ob Verzeichnis verschlüsselt
        // Annahme zunächst kein Schlüssel
              if (state1 != Qt::Checked) {
        	attribute = "3 fsarchiver archinfo " + folder_dir;
                save_attribut_dir(attribute);
                befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_dir;
              if(system (befehl.toLatin1().data()))
                    befehl = "";
                QThread::msleep(10 * sleepfaktor);
                optionkey = datei_auswerten_dir("p");
                if(optionkey == "13") 
                 {
                 chk_key->setChecked(true);
                 lineKey->setEnabled(true);
                 QMessageBox::about(this,tr("Note", "Hinweis"),
         	 tr("The partition is encrypted. Please enter the key", "Die Partition ist verschlüsselt. Bitte geben Sie den Schlüssel ein\n"));
                 return 1;
               	 } 
         }
         if (state1 == Qt::Checked) { // Verzeichnis mit Schlüssel gesichert
                parameter[3] = keyText;
		if (parameter[3].size() < 6 || parameter[3].size() > 64) {
                QMessageBox::about(this, tr("Note", "Hinweis"),
         		tr("The key length must be between 6 and 64 characters\n", "Die Schlüssellänge muss zwischen 6 und 64 Zeichen sein\n"));
                	return 0 ; 
               	}
                parameter[4] = folder_dir;
                attribute = "5 fsarchiver archinfo -c " + keyText + " "  + folder_dir;
                save_attribut_dir(attribute);
                befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_dir;
               if(system (befehl.toLatin1().data()))
                   befehl = "";
                QThread::msleep(10 * sleepfaktor);
                optionkey = datei_auswerten_dir("p");
                if(optionkey == "13") 
                {
                 QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.", "Sie haben ein falsches Passwort eingegeben. \n"));
           		   lineKey->setText ("");
                           return 0;
                 }
               }
        parameter[0] = "fsarchiver";
        parameter[1] = "restdir"; 
        int kerne = cmb_kerne->currentIndex()+1;
        QString index = QString::number(kerne);
        if (index == "0")
   		index = "1"; 
        parameter[2] = "-j" + index;
        indizierung = 3;
        if (state == Qt::Checked){
                parameter[indizierung] = (folder_dir);  //an Originalort zurückschreiben
                indizierung = indizierung + 1;
                parameter[indizierung]= ("/");
                }
        else    {
                parameter[indizierung] = folder_dir ; //an gewähltes Verzeichnis zurückschreiben
                indizierung = indizierung  + 1;
                parameter[indizierung] = folder_path ;
                }
        if (state1 == Qt::Checked) { // Verzeichnis mit Schlüssel gesichert
                parameter[5] = "-c";
                parameter[6] = keyText;
		indizierung = 6;
                }
         QString attribute; 
	 for ( int i=0; i<7; i++)
  	  {
  	  if (parameter[i] != " ")
     		attribute = attribute + " " + parameter[i];
  	  }
	attribute = QString::number(indizierung + 1)  + attribute;
        save_attribut_dir(attribute);
        indicator_reset();
        bt_save->setEnabled(false);
        bt_end->setEnabled(false);
        flag_View_dir = 2;
        this->setCursor(Qt::WaitCursor);
        befehl = "/usr/sbin/qt-fsarchiver.sh  1 " + userpath_dir;
       if(system (befehl.toLatin1().data()))
               befehl = "";
        QThread::msleep(10 * sleepfaktor);
        optionkey = datei_auswerten_dir("p");
        if(optionkey == "11")
        {
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have selected an incorrect fsa_file. ", "Sie haben ein falsche fsa_Datei gewählt. \n"));
        this->setCursor(Qt::ArrowCursor);
        return 0;
        }
        ViewProzent();
        }
  return 1;
}

void DialogDIR::treeview_show()
{
	state = chk_path->checkState();
        if (state == Qt::Checked)
           treeView_path->setEnabled(false);
        else 
           treeView_path->setEnabled(true);
}

void DialogDIR::thread1Ready()  {
   QString err_regfile_;
   int anzahl;
   QString text_integer; 
   if (endeThread_ > 0) {
       if (endeThread_ == 10){
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/anzahlfile.txt");
       anzahl  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
       if (anzahl != 0) { 
          text_integer = text_integer.setNum(anzahl);
           }
       AnzahlgesicherteFile ->setText(text_integer);
       bt_end->setEnabled(true);
       bt_save->setEnabled(true);
       progressBar->setValue(100); 
       SekundeRemaining ->setText("0");
       // AnzahlgesicherteFile ->setText(text_integer);
       dummy = datei_auswerten_dir("f"); 
       int cnt_regfile  = dummy.toInt();
       QString cnt_regfile_ = QString::number(cnt_regfile);
       dummy = datei_auswerten_dir("g"); 
       int cnt_dir  = dummy.toInt();
       QString cnt_dir_ = QString::number(cnt_dir); 
       dummy = datei_auswerten_dir("h"); 
       int cnt_symlinks  = dummy.toInt();
       QString cnt_symlinks_ = QString::number(cnt_symlinks);
       dummy = datei_auswerten_dir("i"); 
       int cnt_hardlinks  = dummy.toInt(); 
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       cnt_hardlinks = cnt_hardlinks + cnt_symlinks;
       cnt_hardlinks_ = QString::number(cnt_hardlinks);
       dummy = datei_auswerten_dir("j"); 
       int cnt_special  = dummy.toInt();
       QString cnt_special_;
       cnt_special_ = QString::number(cnt_special);
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The backup of the directory was successful.\n", "Die Sicherung des Verzeichnisses war erfolgreich.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr("  directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr("  links and ", " Links und ") + cnt_special_ + tr(" specials have been backed up.", " spezielle Daten wurden gesichert."));
      }
      else if (flag_end_dir == 1)
      {
         QMessageBox::about(this, tr("Note", "Hinweis"),
         tr("The backup of the folder was aborted by the user!\n", "Die Sicherung des Verzeichnisses wurde vom Benutzer abgebrochen!\n") );
         bt_save->setEnabled(true);
	}
       else
       {
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       dummy = datei_auswerten_dir("a");
       int err_regfile = dummy.toInt();    
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten_dir("b");
       int err_dir = dummy.toInt();  
       QString err_dir_ = QString::number(err_dir); 
       dummy = datei_auswerten_dir("c");
       int err_symlinks = dummy.toInt(); 
       dummy = datei_auswerten_dir("e");
       int err_hardlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten_dir("k"); //err_special
       int err_special = dummy.toInt(); 
       QString err_special_ = QString::number(err_special);
       QMessageBox::about(this,tr("Note", "Hinweis"), 
         err_regfile_ + tr(" Files, ", " Dateien, ")    + err_dir_ 
	+ tr(" directories, and ", " Verzeichnisse und ") + 
         err_hardlinks_ + tr(" Links were not saved correctly. The backup of the directories was only partially successful.\n", " Links wurden nicht korrekt gesichert. Die Sicherung der Verzeichnisse war nur teilweise erfolgreich\n") );
     }
   }
   thread_run_dir = 0; 
   dialog_auswertung = 4;
   bt_save->setEnabled(true);
   bt_end->setEnabled(true);
   progressBar->setValue(0);
   dir_sekunde_summe = 0;
   dir_minute_elapsed = 0;
   dir_sekunde_elapsed = 0;
}

void DialogDIR::thread2Ready()  {
   QString err_regfile_;
   int anzahl;
   QString text_integer; 
   QString dummy;
   dummy = datei_auswerten_dir("f"); //nochmals prüfen
   int meldung  = dummy.toInt();
   if (endeThread_ > 0) {
       if (endeThread_ == 10){
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/anzahlfile.txt");
       anzahl  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
       if (anzahl != 0) { 
          text_integer = text_integer.setNum(anzahl);
           }
       progressBar->setValue(100);
       SekundeRemaining ->setText("0");
       dummy = datei_auswerten_dir("f"); 
       int cnt_regfile  = dummy.toInt();
       QString cnt_regfile_ = QString::number(cnt_regfile);
       dummy = datei_auswerten_dir("g"); 
       int cnt_dir  = dummy.toInt();
       QString cnt_dir_ = QString::number(cnt_dir); 
       dummy = datei_auswerten_dir("h"); 
       int cnt_symlinks  = dummy.toInt();
       QString cnt_symlinks_ = QString::number(cnt_symlinks);
       dummy = datei_auswerten_dir("i"); 
       int cnt_hardlinks  = dummy.toInt(); 
       QString cnt_hardlinks_ = QString::number(cnt_hardlinks);
       cnt_hardlinks = cnt_hardlinks + cnt_symlinks;
       cnt_hardlinks_ = QString::number(cnt_hardlinks);
       dummy = datei_auswerten_dir("j"); 
       int cnt_special  = dummy.toInt();
       QString cnt_special_;
       cnt_special_ = QString::number(cnt_special);
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("The restoring of the directory was successful.\n", "Die Wiederherstellung des Verzeichnisses war erfolgreich.\n") + cnt_regfile_ + 
        tr(" files, ", " Dateien, ") + cnt_dir_ + tr(" directories, ", " Verzeichnisse, ") + cnt_hardlinks_ + tr(" links and ", " Links und ") + cnt_special_ + tr(" special data has been restored.", " spezielle Daten wurden wieder hergestellt."));
        }
   if (flag_end_dir == 1) {
        QMessageBox::about(this, tr("Note", "Hinweis"),
         tr("The restore of the folder was break by user!\n", "Die Wiederherstellung des Verzeichnisses wurde vom Benutzer abgebrochen!\n") );
	     }
   if (endeThread_ == 11) {
       progressBar->setValue(0);
       SekundeRemaining ->setText("0");
       // Anzahl nicht korrekt gesicherte Dateien ausgeben
       dummy = datei_auswerten_dir("a");
       int err_regfile = dummy.toInt();    
       QString err_regfile_ = QString::number(err_regfile);
       dummy = datei_auswerten_dir("b");
       int err_dir = dummy.toInt();  
       QString err_dir_ = QString::number(err_dir); 
       dummy = datei_auswerten_dir("c");
       int err_symlinks = dummy.toInt(); 
       dummy = datei_auswerten_dir("e");
       int err_hardlinks = dummy.toInt();
       err_hardlinks = err_symlinks + dummy.toInt(); 
       QString err_hardlinks_ = QString::number(err_hardlinks); 
       dummy = datei_auswerten_dir("k"); //err_special
       int err_special = dummy.toInt(); 
       QString err_special_ = QString::number(err_special);
       QMessageBox::about(this,tr("Note", "Hinweis"),
         err_regfile_ + tr(" files,", " Dateien, ")    + err_dir_ + 
         tr(" directories, and ", " Verzeichnisse und ") + err_hardlinks_ + 
         tr(" links were not restored correctly. Directory recovery was only partially successful.", " Links wurden nicht korrekt wiederhergestellt. Die Wiederherstellung der Verzeichnisse war nur teilweise erfolgreich\n"));
       }
   if (meldung == 103) { 
        QMessageBox::about(this, tr("Note", "Hinweis"), tr("You have entered an incorrect password.\n", "Sie haben ein falsches Passwort eingegeben.\n"));
      //  werte_uebergeben(100,4);
        endeThread_ = 0;
        lineKey->setText ("");
      }
   if (meldung == 104) {
       QMessageBox::about(this, tr("Note", "Hinweis"), 
       tr("You have tried to restore a directory. The selected file can only restore partitions.\n", "Sie haben versucht ein Verzeichnis wiederherzustellen. Die gewählte Datei kann nur Partitionen wiederherstellen.\n"));
   }
   if (meldung == 106) {
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("Error in fsarchiver. The directory can not be restored!", "Fehler in fsarchiver. Das Verzeichnis kann nicht wiederhergestellt werden!!\n"));
       endeThread_ = 0;
   }
   if (meldung == 107) {
       QMessageBox::about(this, tr("Note", "Hinweis"), tr("Error! The directory was only partially restored.", "Fehler! Das Verzeichnis wurde nur teilweise wiederhergestellt. \n"));
       endeThread_ = 0;
   }
}
   thread_run_dir = 0;
   dialog_auswertung = 5;
   bt_save->setEnabled(true);
   bt_end->setEnabled(true);
   dir_sekunde_summe = 0;
   dir_minute_elapsed = 0;
   dir_sekunde_elapsed = 0;
}

void DialogDIR::elapsedTime()
 {
    dir_sekunde_elapsed = dir_sekunde_elapsed + 1; 
    dir_sekunde_summe = dir_sekunde_summe + 1; 
    if (dir_sekunde_elapsed == 60) {
        dir_sekunde_elapsed = 0 ;
        dir_minute_elapsed = dir_minute_elapsed + 1;
       }
    QString sekunde_ = QString::number(dir_sekunde_elapsed);
    SekundeElapsed ->setText(sekunde_);
    QString minute_ = QString::number(dir_minute_elapsed);
    MinuteElapsed ->setText(minute_);
}

void DialogDIR::remainingTime(int prozent)
 {
    if (prozent <= 1) 
       sekunde_tara_dir  = dir_sekunde_summe ;
    int sekunde_netto = dir_sekunde_summe - sekunde_tara_dir ;
    if (prozent <= 5) {
	SekundeRemaining ->setText(" ");
        MinuteRemaining ->setText(" ");
    }
    if (prozent >= 5) {
       double remaining_time =((100 * sekunde_netto/prozent)- sekunde_netto);
       int dummy = (int)remaining_time;
       int min_remaining = (int)(remaining_time/60);
       QString minute_ = QString::number(min_remaining);
       MinuteRemaining ->setText(minute_);
       int sek_remaining = (dummy % 60); 
       QString sekunde_ = QString::number(sek_remaining);
       SekundeRemaining ->setText(sekunde_);
    }
}

void DialogDIR::indicator_reset() {
// Anzeige zurücksetzen für neuen Aufruf fsarchiver
   //  werte_reset();
     progressBar->setValue(0);
     AnzahlgesicherteFile ->setText(0);
     AnzahlsaveFile ->setText(0); 
     SekundeRemaining ->setText(" ");
     MinuteRemaining ->setText(" ");
     SekundeElapsed ->setText("0");
     MinuteElapsed ->setText("0");
     dir_sekunde_summe = 0;
     dir_minute_elapsed = 0;
     endeThread_ = 0;
     dir_sekunde_elapsed = 0;
     dir_minute_elapsed = 0;
}

void DialogDIR::ViewProzent()
{
QString sekunde;
int sekunde_;
QString minute;
int minute_;
int anzahl;
int anzahl1;
QString text;
QString text_integer;
int flag = 0;
QString dummy;
QString dummy1;
text = datei_auswerten_dir("p");
endeThread_ = text.toInt();
if ((endeThread_ == 10 && flag_View_dir == 1) or (endeThread_ == 11 && flag_View_dir == 1))
   thread1Ready();
if ((endeThread_ == 10 && flag_View_dir == 2) or (endeThread_ == 11 && flag_View_dir == 2))
   thread2Ready();
if (endeThread_ != 10 and endeThread_ != 11)  //noch fejhlerhaft bei 11
{
 timer->singleShot( 1000, this , SLOT(ViewProzent( )) ) ;
  elapsedTime();
  this->repaint();
  dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/meldung.txt"); 
  flag = dummy.toInt();
if (flag_View_dir == 1) // nur bei sichern
	{
 	if (flag == 0)
         {
          dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/anzahl_file.txt"); 
          anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
          if (anzahl != 0){
  	   text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);
           }
 	}
      if (flag == 1)
 	   {
           dummy = dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/anzahl_file.txt"); 
           anzahl  = dummy.toInt(); // anzahl der zu sichernden Dateien
           text_integer = text_integer.setNum(anzahl);
           AnzahlsaveFile ->setText(text_integer);

           dummy = dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/anzahlfile.txt");
           anzahl1  = dummy.toInt(); // anzahl der bereits gesicherten Dateien
           if (anzahl1 != 0) { 
 	   text_integer = text_integer.setNum(anzahl1);
           AnzahlgesicherteFile ->setText(text_integer);
           }
      }     
	}
  dummy = dummy = datei_auswerten_1_dir(userpath_dir + "/.config/qt-fsarchiver/prozent.txt");
  dummy = dummy.left(dummy.size()-1);
  dummy1  = dummy.toInt(); // Prozent
  if (dummy1 > 0){
     prozent_ = dummy.toInt();
}
 if (dummy_prozent_dir != prozent_)
     remainingTime(prozent_);
 else {
        if (prozent_ > 5)
       {
        // Sekunden nach unten zählen
        // SekundenRemaining einlesen
        sekunde = SekundeRemaining->text();
        sekunde_ = sekunde.toInt();
        minute = MinuteRemaining->text();
        minute_ = minute.toInt();
        if (sekunde_ > 0)
        {
            sekunde_ = sekunde_ - 1;
            if (sekunde_ == 0) 
            {
		if (minute_ > 0)
                {		
			minute_ = minute_ - 1;
                	minute = QString::number(minute_); 
        		MinuteRemaining ->setText(minute);
                       	sekunde_ = 59;
                }
	    }
        }		
        sekunde = QString::number(sekunde_); 
        SekundeRemaining ->setText(sekunde);
	    } 
    }   
 dummy_prozent_dir = prozent_;
}
    // bei mehrmaligem Aufruf von fsarchiver wird am Anfang der Sicherung kurzfristig 100 % angezeigt, was falsch ist
     if (prozent_ != 100 && prozent_ > 0) 
     	progressBar->setValue(prozent_);
 return;
} 

int DialogDIR::questionMessage(QString frage)
{
	QMessageBox msg(QMessageBox::Question, tr("Note", "Hinweis"), frage);
	QPushButton* yesButton = msg.addButton(tr("Yes", "Ja"), QMessageBox::YesRole);
	QPushButton* noButton = msg.addButton(tr("No", "Nein"), QMessageBox::NoRole);
	msg.exec();
	if (msg.clickedButton() == yesButton)
    		return 1;
	else if (msg.clickedButton() == noButton)
    		return 2;
return 0;
}

void DialogDIR::chkhidden(){
     Qt::CheckState state;
     state = chk_hidden->checkState();
     filters << "*.fsa";
     if (state != Qt::Checked)
        {
   	dirModel1->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel1->setNameFilters(filters); 
        dirModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
   	dirModel->setNameFilters(filters); 
        }
     if (state == Qt::Checked)
       	{
     	dirModel1->setFilter(QDir::AllDirs  | QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot);
      	dirModel1->setNameFilters(filters); 
       	dirModel->setFilter(QDir::AllDirs | QDir::Hidden | QDir::Files | QDir::NoDotAndDotDot);
       	dirModel->setNameFilters(filters); 
       	}
}

void DialogDIR::zip_einlesen_dir() {
int zip = cmb_zip->currentIndex();
    if (zip == 10) 
       cmb_zstd_dir->setEnabled(true);
    else
       cmb_zstd_dir->setEnabled(false);
}

void DialogDIR::save_attribut_dir(QString attribut)
{
QString dateiname = userpath_dir + "/.config/qt-fsarchiver/attribute.txt";
QFile file(dateiname);
file.open(QIODevice::WriteOnly);
QDataStream out(&file);
out << attribut;
file.close();
}

QString DialogDIR::datei_auswerten_dir(QString buchstabe)
{
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString text;
QString filename = userpath_dir + "/.config/qt-fsarchiver/zahlen.txt";
QFile file(filename);
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream ds(&file);
            text = ds.readLine();
            int pos = text.indexOf(buchstabe);
            if (pos > 0)
      	       dev_sdx_ = text;
      	   else
      	   {    
            while (!ds.atEnd())
      	    {
      	    text = ds.readLine();
            int pos = text.indexOf(buchstabe);
               if (pos > 0)
      	       dev_sdx_ = text;
            }
          } 
       } 
          file.close();
          dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
          //dev_sdx = dev_sdx_.split(QRegExp(" "));
          return dev_sdx[0];
}

QString DialogDIR::datei_auswerten_1_dir(QString dateiname)
{
QStringList dev_sdx;
QString dev_sdx_;
QString devsdx[100][6];
QString text;
QString filename = dateiname;
QFile file(filename);
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream ds(&file);
            text = ds.readLine();
            dev_sdx_ = text;
          }  
          file.close();
          dev_sdx = dev_sdx_.split(QRegExp("\\s+"));
          return dev_sdx[0];
}

void DialogDIR::folder_expand_dir(){
   QModelIndex index = treeView_dir->currentIndex();
   treeView_dir->expand(index);
}
void DialogDIR::folder_expand_path()
   {
   QModelIndex index = treeView_path->currentIndex();
   treeView_path->expand(index);
}






